
//          Copyright Felix Uhl 2014-2016
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// ----- This header defines: ------
//
// BOOST_ENUM_EMPTY_ARG(a)
//     Expands to 1 if a is an empty tuple, represented by _
//     and to 0 if a is something enclosed by ()
//     The result is not defined for anything else!
//
// ----------------------------------

//the result is 1 for _ and 0 for everything else

#ifndef BOOST_ENUM_IG_EMPTY_ARGUMENT_HPP
#define BOOST_ENUM_IG_EMPTY_ARGUMENT_HPP

#include <boost/preprocessor/cat.hpp>

//macro to use
#define BOOST_ENUM_EMPTY_ARG(a)									\
	BOOST_PP_CAT(BOOST_ENUM_EMPTY_ARG_, a)						\

//argument is _
#define BOOST_ENUM_EMPTY_ARG__ 1

//argument is a tuple, array or list
#define BOOST_ENUM_EMPTY_ARG_(a) 0

#endif