

//define a struct that holds the name and value of an enum value

#pragma once

#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/stringize.hpp>

//implementation
#define BOOST_ADVANCED_ENUM__IDEFINE_NAME_VALUE_PAIR_3(...)					\
    struct BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__){							\
        static const std::string name;										\
        static const EnumT value =											\
			EnumT::BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__);					\
	};																		\
    const std::string BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__)::name =		\
		BOOST_PP_VARIADIC_ELEM(2, __VA_ARGS__);								\


#define BOOST_ADVANCED_ENUM__IDEFINE_NAME_VALUE_PAIR_1(...)					\
	BOOST_ADVANCED_ENUM__IDEFINE_NAME_VALUE_PAIR_3(							\
		BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__),								\
		_,																	\
		BOOST_PP_STRINGIZE(BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__))			\
	)																		\

//The given value in the tuple is ignored
#define BOOST_ADVANCED_ENUM__IDEFINE_NAME_VALUE_PAIR_2(...)					\
	BOOST_ADVANCED_ENUM__IDEFINE_NAME_VALUE_PAIR_1(__VA_ARGS__)				\


#define BOOST_ADVANCED_ENUM__IDEFINE_NAME_VALUE_PAIR(...)					\
	BOOST_PP_CAT(															\
		BOOST_ADVANCED_ENUM__IDEFINE_NAME_VALUE_PAIR_,						\
		BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)									\
	)(__VA_ARGS__)															\

//sequence unpacking
#define BOOST_ADVANCED_ENUM__IDEFINE_NAME_VALUE_PAIR_A(...)					\
	BOOST_ADVANCED_ENUM__IDEFINE_NAME_VALUE_PAIR(__VA_ARGS__)				\
	BOOST_ADVANCED_ENUM__IDEFINE_NAME_VALUE_PAIR_B

#define BOOST_ADVANCED_ENUM__IDEFINE_NAME_VALUE_PAIR_B(...)					\
	BOOST_ADVANCED_ENUM__IDEFINE_NAME_VALUE_PAIR(__VA_ARGS__)				\
	BOOST_ADVANCED_ENUM__IDEFINE_NAME_VALUE_PAIR_A

#define BOOST_ADVANCED_ENUM__IDEFINE_NAME_VALUE_PAIR_A_
#define BOOST_ADVANCED_ENUM__IDEFINE_NAME_VALUE_PAIR_B_

//macro to call
#define BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(seq)					\
	BOOST_PP_CAT(BOOST_ADVANCED_ENUM__IDEFINE_NAME_VALUE_PAIR_A seq, _)		\

