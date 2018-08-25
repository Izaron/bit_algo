/*
  Copyright (c) Evgeny Shulgin <izaronplatz@gmail.com>, 2018

  Distributed under the license described in the LICENSE file
*/

/// \file bits.hpp
/// \brief Provides fast implementations of common bit algorithms.
/// \author Evgeny Shulgin

#ifndef BIT_ALGORITHM_HPP
#define BIT_ALGORITHM_HPP

#include <boost/detail/workaround.hpp>

// Trying to access Microsoft intrinsics
#if (defined(BOOST_MSVC) && (BOOST_MSVC >= 1600)) || (defined(__clang__) && defined(__c2__)) || (defined(BOOST_INTEL) && defined(_MSC_VER)) && (defined(_M_IX86) || defined(_M_X64))
#   define BIT_ALGORITHM_MSVC
#   ifdef _M_X64
#       define BIT_ALGORITHM_MSVC_64
#   endif
// Trying to access GCC intrinsics
#elif defined(BOOST_GCC) || defined(__clang__) || (defined(BOOST_INTEL) && defined(__GNUC__))
#   define BIT_ALGORITHM_GCC
#endif

namespace bit_algo {

}

#endif // BIT_ALGORITHM_HPP
