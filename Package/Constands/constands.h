#ifndef CONSTANDS_H
#define CONSTANDS_H

#include <iostream>
#include <cstdint>

using namespace std;

// constexpr uint64_t BOARDLIMITS = 0xFF818181818181FF;

// constexpr uint64_t D_BOARDLIMITS = 0xFFFFFFFFFFFFFF00;
// constexpr uint64_t U_BOARDLIMITS = 0x00FFFFFFFFFFFFFF;
// constexpr uint64_t L_BOARDLIMITS = 0xFEFEFEFEFEFEFEFE;
// constexpr uint64_t R_BOARDLIMITS = 0x7F7F7F7F7F7F7F7F;

constexpr uint64_t H_ATTACKS = 0x0000000A1100110A;

// from stockfish
constexpr uint64_t AllSquares = ~uint64_t(0);
constexpr uint64_t DarkSquares = 0xAA55AA55AA55AA55ULL;

constexpr uint64_t FileABB = 0x0101010101010101ULL;
constexpr uint64_t FileBBB = FileABB << 1;
constexpr uint64_t FileCBB = FileABB << 2;
constexpr uint64_t FileDBB = FileABB << 3;
constexpr uint64_t FileEBB = FileABB << 4;
constexpr uint64_t FileFBB = FileABB << 5;
constexpr uint64_t FileGBB = FileABB << 6;
constexpr uint64_t FileHBB = FileABB << 7;

constexpr uint64_t Rank1BB = 0xFF;
constexpr uint64_t Rank2BB = Rank1BB << (8 * 1);
constexpr uint64_t Rank3BB = Rank1BB << (8 * 2);
constexpr uint64_t Rank4BB = Rank1BB << (8 * 3);
constexpr uint64_t Rank5BB = Rank1BB << (8 * 4);
constexpr uint64_t Rank6BB = Rank1BB << (8 * 5);
constexpr uint64_t Rank7BB = Rank1BB << (8 * 6);
constexpr uint64_t Rank8BB = Rank1BB << (8 * 7);

constexpr uint64_t QueenSide = FileABB | FileBBB | FileCBB | FileDBB;
constexpr uint64_t CenterFiles = FileCBB | FileDBB | FileEBB | FileFBB;
constexpr uint64_t KingSide = FileEBB | FileFBB | FileGBB | FileHBB;
constexpr uint64_t Center = (FileDBB | FileEBB) & (Rank4BB | Rank5BB);

/*
constexpr uint64_t KingFlank[FILE_NB] = {
    QueenSide ^ FileDBB, QueenSide, QueenSide,
    CenterFiles, CenterFiles,
    KingSide, KingSide, KingSide ^ FileEBB};

extern uint8_t PopCnt16[1 << 16];
extern uint8_t SquareDistance[SQUARE_NB][SQUARE_NB];

extern uint64_t BetweenBB[SQUARE_NB][SQUARE_NB];
extern uint64_t LineBB[SQUARE_NB][SQUARE_NB];
extern uint64_t PseudoAttacks[PIECE_TYPE_NB][SQUARE_NB];
extern uint64_t PawnAttacks[COLOR_NB][SQUARE_NB];
*/

#endif
