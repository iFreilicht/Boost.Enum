
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// ----- This header defines: ------
//
// BOOST_ENUM_OVERLOAD_EQUALITY_OPERATORS(enum_name)
//     Overloads the operators == and != for enum_name.
//
// ----------------------------------

#ifndef BOOST_ENUM_IG_OVERLOAD_EQUALITY_OPERATORS_HPP
#define BOOST_ENUM_IG_OVERLOAD_EQUALITY_OPERATORS_HPP

#define BOOST_ENUM_OVERLOAD_EQUALITY_OPERATORS(enum_name)				\
inline bool operator ==(const enum_name& lhs, const enum_name& rhs)		\
	{ return lhs.value_ == rhs.value_; }								\
inline bool operator !=(const enum_name& lhs, const enum_name& rhs)		\
	{ return !(lhs == rhs); }											\

#endif

