


//defines the value of an enum value, 
//either by using the second argument of a valtup,
//or by using the typedefed 

#pragma once

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/size.hpp>

#include "empty_argument.h"

#define BOOST_ADVANCED_ENUM__GET_SUPPLY_VALUE(enum_name, valtup) \
	::boost::advanced_enum::supplies::at<\
		BOOST_PP_CAT(_artifacts_, enum_name)::UnderlyingT, \
		BOOST_PP_CAT(_artifacts_, enum_name)::supply::values, \
		static_cast<unsigned int>(BOOST_PP_CAT(_artifacts_, enum_name)::index::BOOST_PP_TUPLE_ELEM(0, valtup))\
		>::value

#define BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE_EMPTY_1(enum_name, deftup) \
	BOOST_ADVANCED_ENUM__GET_SUPPLY_VALUE(enum_name, deftup)

#define BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE_EMPTY_0(enum_name, deftup) \
	BOOST_PP_TUPLE_ELEM(0, BOOST_PP_TUPLE_ELEM(1, deftup))

#define BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE_1(enum_name, deftup) \
	BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE_EMPTY_1(enum_name, deftup)

#define BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE_2(enum_name, deftup) \
	BOOST_PP_CAT( \
		BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE_EMPTY_, \
		BOOST_ADVANCED_ENUM_EMPTY_ARG(BOOST_PP_TUPLE_ELEM(1, deftup)) \
	)(enum_name, deftup)

#define BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE_3(enum_name, deftup) \
	BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE_2(enum_name, deftup)

#define BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE(enum_name, deftup) \
	BOOST_PP_CAT( \
		BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE_, \
		BOOST_PP_TUPLE_SIZE(deftup) \
	)(enum_name, deftup)

#define BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(enum_name, deftup) \
	BOOST_PP_TUPLE_ELEM(0, deftup) = BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE(enum_name, deftup),

