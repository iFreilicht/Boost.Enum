
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// ----- This header defines: ------
//
// BOOST_ENUM_OVERLOAD_STREAM_OPERATORS(enum_name)
//     Overloads the stream operators << and >> for enum_name.
// BOOST_ENUM_OVERLOAD_STREAM_OPERATORS_ADAPT(enum_name, enum_name_e)
//     Overloads the stream operators << and >> for enum_name.
//     These will perform conversions to enum_name_e in the process.
//
// ----------------------------------

#ifndef BOOST_ENUM_IG_OVERLOAD_STREAM_OPERATORS_HPP
#define BOOST_ENUM_IG_OVERLOAD_STREAM_OPERATORS_HPP

#include <boost/enum/macros/artifacts_namespace.hpp>
#include <boost/preprocessor/control/iif.hpp>

#define BOOST_ENUM_OVERLOAD_STREAM_OPERATORS_ADAPT(enum_name, enum_name_e)	\
inline enum_name_e::istream_type&											\
operator>>(enum_name_e::istream_type& lhs, enum_name& rhs){					\
	enum_name_e::StringT str;												\
	lhs >> str;																\
	try{																	\
		rhs = static_cast<enum_name_e>(str);								\
	}																		\
	catch(const std::invalid_argument&){									\
		lhs.setstate(std::ios_base::failbit);								\
	}																		\
	return lhs;																\
}																			\
																			\
inline enum_name_e::ostream_type&											\
operator<<(enum_name_e::ostream_type& lhs, const enum_name& rhs){			\
	return lhs << static_cast<enum_name_e::StringT>(						\
		static_cast<enum_name_e>(rhs)										\
	);																		\
}																			\


//if out_int is 1, output the string representation of the underlying
//integral value
//if it is 0, output the stringised name of the enumerator
#define BOOST_ENUM_OVERLOAD_STREAM_OPERATORS(enum_name, out_int)			\
inline enum_name::istream_type&												\
operator >>(enum_name::istream_type& lhs, enum_name& rhs){					\
	enum_name::StringT str;													\
	lhs >> str;																\
	try{																	\
		rhs = static_cast<enum_name>(str);									\
	}																		\
	catch (const std::invalid_argument&){									\
		lhs.setstate(std::ios_base::failbit);								\
	}																		\
	return lhs;																\
}																			\
inline enum_name::ostream_type&												\
operator <<(enum_name::ostream_type& lhs, enum_name rhs){					\
	return lhs << static_cast<												\
		BOOST_PP_IIF(out_int, enum_name::UnderlyingT, enum_name::StringT)	\
	>(rhs);																	\
}																			\

#endif