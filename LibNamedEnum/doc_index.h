
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


/** \mainpage Boost.Advanced_Enum
 * \tableofcontents
 * \section intro_sec Introduction
 * Advanced_Enum is a header-only library dedicated to extending the functionality of enumeration types,
 * while preserving the natural syntax with which enumerations are used.
 * 
 * As of now, added functionality consists of:
 * * conversions from and to `std::string`
 * * compatibility with iostreams `<<` and `>>` operators
 * * ability to redefine the conventions by which underlying values are selected
 *
 * \section quickstart_sec Quickstart
 * We will only scratch the surface, but this should give you a rough idea what you can do with Advanced_Enums.
 *
 * ##Here you will see how to...
 * ... define an enum with the name `Zott` and the values `zero`, `one`, `two` and `three`:
 * \code
 *     BOOST_ADVANCED_ENUM_DEFINE(Zott,
 *         zero,
 *         one,
 *         two,
 *         three
 *     );
 * \endcode
 * 
 * ... create a variable of type `Zott`:
 * \code
 *     Zott var = Zott::one;
 * \endcode
 *
 * ... convert to a `std::string`:
 * \code
 *     std::string str = static_cast<std::string>(var);
 * \endcode
 *
 * ... read a value of type `Zott` from `std::cin`:
 * \code
 *     std::cin >> var;
 * \endcode
 *
 * ... define an enum with underlying values of 2^0, 2^1, 2^2 and so on of type unsigned int:
 * \code
 *     BOOST_ADVANCED_ENUM_DEFINE_W_SUPPLY(TwoToThePowerOf,
 *         ::boost::advanced_enum::supplies::shiftL1<int>,
 *         zero,
 *         one,
 *         two,
 *         three,
 *         four
 *     );
 * \endcode
 *
*/

