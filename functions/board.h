#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <cstdint>
#include "./constands.h"

using namespace std;

class Board
{
public:
    uint64_t bK;
    uint64_t wK;

    uint64_t bQ;
    uint64_t wQ;

    uint64_t bB;
    uint64_t wB;

    uint64_t bR;
    uint64_t wR;

    uint64_t bp;
    uint64_t wp;

    uint64_t bN;
    uint64_t wN;

    Board();
    Board(char state[]);

    uint64_t rookAttacks_w();
    uint64_t horseAttacks_w();
    uint64_t qeenAttacks_w();
    uint64_t kingAttacks_w();
    uint64_t pownAttacks_w();
    uint64_t bishopAttacks_w();

    uint64_t rookAttacks_b();
    uint64_t horseAttacks_b();
    uint64_t qeenAttacks_b();
    uint64_t kingAttacks_b();
    uint64_t pownAttacks_b();
    uint64_t bishopAttacks_b();

    void setBoard(char state[]);

private:
};

#endif
