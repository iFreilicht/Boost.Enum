
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//overload the istream and ostream operators >> and <<

#ifndef BOOST_ENUM_IG_OVERLOAD_STREAM_OPERATORS_HPP
#define BOOST_ENUM_IG_OVERLOAD_STREAM_OPERATORS_HPP

#include <boost/enum/macros/artifacts_namespace.hpp>

#define BOOST_ENUM_OVERLOAD_STREAM_OPERATORS_ADAPT(enum_name, enum_name_e)	\
inline std::istream& operator>>(std::istream& lhs, enum_name& rhs){			\
	std::string str;														\
	lhs >> str;																\
	try{																	\
		rhs = static_cast<enum_name_e>(str);								\
	}																		\
	catch(const std::invalid_argument&){}									\
	return lhs;																\
}																			\
																			\
inline std::ostream& operator<<(std::ostream& lhs, const enum_name& rhs){	\
	return lhs << static_cast<std::string>(static_cast<enum_name_e>(rhs));	\
}																			\

#define BOOST_ENUM_OVERLOAD_STREAM_OPERATORS(enum_name)						\
inline std::istream& operator >>(std::istream& lhs, enum_name& rhs){		\
	std::string str;														\
	lhs >> str;																\
	try{																	\
		rhs = static_cast<enum_name>(str);									\
	}																		\
	catch (const std::invalid_argument&){}									\
	return lhs;																\
}																			\
inline std::ostream& operator <<(std::ostream& lhs, enum_name rhs){			\
	return lhs << static_cast<std::string>(rhs);							\
}																			\

#endif