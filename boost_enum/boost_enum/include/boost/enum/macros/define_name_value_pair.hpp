
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// ----- This header defines: ------
//
// BOOST_ENUM_DEFINE_ENUM_VALUE(seq)
//     Expands (for every element of seq) to a struct that has a static member function "name()"
//     which returns the name of the enumeration value
//     and a static const member variable "value" which is the value
//     of the enumeration value
//
// ----------------------------------

#ifndef BOOST_ENUM_IG_DEFINE_NAME_VALUE_PAIR_HPP
#define BOOST_ENUM_IG_DEFINE_NAME_VALUE_PAIR_HPP

#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/stringize.hpp>

//macro to use
#define BOOST_ENUM_DEFINE_NAME_VALUE_PAIR(seq)								\
	BOOST_PP_CAT(BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_A seq, _)				\

// ---- Implementation
//sequence unpacking
#define BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_A(...)							\
	BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR(__VA_ARGS__)							\
	BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_B

#define BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_B(...)							\
	BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR(__VA_ARGS__)							\
	BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_A

#define BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_A_
#define BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_B_

// ---- Step 1 
//Determine behaviour to follow depending on the length of the tuple
#define BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR(...)								\
	BOOST_PP_CAT(															\
		BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_,								\
		BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)									\
	)(__VA_ARGS__)															\

// ---- Step 2
//If the tuple has one element, stringize the name
#define BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_1(...)							\
	BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_FINAL(								\
		BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__),								\
		_,																	\
		BOOST_PP_STRINGIZE(BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__))			\
	)																		\

//If the tuple has two elements, stringize the name and ignore the value,
//it is already avaialble through other means
#define BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_2(...)							\
	BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_FINAL(								\
		BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__),								\
		_,																	\
		BOOST_PP_STRINGIZE(BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__))			\
	)																		\


//If the tuple has three elements, use the supplied name
#define BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_3(...)							\
    BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_FINAL(								\
		BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__),								\
		_,																	\
		BOOST_PP_VARIADIC_ELEM(2, __VA_ARGS__)								\
	)																		\

// ---- Step 3
//Define the struct holding name and value of the enumeration value
#define BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_FINAL(name_, _, string)			\
    struct name_{															\
        static const StringT name(){										\
			return string;													\
		}																	\
        static const EnumT value =											\
			EnumT::name_;													\
	};																		\


#endif