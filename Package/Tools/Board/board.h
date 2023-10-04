#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <cstdint>
#include "../../Constands/constands.h"

using namespace std;

class Board
{
public:
    bool isWhiteToPlay;
    bool castlingK;
    bool castlingk;
    bool castlingQ;
    bool castlingq;

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

    uint64_t bA;
    uint64_t wA;

    Board();
    Board(char state[]);
    void setBoard(char state[]);

    uint64_t rookAttacksGen(bool white = true);
    uint64_t nightAttacksGen(bool white = true);
    uint64_t queenAttacksGen(bool white = true);
    uint64_t kingAttacksGen(bool white = true);
    uint64_t pownAttacksGen(bool white = true);
    uint64_t bishopAttacksGen(bool white = true);

    uint64_t genMovesSq(uint64_t sq);

private:
};

#endif
