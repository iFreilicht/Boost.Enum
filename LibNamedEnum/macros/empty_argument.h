
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//Checks wether the argument is _ or not.
//WARNING! currently the result is only defined for _ and Boost.PP data types

//the result is 1 for _ and 0 for everything else
#pragma once

#include <boost/preprocessor/cat.hpp>

#define BOOST_ADVANCED_ENUM_EMPTY_ARG(a)									\
	BOOST_PP_CAT(BOOST_ADVANCED_ENUM__EMPTY_ARG_, a)						\

//argument is _
#define BOOST_ADVANCED_ENUM__EMPTY_ARG__ 1

//argument is a tuple, array or list
#define BOOST_ADVANCED_ENUM__EMPTY_ARG_(a) 0

