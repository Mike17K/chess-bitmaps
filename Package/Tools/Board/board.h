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

    void rookAttacksGen();
    void rookAttacksGen2();
    void nightAttacksGen();
    void qeenAttacksGen();
    void kingAttacksGen();
    void pownAttacksGen();
    void bishopAttacksGen();

    void setBoard(char state[]);

private:
};

#endif
