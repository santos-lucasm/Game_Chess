#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.hpp"


class Queen: public Piece {
public:
    Queen(char a, bool b): Piece::Piece(a, b){}
private:
    virtual char GetPiece(){ return 'Q'; }
	bool IsLegalMove( int LinI, int ColI, int LinF, int ColF, Piece* mat[8][8] ) {
		int LinVar = abs(LinF - LinI);
		int ColVar = abs(ColF - ColI);

		//verifico se a rainha andara em diagonal
		if (LinVar == ColVar) {
			// decido para qual quadrante eu vou andar
			int PassoLinha = (LinF - LinI > 0) ? 1 : -1;
			int PassoColuna = (ColF - ColI > 0) ? 1 : -1;

			for (int i = LinI + PassoLinha, j = ColI + PassoColuna;
				i != LinF;
				i += PassoLinha, j += PassoColuna)
			{
				if (mat[i][j] != 0) {
					return false;
				}
			}
			return true;
		}
		//verifico se a rainha andara em linha reta
		else if (LinI != LinF && ColI == ColF) {//movimento vertical
			if (LinI < LinF) { //movimento vertical de baixo para cima
				for (int i = LinI + 1; i < LinF; i++) {
					if (mat[i][ColI] != 0) {
						return false;
					}
				}
			}
			else { //movimento vertical de cima para baixo
				for (int i = LinI - 1; i > LinF; i--) {
					if (mat[i][ColI] != 0) {
						return false;
					}
				}
			}
			return true;
		}
		else if (LinI == LinF && ColI != ColF) { //movimento horizontal
			if (ColI < ColF) { //movimento horizontal de esq para direita
				for (int i = ColI + 1; i < ColF; i++) {
					if (mat[LinI][i] != 0) {
						return false;
					}
				}
			}
			else { //movimento horizontal da direita para esq
				for (int i = ColI - 1; i > ColF; i--) {
					if (mat[LinI][i] != 0) {
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