
//do the same as define_name_value_pair, but use an adatup

#pragma once

#include "define_name_value_pair.h"

#define BOOST_ADVANCED_ENUM__ADAPT_NAME_VALUE_PAIR_1(adatup) \
	BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_1(adatup)

#define BOOST_ADVANCED_ENUM__ADAPT_NAME_VALUE_PAIR_2(adatup) \
	BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_3( \
		( \
			BOOST_PP_TUPLE_ELEM(0, adatup), \
			_, \
			BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(1, adatup))\
		)\
	)

#define BOOST_ADVANCED_ENUM__ADAPT_NAME_VALUE_PAIR(adatup) \
	BOOST_PP_CAT( \
		BOOST_ADVANCED_ENUM__ADAPT_NAME_VALUE_PAIR_, \
		BOOST_PP_TUPLE_SIZE(adatup) \
	)(adatup)

