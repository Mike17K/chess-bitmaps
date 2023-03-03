#include <iostream>
#include <chrono>

#include "./functions/Night.h"
#include "./functions/display.h"
#include "./functions/bitFunctions.h"
#include "./functions/board.h"

using namespace std;

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

  Board *b = new Board("r1bqkbnr/ppp1pppp/2n5/3p4/3P4/5N2/PPP1PPPP/RNBQKB1R w KQkq d6 3 2");

  bShow(b->bB);

  /*
    int i = 0;
    std::chrono::seconds duration(1); // 1 second duration
    // loop for 1 second
    auto start = std::chrono::high_resolution_clock::now();
    while (std::chrono::high_resolution_clock::now() - start < duration) {
      i++;
    }

    std::cout << "i increased to " << i << std::endl;


    i = 0;
    // loop for 1 second
    start = std::chrono::high_resolution_clock::now();
    while (std::chrono::high_resolution_clock::now() - start < duration) {
      i++;
      // function to time

    }

    std::cout << "i increased to " << i << std::endl;
  //*/
  return 0;
}
