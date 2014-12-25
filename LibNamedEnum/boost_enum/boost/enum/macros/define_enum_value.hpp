
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

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

#define BOOST_ENUM_GET_SUPPLY_VALUE(...)							\
		supply::values<														\
			static_cast<unsigned int>(										\
				index::BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__)				\
			)																\
		>::value															\

#define BOOST_ENUM_DETERMINE_ENUM_VALUE_EMPTY_1(...)				\
	BOOST_ENUM_GET_SUPPLY_VALUE(__VA_ARGS__)						\

#define BOOST_ENUM_DETERMINE_ENUM_VALUE_EMPTY_0(...)				\
	BOOST_PP_TUPLE_ELEM(0, BOOST_PP_VARIADIC_ELEM(1, __VA_ARGS__))			\

#define BOOST_ENUM_DETERMINE_ENUM_VALUE_1(...)					\
	BOOST_ENUM_DETERMINE_ENUM_VALUE_EMPTY_1(__VA_ARGS__)			\

#define BOOST_ENUM_DETERMINE_ENUM_VALUE_2(...)					\
	BOOST_PP_CAT(															\
		BOOST_ENUM_DETERMINE_ENUM_VALUE_EMPTY_,					\
		BOOST_ENUM_EMPTY_ARG(										\
			BOOST_PP_VARIADIC_ELEM(1, __VA_ARGS__)							\
		)																	\
	)(__VA_ARGS__)															\

#define BOOST_ENUM_DETERMINE_ENUM_VALUE_3(...)					\
	BOOST_ENUM_DETERMINE_ENUM_VALUE_2(__VA_ARGS__)				\

#define BOOST_ENUM_DETERMINE_ENUM_VALUE(...)						\
	BOOST_PP_CAT(															\
		BOOST_ENUM_DETERMINE_ENUM_VALUE_,							\
		BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)									\
	)(__VA_ARGS__)															\

#define BOOST_ENUM_IDEFINE_ENUM_VALUE(...)						\
	BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__) =								\
		BOOST_ENUM_DETERMINE_ENUM_VALUE(__VA_ARGS__),				\

//sequence unpacking
#define BOOST_ENUM_IDEFINE_ENUM_VALUE_A(...)						\
	BOOST_ENUM_IDEFINE_ENUM_VALUE(__VA_ARGS__)					\
	BOOST_ENUM_IDEFINE_ENUM_VALUE_B								\

#define BOOST_ENUM_IDEFINE_ENUM_VALUE_B(...)						\
	BOOST_ENUM_IDEFINE_ENUM_VALUE(__VA_ARGS__)					\
	BOOST_ENUM_IDEFINE_ENUM_VALUE_A								\

#define BOOST_ENUM_IDEFINE_ENUM_VALUE_A_
#define BOOST_ENUM_IDEFINE_ENUM_VALUE_B_


//macro to use
#define BOOST_ENUM_DEFINE_ENUM_VALUE(seq)							\
	BOOST_PP_CAT(BOOST_ENUM_IDEFINE_ENUM_VALUE_A seq, _)			\

#endif