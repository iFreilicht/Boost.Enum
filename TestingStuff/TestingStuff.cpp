// TestingStuff.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_PP_VARIADICS 1
#define BOOST_PP_VARIADICS_MSVC 1

#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <macros/empty_argument.h>

#define INAME_COMMA_1(...) BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__), 

#define INAME_COMMA_2(...) \
	BOOST_PP_CAT(INAME_COMMA_2_, \
		BOOST_ADVANCED_ENUM_EMPTY_ARG(\
			BOOST_PP_VARIADIC_ELEM(1, __VA_ARGS__)\
		)\
	)(__VA_ARGS__)

#define INAME_COMMA_2_0(...) \
	BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__) = \
	BOOST_PP_TUPLE_ELEM(0, \
		BOOST_PP_VARIADIC_ELEM(1, __VA_ARGS__)\
	),

#define INAME_COMMA_2_1(...) INAME_COMMA_1(__VA_ARGS__)

#define INAME_COMMA_3(...) INAME_COMMA_2(__VA_ARGS__)

#define INAME_COMMA(...) BOOST_PP_CAT(INAME_COMMA_, BOOST_PP_VARIADIC_SIZE(__VA_ARGS__))(__VA_ARGS__)

#define INAME_COMMA_A(...) INAME_COMMA(__VA_ARGS__) INAME_COMMA_B
#define INAME_COMMA_B(...) INAME_COMMA(__VA_ARGS__) INAME_COMMA_A

#define INAME_COMMA_A_
#define INAME_COMMA_B_

#define INAME_COMMA_I(arg) BOOST_PP_CAT(arg, _)
#define NAME_COMMA(seq) INAME_COMMA_I(INAME_COMMA_A ## seq)

enum class TestE{
	NAME_COMMA((five))
	NAME_COMMA((six, _))
	NAME_COMMA((seven, (7), "S"))
};




int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

