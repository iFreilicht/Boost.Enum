
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ENUM_IG_DEFINE_FLAG_HPP
#define BOOST_ENUM_IG_DEFINE_FLAG_HPP

#include <boost/enum/define.hpp>

#define BOOST_ENUM_DEFINE_FLAG(enum_name, seq)		\
	BOOST_ENUM_DEFINE_W_OPTIONS(enum_name,			\
		(::boost::enum_::options<::boost::enum_::option_vals::is_flag, unsigned int>),\
		seq\
	)

#endif