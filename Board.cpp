#include "Classes/Board.hpp"
#include <iostream>

Board::Board(){

    //inicio a matriz que recebera as peças
    for(int lin=0; lin<8; lin++){
        for(int col=0; col<8; col++){
            matriz[lin][col] = 0;
        }
    }

    //alocar peças pretas
    for (int col = 0; col < 8; col++) {
        matriz[6][col] = new Pawn('B', false);
    }
    matriz[7][0] = new Rook('B', false);
    matriz[7][1] = new Knight('B', false);
    matriz[7][2] = new Bishop('B', false);
    matriz[7][3] = new King('B', false);
    matriz[7][4] = new Queen('B', false);
    matriz[7][5] = new Bishop('B', false);
    matriz[7][6] = new Knight('B', false);
    matriz[7][7] = new Rook('B', false);

    //alocar peças brancas
    for (int col = 0; col < 8; col++) {
        matriz[1][col] = new Pawn('W', false);
    }
    matriz[0][0] = new Rook('W', false);
    matriz[0][1] = new Knight('W', false);
    matriz[0][2] = new Bishop('W', false);
    matriz[0][3] = new King('W', false);
    matriz[0][4] = new Queen('W', false);
    matriz[0][5] = new Bishop('W', false);
    matriz[0][6] = new Knight('W', false);
    matriz[0][7] = new Rook('W', false);
        
}

void Board::Print(){
	int aux = 1;
    std::cout << std::endl << "   -----------------------------------------" << std::endl;
    for(int lin=0; lin<8; lin++){ //MUDEI
        for(int col=0; col<8; col++){ //MUDEI
            if(col==0){
                std::cout << " " << aux << " | ";
				aux++;
            }
            if( matriz[lin][col] == 0 )
                std::cout << "   | ";
            else
                std::cout << (matriz[lin][col])->GetColor() << (matriz[lin][col])->GetPiece() << " | ";
        }
        std::cout << std::endl;
        std::cout << "   -----------------------------------------" << std::endl;		
    }
	std::cout << "   ";
	for (int col = 0; col < 8; col++) {
		std::cout << "  " << static_cast<char>(97 + col) << "  ";
	}
	std::cout << " " << std::endl;
}

bool Board::Movement(int LinI, int ColI, int LinF, int ColF, char jogador){

	if (LinI == LinF && ColI == ColF) {
		return false;
	}

    Piece* atual = matriz[LinI][ColI];

    if(atual != 0 && atual->GetColor()==jogador){

        //confiro se a posicao final eh valida
        if( atual->IsActionLegal(LinI, ColI, LinF, ColF, matriz) ){

			Piece* temp = 0;

			//movimentacao especial no caso do roque
			if (atual->GetPiece()=='K' && Roque(LinI, ColI, LinF, ColF, jogador) ) {

				int ColVariacao = ColF - ColI;
				int Passo = (ColVariacao > 0) ? 1 : -1;

				//mudo o rei de posicao
				temp = matriz[LinF][ColF];
				matriz[LinF][ColF] = matriz[LinI][ColI];
				matriz[LinI][ColI] = 0;
				
				//descubro a torre, e a mudo de posicao
				if (jogador == 'W' && Passo == 1) {
					matriz[LinF][ColF - Passo] = matriz[0][7];
					matriz[0][7] = 0;
				}
				else if (jogador == 'W' && Passo == -1) {
					matriz[LinF][ColF - Passo] = matriz[0][0];
					matriz[0][0] = 0;
				}
				else if (jogador == 'B' && Passo == 1) {
					matriz[LinF][ColF - Passo] = matriz[7][7];
					matriz[7][7] = 0;
				}
				else if (jogador == 'B' && Passo == -1) {
					matriz[LinF][ColF - Passo] = matriz[7][0];
					matriz[7][0] = 0;
				}
				
			}
			//movimentacao padrao, entra caso roque for falso
			else {
				temp = matriz[LinF][ColF];
				matriz[LinF][ColF] = matriz[LinI][ColI];
				matriz[LinI][ColI] = 0;
			}

			//ver se esta em xeque
			if (!IsCheck(jogador)) {
				(matriz[LinF][ColF])->SetHasMoved(true);
				return true;
			}
			//desfaz a movimentacao padrao (roque ja verifica se ha xeque, entao nao precisa desfazer)
			else {
				matriz[LinI][ColI] = matriz[LinF][ColF];
				matriz[LinF][ColF] = temp;
				return false;
			}
        }
    }
	return false;
}

bool Board::IsCheck(char time) {
	int ReiLinha = 0;
	int ReiColuna = 0;

	//percorro o tabuleiro
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			// se a posicao nao for nula
			if ( matriz[i][j] != 0) {
				// se a posicao for ocupada pelo time
				if ( (matriz[i][j])->GetColor() == time) {
					// se o rei estiver na posicao
					if ( (matriz[i][j])->GetPiece() == 'K') {
						//encontrei a posicao do rei
						ReiLinha = i;
						ReiColuna = j;
					}
				}
			}
		}
	}
	// percorro o tabuleiro novamente
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			// se a posicao nao for nula
			if ( matriz[i][j] != 0) {
				// se a posicao for ocupada pelo outro time
				if ( (matriz[i][j])->GetColor() != time) { 
					//verifico se alguem pode se mover ate o rei
					if ( (matriz[i][j])->IsActionLegal(i, j, ReiLinha, ReiColuna, matriz)) {
						std::cout << "Rei do jogador " << time << " esta em xeque." << std::endl;
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Board::IsCheck(int Linha, int Coluna, char time) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			// se a posicao nao for nula
			if (matriz[i][j] != 0) {
				// se a posicao for ocupada pelo outro time
				if ((matriz[i][j])->GetColor() != time) {
					//verifico se alguem pode se mover ate o rei
					if ((matriz[i][j])->IsActionLegal(i, j, Linha, Coluna, matriz)) {
						std::cout << "Rei do jogador " << time << " esta em xeque." << std::endl;
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Board::Roque(int LinI, int ColI, int LinF, int ColF, char jogador) {
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
			if (matriz[LinI][i] != 0)
				return false;
			else if (IsCheck(LinI, i-1, jogador))
				return false;
		}
		return true;
	}
	return false;
}

Board::~Board(){
    //desaloco as casas dinamicamente
	
    for(int lin=0; lin<8; lin++){
        for(int col=0; col<8; col++){
            delete matriz[lin][col];
            matriz[lin][col] = 0;
        }
    }
	
}
