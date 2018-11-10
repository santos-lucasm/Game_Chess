#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.hpp"


class Knight: public Piece {
public:
    Knight(char a, bool b): Piece::Piece(a, b){}
private:
    virtual char GetPiece(){ return 'N'; }
	bool IsLegalMove(int LinI, int ColI, int LinF, int ColF, Piece* mat[8][8]) {
		int LinVar = abs(LinF - LinI);
		int ColVar = abs(ColF - ColI);

		if (LinVar == 2 && ColVar == 1) {
			return true;
		}
		else if (LinVar == 1 && ColVar == 2) {
			return true;
		}
		else {
			return false;
		}
	}

};

#endif