

//overload the istream and ostream operators >> and <<

#pragma once

#include <string>
#include <istream>
#include <ostream>

#include "artifacts_namespace.h"

#define BOOST_ADVANCED_ENUM__FWD_OVERLOAD_STREAM_OPERATORS_W_NAME(enum_name)\
	inline std::istream& operator >>(std::istream& lhs, enum_name& rhs);	\
	inline std::ostream& operator <<(std::ostream& lhs, enum_name rhs);		\
	inline std::string etos(const enum_name& val);							\
	inline void stoe(const std::string& str, enum_name& out);				\

#define BOOST_ADVANCED_ENUM__OVERLOAD_STREAM_OPERATORS_W_NAME(enum_name)	\
inline std::istream& operator >>(std::istream& lhs, enum_name& rhs){		\
	BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::advanced_enum a;				\
	lhs >> a;																\
	rhs = a;																\
	return lhs;																\
}																			\
inline std::ostream& operator <<(std::ostream& lhs, enum_name rhs){			\
	return lhs <<															\
		BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::advanced_enum(rhs)		\
	;																		\
}																			\
inline std::string etos(const enum_name& val){								\
	return static_cast<std::string>(										\
		BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::advanced_enum(val)		\
	);																		\
}																			\
inline void stoe(const std::string& str, enum_name& out){					\
	out = static_cast<														\
		BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::advanced_enum			\
	>(str);																	\
}																			\

#define BOOST_ADVANCED_ENUM__OVERLOAD_STREAM_OPERATORS						\
inline std::istream& operator >>(std::istream& lhs, EnumT& rhs){			\
	advanced_enum a;														\
	lhs >> a;																\
	rhs = a;																\
	return lhs;																\
}																			\
inline std::ostream& operator <<(std::ostream& lhs, EnumT rhs){				\
	return lhs << advanced_enum(rhs);										\
}																			\
inline std::string etos(const EnumT& val){									\
	return static_cast<std::string>(advanced_enum(val));					\
}																			\
inline void stoe(const std::string& str, EnumT& out){						\
	out = static_cast<advanced_enum>(str);									\
}																			\


