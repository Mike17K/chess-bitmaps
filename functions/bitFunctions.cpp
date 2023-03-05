#include "./bitFunctions.h"
#include "./constands.h"

using namespace std;

uint64_t lsb(uint64_t b)
{
    // returns the least significant '1' of the given number
    return ((b ^ (b - 1)) >> 1) + 1;
}

uint64_t pop_lsb(uint64_t b)
{
    // removes the least significant '1' from given number and returns the result
    return b & (b - 1);
}

uint64_t _rank(uint64_t b) // returns the rank of the '1'
{
    return (((b * Rank1BB) & FileHBB) >> 7) * Rank1BB;
}

uint64_t _file(uint64_t b) // returns the file of the '1'
{
    return (((b * FileABB) & Rank8BB) >> 56) * FileABB;
}
