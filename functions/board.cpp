#include "./board.h"
#include "./bitFunctions.h"

using namespace std;

Board::Board(){};
Board::Board(char state[])
{
    this->setBoard(state);
};

void Board::setBoard(char txt[])
{
    cout << "Board set to: " << txt << endl;
    int i = 0;
    for (int rank = 7; rank >= 0; rank--)
    {
        for (int file = 0; file <= 8; file++)
        {
            char c = txt[i++];
            if (c == '/')
            {
                break;
            }

            if (int(c) > 48 && int(c) < 56)
            {
                // cout << "scipped " << int(c) - 48 << " using " << c;
                file += int(c) - 48 - 1;
                continue;
            }

            if (c == ' ')
                break;

            int tmp_pos = file + rank * 8;
            // cout << file << " " << rank << "(" << c << ")"<< " ";

            // i have the border position in : tmp_pos and the piece type in : c
            switch (c)
            {
            case 'p':
                this->bp |= (uint64_t)1 << tmp_pos;
                break;
            case 'P':
                this->wp |= (uint64_t)1 << tmp_pos;
                break;
            case 'n':
                this->bN |= (uint64_t)1 << tmp_pos;
                break;
            case 'N':
                this->wN |= (uint64_t)1 << tmp_pos;
                break;
            case 'b':
                this->bB |= (uint64_t)1 << tmp_pos;
                break;
            case 'B':
                this->wB |= (uint64_t)1 << tmp_pos;
                break;
            case 'r':
                this->bR |= (uint64_t)1 << tmp_pos;
                break;
            case 'R':
                this->wR |= (uint64_t)1 << tmp_pos;
                break;
            case 'q':
                this->bQ |= (uint64_t)1 << tmp_pos;
                break;
            case 'Q':
                this->wQ |= (uint64_t)1 << tmp_pos;
                break;
            case 'k':
                this->bK |= (uint64_t)1 << tmp_pos;
                break;
            case 'K':
                this->wK |= (uint64_t)1 << tmp_pos;
                break;

            default:
                break;
            }
        }
    }

    // handle the rest of the info here ...
};

uint64_t Board::horseAttacks_w()
{
    uint64_t b = this->wN;
    uint64_t finalMoves = 0;
    // until no '1' in horsepositions
    while (b != 0x00)
    {
        // take lsb '1'
        uint64_t t = lsb(b);
        // find moves for this pos
        uint64_t newAttacks;
        if (t < 0x0000000000040000)
        { // handle t overflow
            newAttacks = (t * H_ATTACKS) >> 18;
        }
        else
        {
            newAttacks = (t >> 18) * H_ATTACKS;
        }

        // overflow check
        if ((t & 0x00003C3C3C3C0000) == 0)
        {
            // handle overflow
            if (t & 0x0303030303030303)
            { // left overflow
                newAttacks &= 0x3F3F3F3F3F3F3F3F;
            }
            else if (t & 0xC0C0C0C0C0C0C0C0)
            { // right overflow
                newAttacks &= 0xFCFCFCFCFCFCFCFC;
            }

            if (t & 0xFFFF000000000000)
            { // up overflow
                newAttacks &= 0xFFFFFFFFFFFF0000;
            }
            else if (t & 0x000000000000FFFF)
            { // down overflow
                newAttacks &= 0x0000FFFFFFFFFFFF;
            }
        }

        // add moves to final map
        finalMoves |= newAttacks;
        // remove '1'
        b = pop_lsb(b);
    }

    return finalMoves;
};

uint64_t Board::rookAttacks_w()
{
    uint64_t attacked_sq = 0;
    // uint64_t tmp_attacks=0;

    uint64_t tmp_b = this->bR;

    int directions[4] = {8, -1, -8, 1};

    for (int direction = 0; direction < 4; direction++)
    { // for each direction

        while (tmp_b != 0)
        {
            // delete the limits
            if (directions[direction] == -8)
                tmp_b &= D_BOARDLIMITS;
            if (directions[direction] == 8)
                tmp_b &= U_BOARDLIMITS;
            if (directions[direction] == -1)
                tmp_b &= L_BOARDLIMITS;
            if (directions[direction] == 1)
                tmp_b &= R_BOARDLIMITS;

            // new pos calculation
            uint64_t new_pos;
            if (directions[direction] < 0)
            {
                new_pos = tmp_b >> -directions[direction];
            }
            else
            {
                new_pos = tmp_b << directions[direction];
            }

            cout << new_pos << endl;

            // check for intersactions with same color pieces

            // check for intersactions with oposite color pieces

            // if(tmp_b & BOARDLIMITS !=0 && )
        }
    }

    return attacked_sq;
};
