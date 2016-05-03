
//          Copyright Felix Uhl 2014-2016
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)




// ----- This header defines: ------
//
// BOOST_ENUM_INSERT_ENUM_VALUE(enum_name, seq)
//    Evaluates to (for every element in the sequence):
//        static const EnumT name = EnumT::name;
//    Where:
//         enum_name: Name of enumeration, not used
//         seq: Sequence, only first element is used
//         name: the name of the enumeration value
//
// -----------------------------------


#ifndef BOOST_ENUM_IG_INSERT_ENUM_VALUE_HPP
#define BOOST_ENUM_IG_INSERT_ENUM_VALUE_HPP

#include <boost/enum/config/config.hpp>
#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>

//macro to use
#define BOOST_ENUM_INSERT_ENUM_VALUE(seq)									\
	BOOST_PP_CAT(BOOST_ENUM_IINSERT_ENUM_VALUE_A seq, _)					\

// ---- Implementation ----
//sequence unpacking
#define BOOST_ENUM_IINSERT_ENUM_VALUE_A(...)								\
	BOOST_ENUM_IINSERT_ENUM_VALUE(__VA_ARGS__)								\
		BOOST_ENUM_IINSERT_ENUM_VALUE_B										\

#define BOOST_ENUM_IINSERT_ENUM_VALUE_B(...)								\
	BOOST_ENUM_IINSERT_ENUM_VALUE(__VA_ARGS__)								\
		BOOST_ENUM_IINSERT_ENUM_VALUE_A										\

#define BOOST_ENUM_IINSERT_ENUM_VALUE_A_
#define BOOST_ENUM_IINSERT_ENUM_VALUE_B_

//IntelliSense is not able to find any values in EnumT, so if it is active,
//a dummy value needs to be used instead.
#if defined BOOST_ENUM_DISABLE_INTELLISENSE_WORKAROUND || !defined __INTELLISENSE__
#define BOOST_ENUM_USE_DUMMY_VALUE 0
#else
#define BOOST_ENUM_USE_DUMMY_VALUE 1
#endif

#if defined BOOST_NO_CONSTEXPR
#define BOOST_ENUM_INSERT_CONSTEXPR static const EnumT
#else
#define BOOST_ENUM_INSERT_CONSTEXPR static constexpr OwnT
#endif

//Define the enumeration value constant.
//If constexpr is available, the constant will be of type OwnT, or the actual type of the enumeration.
//If constexpr is not avialable, the constant will be of type EnumT. This means that the operators
//have to be overloaded manually for all combonations of EnumT and OwnT, resulting in worse compiling performance.
#define BOOST_ENUM_IINSERT_ENUM_VALUE(...)									\
	BOOST_ENUM_INSERT_CONSTEXPR BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__) =				\
		BOOST_PP_IIF(BOOST_ENUM_USE_DUMMY_VALUE,							\
			(EnumT)0, EnumT::BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__)			\
		);																	\

#endif