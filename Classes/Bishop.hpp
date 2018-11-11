#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.hpp"


class Bishop: public Piece {
public:
    Bishop(char a, bool b): Piece::Piece(a, b){}
private:
    virtual char GetPiece(){ return 'B'; }
	
	bool IsLegalMove(int LinI, int ColI, int LinF, int ColF, Piece* mat[8][8]) {
		int LinVar = abs(LinF - LinI);
		int ColVar = abs(ColF - ColI);

		//verifico se o bispo anda em diagonal
		if ( LinVar == ColVar ) {
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
		return false;
	}
};

#endif