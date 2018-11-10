#ifndef ROOK_H
#define ROOK_H
#include "Piece.hpp"


class Rook: public Piece {
public:
    Rook(char a, bool b): Piece::Piece(a, b){}
private:
    virtual char GetPiece(){ return 'R'; }

	bool IsLegalMove(int LinI, int ColI, int LinF, int ColF, Piece* mat[8][8]) {

		if (LinI != LinF && ColI == ColF) {//movimento vertical
			if (LinI < LinF) { //movimento vertical de baixo para cima
				for (int i = LinI + 1; i < LinF; i++) {
					if (mat[i][ColI] != 0) {
						return false;
					}
				}
			}
			else { //movimento vertical de cima para baixo
				for (int i = LinI - 1; i > LinF; i--) {
					if ( mat[i][ColI] != 0) {
						return false;
					}
				}
			}
			return true;
		}
		if (LinI == LinF && ColI != ColF) { //movimento horizontal
			if (ColI < ColF) { //movimento horizontal de esq para direita
				for (int i = ColI + 1; i < ColF; i++) {
					if (mat[LinI][i] != 0 ) {
						return false;
					}
				}
			}
			else { //movimento horizontal da direita para esq
				for (int i = ColI - 1; i > ColF; i--) {
					if ( mat[LinI][i] != 0) {
						return false;
					}
				}
			}
			return true;
		}
		return false;
	}
};

#endif