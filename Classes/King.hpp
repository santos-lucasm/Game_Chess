#ifndef KING_H
#define KING_H

#include <iostream>
#include "Piece.hpp"

class King: public Piece{
public:
    King(char a, bool b): Piece::Piece(a, b){}

private:
    virtual char GetPiece(){ return 'K'; }
    
	bool IsLegalMove(int LinI, int ColI, int LinF, int ColF, Piece* matriz[8][8]) {
		int LinVariacao = LinF - LinI;
		int ColVariacao = ColF - ColI;
		int Passo = (ColVariacao > 0) ? 1 : -1;

		if (LinVariacao <= 1 && LinVariacao >= -1 && ColVariacao <= 1 && ColVariacao >= -1)
			return true;
		
		else if (Castling(LinI, ColI, LinF, ColF, GetColor(), matriz)) {
			return true;
		}

		return false;
	}

	bool EhCheck(int Linha, int Coluna, char time, Piece* matriz[8][8]) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				// se a posicao nao for nula
				if (matriz[i][j] != 0) {
					// se a posicao for ocupada pelo outro time
					if ((matriz[i][j])->GetColor() != time) {
						//verifico se alguem pode se mover ate o rei
						if ((matriz[i][j])->IsActionLegal(i, j, Linha, Coluna, matriz)) {
							return true;
						}
					}
				}
			}
		}
		return false;
	}
	
	bool Castling(int LinI, int ColI, int LinF, int ColF, char jogador, Piece* matriz[8][8]) {
		int LinVariacao = LinF - LinI;
		int ColVariacao = ColF - ColI;
		int Passo = (ColVariacao > 0) ? 1 : -1;

		//Confiro se o rei ou torre correspondente a jogada ja se moveram no jogo
		if ((matriz[LinI][ColI])->HasMovedBefore()) {
			return false;
		}

		if (jogador == 'W') {
			if (matriz[0][7] != 0) {
				if (Passo == 1 && (matriz[0][7])->HasMovedBefore()) {
					return false;
				}
			}
			if (matriz[0][0] != 0) {
				if (Passo == -1 && (matriz[0][0])->HasMovedBefore()) {
					return false;
				}
			}
		}
		if (jogador == 'B') {
			if (matriz[7][7] != 0) {
				if (Passo == 1 && (matriz[7][7])->HasMovedBefore()) {
					return false;
				}
			}
			if (matriz[7][0] != 0) {
				if (Passo == -1 && (matriz[7][0])->HasMovedBefore()) {
					return false;
				}
			}
		}

		//confiro se nao ha pecas entre o roque, e se as casas nao estao em xeque
		if ((ColVariacao == 2 || ColVariacao == -2) && LinVariacao == 0) {
			for (int i = ColI + Passo; i != ColF; i += Passo) {
				if (matriz[LinI][i] != 0) {
					return false;
				}
				else if (EhCheck(LinI, i-Passo, jogador, matriz)) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
	
};

#endif