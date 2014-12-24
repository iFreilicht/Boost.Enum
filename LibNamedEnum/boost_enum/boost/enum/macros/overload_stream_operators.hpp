
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//overload the istream and ostream operators >> and <<

#ifndef BOOST_ENUM_IG_OVERLOAD_STREAM_OPERATORS_HPP
#define BOOST_ENUM_IG_OVERLOAD_STREAM_OPERATORS_HPP

#include <string>
#include <istream>
#include <ostream>

#include <boost/enum/macros/artifacts_namespace.hpp>

#define BOOST_ENUM_FWD_OVERLOAD_STREAM_OPERATORS_W_NAME(enum_name)\
	inline std::istream& operator >>(std::istream& lhs, enum_name& rhs);	\
	inline std::ostream& operator <<(std::ostream& lhs, enum_name rhs);		\
	inline std::string etos(const enum_name& val);							\
	inline void stoe(const std::string& str, enum_name& out);				\

#define BOOST_ENUM_OVERLOAD_STREAM_OPERATORS_W_NAME(enum_name)	\
inline std::istream& operator >>(std::istream& lhs, enum_name& rhs){		\
	BOOST_ENUM_ARTIFACTS(enum_name)::advanced_enum a;				\
	lhs >> a;																\
	rhs = a;																\
	return lhs;																\
}																			\
inline std::ostream& operator <<(std::ostream& lhs, enum_name rhs){			\
	return lhs <<															\
		BOOST_ENUM_ARTIFACTS(enum_name)::advanced_enum(rhs)		\
	;																		\
}																			\
inline std::string etos(const enum_name& val){								\
	return static_cast<std::string>(										\
		BOOST_ENUM_ARTIFACTS(enum_name)::advanced_enum(val)		\
	);																		\
}																			\
inline void stoe(const std::string& str, enum_name& out){					\
	out = static_cast<														\
		BOOST_ENUM_ARTIFACTS(enum_name)::advanced_enum			\
	>(str);																	\
}																			\

#define BOOST_ENUM_OVERLOAD_STREAM_OPERATORS						\
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


#endif