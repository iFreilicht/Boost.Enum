
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// ----- This header defines: ------
//
// BOOST_ENUM_DEFINE_ENUM_VALUE(seq)
//     Expands to the following for every element of seq:
//          enum_value,
//     where enum_value is either the second argument of the element,
//     or, if that argument is empty, taken from the enumerations supply
//
// ----------------------------------


//defines the value of an enum value, 
//either by using the second argument of a valtup,
//or by using the typedefed 

#ifndef BOOST_ENUM_IG_DEFINE_ENUM_VALUE_HPP
#define BOOST_ENUM_IG_DEFINE_ENUM_VALUE_HPP

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/variadic/size.hpp>

#include <boost/enum/macros/empty_argument.hpp>


//macro to use
#define BOOST_ENUM_DEFINE_ENUM_VALUE(seq)									\
	BOOST_PP_CAT(BOOST_ENUM_IDEFINE_ENUM_VALUE_A seq, _)					\

// ---- Implementation ----
//sequence unpacking
#define BOOST_ENUM_IDEFINE_ENUM_VALUE_A(...)								\
	BOOST_ENUM_IDEFINE_ENUM_VALUE(__VA_ARGS__)								\
	BOOST_ENUM_IDEFINE_ENUM_VALUE_B											\

#define BOOST_ENUM_IDEFINE_ENUM_VALUE_B(...)								\
	BOOST_ENUM_IDEFINE_ENUM_VALUE(__VA_ARGS__)								\
	BOOST_ENUM_IDEFINE_ENUM_VALUE_A											\

#define BOOST_ENUM_IDEFINE_ENUM_VALUE_A_
#define BOOST_ENUM_IDEFINE_ENUM_VALUE_B_

// ---- Step 1
//use the name and start determining the value to use
#define BOOST_ENUM_IDEFINE_ENUM_VALUE(...)									\
	BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__) =								\
		BOOST_ENUM_DETERMINE_ENUM_VALUE(__VA_ARGS__),						\

// ---- Step 2
//Determine what behaviour to follow depending on the length of the tuple
#define BOOST_ENUM_DETERMINE_ENUM_VALUE(...)								\
	BOOST_PP_CAT(															\
		BOOST_ENUM_DETERMINE_ENUM_VALUE_,									\
		BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)									\
	)(__VA_ARGS__)															\

// ---- Step 3
//If the tuple has just one element, the value can't be specified
#define BOOST_ENUM_DETERMINE_ENUM_VALUE_1(...)								\
	BOOST_ENUM_DETERMINE_ENUM_VALUE_EMPTY_1(__VA_ARGS__)					\

//If the tuple has two elements, check whether the second element is empty or not
#define BOOST_ENUM_DETERMINE_ENUM_VALUE_2(...)								\
	BOOST_PP_CAT(															\
		BOOST_ENUM_DETERMINE_ENUM_VALUE_EMPTY_,								\
		BOOST_ENUM_EMPTY_ARG(												\
			BOOST_PP_VARIADIC_ELEM(1, __VA_ARGS__)							\
		)																	\
	)(__VA_ARGS__)															\

//If the tuple has three elements, do the same as if it had two
#define BOOST_ENUM_DETERMINE_ENUM_VALUE_3(...)								\
	BOOST_ENUM_DETERMINE_ENUM_VALUE_2(__VA_ARGS__)							\

// ---- Step 4
//If the value is not specified in the tuple, get the value from the supply
#define BOOST_ENUM_DETERMINE_ENUM_VALUE_EMPTY_1(...)					\
	supply::values<														\
		static_cast<unsigned int>(										\
			index::BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__)				\
		)																\
	>::value															\


//If the value is specified in the tuple, use that
#define BOOST_ENUM_DETERMINE_ENUM_VALUE_EMPTY_0(...)					\
	BOOST_PP_TUPLE_ELEM(0, BOOST_PP_VARIADIC_ELEM(1, __VA_ARGS__))		\



#endif