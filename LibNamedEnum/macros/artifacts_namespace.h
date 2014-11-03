

#pragma once

#include <boost/preprocessor/cat.hpp>

#define BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)							\
	BOOST_PP_CAT(_artifacts_, enum_name)									\

#define BOOST_ADVANCED_ENUM__ENTER_ARTIFACTS_NS(enum_name)					\
	namespace {																\
		namespace BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name) {				\

#define BOOST_ADVANCED_ENUM__EXIT_ARTIFACTS_NS								\
		}																	\
	}																		\

