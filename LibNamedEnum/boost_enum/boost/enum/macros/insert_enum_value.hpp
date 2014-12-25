
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//evaluates to the first argument of a tuple, followed by a comma


#ifndef BOOST_ENUM_IG_INSERT_ENUM_VALUE_HPP
#define BOOST_ENUM_IG_INSERT_ENUM_VALUE_HPP

#include <boost/enum/config/config.hpp>
#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/enum/macros/cat.hpp>

//actual implementation
#ifdef BOOST_NO_CONSTEXPR
#define BOOST_ENUM_IINSERT_ENUM_VALUE(...)								\
	static const EnumT BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__) =							\
		EnumT::BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__);								\

#else
#define BOOST_ENUM_IINSERT_ENUM_VALUE(...)								\
	static constexpr OwnT BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__) =							\
		EnumT::BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__);								\

#endif

//sequence unpacking
#define BOOST_ENUM_IINSERT_ENUM_VALUE_A(...)								\
	BOOST_ENUM_IINSERT_ENUM_VALUE(__VA_ARGS__)							\
		BOOST_ENUM_IINSERT_ENUM_VALUE_B									\

#define BOOST_ENUM_IINSERT_ENUM_VALUE_B(...)								\
	BOOST_ENUM_IINSERT_ENUM_VALUE(__VA_ARGS__)							\
		BOOST_ENUM_IINSERT_ENUM_VALUE_A									\

#define BOOST_ENUM_IINSERT_ENUM_VALUE_A_
#define BOOST_ENUM_IINSERT_ENUM_VALUE_B_

//macro to call
#define BOOST_ENUM_INSERT_ENUM_VALUE(seq)								\
	BOOST_ENUM_CAT(BOOST_ENUM_IINSERT_ENUM_VALUE_A seq, _)					\



//actual implementation
#define BOOST_ENUM_IDECLARE_ENUM_VALUE(...)								\
	static const EnumT BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__) =							\
		EnumT::BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__);								\

//sequence unpacking
#define BOOST_ENUM_IDECLARE_ENUM_VALUE_A(enum_name, ...)								\
	BOOST_ENUM_IDECLARE_ENUM_VALUE(__VA_ARGS__)							\
		BOOST_ENUM_IDECLARE_ENUM_VALUE_B									\

#define BOOST_ENUM_IDECLARE_ENUM_VALUE_B(...)								\
	BOOST_ENUM_IDECLARE_ENUM_VALUE(__VA_ARGS__)							\
		BOOST_ENUM_IDECLARE_ENUM_VALUE_A									\

#define BOOST_ENUM_IDECLARE_ENUM_VALUE_A_
#define BOOST_ENUM_IDECLARE_ENUM_VALUE_B_

//macro to call
#define BOOST_ENUM_DECLARE_ENUM_VALUE(enum_name, seq)								\
	BOOST_ENUM_CAT(BOOST_ENUM_IDECLARE_ENUM_VALUE_A seq, _)					\

#endif