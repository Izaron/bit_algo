/*
  Copyright (c) Evgeny Shulgin <izaronplatz@gmail.com>, 2018

  Distributed under the license described in the LICENSE file
*/

/// \file bits.hpp
/// \brief Provides fast implementations of common bit algorithms.
/// \author Evgeny Shulgin

#ifndef BIT_ALGORITHM_HPP
#define BIT_ALGORITHM_HPP

#include <iostream>

#include <boost/detail/workaround.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/utility/enable_if.hpp>

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

// Define specifiers for all functions
// Firstly, it defines a function 'constexpr' if possible
// Although 'constexpr' implies 'inline', we still define forced inlining
#define BIT_ALGORITHM_FUNC_SPEC BOOST_CONSTEXPR BOOST_FORCEINLINE

namespace bit_algo {

namespace impl {

typedef unsigned char byte_type;
const unsigned int table_width = 8;

// ------- bit_count function implementation --------------

template <bool dummy_name = true>
struct count_table { static const byte_type table[]; };

template <>
struct count_table<false> { /* no table */ };

template <bool b>
const byte_type count_table<b>::table[] =
{
    // Automatically generated bit_count values for [0; 255]
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
};


// ------- first_set function implementation --------------

template <bool dummy_name = true>
struct first_set_table { static const byte_type table[]; };

template <>
struct first_set_table<false> { /* no table */ };

template <bool b>
const byte_type first_set_table<b>::table[] =
{
    // Automatically generated first_set values for [0; 255]
    0, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1, 5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1, 5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    7, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1, 5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1, 5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    8, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1, 5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1, 5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    7, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1, 5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1, 5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1
};

}

/// \fn bit_count ( IntType value )
/// \return Number of bits set to 1 in value of an integral type
///
/// \param value    The value to get its bit count
///
/// \note This function works regardless of the value sign.
template <typename T>
BIT_ALGORITHM_FUNC_SPEC typename boost::enable_if<
    boost::is_integral<T>, int
>::type bit_count(T value)
{
    int res = 0;
    while (value)
    {
        res += impl::count_table<true>
            ::table[value & ((1u << impl::table_width) - 1)];
        value >>= impl::table_width;
    }
    return res;
}

#if defined(BIT_ALGORITHM_MSVC)

// Using __popcnt variations
template<>
BIT_ALGORITHM_FUNC_SPEC int bit_count(unsigned short value)
{
    return static_cast<int>(__popcnt16(value));
}

template<>
BIT_ALGORITHM_FUNC_SPEC int bit_count(unsigned int value)
{
    return static_cast<int>(__popcnt(value));
}

#if defined(BIT_ALGORITHM_MSVC_64)

template<>
BIT_ALGORITHM_FUNC_SPEC int bit_count(unsigned __int64 value)
{
    return static_cast<int>(__popcnt64(value));
}

// Casting signed args to unsigned
template<>
BIT_ALGORITHM_FUNC_SPEC int bit_count(__int64 value)
{
    return static_cast<unsigned __int64>(bit_count(value));
}

#else // !defined(BIT_ALGORITHM_MSVC_64)

// Win32 doesn't have __popcnt64, emulate it with two 32 bit calls
template<>
BIT_ALGORITHM_FUNC_SPEC int bit_count(unsigned long long value)
{
    return bit_count(static_cast<unsigned int>(value >> 32)) +
        bit_count(static_cast<unsigned int>(value)); // cuts out leading 32 bits
}

// Casting signed args to unsigned
template<>
BIT_ALGORITHM_FUNC_SPEC int bit_count(long long value)
{
    return static_cast<unsigned long long>(bit_count(value));
}

#endif

// Casting signed args to unsigned
template<>
BIT_ALGORITHM_FUNC_SPEC int bit_count(short value)
{
    return bit_count(static_cast<unsigned short>(value));
}

template<>
decltype(bit_count<int>) bit_count(int value)
{
    return bit_count(static_cast<unsigned int>(value));
}

#elif defined(BIT_ALGORITHM_GCC)

// Using __builtin_popcount variations
template<>
BIT_ALGORITHM_FUNC_SPEC int bit_count(unsigned int value)
{
    return __builtin_popcount(value);
}

template<>
BIT_ALGORITHM_FUNC_SPEC int bit_count(unsigned long value)
{
    return __builtin_popcountl(value);
}

template<>
BIT_ALGORITHM_FUNC_SPEC int bit_count(unsigned long long value)
{
    return __builtin_popcountll(value);
}

// Casting signed args to unsigned
template<>
BIT_ALGORITHM_FUNC_SPEC int bit_count(int value)
{
    return bit_count(static_cast<unsigned int>(value));
}

template<>
BIT_ALGORITHM_FUNC_SPEC int bit_count(long value)
{
    return bit_count(static_cast<unsigned long>(value));
}

template<>
BIT_ALGORITHM_FUNC_SPEC int bit_count(long long value)
{
    return bit_count(static_cast<unsigned long long>(value));
}

#endif // BIT_ALGORITHM_GCC


/// \fn parity ( IntType value )
/// \return true if the number of bits set to 1 in value is even,
///         false otherwise.
///
/// \param value    The value to get its parity
///
/// \note This function works regardless of the value sign.
template <typename T>
BIT_ALGORITHM_FUNC_SPEC typename boost::enable_if<
    boost::is_integral<T>, bool
>::type parity(T value)
{
    return bit_count<T>(value) & 1;
}

/// \fn first_set ( IntType value )
/// \return Returns one plus the index of the least significant 1-bit of value.
///         If x is zero, returns zero. If x is negative, return the maximum
///         bit index, as the sign bit is the least one.
///
/// \param value    The value to get its least significant bit set
template <typename T>
BIT_ALGORITHM_FUNC_SPEC typename boost::enable_if_c<
    boost::is_integral<T>::value, int
>::type first_set(T value)
{
    if (value == 0)
        return 0;

    int add = 0, res = 0;
    while (true)
    {
        res = impl::first_set_table<true>
            ::table[value & ((1u << impl::table_width) - 1)];
        if (res)
            break;
        value >>= impl::table_width;
        add += impl::table_width;
    }

    return add + res;
}

#if defined(BIT_ALGORITHM_MSVC)

template<>
BIT_ALGORITHM_FUNC_SPEC int first_set(unsigned long value)
{
    unsigned long index;
    if (_BitScanForward(&index, value))
        return index + 1;
    else
        return 0;
}

template<>
BIT_ALGORITHM_FUNC_SPEC int first_set(long value)
{
    return first_set(static_cast<unsigned long>(value));
}

template<>
BIT_ALGORITHM_FUNC_SPEC int first_set(unsigned int value)
{
    return first_set(static_cast<unsigned long>(value));
}

template<>
BIT_ALGORITHM_FUNC_SPEC int first_set(int value)
{
    return first_set(static_cast<unsigned int>(value));
}

#if defined(BIT_ALGORITHM_MSVC_64)

template<>
BIT_ALGORITHM_FUNC_SPEC int first_set(unsigned __int64 value)
{
    unsigned long index;
    if (_BitScanForward64(&index, value))
        return index + 1;
    else
        return 0;
}

template<>
BIT_ALGORITHM_FUNC_SPEC int first_set(__int64 value)
{
    return first_set(static_cast<unsigned __int64>(value));
}

#else // !defined(BIT_ALGORITHM_MSVC_64)

// Win32 doesn't have _BitScanForward64, emulate it with two 32 bit calls
template<>
BIT_ALGORITHM_FUNC_SPEC int first_set(unsigned long long value)
{
    if (value == 0)
        return 0;
    int first_half = first_set(static_cast<unsigned int>(value)); // cuts last 32 bits
    if (!first_half)
        return 32 + first_set(static_cast<unsigned int>(value >> 32));
    return first_half;
}

// Casting signed args to unsigned
template<>
BIT_ALGORITHM_FUNC_SPEC int first_set(long long value)
{
    return static_cast<unsigned long long>(first_set(value));
}

#endif // BIT_ALGORITHM_MSVC_64

#elif defined(BIT_ALGORITHM_GCC)

template<>
BIT_ALGORITHM_FUNC_SPEC int first_set(int value)
{
    return __builtin_ffs(value);
}

template<>
BIT_ALGORITHM_FUNC_SPEC int first_set(long value)
{
    return __builtin_ffsl(value);
}

template<>
BIT_ALGORITHM_FUNC_SPEC int first_set(long long value)
{
    return __builtin_ffsll(value);
}

template<>
BIT_ALGORITHM_FUNC_SPEC int first_set(unsigned int value)
{
    return first_set(static_cast<int>(value));
}

template<>
BIT_ALGORITHM_FUNC_SPEC int first_set(unsigned long value)
{
    return first_set(static_cast<long>(value));
}

template<>
BIT_ALGORITHM_FUNC_SPEC int first_set(unsigned long long value)
{
    return first_set(static_cast<long long>(value));
}

#endif

}

#endif // BIT_ALGORITHM_HPP
