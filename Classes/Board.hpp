#ifndef BOARD_H
#define BOARD_H

#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"

class Board {
private:
    Piece* matriz[8][8];
public:
    Board(); //construtor padrão, inicia game do zero
    
	bool IsCheck(char);
	bool IsCheck(int, int, char); //IsCheck em determinada posicao (usada no Roque)
    bool Movement(int, int, int, int, char);
	bool Roque(int, int, int, int, char);
    void Print();

    ~Board();
};


#endif