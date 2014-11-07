
//do the same as define_name_value_pair, but use an adatup

#pragma once

#include "define_name_value_pair.h"

#include <boost/preprocessor/variadic/to_tuple.hpp>
#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

//actual implementation
#define BOOST_ADVANCED_ENUM__IADAPT_NAME_VALUE_PAIR_1(...)					\
	BOOST_ADVANCED_ENUM__IDEFINE_NAME_VALUE_PAIR_1(__VA_ARGS__)				\

#define BOOST_ADVANCED_ENUM__IADAPT_NAME_VALUE_PAIR_2(...)					\
	BOOST_ADVANCED_ENUM__IDEFINE_NAME_VALUE_PAIR_3(							\
		BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__),								\
		_,																	\
		BOOST_PP_VARIADIC_ELEM(1, __VA_ARGS__)								\
	)																		\

#define BOOST_ADVANCED_ENUM__IADAPT_NAME_VALUE_PAIR(...)					\
	BOOST_PP_CAT(															\
		BOOST_ADVANCED_ENUM__IADAPT_NAME_VALUE_PAIR_,						\
		BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)									\
	)(__VA_ARGS__)															\

//sequence unpacking
#define BOOST_ADVANCED_ENUM__IADAPT_NAME_VALUE_PAIR_A(...)					\
	BOOST_ADVANCED_ENUM__IADAPT_NAME_VALUE_PAIR(__VA_ARGS__)				\
	BOOST_ADVANCED_ENUM__IADAPT_NAME_VALUE_PAIR_B							\

#define BOOST_ADVANCED_ENUM__IADAPT_NAME_VALUE_PAIR_B(...)					\
	BOOST_ADVANCED_ENUM__IADAPT_NAME_VALUE_PAIR(__VA_ARGS__)				\
	BOOST_ADVANCED_ENUM__IADAPT_NAME_VALUE_PAIR_A							\

#define BOOST_ADVANCED_ENUM__IADAPT_NAME_VALUE_PAIR_A_
#define BOOST_ADVANCED_ENUM__IADAPT_NAME_VALUE_PAIR_B_

//macro to use
#define BOOST_ADVANCED_ENUM__ADAPT_NAME_VALUE_PAIR(seq)						\
	BOOST_PP_CAT(BOOST_ADVANCED_ENUM__IADAPT_NAME_VALUE_PAIR_A seq, _)		\