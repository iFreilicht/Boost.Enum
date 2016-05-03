
//          Copyright Felix Uhl 2014-2016
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// ---- This header defines: ----
//
// BOOST_ENUM_DEFINE_FLAG(enum_name, seq)
//     Defines a new enumeration with all options recommended for a bitwise flag enumeration.
//     If you want to change these options, use BOOST_ENUM_DEFINE instead.
//
// BOOST_ENUM_DEFINE_FLAG_IN_CLASS_I(enum_name, seq)
//     Like BOOST_ENUM_DEFINE_FLAG if the new enumeration should be part of a class.
//     Requires BOOST_ENUM_DEFINE_FLAG_IN_CLASS_II to be used after the class definition.
//
// BOOST_ENUM_DEFINE_FLAG_IN_CLASS_II(enum_name)
//     To be used after a class that had BOOST_ENUM_DEFINE_FLAG_IN_CLASS_I used inside it.
//     Has to be used once for each enumeration defined in that class. See also 


#ifndef BOOST_ENUM_IG_DEFINE_FLAG_HPP
#define BOOST_ENUM_IG_DEFINE_FLAG_HPP

#include <boost/enum/define.hpp>
#include <boost/enum/options.hpp>

#define BOOST_ENUM_DEFINE_FLAG_IN_CLASS_I(enum_name, seq)					\
	BOOST_ENUM_DEFINE_IN_CLASS_I_W_OPTIONS(enum_name,						\
		(::boost::enum_::options<::boost::enum_::option_vals::is_flag, unsigned int>),\
		seq																	\
	)																		\

#define BOOST_ENUM_DEFINE_FLAG_IN_CLASS_II(enum_name)						\
	BOOST_ENUM_DEFINE_IN_CLASS_II(enum_name)								\

#define BOOST_ENUM_DEFINE_FLAG(enum_name, seq)								\
	BOOST_ENUM_DEFINE_FLAG_IN_CLASS_I(enum_name, seq)						\
	BOOST_ENUM_DEFINE_FLAG_IN_CLASS_II(enum_name)							\

#endif