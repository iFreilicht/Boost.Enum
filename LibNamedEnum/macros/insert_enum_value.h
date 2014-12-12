
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

//evaluates to the first argument of a tuple, followed by a comma

#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/cat.hpp>
#include "cat.h"

//actual implementation
#define BOOST_ADVANCED_ENUM__IINSERT_ENUM_VALUE(...)								\
	static const EnumT BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__) =							\
		EnumT::BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__);								\

//sequence unpacking
#define BOOST_ADVANCED_ENUM__IINSERT_ENUM_VALUE_A(...)								\
	BOOST_ADVANCED_ENUM__IINSERT_ENUM_VALUE(__VA_ARGS__)							\
		BOOST_ADVANCED_ENUM__IINSERT_ENUM_VALUE_B									\

#define BOOST_ADVANCED_ENUM__IINSERT_ENUM_VALUE_B(...)								\
	BOOST_ADVANCED_ENUM__IINSERT_ENUM_VALUE(__VA_ARGS__)							\
		BOOST_ADVANCED_ENUM__IINSERT_ENUM_VALUE_A									\

#define BOOST_ADVANCED_ENUM__IINSERT_ENUM_VALUE_A_
#define BOOST_ADVANCED_ENUM__IINSERT_ENUM_VALUE_B_

//macro to call
#define BOOST_ADVANCED_ENUM__INSERT_ENUM_VALUE(seq)								\
	BOOST_ADVANCED_ENUM_CAT(BOOST_ADVANCED_ENUM__IINSERT_ENUM_VALUE_A seq, _)					\

