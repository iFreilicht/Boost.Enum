
//          Copyright Felix Uhl 2014-2016
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ENUM_IG_NAME_COMMA_HPP
#define BOOST_ENUM_IG_NAME_COMMA_HPP

// ----- This header defines: ------
//
// BOOST_ENUM_NAME_COMMA(seq)
//     Expands to the first argument of every element, divided by commas
//
// ----------------------------------

//evaluates to the first argument of a tuple, followed by a comma
//useful for filling variadic function or template arguments

#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/cat.hpp>


//macro to use
#define BOOST_ENUM_NAME_COMMA(seq)											\
	BOOST_PP_CAT(BOOST_ENUM_INAME_COMMA_A seq, _)							\

// ---- Implementation ----
//sequence unpacking
#define BOOST_ENUM_INAME_COMMA_A(...)										\
	BOOST_ENUM_INAME_COMMA(__VA_ARGS__)										\
		BOOST_ENUM_INAME_COMMA_B											\

#define BOOST_ENUM_INAME_COMMA_B(...)										\
	BOOST_ENUM_INAME_COMMA(__VA_ARGS__)										\
		BOOST_ENUM_INAME_COMMA_A											\

#define BOOST_ENUM_INAME_COMMA_A_
#define BOOST_ENUM_INAME_COMMA_B_

//Get first element of arguments, append comma
#define BOOST_ENUM_INAME_COMMA(...)											\
	BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__),									\


#endif