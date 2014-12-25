
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/*Using this concatenation macro is necessary in some scenarios 
where subsequent expansions of BOOST_PP_CAT are not executed!*/

#ifndef BOOST_ENUM_IG_CAT_HPP
#define BOOST_ENUM_IG_CAT_HPP

#define BOOST_ENUM_CAT(a, b) BOOST_ENUM_CAT_I(a, b)
#define BOOST_ENUM_CAT_I(a, b) BOOST_ENUM_CAT_II(a, b)
#define BOOST_ENUM_CAT_II(a, b) a ## b

#endif