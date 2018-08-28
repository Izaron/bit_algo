/*
  Copyright (c) Evgeny Shulgin <izaronplatz@gmail.com>, 2018

  Distributed under the license described in the LICENSE file
*/

#include <cassert>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include <boost/chrono.hpp>
#include <boost/container/static_vector.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/type_index.hpp>

#include "../include/bits.hpp"

//const int test_count = 100000;  // 10^5
//const int test_count = 1000000;  // 10^6
const int test_count = 10000000;  // 10^7

// Naive implementations of common bit algorithms
namespace naive_impl {

template <typename T>
BIT_ALGORITHM_FUNC_SPEC int bit_count(T value)
{
    int res = 0;
    while (value)
    {
        res += value & 1;
        value >>= 1;
    }
    return res;
}

template <typename T>
BIT_ALGORITHM_FUNC_SPEC bool parity(T value)
{
    int res = 0;
    while (value)
    {
        res ^= value & 1;
        value >>= 1;
    }
    return res;
}

template <typename T>
BIT_ALGORITHM_FUNC_SPEC int first_set(T value)
{
    if (value == 0)
        return 0;
    int pos = 1;
    while (!(value & 1))
    {
        pos++;
        value >>= 1;
    }
    return pos;
}

template <typename T>
BIT_ALGORITHM_FUNC_SPEC int last_set(T value)
{
    if (value == 0)
        return 0;
    int pos = 1;
    while (value)
    {
        pos++;
        value >>= 1;
    }
    return pos;
}

template <typename T>
BIT_ALGORITHM_FUNC_SPEC int trailing_zeros(T value)
{
    if (value == 0)
        return sizeof(T) * CHAR_BIT;
    return first_set(value) - 1;
}

template <typename T>
BIT_ALGORITHM_FUNC_SPEC int leading_zeros(T value)
{
    return sizeof(T) * CHAR_BIT - last_set(value);
}

} // naive_impl

// Generates test values of the type T,
// accepts only integral unsigned values
template<typename T>
typename boost::enable_if_c<
    boost::is_integral<T>::value && !std::numeric_limits<T>::is_signed,
    std::vector<T>
>::type gen_values()
{
    std::vector<T> res;
    res.reserve(test_count);

    T max_value = std::numeric_limits<T>::max();
    if (max_value <= test_count - 1) {
        for (T i = 0; res.size() < test_count; ++i) {
            res.push_back(i);
        }
    } else {
        // Using a true random number generator
        boost::random_device device;
        boost::random::uniform_int_distribution<T> random(
            0, std::numeric_limits<T>::max()
        );

        // Generate values
        for (int i = 0; i < test_count; ++i) {
            res.push_back(random(device));
        }
    }
    return res;
}

// Simply runs a function on values
template<typename T>
void raw_run(int (*func)(T),
    const std::vector<T>& vector)
{
    // Don't allow the compiler to "optimize" this part
    // by cutting this out, with "volatile" keyword
    volatile int res = 0; 
    for (std::size_t i = 0; i < vector.size(); ++i)
        res += func(vector[i]);
}

// Runs functions on test values and measures running time
template<typename T>
void run_diff(int (*naive)(T), int (*fast)(T),
    const std::vector<T>& vector)
{
    using namespace boost::chrono;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    raw_run(naive, vector);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    duration<double> time_span = duration_cast<
        duration<double>
    >(t2 - t1);
    double t1_seconds = time_span.count();
    std::cout << "Naive solution ran \t" << t1_seconds
        << " seconds" << std::endl;

    t1 = high_resolution_clock::now();
    raw_run(fast, vector);
    t2 = high_resolution_clock::now();

    time_span = duration_cast< duration<double> >(t2 - t1);
    double t2_seconds = time_span.count();
    std::cout << "Fast solution ran  \t" << t2_seconds 
        << " seconds" << std::endl;

    std::cout << "\t\t\tThe fast solution relative speed: " << (t2_seconds / t1_seconds * 100.0)
        << "\%" << std::endl;
}

// Asserts equality of both naive (which is correct by default)
// and fast functions on the same values
template<typename T>
void check_equality(int (*naive)(T), int (*fast)(T),
    const std::vector<T>& vector)
{
    for (std::size_t i = 0; i < vector.size(); ++i)
    {
        int naive_outcome = naive(vector[i]);
        int fast_outcome = fast(vector[i]);
        assert(naive_outcome == fast_outcome);
    }
}

// Checks both naive and fast functions on correctness
// and measures their running time
template<typename T>
void work_with_functions(const std::string& func_name,
    int (*naive)(T), int (*fast)(T),
    const std::vector<T>& vector)
{
    std::cout << "WORKING WITH\t\t" << func_name << std::endl;
    std::cout << "THE TYPE IS\t\t" << boost::typeindex::type_id<T>() << std::endl;

    std::cout << "Check correctness..." << std::endl;
    check_equality(naive, fast, vector);
    std::cout << "The fast realization is correct!" << std::endl;

    std::cout << "Measuring time..." << std::endl;
    run_diff(naive, fast, vector);

    std::cout << std::endl << std::endl;
}

template<typename T>
void benchmark()
{
    std::vector<T> vector = gen_values<T>();

    work_with_functions("bit_count", naive_impl::bit_count<T>,
        bit_algo::bit_count<T>, vector);
    //work_with_functions("parity", naive_impl::parity<T>,
    //    bit_algo::parity<T>, vector);
    work_with_functions("first_set", naive_impl::first_set<T>,
        bit_algo::first_set<T>, vector);
}

int main()
{
    benchmark<unsigned char>();
    benchmark<unsigned short>();
    benchmark<unsigned int>();
    benchmark<unsigned long>();
    benchmark<unsigned long long>();
}
