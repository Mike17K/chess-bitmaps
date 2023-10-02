#ifndef BITFUNCTIONS_H
#define BITFUNCTIONS_H

#include <iostream>
#include <cstdint>

using namespace std;

uint64_t lsb(uint64_t b);

uint64_t msb(uint64_t b);

uint64_t pop_lsb(uint64_t b);

uint64_t _rank(uint64_t b);

uint64_t _file(uint64_t b);

#endif
