
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_ADVANCEDENUM_HPP
#define BOOST_ADVANCEDENUM_HPP

#include "stdafx.h"
#ifdef __EDG__
#define BOOST_PP_VARIADICS 1
#define BOOST_PP_VARIADICS_MSVC 1
#endif
#include <boost/preprocessor/list.hpp>
#include <boost/preprocessor/seq.hpp>
#include <boost/preprocessor/variadic.hpp>
#include <string>
#include <map>
#include <istream>
#include "enum_storage.hpp"


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
				return EnumStorage::etos(value_);
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
				rhs = static_cast<advanced_enum_base<TemplArgs ...>>(s);
			}
			catch (const std::invalid_argument&) //rhs stays unchanged when an error occurs
			{}
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
		inline std::ostream& operator <<(std::ostream& lhs, advanced_enum_base<TemplArgs ...>& rhs){
			std::string s = static_cast<std::string>(rhs);
			lhs << s;
			return lhs;
		}


		//apply a macro or function to all variadic arguments
#		define BOOST_ADVANCED_ENUM__ID_OP(_, func, elem) func(elem)
#		define BOOST_ADVANCED_ENUM__APPLY_TO_ALL(func, ...)			\
			BOOST_PP_SEQ_FOR_EACH(									\
			BOOST_ADVANCED_ENUM__ID_OP, func,							\
			BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)					\
		)


#		define BOOST_ADVANCED_ENUM__BEGIN_DEFINITION(enum_name)				\
		namespace {																\
			namespace _advanced_enum_artifacts{									\
				namespace enum_name{					\

#		define BOOST_ADVANCED_ENUM__DEFINE_NAME_STRING(name)						\
					char name[] = #name;										\

#		define BOOST_ADVANCED_ENUM__BEGIN_INDEX_DEFINITION(supply, ...)			\
					typedef ::boost::advanced_enum::enum_storage<supply::UnderlyingT, supply::values>::	\
						gen<__VA_ARGS__>::get enum_storage;						\
					enum class index : enum_storage::SizeT{						\

#		define BOOST_ADVANCED_ENUM__DEFINE_INDEX(name)								\
						name,													\

#		define BOOST_ADVANCED_ENUM__BEGIN_VALUES_DEFINITION			\
					};															\
					namespace Values{											\
						enum Values{											\

#		define BOOST_ADVANCED_ENUM__DEFINE_VALUES_VALUE(name)										\
							name = enum_storage::													\
								value_at<static_cast<enum_storage::SizeT>(index::name)>::value,		\

#		define BOOST_ADVANCED_ENUM__BEGIN_ENUM_DEFINITION(enum_name)			\
						};														\
					}															\
					typedef ::boost::advanced_enum::advanced_enum_base			\
						<enum_storage, Values::Values> Base;					\
				}																\
			}																	\
		}																		\
		struct  enum_name : _advanced_enum_artifacts::enum_name::Base {			\

#		define BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(name)						\
			static const ValueT name = ValueT::name;							\

#		define BOOST_ADVANCED_ENUM__END_DEFINITION(enum_name)											\
			enum_name() : _advanced_enum_artifacts::enum_name::Base(){}									\
			enum_name(ValueT v) : _advanced_enum_artifacts::enum_name::Base(v){}						\
			explicit enum_name(UnderlyingT v) : _advanced_enum_artifacts::enum_name::Base(v){}			\
			explicit enum_name(const std::string& s) : _advanced_enum_artifacts::enum_name::Base(s){}	\
		};																								\


		///Forward declare an advanced_enum
#		define BOOST_ADVACNED_ENUM_FWD_DECLARE(enum_name) struct enum_name

		///Define an advanced_enum with a supply
		/**
		\sa #BOOST_ADVANCED_ENUM_DEFINE
		*/
#		define BOOST_ADVANCED_ENUM_DEFINE_W_SUPPLY(enum_name, supply, ...)							\
		BOOST_ADVANCED_ENUM__BEGIN_DEFINITION(enum_name)											\
		BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_NAME_STRING, __VA_ARGS__)		\
		BOOST_ADVANCED_ENUM__BEGIN_INDEX_DEFINITION(supply, __VA_ARGS__)							\
		BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_INDEX, __VA_ARGS__)				\
		BOOST_ADVANCED_ENUM__BEGIN_VALUES_DEFINITION												\
		BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_VALUES_VALUE,__VA_ARGS__)		\
		BOOST_ADVANCED_ENUM__BEGIN_ENUM_DEFINITION(enum_name)										\
		BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE, __VA_ARGS__)		\
		BOOST_ADVANCED_ENUM__END_DEFINITION(enum_name)												\

		///Define an advanced_enum without using a supply, with int increments
		/**This macro is just for convenience when you don't want to manually
		 * specify a supply.
		*/
#		define BOOST_ADVANCED_ENUM_DEFINE(enum_name, ...) BOOST_ADVANCED_ENUM_DEFINE_W_SUPPLY(enum_name, ::boost::advanced_enum::supplies::increment<int>, __VA_ARGS__)

#		define BOOST_ADVANCED_ENUM_ARBITRARY_VALUES(...) ::boost::advanced_enum::supplies::arbitrary<__VA_ARGS__>
	}
}

//uncomment to test 

//Action ultimately expands to this:
namespace example{
	namespace {
		namespace _advanced_enum_artifacts{
			namespace Action{
				char jump[] = "jump";
				char look[] = "look";
				char move[] = "move";
				enum class index{
					jump,
					look,
					move,
				};
				typedef ::boost::advanced_enum::enum_storage<int, ::boost::advanced_enum::supplies::shiftL1<int>::values>::gen<jump, look, move>::get enum_storage;
				namespace Values{
					enum Values{
						jump = enum_storage::value_at<static_cast<int>(index::jump)>::value,
						look = enum_storage::value_at<static_cast<int>(index::look)>::value,
						move = enum_storage::value_at<static_cast<int>(index::move)>::value,
					};
				}
				typedef ::boost::advanced_enum::advanced_enum_base <enum_storage, Values::Values> Base;
			}
		}
	}
	struct Action : _advanced_enum_artifacts::Action::Base {
		static const ValueT jump = ValueT::jump;
		static const ValueT look = ValueT::look;
		static const ValueT move = ValueT::move;
		Action() : _advanced_enum_artifacts::Action::Base(){}
		Action(ValueT v) : _advanced_enum_artifacts::Action::Base(v){}
		explicit Action(int v) : _advanced_enum_artifacts::Action::Base(v){}
		explicit Action(const std::string& s) : _advanced_enum_artifacts::Action::Base(s){}
	};
}

#endif //include guard