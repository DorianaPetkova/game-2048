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
void SaveGame() {};
void Instructions();
void Leaderboards() {};
void ExitGame() {};

void StartFormat();

bool MoveLeft();
bool MoveRight();
bool MoveUp();
bool MoveDown();
bool ChooseMove(char move);

bool IsBoardEqual(int board1[10][10], int board2[10][10]);
void CopyBoard(int source[10][10], int destination[10][10]);
void CompressRowLeft(int row[10]);
void PrintBoard();

void GenerateRandomTile();
void CheckLevelTile() {};


int main()
{
	//mainMenu();


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

bool MoveRight()
{
	int oldBoard[10][10];
	CopyBoard(board, oldBoard);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N / 2; j++) {
			int tmp = board[i][j];
			board[i][j] = board[i][N - 1 - j];
			board[i][N - 1 - j] = tmp;
		}

			CompressRowLeft(board[i]);

		for (int j = 0; j < N / 2; j++) {
			int tmp = board[i][j];
			board[i][j] = board[i][N - 1 - j];
			board[i][N - 1 - j] = tmp;
		}
	}
	return !IsBoardEqual(board, oldBoard);
}

bool MoveUp()
{
	int oldBoard[10][10];
	CopyBoard(board, oldBoard);
	for (int j = 0; j < N; j++) {
		int column[10];
		for (int i = 0; i < N; i++) {
			column[i] = board[i][j];
		}
		CompressRowLeft(column);
		for (int i = 0; i < N; i++) {
			board[i][j] = column[i];
		}
	}
	return !IsBoardEqual(board, oldBoard);
}

bool MoveDown()
{
	int oldBoard[10][10];
	CopyBoard(board, oldBoard);
	for (int j = 0; j < N; j++) {
		int column[10];
		for (int i = 0; i < N; i++) {
			column[i] = board[i][j];
		}
		for (int i = 0; i < N / 2; i++) {
			int tmp = column[i];
			column[i] = column[N - 1 - i];
			column[N - 1 - i] = tmp;
		}
		CompressRowLeft(column);
		for (int i = 0; i < N / 2; i++) {
			int tmp = column[i];
			column[i] = column[N - 1 - i];
			column[N - 1 - i] = tmp;
		}
		for (int i = 0; i < N; i++) {
			board[i][j] = column[i];
		}
	}
	return !IsBoardEqual(board, oldBoard);
}

bool ChooseMove(char move)
{
	switch (move) {
	case 'a':
		return MoveLeft();
	case 'd':
		return MoveRight();
	case 'w':
		return MoveUp();
	case 's':
		return MoveDown();
	default:
		std::cout << "Invalid move. Please use w/a/s/d keys.\n";
		return false;
	}
}

void GenerateRandomTile()
{
	srand(time(0));

	int emptyCells[100][2];
	int emptyCount = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == 0) {
				emptyCells[emptyCount][0] = i;
				emptyCells[emptyCount][1] = j;
				emptyCount++;
			}
		}
	}
	if (emptyCount == 0) {
		return;
	}

	int maxTileValue = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] > maxTileValue) {
				maxTileValue = board[i][j];
			}
		}

	}
	int value;
	int r = rand() % 100;

	if (maxTileValue >= 512)
	{
		if(r<50)
			value = 4;
		else if(r<90)
			value = 2;
		else value = 8;
	}
	else {
		if (r < 90)
			value = 2;
		else
			value = 4;
	}

	int pos = rand() % emptyCount;
	board[emptyCells[pos][0]][emptyCells[pos][1]] = value;
}