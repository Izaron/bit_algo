/*
  Copyright (c) Evgeny Shulgin <izaronplatz@gmail.com>, 2018

  Distributed under the license described in the LICENSE file
*/

#include <iostream>

#include "../include/bits.hpp"

int main() {
    long kek = 228;
    int shrek = 1337;
    std::cout << bit_algo::bit_count(kek) << std::endl;
    std::cout << bit_algo::bit_count(shrek) << std::endl;
    return 0;
}
