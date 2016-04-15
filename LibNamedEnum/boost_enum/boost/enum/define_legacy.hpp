
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// ---- This header defines: ----
//
// BOOST_ENUM_DEFINE_LEGACY(enum_name, seq)
//     Defines a new enumeration with all options needed to be non-breaking from
//     unscoped enumerations
//
// BOOST_ENUM_DEFINE_LEGACY_IN_CLASS_I(enum_name, seq)
//     Like BOOST_ENUM_DEFINE_LEGACY if the new enumeration should be part of a class.
//     Requires BOOST_ENUM_DEFINE_LEGACY_IN_CLASS_II to be used after the class definition.
//
// BOOST_ENUM_DEFINE_LEGACY_IN_CLASS_II(enum_name)
//     To be used after a class that had BOOST_ENUM_DEFINE_LEGACY_IN_CLASS_I used inside it.
//     Has to be used once for each enumeration defined in that class. See also 


#ifndef BOOST_ENUM_IG_DEFINE_LEGACY_HPP
#define BOOST_ENUM_IG_DEFINE_LEGACY_HPP

#include <boost/enum/define.hpp>

#define BOOST_ENUM_DEFINE_LEGACY_IN_CLASS_I(enum_name, dseq)				\
	BOOST_ENUM_DEFINE_IMPL(enum_name, (::boost::enum_::options<>), dseq, 0) \
	
#define BOOST_ENUM_DEFINE_LEGACY_IN_CLASS_II(enum_name)						\
	BOOST_ENUM_DEFINE_IN_CLASS_II(enum_name)								\

#define BOOST_ENUM_DEFINE_LEGACY(enum_name, dseq)							\
	BOOST_ENUM_DEFINE_LEGACY_IN_CLASS_I(enum_name, dseq)					\
	BOOST_ENUM_DEFINE_LEGACY_IN_CLASS_II(enum_name)							\

#endif