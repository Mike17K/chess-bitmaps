#include <iostream>
#include <chrono>

#include "./Package/Constands/Night.h"
#include "./Package/Helpers/Display/display.h"
#include "./Package/Helpers/BitFunctions/bitFunctions.h"
#include "./Package/Tools/Board/board.h"

using namespace std;

void timefunction(void *func);

int main()
{
  /* Gives representation of
    56 57 58 59 60 61 62 63
    48 49 50 51 52 53 54 55
    40 41 42 43 44 45 46 47
    32 33 34 35 36 37 38 39
    24 25 26 27 28 29 30 31
    16 17 18 19 20 21 22 23
    8  9  10 11 12 13 14 15
    0  1  2  3  4  5  6  7
  */

  Board *b = new Board("1nbqk2r/ppppp2p/8/8/8/8/PPPPPPPP/R3KBN1 w KQkq - 0 1");
  // Board *b = new Board("3k4/8/8/8/8/8/8/R12K3 w KQkq - 0 1");

  bShow(b->wK | b->bK | b->wQ | b->bQ | b->wN | b->bN | b->wB | b->bB | b->wR | b->bR | b->bp | b->wp);
  //*
  // loop for 1 second
  const int N = 1;

  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < N; i++)
  {
  }
  auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
  std::cout << "Duration: " << duration1.count() << " microseconds" << std::endl;

  cout << sizeof(Board);

  b->kingAttacksGen();
  b->queenAttacksGen();
  b->nightAttacksGen();
  b->bishopAttacksGen();
  b->rookAttacksGen();
  b->pownAttacksGen();

  uint64_t sq = b->bK;
  uint64_t moves = b->genMovesSq(sq);
  cout << "bK Moves: " << endl;
  bShow(moves);
}
