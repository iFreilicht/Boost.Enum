
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

//evaluates to the first argument of a tuple, followed by a comma

#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/cat.hpp>

//actual implementation
#define BOOST_ADVANCED_ENUM__INAME_COMMA(...)								\
	BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__),									\

//sequence unpacking
#define BOOST_ADVANCED_ENUM__INAME_COMMA_A(...)								\
	BOOST_ADVANCED_ENUM__INAME_COMMA(__VA_ARGS__)							\
		BOOST_ADVANCED_ENUM__INAME_COMMA_B									\

#define BOOST_ADVANCED_ENUM__INAME_COMMA_B(...)								\
	BOOST_ADVANCED_ENUM__INAME_COMMA(__VA_ARGS__)							\
		BOOST_ADVANCED_ENUM__INAME_COMMA_A									\

#define BOOST_ADVANCED_ENUM__INAME_COMMA_A_
#define BOOST_ADVANCED_ENUM__INAME_COMMA_B_

//macro to call
#define BOOST_ADVANCED_ENUM__NAME_COMMA(seq)								\
	BOOST_PP_CAT(BOOST_ADVANCED_ENUM__INAME_COMMA_A seq, _)					\

