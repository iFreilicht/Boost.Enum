
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ENUM_IG_FUNCTION_IMPL_HPP
#define BOOST_ENUM_IG_FUNCTION_IMPL_HPP


namespace boost{
	namespace enum_{
		namespace function_impl{
			template<typename Type, bool arbitrary>
			struct UnderlyingToEnumImpl;

			template<typename Type>
			struct UnderlyingToEnumImpl < Type, true > {
			private:
				typedef typename Type::EnumT EnumT;
				typedef typename Type::UnderlyingT UnderlyingT;
			public:
				static inline EnumT f(const UnderlyingT& val){
					return static_cast<EnumT>(val);
				}
			};

			//TODO: change this to disallow arbitrary values
			template<typename Type>
			struct UnderlyingToEnumImpl < Type, false > {
			private:
				typedef typename Type::EnumT EnumT;
				typedef typename Type::UnderlyingT UnderlyingT;
			public:
				static inline EnumT f(const UnderlyingT& val){
					if (Type::has_value(val)){
						return static_cast<EnumT>(val);
					}
					else{
						throw std::invalid_argument(
							"No value in this enum has the underlying value " + 
							std::to_string(val) + 
							" and roundtrip conversion is not allowed!");
					}
				}
			};


			template < typename EnumT, typename UnderlyingT, bool no_ordering >
			class OrderingImpl{
				virtual UnderlyingT get_val_() const = 0;
				virtual void set_val_(UnderlyingT val) = 0;
			};
			
			template < typename EnumT, typename UnderlyingT >
			class OrderingImpl < EnumT, UnderlyingT, false > {
				virtual UnderlyingT get_val_() const = 0;
				virtual void set_val_(UnderlyingT val) = 0;

				inline bool lt(const OrderingImpl& other) const{
					return get_val_() < other.get_val_();
				}
				inline bool gt(const OrderingImpl& other) const{
					return get_val_() > other.get_val_();
				}

				friend bool operator<(const OrderingImpl&, const OrderingImpl&);
				friend bool operator>(const OrderingImpl&, const OrderingImpl&);
			};

			template < typename OrderingImpl >
			bool operator <(const OrderingImpl& lhs, const OrderingImpl& rhs){
				return lhs.lt(rhs);
			}

			template < typename OrderingImpl >
			bool operator >(const OrderingImpl& lhs, const OrderingImpl& rhs){
				return lhs.gt(rhs);
			}

			template < typename OrderingImpl >
			bool operator <=(const OrderingImpl& lhs, const OrderingImpl& rhs){
				return !(lhs > rhs);
			}

			template < typename OrderingImpl >
			bool operator >=(const OrderingImpl& lhs, const OrderingImpl& rhs){
				return !(lhs < rhs);
			}


			template < typename Deriver, typename EnumT, typename UnderlyingT, bool is_flag >
			class BitwiseImpl{
				virtual UnderlyingT get_val_() const = 0;
				virtual void set_val_(UnderlyingT val) = 0;
				virtual Deriver* this_() = 0;
			};

			template < typename Deriver, typename EnumT, typename UnderlyingT >
			class BitwiseImpl < Deriver, EnumT, UnderlyingT, true > {
				virtual UnderlyingT get_val_() const = 0;
				virtual void set_val_(UnderlyingT val) = 0;
				virtual Deriver* this_() = 0;

				inline UnderlyingT and(const Deriver& other) const{
					return get_val_() & ((const BitwiseImpl&)other).get_val_();
				}
				inline UnderlyingT or(const Deriver& other) const{
					return get_val_() | ((const BitwiseImpl&)other).get_val_();
				}
				inline UnderlyingT xor(const Deriver& other) const{
					return get_val_() ^ other.get_val_();
				}
				inline UnderlyingT not() const{
					return ~ get_val_();
				}

			public:
				Deriver& operator &=(const Deriver& other){
					set_val_(and(other));
					return *this_();
				}
				Deriver& operator |=(const Deriver& other){
					set_val_(or(other));
					return *this_();
				}
				Deriver& operator ^=(const Deriver& other){
					set_val_(xor(other));
					return *this_();
				}

				friend Deriver operator &(const Deriver& lhs, const Deriver& rhs){
					Deriver ret = lhs;
					return ret &= rhs;
				}

				friend Deriver operator |(const Deriver& lhs, const Deriver& rhs){
					Deriver ret = lhs;
					return ret |= rhs;
				}

				friend Deriver operator ^(const Deriver& lhs, const Deriver& rhs){
					Deriver ret = lhs;
					return ret ^= rhs;
				}

				friend Deriver operator ~(const Deriver& rhs){
					return static_cast<Deriver>(rhs.not());
				}
			};
		}
	}
}

#endif