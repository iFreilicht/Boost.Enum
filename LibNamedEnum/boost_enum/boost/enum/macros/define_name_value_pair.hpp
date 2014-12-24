
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//define a struct that holds the name and value of an enum value

#ifndef BOOST_ENUM_IG_DEFINE_NAME_VALUE_PAIR_HPP
#define BOOST_ENUM_IG_DEFINE_NAME_VALUE_PAIR_HPP

#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/stringize.hpp>

//implementation
#define BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_3(...)					\
    struct BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__){							\
        static const std::string name;										\
        static const EnumT value =											\
			EnumT::BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__);					\
	};																		\
    const std::string BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__)::name =		\
		BOOST_PP_VARIADIC_ELEM(2, __VA_ARGS__);								\


#define BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_1(...)					\
	BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_3(							\
		BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__),								\
		_,																	\
		BOOST_PP_STRINGIZE(BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__))			\
	)																		\

//The given value in the tuple is ignored
#define BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_2(...)					\
	BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_1(__VA_ARGS__)				\


#define BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR(...)					\
	BOOST_PP_CAT(															\
		BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_,						\
		BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)									\
	)(__VA_ARGS__)															\

//sequence unpacking
#define BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_A(...)					\
	BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR(__VA_ARGS__)				\
	BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_B

#define BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_B(...)					\
	BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR(__VA_ARGS__)				\
	BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_A

#define BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_A_
#define BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_B_

//macro to call
#define BOOST_ENUM_DEFINE_NAME_VALUE_PAIR(seq)					\
	BOOST_PP_CAT(BOOST_ENUM_IDEFINE_NAME_VALUE_PAIR_A seq, _)		\

#endif