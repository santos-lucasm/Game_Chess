#include "Classes/Board.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <ostream>

int*  StringToPosition(std::string posI, std::string posF);
void AlternateTurn(char& player);
int StartMenu();
void InstructionsScreen();
void GameScreen();
void LoadGame();

int main() {
	do {
		system("cls");
		int screen = 0;
		screen = StartMenu();
		
		switch (screen){
			case 1:
				system("cls");
				InstructionsScreen();
				break;
			case 2:
				system("cls");
				GameScreen();
				break;
			case 3:
				system("cls");
				LoadGame();
				break;
			case 4:
				return 0;
			default:
				return 0;
		}
	} while (1);
}

int*  StringToPosition(std::string posI, std::string posF) {
	if (posI[0] > 104 || posI[0] < 97 || posF[0]>104 || posF[0] < 97 ||
		posI[1]>56 || posI[1] < 49 || posF[1]>56 || posF[1] < 49) {
		std::cout << "Quadrados nao existentes." << std::endl;
		return nullptr;
	}
	else if (posI.size() != 2 || posF.size() != 2) {
		std::cout << "Quadrados nao existentes." << std::endl;
		return nullptr;
	}
	else {

		int* array = new int[4];
		//int array[4] = {0, 0, 0, 0};
		array[0] = static_cast<int>(posI[0] - 97);
		array[1] = static_cast<int>(posI[1] - 49);
		array[2] = static_cast<int>(posF[0] - 97);
		array[3] = static_cast<int>(posF[1] - 49);

		return array;
	}
}

void AlternateTurn(char& player) {
	if (player == 'W') {
		player = 'B';
		return;
	}
	else {
		player = 'W';
	}
}

int StartMenu() {
	std::cout << "-------------------------" << std::endl;
	std::cout << "|   (1) - Instructions  |" << std::endl;
	std::cout << "|   (2) - New Game      |" << std::endl;
	std::cout << "|   (3) - Load Game     |" << std::endl;
	std::cout << "|   (4) - Exit          |" << std::endl;
	std::cout << "-------------------------" << std::endl;

	int option = 0;
	std::cout << "Escolha uma opcao: ";
	std::cin >> option;

	while ( (option < 1) || (option > 4) || std::cin.fail() ) {
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Entrada invalida. Por favor, digite novamente: ";
		std::cin >> option;
	}
	return static_cast<int>(option);
}

void InstructionsScreen() {
	
	std::cout << std::endl;
	std::cout << " (*)Pieces first letter indicates its color: " << std::endl;
	std::cout << "\tW: White\n\tB: Black" << std::endl;
	std::cout << " (*)Pieces second letter indicates its class: " << std::endl;
	std::cout << "\tP: Pawn\n\tR: Rook\n\tN: Knight\n\tB: Bishop\n\tK: King\n\tQ: Queen" << std::endl;
	std::cout << std::endl;

	std::cout << " (*)Moving: Enter the current location of the piece followed by a space (or enter)\nthen the final location where you want to move your piece." << std::endl;
	std::cout << " Our implementation doesn't use letters to indicate which piece is moving, just the\ninitial and final squares of each move" << std::endl;
	std::cout << " Ex: a2 a3\nEx: c5 d6" << std::endl;
	std::cout << std::endl;

	std::cout << " (*)Load a game: To load a game, rename the \"game_log.txt\" file that stays into\nthe \"Arquivos_seq\" diretory to \"load_game.txt\" and then choose the third option in the menu." << std::endl;
	std::cout << " To load games that have never been played before, the user should use the same notation as the game_log file: " << std::endl;
	std::cout << "\n MOVE_NUMBER. INITIAL_SQUARE FINAL_SQUARE (followed by a \\n)" << std::endl;
	std::cout << std::endl;
	std::cout << " En passant and promote moves are still not implemented." << std::endl;
	std::cout << std::endl << std::endl;
	system("pause");
}

void LoadGame() {
	Board tabuleiro;

	std::string posInicial;
	std::string posFinal;
	std::string aux;
	int *entradas = {};
	char jogador_turno = 'W';
	int counter = 1;
	bool token;
	std::ofstream ArqPtr("Arquivos_seq/game_log.txt", std::ios::out);
	std::ifstream LoadPtr("Arquivos_seq/load_game.txt", std::ios::in);

	if (!LoadPtr || !ArqPtr)
	{
		std::cerr << "File could not be opened" << std::endl;
		exit(1);
	}

	while ( LoadPtr >> aux >> posInicial>> posFinal ){//Loop do turno
		do {//Loop que espera um movimento valido
			do {//Loop que le o arquivo			

				entradas = StringToPosition(posInicial, posFinal);
			} while (entradas == nullptr);
			token = tabuleiro.Movement(entradas[1], entradas[0], entradas[3], entradas[2], jogador_turno);
			if (token)
				ArqPtr << counter << "." << " " << posInicial << " " << posFinal << std::endl;
		} while (!token);
		counter++;
		AlternateTurn(jogador_turno);
	}

	do {//Loop do turno	
		tabuleiro.Print();
		std::cout << std::endl << "Turno do jogador: " << jogador_turno << std::endl;

		do {//Loop que espera um movimento valido

			do {//Loop que espera uma entrada valida
				std::cout << "Input movement: ";
				std::cin >> posInicial;
				std::cin >> posFinal;
				entradas = StringToPosition(posInicial, posFinal);
			} while (entradas == nullptr);
			token = tabuleiro.Movement(entradas[1], entradas[0], entradas[3], entradas[2], jogador_turno);
			if (token)
				ArqPtr << counter << "." << " " << posInicial << " " << posFinal << std::endl;

		} while (!token);

		counter++;
		AlternateTurn(jogador_turno);
		system("cls");
	} while (1);

	tabuleiro.Print();
	AlternateTurn(jogador_turno);
	std::cout << "Jogador " << jogador_turno << " ganhou !" << std::endl;
	std::cout << std::endl << std::endl;
	system("pause");
}

void GameScreen() {

	Board tabuleiro;

	std::string posInicial;
	std::string posFinal;
	int *entradas = {};
	char jogador_turno = 'W';
	int counter = 1;
	bool token;
	std::ofstream ArqPtr("Arquivos_seq/game_log.txt", std::ios::out);

	if (!ArqPtr)
	{
		std::cerr << "File could not be opened" << std::endl;
		exit(1);
	}

	do {//Loop do turno	
		tabuleiro.Print();
		std::cout << std::endl << "Turno do jogador: " << jogador_turno << std::endl;

		do {//Loop que espera um movimento valido

			do {//Loop que espera uma entrada valida
				std::cout << "Input movement: ";
				std::cin >> posInicial;
				std::cin >> posFinal;
				entradas = StringToPosition(posInicial, posFinal);
			} while (entradas == nullptr);
			token = tabuleiro.Movement(entradas[1], entradas[0], entradas[3], entradas[2], jogador_turno);
			if (token)
				ArqPtr << counter << "." << " " << posInicial << " " << posFinal << std::endl;

		} while (!token);

		counter++;
		AlternateTurn(jogador_turno);
		system("cls");
	} while(1);

	tabuleiro.Print();
	AlternateTurn(jogador_turno);
	std::cout << "Jogador " << jogador_turno << " ganhou !" << std::endl;
	std::cout << std::endl << std::endl;
	system("pause");
}