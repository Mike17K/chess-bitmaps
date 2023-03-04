#include <iostream>
#include <chrono>

#include "./functions/Night.h"
#include "./functions/display.h"
#include "./functions/bitFunctions.h"
#include "./functions/board.h"

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

  Board *b = new Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

  bShow(b->wK | b->bK | b->wQ | b->bQ | b->wN | b->bN | b->wB | b->bB | b->wR | b->bR | b->bp | b->wp);

  cout << sizeof(*b) << endl;

  b->rookAttacksGen();
  b->nightAttacksGen();

  bShow(b->wA);
  bShow(b->bA);

  //*
  int i = 0;
  std::chrono::milliseconds duration(100); // 1 second duration
  // loop for 1 second
  auto start = std::chrono::high_resolution_clock::now();
  while (std::chrono::high_resolution_clock::now() - start < duration)
  {
    i++;
  }

  std::cout << "i increased to " << i << std::endl;

  int i2 = 0;
  // loop for 1 second
  start = std::chrono::high_resolution_clock::now();
  while (std::chrono::high_resolution_clock::now() - start < duration)
  {
    i2++;
    b->rookAttacksGen();
    b->nightAttacksGen();
    //    function to time
  }

  std::cout << "i2 increased to " << i2 << std::endl;
  std::cout << "Function score is " << (float)(i2) / i * 100 << "% of the max." << std::endl;
  //*/
}
