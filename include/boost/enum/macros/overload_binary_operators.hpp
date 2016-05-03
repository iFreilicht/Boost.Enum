
//          Copyright Felix Uhl 2014-2016
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// ----- This header defines: ------
//
// BOOST_ENUM_OVERLOAD_BINARY_OPERATORS(enum_name)
//     Manually overloads the binary operators for all types that are convertible
//     to enum_name, most importantly EnumT
//     Expands to nothing when constexpr is supported because it's not needed in that case.
//
// ----------------------------------

#ifndef BOOST_ENUM_IG_OVERLOAD_BINARY_OPERATORS_HPP
#define BOOST_ENUM_IG_OVERLOAD_BINARY_OPERATORS_HPP

#include <boost/enum/config/config.hpp>

#ifdef BOOST_NO_CONSTEXPR
#define BOOST_ENUM_OVERLOAD_BINARY_OPERATORS(enum_name)						\
	template<typename ValueT>												\
	typename std::enable_if<std::is_convertible<ValueT, enum_name>::value &&\
		!std::is_same<ValueT, enum_name>::value, enum_name>::type			\
	inline operator&(ValueT lhs, ValueT rhs){								\
		return enum_name(lhs) & enum_name(rhs);								\
		}																	\
	template<typename ValueT>												\
	typename std::enable_if<std::is_convertible<ValueT, enum_name>::value &&\
		!std::is_same<ValueT, enum_name>::value, enum_name>::type			\
	inline operator|(ValueT lhs, ValueT rhs){								\
		return enum_name(lhs) | enum_name(rhs);								\
		}																	\
	template<typename ValueT>												\
	typename std::enable_if<std::is_convertible<ValueT, enum_name>::value &&\
		!std::is_same<ValueT, enum_name>::value, enum_name>::type			\
	inline operator^(ValueT lhs, ValueT rhs){								\
		return enum_name(lhs) ^ enum_name(rhs);								\
		}																	\
	template<typename ValueT>												\
	typename std::enable_if<std::is_convertible<ValueT, enum_name>::value &&\
		!std::is_same<ValueT, enum_name>::value, enum_name>::type			\
	inline operator~(ValueT rhs){											\
		return ~enum_name(rhs);												\
		}																	\



#elif
//The overloading is not necessary as INSERT_ENUM_VALUE will define the
//value constants as static constexpr OwnT, not static const EnumT
#define BOOST_ENUM_OVERLOAD_BINARY_OPERATORS(enum_name)


#endif

#endif