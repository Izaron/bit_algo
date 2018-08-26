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

// Trying to access Microsoft Visual C++ intrinsics
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

/// \fn bit_count ( IntType value )
/// \return Number of bits set to 1 in value of an integral type
///
/// \param value    The value to get its bit count
///
/// \note This function works regardless of the value sign.
///     Complexity: O(N).
template <typename T>
BOOST_FORCEINLINE typename std::enable_if<std::is_integral<T>::value, int>::type
bit_count(T value) BOOST_NOEXCEPT
{
    int res = 0;
    while (value)
    {
        res += value & 1;
        value >>= 1;
    }
    return res;
}

#if defined(BIT_ALGORITHM_MSVC)

// Using __popcnt variations
template<>
BOOST_FORCEINLINE int bit_count(unsigned short value) BOOST_NOEXCEPT
{
    return static_cast<int>(__popcnt16(value));
}

template<>
BOOST_FORCEINLINE int bit_count(unsigned int value) BOOST_NOEXCEPT
{
    return static_cast<int>(__popcnt(value));
}

#if defined(BIT_ALGORITHM_MSVC_64)

template<>
BOOST_FORCEINLINE int bit_count(unsigned __int64 value) BOOST_NOEXCEPT
{
    return static_cast<int>(__popcnt64(value));
}

// Casting signed args to unsigned
template<>
BOOST_FORCEINLINE int bit_count(__int64 value) BOOST_NOEXCEPT
{
    return static_cast<unsigned __int64>(bit_count(value));
}

#else // !defined(BIT_ALGORITHM_MSVC_64)

// Win32 doesn't have __popcnt64, emulate it with two 32 bit calls
template<>
BOOST_FORCEINLINE int bit_count(unsigned long long value) BOOST_NOEXCEPT
{
    return bit_count(static_cast<unsigned int>(value >> 32)) +
        bit_count(static_cast<unsigned int>(value)); // cuts out leading 32 bits
}

// Casting signed args to unsigned
template<>
BOOST_FORCEINLINE int bit_count(long long value) BOOST_NOEXCEPT
{
    return static_cast<unsigned long long>(bit_count(value));
}

#endif

// Casting signed args to unsigned
template<>
BOOST_FORCEINLINE int bit_count(short value) BOOST_NOEXCEPT
{
    return bit_count(static_cast<unsigned short>(value));
}

template<>
BOOST_FORCEINLINE int bit_count(int value) BOOST_NOEXCEPT
{
    return bit_count(static_cast<unsigned int>(value));
}

#elif defined(BIT_ALGORITHM_GCC)

// Using __builtin_popcount variations
template<>
BOOST_FORCEINLINE int bit_count(unsigned int value) BOOST_NOEXCEPT
{
    return __builtin_popcount(value);
}

template<>
BOOST_FORCEINLINE int bit_count(unsigned long value) BOOST_NOEXCEPT
{
    return __builtin_popcountl(value);
}

template<>
BOOST_FORCEINLINE int bit_count(unsigned long long value) BOOST_NOEXCEPT
{
    return __builtin_popcountll(value);
}

// Casting signed args to unsigned
template<>
BOOST_FORCEINLINE int bit_count(int value) BOOST_NOEXCEPT
{
    return bit_count(static_cast<unsigned int>(value));
}

template<>
BOOST_FORCEINLINE int bit_count(long value) BOOST_NOEXCEPT
{
    return bit_count(static_cast<unsigned long>(value));
}

template<>
BOOST_FORCEINLINE int bit_count(long long value) BOOST_NOEXCEPT
{
    return bit_count(static_cast<unsigned long long>(value));
}

#endif // BIT_ALGORITHM_GCC

}

#endif // BIT_ALGORITHM_HPP
