
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ENUM_IG_FUNCTION_IMPL_HPP
#define BOOST_ENUM_IG_FUNCTION_IMPL_HPP

namespace boost{
	namespace enum_{

		//All classes in this namespace implement functionality for the enumerations
		//that is dependent on their options.
		namespace function_impl{

			//Implementation for the conversion from UnderlyingT to EnumT
			// Type:
			//     The type of the enumeration
			// arbitrary:
			//     Whether arbitrary values are allowed for this enumeration
			template<typename Type, bool arbitrary>
			struct UnderlyingToEnumImpl;

			//When arbitrary values are allowed, the conversion will always succeed
			template<typename Type>
			struct UnderlyingToEnumImpl < Type, true > {
			private:
				typedef typename Type::EnumT EnumT;
				typedef typename Type::UnderlyingT UnderlyingT;
			public:
				//actual implementation that is to be called
				static inline EnumT f(const UnderlyingT& val){
					return static_cast<EnumT>(val);
				}
			};

			//When only values defined by the enum are allowed, the argument has
			//has to be checked in order for the conversion to be valid.
			//If it isn't, an std::invalid_argument exception is thrown.
			template<typename Type>
			struct UnderlyingToEnumImpl < Type, false > {
			private:
				typedef typename Type::EnumT EnumT;
				typedef typename Type::UnderlyingT UnderlyingT;
			public:
				//actual implementation that is to be called
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

			//Implementation for the ordering of enumeration values
			//The enumeration will inherit from this to make the operators available.
			template < typename EnumT, typename UnderlyingT, bool no_ordering >
			class OrderingImpl{
				virtual UnderlyingT get_val_() const = 0;
				virtual void set_val_(UnderlyingT val) = 0;
			};
			
			//if ordering is supported, the functions accessed by the ordering operators
			//will be defined
			template < typename EnumT, typename UnderlyingT >
			class OrderingImpl < EnumT, UnderlyingT, false > {
				//these functions will be overridden by the enumeration to give access to
				//its internal value to this class
				virtual UnderlyingT get_val_() const = 0;
				virtual void set_val_(UnderlyingT val) = 0;

				//lower than
				inline bool lt(const OrderingImpl& other) const{
					return get_val_() < other.get_val_();
				}

				//greater than
				inline bool gt(const OrderingImpl& other) const{
					return get_val_() > other.get_val_();
				}

				friend bool operator<(const OrderingImpl&, const OrderingImpl&);
				friend bool operator>(const OrderingImpl&, const OrderingImpl&);
			};

			//ordering operators
			//the equal and non-equal operators will always be defined so they don't show up here
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


			//Implementation for bitwise operators
			//The enumeration will inherit from this to make the operators available.
			template < typename Deriver, typename EnumT, typename UnderlyingT, bool is_flag >
			class BitwiseImpl{
				virtual UnderlyingT get_val_() const = 0;
				virtual void set_val_(UnderlyingT val) = 0;
				virtual Deriver* this_() = 0;
			};

			//if bitwise operations are allowed, the functions accessed by the bitwise
			//operators will be defined
			template < typename Deriver, typename EnumT, typename UnderlyingT >
			class BitwiseImpl < Deriver, EnumT, UnderlyingT, true > {
				//these functions will be overridden by the enumeration to give access to
				//the internal value to this class
				virtual UnderlyingT get_val_() const = 0;
				virtual void set_val_(UnderlyingT val) = 0;
				//this function will be overridden by the enumeration to enable returning
				//the *this reference by the bitwise assignment operators
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
				operator bool() const{
					return get_val_() != 0;
				}

				//assignment operators
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

				//operators
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