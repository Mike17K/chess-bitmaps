#include "./board.h"
#include "../../Helpers/BitFunctions/bitFunctions.h"
#include "../../Helpers/Display/display.h"

using namespace std;

Board::Board(){};
Board::Board(char state[])
{
    this->isWhiteToPlay = true;

    this->castlingK = false;
    this->castlingk = false;
    this->castlingQ = false;
    this->castlingq = false;

    this->bK = 0x0;
    this->wK = 0x0;
    this->bQ = 0x0;
    this->wQ = 0x0;
    this->bB = 0x0;
    this->wB = 0x0;
    this->bR = 0x0;
    this->wR = 0x0;
    this->bp = 0x0;
    this->wp = 0x0;
    this->bN = 0x0;
    this->wN = 0x0;

    this->bA = 0x0;
    this->wA = 0x0;

    this->setBoard(state);
};

void Board::setBoard(char txt[])
{
    /*
   A FEN string defines a particular position using only the ASCII character set.

   A FEN string contains six fields separated by a space. The fields are:

   1) Piece placement (from white's perspective). Each rank is described, starting
      with rank 8 and ending with rank 1. Within each rank, the contents of each
      square are described from file A through file H. Following the Standard
      Algebraic Notation (SAN), each piece is identified by a single letter taken
      from the standard English names. White pieces are designated using upper-case
      letters ("PNBRQK") whilst Black uses lowercase ("pnbrqk"). Blank squares are
      noted using digits 1 through 8 (the number of blank squares), and "/"
      separates ranks.

   2) Active color. "w" means white moves next, "b" means black.

   3) Castling availability. If neither side can castle, this is "-". Otherwise,
      this has one or more letters: "K" (White can castle kingside), "Q" (White
      can castle queenside), "k" (Black can castle kingside), and/or "q" (Black
      can castle queenside).

   4) En passant target square (in algebraic notation). If there's no en passant
      target square, this is "-". If a pawn has just made a 2-square move, this
      is the position "behind" the pawn. Following X-FEN standard, this is recorded only
      if there is a pawn in position to make an en passant capture, and if there really
      is a pawn that might have advanced two squares.

   5) Halfmove clock. This is the number of halfmoves since the last pawn advance
      or capture. This is used to determine if a draw can be claimed under the
      fifty-move rule.

   6) Fullmove number. The number of the full move. It starts at 1, and is
      incremented after Black's move.
*/
    int i = 0;
    for (int rank = 7; rank >= 0; rank--)
    {
        for (int file = 0; file <= 8; file++)
        {
            char c = txt[i++];
            if (c == '/')
                break;

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

            this->bp |= ((uint64_t)1 << tmp_pos) * (c == 'p');
            this->wp |= ((uint64_t)1 << tmp_pos) * (c == 'P');
            this->bN |= ((uint64_t)1 << tmp_pos) * (c == 'n');
            this->wN |= ((uint64_t)1 << tmp_pos) * (c == 'N');
            this->bB |= ((uint64_t)1 << tmp_pos) * (c == 'b');
            this->wB |= ((uint64_t)1 << tmp_pos) * (c == 'B');
            this->bR |= ((uint64_t)1 << tmp_pos) * (c == 'r');
            this->wR |= ((uint64_t)1 << tmp_pos) * (c == 'R');
            this->bQ |= ((uint64_t)1 << tmp_pos) * (c == 'q');
            this->wQ |= ((uint64_t)1 << tmp_pos) * (c == 'Q');
            this->bK |= ((uint64_t)1 << tmp_pos) * (c == 'k');
            this->wK |= ((uint64_t)1 << tmp_pos) * (c == 'K');
        }
        if (txt[i] == ' ')
            break;
    }

    // handle the who is playing
    char c = txt[i];
    this->isWhiteToPlay = c == 'w';
    i++;

    // handle the castling rights
    this->castlingK = false;
    this->castlingk = false;
    this->castlingQ = false;
    this->castlingq = false;
    while (1)
    {
        i++;
        if (txt[i] == ' ' || (txt[i] != 'K' && txt[i] != 'k' && txt[i] != 'Q' && txt[i] != 'q'))
            break;

        this->castlingK |= txt[i] == 'K';
        this->castlingk |= txt[i] == 'k';
        this->castlingQ |= txt[i] == 'Q';
        this->castlingq |= txt[i] == 'q';
    }

    if (txt[i] == ' ')
        i++;

    // extra info about last move and the number of half-moves since the last capture or pawn and the move number on which the current state of the game was reached
    // not importand for now
    // cout << txt + i << endl;
};

uint64_t Board::nightAttacksGen(bool white)
{

    uint64_t attacking_sq_w = 0;
    uint64_t attacking_sq_b = 0;

    uint64_t tmp_w = this->wN;
    uint64_t tmp_b = this->bN;

    // until no '1' in horsepositions
    while (tmp_w != 0x00 || tmp_b != 0x00)
    {
        // take lsb '1'
        uint64_t t_w = lsb(tmp_w);
        uint64_t t_b = lsb(tmp_b);

        // find moves for this pos
        uint64_t newAttacks_w = (t_w < 0x0000000000040000) ? (t_w * H_ATTACKS) >> 18 : (t_w >> 18) * H_ATTACKS;
        uint64_t newAttacks_b = (t_b < 0x0000000000040000) ? (t_b * H_ATTACKS) >> 18 : (t_b >> 18) * H_ATTACKS;

        // handle overflow
        if ((t_w & 0x00003C3C3C3C0000) == 0)
        {
            newAttacks_w = (t_w & 0x0303030303030303) ? /*left overflow*/ newAttacks_w & 0x3F3F3F3F3F3F3F3F : ((t_w & 0xC0C0C0C0C0C0C0C0) ? /*right overflow*/ newAttacks_w & 0xFCFCFCFCFCFCFCFC : newAttacks_w);
            newAttacks_w = (t_w & 0xFFFF000000000000) ? /*up overflow*/ newAttacks_w & 0xFFFFFFFFFFFF0000 : ((t_w & 0x000000000000FFFF) ? /*right overflow*/ newAttacks_w & 0x0000FFFFFFFFFFFF : newAttacks_w);
        }
        if ((t_b & 0x00003C3C3C3C0000) == 0)
        {
            newAttacks_b = (t_b & 0x0303030303030303) ? /*left overflow*/ newAttacks_b & 0x3F3F3F3F3F3F3F3F : ((t_b & 0xC0C0C0C0C0C0C0C0) ? /*right overflow*/ newAttacks_b & 0xFCFCFCFCFCFCFCFC : newAttacks_b);
            newAttacks_b = (t_b & 0xFFFF000000000000) ? /*up overflow*/ newAttacks_b & 0xFFFFFFFFFFFF0000 : ((t_b & 0x000000000000FFFF) ? /*right overflow*/ newAttacks_b & 0x0000FFFFFFFFFFFF : newAttacks_b);
        }

        // add moves to final map
        attacking_sq_w |= newAttacks_w;
        attacking_sq_b |= newAttacks_b;

        // remove '1'
        tmp_w = pop_lsb(tmp_w);
        tmp_b = pop_lsb(tmp_b);
    }

    this->wA |= attacking_sq_w; // finished here calculating the w N posible moves
    this->bA |= attacking_sq_b; // finished here calculating the w N posible moves

    return (white) ? attacking_sq_w : attacking_sq_b;
};

uint64_t Board::rookAttacksGen(bool white)
{
    uint64_t tmp_w = this->wR; // for white
    uint64_t tmp_b = this->bR; // for black

    uint64_t attacking_sq_w = 0;
    uint64_t attacking_sq_b = 0;

    int directions[4] = {-8, 1, 8, -1};
    uint64_t limitboards[4] = {Rank1BB, FileHBB, Rank8BB, FileABB}; // based of the directions order we put the limit testing here

    uint64_t blackPieces = this->bB | this->bN | this->bR | this->bp | this->bQ | this->bK; // posibly make it class atr
    uint64_t whitePieces = this->wB | this->wN | this->wR | this->wp | this->wQ | this->wK; // this too
    uint64_t allPieces = blackPieces | whitePieces;

    for (int direction = 0; direction < 4; direction++)
    { // for each direction
        tmp_w = this->wR;
        tmp_b = this->bR;
        while (tmp_w != 0 || tmp_b != 0)
        {
            tmp_w &= ~limitboards[direction]; // this line is clearing if the limits are reached
            tmp_b &= ~limitboards[direction]; // this line is clearing if the limits are reached

            // new pos calculation
            uint64_t new_pos_w = (directions[direction] < 0) ? tmp_w >> -directions[direction] : tmp_w << directions[direction];
            uint64_t new_pos_b = (directions[direction] < 0) ? tmp_b >> -directions[direction] : tmp_b << directions[direction];

            // find the intersactions in general
            uint64_t intersections_w = allPieces & new_pos_w;
            uint64_t intersections_b = allPieces & new_pos_b;

            // uint64_t same_intersactions_w = whitePieces & new_pos_w;
            // uint64_t same_intersactions_b = blackPieces & new_pos_b;

            // uint64_t different_intersactions_w = blackPieces & new_pos_w;
            // uint64_t different_intersactions_b = whitePieces & new_pos_b;

            attacking_sq_w |= new_pos_w; // attacking sq are also the sq of the intersactions when there are same color pieces too
            attacking_sq_b |= new_pos_b; // attacking sq are also the sq of the intersactions when there are same color pieces too

            // check for intersactions with same color pieces
            // check for intersactions with oposite color pieces
            // remove the intersactions from the new_pos cause the pieces can now overlap
            new_pos_w -= intersections_w; // same_intersactions_w | different_intersactions_w;
            new_pos_b -= intersections_b; // same_intersactions_b | different_intersactions_b;

            // set last position to new position
            tmp_w = new_pos_w;
            tmp_b = new_pos_b;
        }
    }
    this->wA |= attacking_sq_w; // add to the array the extra attacks
    this->bA |= attacking_sq_b; // add to the array the extra attacks

    return (white) ? attacking_sq_w : attacking_sq_b;
};

uint64_t Board::bishopAttacksGen(bool white)
{

    uint64_t tmp_w = this->wB; // for white
    uint64_t tmp_b = this->bB; // for black

    uint64_t attacking_sq_w = 0;
    uint64_t attacking_sq_b = 0;

    int directions[4] = {9, 7, -9, -7};
    uint64_t limitboards[4] = {Rank8BB | FileHBB, Rank8BB | FileABB, Rank1BB | FileABB, Rank1BB | FileHBB}; // based of the directions order we put the limit testing here

    uint64_t blackPieces = this->bB | this->bN | this->bR | this->bp | this->bQ | this->bK; // posibly make it class atr
    uint64_t whitePieces = this->wB | this->wN | this->wR | this->wp | this->wQ | this->wK; // this too
    uint64_t allPieces = blackPieces | whitePieces;

    for (int direction = 0; direction < 4; direction++)
    { // for each direction
        tmp_w = this->wB;
        tmp_b = this->bB;
        while (tmp_w != 0 || tmp_b != 0)
        {
            tmp_w &= ~limitboards[direction]; // this line is clearing if the limits are reached
            tmp_b &= ~limitboards[direction]; // this line is clearing if the limits are reached

            // new pos calculation
            uint64_t new_pos_w = (directions[direction] < 0) ? tmp_w >> -directions[direction] : tmp_w << directions[direction];
            uint64_t new_pos_b = (directions[direction] < 0) ? tmp_b >> -directions[direction] : tmp_b << directions[direction];

            // find the intersactions in general
            uint64_t intersections_w = allPieces & new_pos_w;
            uint64_t intersections_b = allPieces & new_pos_b;

            // uint64_t same_intersactions_w = whitePieces & new_pos_w;
            // uint64_t same_intersactions_b = blackPieces & new_pos_b;

            // uint64_t different_intersactions_w = blackPieces & new_pos_w;
            // uint64_t different_intersactions_b = whitePieces & new_pos_b;

            attacking_sq_w |= new_pos_w; // attacking sq are also the sq of the intersactions when there are same color pieces too
            attacking_sq_b |= new_pos_b; // attacking sq are also the sq of the intersactions when there are same color pieces too

            // check for intersactions with same color pieces
            // check for intersactions with oposite color pieces
            // remove the intersactions from the new_pos cause the pieces can now overlap
            new_pos_w -= intersections_w; // same_intersactions_w | different_intersactions_w;
            new_pos_b -= intersections_b; // same_intersactions_b | different_intersactions_b;

            // set last position to new position
            tmp_w = new_pos_w;
            tmp_b = new_pos_b;
        }
    }
    this->wA |= attacking_sq_w; // add to the array the extra attacks
    this->bA |= attacking_sq_b; // add to the array the extra attacks
                                // uint64_t different_intersactions_b

    return (white) ? attacking_sq_w : attacking_sq_b;
}

uint64_t Board::queenAttacksGen(bool white)
{
    uint64_t tmp_w = this->wQ; // for white
    uint64_t tmp_b = this->bQ; // for black

    uint64_t attacking_sq_w = 0;
    uint64_t attacking_sq_b = 0;

    int directions[8] = {9, 7, -9, -7, -8, 1, 8, -1};
    // based of the directions order we put the limit testing here
    uint64_t limitboards[8] = {Rank8BB | FileHBB, Rank8BB | FileABB, Rank1BB | FileABB, Rank1BB | FileHBB, Rank1BB, FileHBB, Rank8BB, FileABB};

    uint64_t blackPieces = this->bB | this->bN | this->bR | this->bp | this->bQ | this->bK; // posibly make it class atr
    uint64_t whitePieces = this->wB | this->wN | this->wR | this->wp | this->wQ | this->wK; // this too
    uint64_t allPieces = blackPieces | whitePieces;

    for (int direction = 0; direction < 8; direction++)
    { // for each direction
        tmp_w = this->wQ;
        tmp_b = this->bQ;
        while (tmp_w != 0 || tmp_b != 0)
        {
            tmp_w &= ~limitboards[direction]; // this line is clearing if the limits are reached
            tmp_b &= ~limitboards[direction]; // this line is clearing if the limits are reached

            // new pos calculation
            uint64_t new_pos_w = (directions[direction] < 0) ? tmp_w >> -directions[direction] : tmp_w << directions[direction];
            uint64_t new_pos_b = (directions[direction] < 0) ? tmp_b >> -directions[direction] : tmp_b << directions[direction];

            // find the intersactions in general
            uint64_t intersections_w = allPieces & new_pos_w;
            uint64_t intersections_b = allPieces & new_pos_b;

            // uint64_t same_intersactions_w = whitePieces & new_pos_w;
            // uint64_t same_intersactions_b = blackPieces & new_pos_b;

            // uint64_t different_intersactions_w = blackPieces & new_pos_w;
            // uint64_t different_intersactions_b = whitePieces & new_pos_b;

            attacking_sq_w |= new_pos_w; // attacking sq are also the sq of the intersactions when there are same color pieces too
            attacking_sq_b |= new_pos_b; // attacking sq are also the sq of the intersactions when there are same color pieces too

            // check for intersactions with same color pieces
            // check for intersactions with oposite color pieces
            // remove the intersactions from the new_pos cause the pieces can now overlap
            new_pos_w -= intersections_w; // same_intersactions_w | different_intersactions_w;
            new_pos_b -= intersections_b; // same_intersactions_b | different_intersactions_b;

            // set last position to new position
            tmp_w = new_pos_w;
            tmp_b = new_pos_b;
        }
    }
    this->wA |= attacking_sq_w; // add to the array the extra attacks
    this->bA |= attacking_sq_b; // add to the array the extra attacks

    return (white) ? attacking_sq_w : attacking_sq_b;
}

uint64_t Board::kingAttacksGen(bool white)
{
    uint64_t tmp_w = this->wK; // for white
    uint64_t tmp_b = this->bK; // for black

    uint64_t attacking_sq_w = 0;
    uint64_t attacking_sq_b = 0;

    int directions[8] = {9, 7, -9, -7, -8, 1, 8, -1};
    // based of the directions order we put the limit testing here
    uint64_t limitboards[8] = {Rank8BB | FileHBB, Rank8BB | FileABB, Rank1BB | FileABB, Rank1BB | FileHBB, Rank1BB, FileHBB, Rank8BB, FileABB};

    uint64_t blackPieces = this->bB | this->bN | this->bR | this->bp | this->bQ | this->bK; // posibly make it class atr
    uint64_t whitePieces = this->wB | this->wN | this->wR | this->wp | this->wQ | this->wK; // this too
    uint64_t allPieces = blackPieces | whitePieces;

    for (int direction = 0; direction < 8; direction++)
    { // for each direction
        tmp_w = this->wK;
        tmp_b = this->bK;
        tmp_w &= ~limitboards[direction]; // this line is clearing if the limits are reached
        tmp_b &= ~limitboards[direction]; // this line is clearing if the limits are reached

        // new pos calculation
        uint64_t new_pos_w = (directions[direction] < 0) ? tmp_w >> -directions[direction] : tmp_w << directions[direction];
        uint64_t new_pos_b = (directions[direction] < 0) ? tmp_b >> -directions[direction] : tmp_b << directions[direction];

        attacking_sq_w |= new_pos_w; // attacking sq are also the sq of the intersactions when there are same color pieces too
        attacking_sq_b |= new_pos_b; // attacking sq are also the sq of the intersactions when there are same color pieces too

        // set last position to new position
        tmp_w = new_pos_w;
        tmp_b = new_pos_b;
    }
    this->wA |= attacking_sq_w; // add to the array the extra attacks
    this->bA |= attacking_sq_b; // add to the array the extra attacks

    return (white) ? attacking_sq_w : attacking_sq_b;
}

uint64_t Board::pownAttacksGen(bool white)
{
    uint64_t tmp_w = this->wp; // for white
    uint64_t tmp_b = this->bp; // for black

    uint64_t attacking_sq_w = 0;
    uint64_t attacking_sq_b = 0;

    attacking_sq_w |= (tmp_w << 7) & ~FileHBB; // left attack
    attacking_sq_w |= (tmp_w << 9) & ~FileABB; // right attack

    attacking_sq_b |= (tmp_b >> 7) & ~FileABB; // left attack
    attacking_sq_b |= (tmp_b >> 9) & ~FileHBB; // right attack

    this->wA |= attacking_sq_w; // add to the array the extra attacks
    this->bA |= attacking_sq_b; // add to the array the extra attacks

    return (white) ? attacking_sq_w : attacking_sq_b;
}

uint64_t Board::genMovesSq(uint64_t sq)
{
    uint64_t moves = 0;

    uint64_t blackPieces = this->bB | this->bN | this->bR | this->bp | this->bQ | this->bK; // posibly make it class atr
    uint64_t whitePieces = this->wB | this->wN | this->wR | this->wp | this->wQ | this->wK; // this too
    uint64_t allPieces = blackPieces | whitePieces;

    if (sq & this->bp)
    {
        cout << "black pawn" << endl;
    }
    else if (sq & this->wp)
    {
        cout << "white pawn" << endl;
    }
    else if (sq & this->bN)
    {
        cout << "black night" << endl;
    }
    else if (sq & this->wN)
    {
        cout << "white night" << endl;
    }
    else if (sq & this->wB)
    {
        cout << "white bishop" << endl;
    }
    else if (sq & this->bB)
    {
        cout << "black bishop" << endl;
    }
    else if (sq & this->wR)
    {
        cout << "white rook" << endl;
    }
    else if (sq & this->bR)
    {
        cout << "black rook" << endl;
    }
    else if (sq & this->wQ)
    {
        cout << "white queen" << endl;
    }
    else if (sq & this->bQ)
    {
        cout << "black queen" << endl;
    }
    else if (sq & this->wK) // fix add checks for existing rook and the middle sq should be empty
    {
        // white king
        uint64_t wK_attacks = this->kingAttacksGen(true);
        moves = wK_attacks & ~this->bA;

        // O-O castling
        moves |= ((0x000000000000000E & ~this->bA & ~(allPieces ^ this->wK)) == 0x060000000000000E && this->castlingK) ? 0x0000000000000002 : 0;

        // O-O-O castling
        moves |= ((0x0000000000000038 & ~this->bA & ~(allPieces ^ this->wK)) == 0x0000000000000038 && this->castlingQ) ? 0x0000000000000040 : 0;
    }
    else if (sq & this->bK) // fix add checks for existing rook and the middle sq should be empty
    {
        // black king
        uint64_t bK_attacks = this->kingAttacksGen(false);
        moves = bK_attacks & ~this->wA;

        // O-O castling
        moves |= ((0x0E00000000000000 & ~this->wA & ~(allPieces ^ this->bK)) == 0x0E00000000000000 && this->castlingk) ? 0x0200000000000000 : 0;

        // O-O-O castling
        moves |= ((0x3800000000000000 & ~this->wA & ~(allPieces ^ this->bK)) == 0x3800000000000000 && this->castlingq) ? 0x2000000000000000 : 0;
    }

    return moves;
}
