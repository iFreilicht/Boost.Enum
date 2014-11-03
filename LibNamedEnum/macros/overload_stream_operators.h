

//overload the istream and ostream operators >> and <<

#pragma once

#include <string>
#include <istream>
#include <ostream>

#include "artifacts_namespace.h"

#define BOOST_ADVANCED_ENUM__OVERLOAD_STREAM_OPERATORS(enum_name)			\
inline std::istream& operator >>(std::istream& lhs, enum_name& rhs){		\
	std::string s;															\
	lhs >> s;																\
	try{																	\
		rhs = static_cast<													\
			BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::advanced_enum		\
		>(s);																\
		}																	\
	catch (const std::invalid_argument&){}									\
	return lhs;																\
}																			\
inline std::ostream& operator <<(std::ostream& lhs, enum_name rhs){			\
	return lhs << static_cast<std::string>(									\
		(BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::advanced_enum) rhs		\
	);																		\
}																			\

