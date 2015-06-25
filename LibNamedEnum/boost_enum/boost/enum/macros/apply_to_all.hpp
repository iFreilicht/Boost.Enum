
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


//===========================================
//===========================================
//============== UNUSED!!! ==================
//===========================================
//===========================================

//apply a macro or function to all variadic arguments

#ifndef BOOST_ENUM_IG_APPLY_TO_ALL_HPP
#define BOOST_ENUM_IG_APPLY_TO_ALL_HPP


#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#define BOOST_ENUM_ID_OP(_, func, elem) func(elem)


#define BOOST_ENUM_APPLY_TO_ALL(func, ...)						\
		BOOST_PP_SEQ_FOR_EACH(												\
		BOOST_ENUM_ID_OP, func,									\
		BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)								\
	)																		\

#define BOOST_ENUM_ID_OP_W_NAME(_, tuple, elem)					\
		BOOST_PP_TUPLE_ELEM(0,tuple)(BOOST_PP_TUPLE_ELEM(1,tuple), elem)	\

#define BOOST_ENUM_APPLY_TO_ALL_W_NAME(enum_name, func, ...)		\
		BOOST_PP_SEQ_FOR_EACH(												\
		BOOST_ENUM_ID_OP_W_NAME, (func, enum_name),				\
		BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)								\
	)																		\

#endif