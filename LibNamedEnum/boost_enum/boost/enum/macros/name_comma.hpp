
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ENUM_IG_NAME_COMMA_HPP
#define BOOST_ENUM_IG_NAME_COMMA_HPP

//evaluates to the first argument of a tuple, followed by a comma

#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/enum/macros/cat.hpp>

//actual implementation
#define BOOST_ENUM_INAME_COMMA(...)								\
	BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__),									\

//sequence unpacking
#define BOOST_ENUM_INAME_COMMA_A(...)								\
	BOOST_ENUM_INAME_COMMA(__VA_ARGS__)							\
		BOOST_ENUM_INAME_COMMA_B									\

#define BOOST_ENUM_INAME_COMMA_B(...)								\
	BOOST_ENUM_INAME_COMMA(__VA_ARGS__)							\
		BOOST_ENUM_INAME_COMMA_A									\

#define BOOST_ENUM_INAME_COMMA_A_
#define BOOST_ENUM_INAME_COMMA_B_

//macro to call
#define BOOST_ENUM_NAME_COMMA(seq)								\
	BOOST_ENUM_CAT(BOOST_ENUM_INAME_COMMA_A seq, _)					\

#endif