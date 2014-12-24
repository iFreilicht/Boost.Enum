
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//derive from enum_base and define operator << and >>

#ifndef BOOST_ENUM_IG_DERIVE_ENUM_BASE_HPP
#define BOOST_ENUM_IG_DERIVE_ENUM_BASE_HPP

#include <boost/preprocessor/cat.hpp>


#define BOOST_ENUM_DERIVE_ENUM_BASE								\
struct advanced_enum : Base{												\
	advanced_enum() : Base(){}												\
	advanced_enum(ValueT v) : Base(v){}										\
	explicit advanced_enum(UnderlyingT v) : Base(v){}						\
	explicit advanced_enum(const std::string& s) : Base(s){}				\
};																			\

#endif