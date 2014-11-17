
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_ADVANCEDENUM_HPP
#define BOOST_ADVANCEDENUM_HPP

#include <boost/preprocessor/list.hpp>
#include <boost/preprocessor/seq.hpp>
#include <boost/preprocessor/variadic.hpp>
#include <string>
#include <map>
#include <istream>


namespace boost{
	namespace advanced_enum{

		///Base class for all advanced enumerations
		/**
		
		*/
		template<typename EnumStorage, typename ValueT>
		class advanced_enum_base{
		public:
			typedef typename ValueT ValueT; /*!Makes ValueT publicly available*/
			typedef typename EnumStorage EnumStorage; /*!Makes EnumStorage publicly available*/
			typedef typename EnumStorage::UnderlyingT UnderlyingT; /*!The underlying integral type*/
		private:
			ValueT value_; //real enumeration, containing all values for this advanced_enum
		public:
			//-----construction and assignment-------
			///Constructor that doesn't set any value
			/**
			 * \warning If an enum is constructed like this, the value of it is undefined!
			*/
			advanced_enum_base(){}
			///Construct from ValueT
			advanced_enum_base(ValueT value) :
				value_(value)
			{}
			//convert to ValueT implicitly
			operator ValueT() const{
				return value_;
			}

			///Copy assignment
			advanced_enum_base& operator=(const advanced_enum_base& rhs){
				value_ = rhs.value_;
				return *this;
			}

			///Assignment from ValueT
			advanced_enum_base& operator=(ValueT rhs){
				value_ = rhs;
				return *this;
			}

			//---------------conversion---------------
			///Initliaise lookup maps
			/**
			 * This is not necessary for conversion, but it can speed up conversion significantly
			 * if the enumeration has a lot of values or a lot of conversions are executed.
			*/
			static void init_lookupmaps(){
				EnumStorage::init_lookupmaps();
			}

			///Convert from UnderlyingT explicitly
			explicit advanced_enum_base(UnderlyingT value) :
				value_(static_cast<ValueT>(value))
			{}
			///Convert from std::string explicitly
			explicit advanced_enum_base(const std::string& name) :
				value_(static_cast<ValueT>(EnumStorage::stoe(name)))
			{}

			///Convert to UnderlyingT explicitly
			explicit operator UnderlyingT() const{
				return static_cast<UnderlyingT>(value_);
			}
			///Convert to std::string explicitly
			explicit operator std::string() const{
				return EnumStorage::etos(static_cast<UnderlyingT>(value_));
			}

			//------------comparison---------------
			bool operator ==(const advanced_enum_base& other) const{
				return value_ == other.value_;
			}

			bool operator !=(const advanced_enum_base& other) const{
				return value_ != other.value_;
			}

			bool operator >=(const advanced_enum_base& other) const{
				return value_ >= other.value_;
			}

			bool operator <=(const advanced_enum_base& other) const{
				return value_ <= other.value_;
			}

			bool operator >(const advanced_enum_base& other) const{
				return value_ > other.value_;
			}

			bool operator <(const advanced_enum_base& other) const{
				return value_ < other.value_;
			}

		};

		///Overloading of input operator >>
		/**\warning In contrast to normal enums, advanced_enums will be
		 * initialised from a string, not from an integer!
		 *
		 * If you want to assign an int value via operator >>, assign to an int
		 * first, then convert to the advanced_enum explicitly!
		*/
		template<typename ... TemplArgs>
		std::istream& operator >>(std::istream& lhs, advanced_enum_base<TemplArgs ...>& rhs){
			std::string s;
			lhs >> s;
			try{
				rhs = static_cast<advanced_enum_base<TemplArgs ...> >(s);
			}
			catch (const std::invalid_argument&){}
			return lhs;
		}

		//Overloading of output operator <<
		/**\warning In contrast to normal enums, advanced_enums will be output
		 * as a string, not as an integer!
		 *
		 * If you want to output an int value, use this syntax:
		 * \code
		 *     std::cout << static_cast<int>(myEnum);
		 * \endcode
		*/
		template<typename ... TemplArgs>
		inline std::ostream& operator <<(std::ostream& lhs, const advanced_enum_base<TemplArgs ...>& rhs){
			return lhs << static_cast<std::string>(rhs);
		}

	}
}

#endif //include guard