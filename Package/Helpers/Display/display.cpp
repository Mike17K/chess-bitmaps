#include "./display.h"
#include "../../Tools/Board/board.h"

void bShow(uint64_t bittmap)
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

    uint64_t b = bittmap;
    uint64_t p = 0x100000000000000;

    cout << "================" << endl;
    for (int i = 0; i < 64; i++)
    {
        cout << (((b & p) > 0) ? 1 : 0) << " ";

        p = p << 1;

        if ((i + 1) % 8 == 0)
        {
            p = 0x100000000000000;
            b = b << 8;
            cout << endl;
        }
    }
    cout << "================" << endl;
}

void BShow(Board b){};
/*
    uint64_t p = 0x100000000000000;

    cout << "================" << endl;
    for (int i = 0; i < 64; i++)
    {
        cout << "[♔]"
             << " ";

        cout << (((b.wK & p) > 0) ? "♔" : "");
        cout << (((b.bK & p) > 0) ? "♚" : "");
        cout << (((b.wQ & p) > 0) ? "♕" : "");
        cout << (((b.bQ & p) > 0) ? "♛" : "");
        cout << (((b.wB & p) > 0) ? "♗" : "");
        cout << (((b.bB & p) > 0) ? "♝" : "");
        cout << (((b.wN & p) > 0) ? "♘" : "");
        cout << (((b.bN & p) > 0) ? "♞" : "");
        cout << (((b.wp & p) > 0) ? "♙" : "");
        cout << (((b.bp & p) > 0) ? "♟" : "");
        cout << (((b.wR & p) > 0) ? "♖" : "");
        cout << (((b.bR & p) > 0) ? "♜" : "");
        cout << " ";

        p = p << 1;

        if ((i + 1) % 8 == 0)
        {
            p = 0x100000000000000;
            cout << endl;
        }
    }
    cout << "================" << endl;
}
*/