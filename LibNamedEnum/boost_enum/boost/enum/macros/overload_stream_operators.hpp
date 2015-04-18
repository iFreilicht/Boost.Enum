
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//overload the istream and ostream operators >> and <<

#ifndef BOOST_ENUM_IG_OVERLOAD_STREAM_OPERATORS_HPP
#define BOOST_ENUM_IG_OVERLOAD_STREAM_OPERATORS_HPP

#include <boost/enum/macros/artifacts_namespace.hpp>

#define BOOST_ENUM_OVERLOAD_STREAM_OPERATORS_ADAPT(enum_name, enum_name_e)	\
inline enum_name_e::istream_type&											\
operator>>(enum_name_e::istream_type& lhs, enum_name& rhs){					\
	enum_name_e::StringT str;												\
	lhs >> str;																\
	try{																	\
		rhs = static_cast<enum_name_e>(str);								\
	}																		\
	catch(const std::invalid_argument&){}									\
	return lhs;																\
}																			\
																			\
inline enum_name_e::ostream_type&											\
operator<<(enum_name_e::ostream_type& lhs, const enum_name& rhs){			\
	return lhs << static_cast<enum_name_e::StringT>(						\
		static_cast<enum_name_e>(rhs)										\
	);																		\
}																			\

#define BOOST_ENUM_OVERLOAD_STREAM_OPERATORS(enum_name)						\
inline enum_name::istream_type&												\
operator >>(enum_name::istream_type& lhs, enum_name& rhs){					\
	enum_name::StringT str;													\
	lhs >> str;																\
	try{																	\
		rhs = static_cast<enum_name>(str);									\
	}																		\
	catch (const std::invalid_argument&){}									\
	return lhs;																\
}																			\
inline enum_name::ostream_type&												\
operator <<(enum_name::ostream_type& lhs, enum_name rhs){					\
	return lhs << static_cast<enum_name::StringT>(rhs);						\
}																			\

#endif