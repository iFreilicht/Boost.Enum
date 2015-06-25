
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// ----- This header defines: ------
//
// BOOST_ENUM_CAT(a, b)
//     Concatenates a and b, with equivalent behaviour to Boost.PPs BOOST_PP_CAT macro
//     NOTE: This has to be used in some cases where 
//     subsequent expansions of BOOST_PP_CAT are not executed!
//
// ----------------------------------


#ifndef BOOST_ENUM_IG_CAT_HPP
#define BOOST_ENUM_IG_CAT_HPP

//macro to use
#define BOOST_ENUM_CAT(a, b) BOOST_ENUM_CAT_I(a, b)

// ---- Implementation ----
// ---- Step 1: expand arguments 
#define BOOST_ENUM_CAT_I(a, b) BOOST_ENUM_CAT_II(a, b)
// ---- Step 2: concatenate arguments
#define BOOST_ENUM_CAT_II(a, b) a ## b

#endif