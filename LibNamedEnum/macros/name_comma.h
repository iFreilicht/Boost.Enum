
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

//evaluates to the first argument of a tuple, followed by a comma

#include <boost/preprocessor/tuple/elem.hpp>

#define BOOST_ADVANCED_ENUM__NAME_COMMA(valtup) \
	BOOST_PP_TUPLE_ELEM(0, valtup),	\

