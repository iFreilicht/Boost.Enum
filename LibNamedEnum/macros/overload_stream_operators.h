

//overload the istream and ostream operators >> and <<

#pragma once

#include <string>
#include <istream>
#include <ostream>

#include "artifacts_namespace.h"

#define BOOST_ADVANCED_ENUM__OVERLOAD_STREAM_OPERATORS_W_NAME(enum_name)	\
inline std::istream& operator >>(std::istream& lhs, enum_name& rhs){		\
	BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::advanced_enum a;				\
	lhs >> a;																\
	rhs = a;																\
	return lhs;																\
}																			\
inline std::ostream& operator <<(std::ostream& lhs, enum_name rhs){			\
	return lhs <<															\
		(BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::advanced_enum) rhs		\
	;																		\
}																			\


#define BOOST_ADVANCED_ENUM__OVERLOAD_STREAM_OPERATORS						\
inline std::istream& operator >>(std::istream& lhs, EnumT& rhs){			\
	advanced_enum a;														\
	lhs >> a;																\
	rhs = a;																\
	return lhs;																\
}																			\
inline std::ostream& operator <<(std::ostream& lhs, EnumT rhs){				\
	return lhs << (advanced_enum) rhs;										\
}																			\


