
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// ----- This header defines: ------
//
// BOOST_ENUM_ADAPT_NAME_VALUE_PAIR(seq)
//     See BOOST_ENUM_DEFINE_NAME_VALUE_PAIR, but seq consists 
//     of tuples used for ADAPT
//
// ----------------------------------


#ifndef BOOST_ENUM_IG_ADAPT_NAME_VALUE_PAIR_HPP
#define BOOST_ENUM_IG_ADAPT_NAME_VALUE_PAIR_HPP

#include <boost/enum/macros/define_name_value_pair.hpp>

#include <boost/preprocessor/variadic/to_tuple.hpp>
#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

//macro to use
#define BOOST_ENUM_ADAPT_NAME_VALUE_PAIR(aseq)								\
	BOOST_PP_CAT(BOOST_ENUM_IADAPT_NAME_VALUE_PAIR_A aseq, _)				\

// ---- Implementation ----
//Sequence unpacking
#define BOOST_ENUM_IADAPT_NAME_VALUE_PAIR_A(...)							\
	BOOST_ENUM_IADAPT_NAME_VALUE_PAIR(__VA_ARGS__)							\
	BOOST_ENUM_IADAPT_NAME_VALUE_PAIR_B										\

#define BOOST_ENUM_IADAPT_NAME_VALUE_PAIR_B(...)							\
	BOOST_ENUM_IADAPT_NAME_VALUE_PAIR(__VA_ARGS__)							\
	BOOST_ENUM_IADAPT_NAME_VALUE_PAIR_A										\

#define BOOST_ENUM_IADAPT_NAME_VALUE_PAIR_A_
#define BOOST_ENUM_IADAPT_NAME_VALUE_PAIR_B_

// ---- Step 1
//Determine behaviour to follow based on the length of the tuple
#define BOOST_ENUM_IADAPT_NAME_VALUE_PAIR(...)								\
	BOOST_PP_CAT(															\
		BOOST_ENUM_IADAPT_NAME_VALUE_PAIR_,									\
		BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)									\
	)(__VA_ARGS__)															\

// ---- Step 2
//If tuple has one element, implementation is equal to IDEFINE_NAME_VALUE_PAIR_1
#define BOOST_ENUM_IADAPT_NAME_VALUE_PAIR_1(...)							\
	BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_1(__VA_ARGS__)						\

//If tuple has two elements, implementation is equal to IDEFINE_NAME_VALUE_PAIR_3
#define BOOST_ENUM_IADAPT_NAME_VALUE_PAIR_2(...)							\
	BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_3(									\
		BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__),								\
		_,																	\
		BOOST_PP_VARIADIC_ELEM(1, __VA_ARGS__)								\
	)																		\

#endif