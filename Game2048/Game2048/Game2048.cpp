/**
*
* Solution to course project #8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author --
* @idnumber ---
* @compiler VC
*
* <Used as a Main - holds all of the code>
*
*/


#include <iostream>
#include <fstream>

// Global constants

int board[10][10];
int N; // Size of the board
char username[101];

// declaration of functions

void mainMenu();
void StartNewGame() {};
void LoadGame() {};
void Instructions();
void Leaderboards() {};
void ExitGame() {};

void StartFormat();

bool MoveLeft();
bool MoveRight() { return false; } //opravi go da ne e false posle
bool MoveUp() { return false; }
bool MoveDown() { return false; }

bool IsBoardEqual(int board1[10][10], int board2[10][10]);
void CopyBoard(int source[10][10], int destination[10][10]);
void CompressRowLeft(int row[10]);
void PrintBoard();



int main()
{
	//mainMenu();

	N = 4; //NE SI SLAGAI INTA
	int test[4][4] = {
		{2, 0, 2, 4},
		{0, 4, 4, 0},
		{2, 2, 2, 2},
		{0, 0, 0, 2}
	};
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			board[i][j] = test[i][j];

	std::cout << "BeforE\n";
	PrintBoard();
	MoveLeft();
	std::cout << "\nAfter\n";
	PrintBoard();

	return 0;
}

void mainMenu()
{
	StartFormat();

	int UserChoice;
	do {
		std::cin >> UserChoice;
		while (std::cin.get() != '\n');
		std::cout << "\n";

		switch (UserChoice) {
		case 1:
			StartNewGame();
			break;
		case 2:
			LoadGame();
			break;
		case 3:
			Instructions();
			break;
		case 4:
			Leaderboards();
			break;
		case 5:
			ExitGame();
			break;
		default:
			std::cout << "Invalid choice. Please try again.\n";
			break;
		}
	} while (UserChoice != 5);
}

void StartFormat()
{
	std::cout << "\n";
	std::cout << "  -------------------\n";
	std::cout << "  |    2048 GAME    |\n";
	std::cout << "  -------------------\n\n";
	std::cout << "1. Start New Game\n";
	std::cout << "2. Load Game\n";
	std::cout << "3. Instructions\n";
	std::cout << "4. Leaderboards\n";
	std::cout << "5. Exit\n";
	std::cout << "\n  ==================\n\n";
	std::cout << "  >> ";
}

void Instructions()
{
	std::cout << "Instructions:\n";
	std::cout << "Use the w/a/s/d keys to move the tiles on the board, up, left, down and right respectfully.\n";
	std::cout << "When two tiles with the same number touch, they merge into one!\n";
	std::cout << "The goal is to create a tile with the number 2048 (or more!).\n";
	std::cout << "Good luck!\n\n";
	std::cout << "  >> ";
}

bool IsBoardEqual(int board1[10][10], int board2[10][10])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board1[i][j] != board2[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void CopyBoard(int source[10][10], int destination[10][10])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			destination[i][j] = source[i][j];
		}
	}
}

void PrintBoard() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cout << board[i][j] << "\t";
		}
		std::cout << "\n";
	}
}


void CompressRowLeft(int row[10])
{
	int temp[10] = { 0 };
	int index = 0;
	for (int j = 0; j < N; j++) {
		if (row[j] != 0) {
			temp[index++] = row[j];
		}
	}
	
	for (int j = 0; j < N - 1; j++)
	{
		if (temp[j] != 0 && temp[j] == temp[j + 1]) {
		{
			temp[j] *= 2;
			temp[j + 1] = 0;
		}
	}
		for (int j = 0; j < N; j++)
			row[j] = 0;
		index = 0;
		for (int j = 0; j < N; j++) {
			if (temp[j] != 0) {
				row[index++] = temp[j];
			}
		}
	}
	
}
bool MoveLeft()
{
	int oldBoard[10][10];
	CopyBoard(board, oldBoard);
	for (int i = 0; i < N; i++) {
		CompressRowLeft(board[i]);
	}

	return !IsBoardEqual(board, oldBoard);
}

