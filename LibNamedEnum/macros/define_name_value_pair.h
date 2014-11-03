

//define a struct that holds the name and value of an enum value

#pragma once

#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/stringize.hpp>


#define BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(deftup)					\
	BOOST_PP_CAT(															\
		BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_,						\
		BOOST_PP_TUPLE_SIZE(deftup)											\
	)(deftup)																\

#define BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_3(deftup)				\
    struct BOOST_PP_TUPLE_ELEM(0, deftup){									\
        static const std::string name;										\
        static const EnumT value = EnumT::BOOST_PP_TUPLE_ELEM(0, deftup);	\
							    };											\
    const std::string BOOST_PP_TUPLE_ELEM(0, deftup)::name =				\
		BOOST_PP_TUPLE_ELEM(2, deftup);										\


#define BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_1(valtup)				\
	BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_3(							\
		(																	\
			BOOST_PP_TUPLE_ELEM(0, valtup),									\
			_,																\
			BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(0, valtup))				\
		)																	\
	)																		\

//The given value in the tuple is ignored
#define BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_2(deftup)				\
	BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_1(deftup)					\

