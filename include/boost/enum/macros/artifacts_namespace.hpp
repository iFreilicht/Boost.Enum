
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// ----- This header defines: ------
//
// BOOST_ENUM_ARTIFACTS(enum_name)
//     Expands to the name of the artifacts namespace of enum_name
//
// BOOST_ENUM_ENTER_ARTIFACTS_NS(enum_name)
//     Enters the artifacts namespace of enum_name
//
// BOOST_ENUM_EXIT_ARTIFACTS_NS
//     Exits an artifacts namespace
//
// -----------------------------------

#ifndef BOOST_ENUM_IG_ARTIFACTS_NAMESPACE_HPP
#define BOOST_ENUM_IG_ARTIFACTS_NAMESPACE_HPP

#include <boost/preprocessor/cat.hpp>

#define BOOST_ENUM_ARTIFACTS(enum_name)								\
	BOOST_PP_CAT(_artifacts_, enum_name)							\

#define BOOST_ENUM_ENTER_ARTIFACTS_NS(enum_name)					\
	class BOOST_ENUM_ARTIFACTS(enum_name) {							\
		public:														\

#define BOOST_ENUM_EXIT_ARTIFACTS_NS								\
	};																\

#endif