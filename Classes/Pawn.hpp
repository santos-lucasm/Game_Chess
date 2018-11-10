#ifndef PAWN_H
#define PAWN_H
#include "Piece.hpp"


class Pawn: public Piece {
public:
    Pawn(char a, bool b): Piece::Piece(a, b){}
private:
    virtual char GetPiece(){ return 'P'; }

	bool IsLegalMove(int LinI, int ColI, int LinF, int ColF, Piece* mat[8][8]) {
		char aux = (mat[LinI][ColI])->GetColor();
		int LinVar = LinF - LinI;
		int ColVar = ColF - ColI;

		//se peao for branco, sempre descendo
		if (aux == 'W') {
			if (LinI == 1) {
				//tentar andar uma ou duas casa na primeira fileira
				if ( (LinVar==2 || LinVar==1) && ColVar == 0 && mat[LinF][ColF]==0) {
					for (int i = LinI + 1; i < LinF; i++) {
						if (mat[i][ColI] != 0) {
							return false;
						}
					}
					return true;
				}
				//tentar comer na primeira fileira
				else if (LinVar==1 && (ColVar==1 || ColVar==-1) ) {
					if (mat[LinF][ColF] != 0)
						return true;
				}
				return false;
			}
			else {
				//tentar andar fora da primeira fileira
				if (LinVar == 1 && ColVar == 0 && mat[LinF][ColF] == 0) {
					return true;
				}
				//tentar comer fora da primeira fileira
				else if (LinVar == 1 && (ColVar == 1 || ColVar == -1)) {
					if (mat[LinF][ColF] != 0)
						return true;
				}
				return false;
			}
		}
		//se for preto, sempre subindo
		else {
			if (LinI == 6) {
				//tentar andar na primeira fileira
				if ((LinVar == -2 || LinVar == -1) && ColVar == 0 && mat[LinF][ColF] == 0) {
					for (int i = LinI - 1; i > LinF; i--) {
						if (mat[i][ColI] != 0) {
							return false;
						}
					}
					return true;
				}
				//tentar comer na primeira fileira
				else if (LinVar == -1 && (ColVar == 1 || ColVar == -1)) {
					if (mat[LinF][ColF] != 0)
						return true;
				}
				return false;
			}
			else {
				//tentar andar fora da primeira fileira
				if (LinVar == -1 && ColVar == 0 && mat[LinF][ColF] == 0) {
					return true;
				}
				//tentar comer fora da primeira fileira
				else if (LinVar == -1 && (ColVar == 1 || ColVar == -1)) {
					if (mat[LinF][ColF] != 0)
						return true;
				}
				return false;
			}
		}
	}

};

#endif