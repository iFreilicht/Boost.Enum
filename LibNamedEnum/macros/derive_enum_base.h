




//derive from advanced_enum_base and define operator << and >>

#pragma once

#include <boost/preprocessor/cat.hpp>


#define BOOST_ADVANCED_ENUM__DERIVE_ENUM_BASE								\
struct advanced_enum : Base{												\
	advanced_enum() : Base(){}												\
	advanced_enum(ValueT v) : Base(v){}										\
	explicit advanced_enum(UnderlyingT v) : Base(v){}						\
	explicit advanced_enum(const std::string& s) : Base(s){}				\
};																			\

