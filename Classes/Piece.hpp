#ifndef PIECE_H
#define PIECE_H
#include <iostream>

class  Piece{
protected:
    char team; // W or B
	bool hasmove;
	virtual bool IsLegalMove(int, int, int, int, Piece* (*)[8]) = 0; //confere se a peca anda conforme as regras

public:
    Piece(char a, bool b): team(a), hasmove(b) {}
	virtual ~Piece() {}

	void SetHasMoved(bool a) { hasmove = a; }
	bool HasMovedBefore() { return hasmove; }
    char GetColor(){ return team; }
    virtual char GetPiece() = 0; //utilizada para mostrar o tabuleiro, cada peca tem seu caracter
    
    bool IsActionLegal(int iLin, int iCol, int fLin, int fCol, Piece* mat[8][8]) {

		Piece* dest = mat[fLin][fCol];
		if ( (dest == 0) || (team != dest->GetColor()) ) {
			return IsLegalMove(iLin, iCol, fLin, fCol, mat);
		}
		else {
			return false;
		}
	}
};



#endif