/**
* Solution to course project #8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026

* @author --
* @idnumber ---
* @compiler VC

* <Used as header for all game structure related functions>
*/

#include <iostream>
#include "../include/GameLogic.h"
#include "../include/MovingLogic.h"
#include "../include/HelperFunctions.h"
#include "../include/Leaderboard.h"
#include "../include/Design.h"

int board[10][10];
int N;
char username[101];

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
			Instructions();
			break;
		case 3:
			Leaderboards();
			break;
		case 4:
			std::cout << "Exiting..";
			exit(0);
			break;
		default:
			std::cout << "Invalid choice. Please try again.\n";
			break;
		}
	} while (UserChoice != 5);
}

int FindMaxTileValue()
{
	int maxTileValue = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] > maxTileValue) {
				maxTileValue = board[i][j];
			}
		}
	}
	return maxTileValue;
}

int CheckLevelTile()
{
	int maxTileValue = FindMaxTileValue();
	int value;
	int r = rand() % 100;

	if (maxTileValue >= 512)
	{
		if (r < 50)
			value = 4;
		else if (r < 90)
			value = 2;
		else
			value = 8;
	}
	else {
		if (r < 90)
			value = 2;
		else
			value = 4;
	}
	return value;
}

void GenerateRandomTile()
{
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

	int value = CheckLevelTile();
	int pos = rand() % emptyCount;
	board[emptyCells[pos][0]][emptyCells[pos][1]] = value;
}

void StartNewGame() {
	std::cout << "Enter username: ";
	std::cin.getline(username, 101);

	do {
		std::cout << "Enter board size (4-10): ";
		std::cin >> N;
		std::cin.ignore();

		if (N < 4 || N > 10) {
			std::cout << "Invalid size! Please choose between 4 and 10.\n";
		}
	} while (N < 4 || N > 10);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = 0;
		}
	}

	GenerateRandomTile();
	GenerateRandomTile();
	GameLoop();
}

bool CheckGameOver() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == 0) {
				return false;
			}
		}
	}

	int tempBoard[10][10];
	CopyBoard(board, tempBoard);

	if (MoveLeft()) {
		CopyBoard(tempBoard, board);
		return false;
	}
	if (MoveRight()) {
		CopyBoard(tempBoard, board);
		return false;
	}
	if (MoveUp()) {
		CopyBoard(tempBoard, board);
		return false;
	}
	if (MoveDown()) {
		CopyBoard(tempBoard, board);
		return false;
	}

	CopyBoard(tempBoard, board);
	return true;
}

void HandleGameOver(int movesCount) {
	std::cout << "\n GAME OVER! No moves possible.\n";
	std::cout << "Final Score: " << FindMaxTileValue() << "\n";
	SaveToLeaderboard(movesCount);
	std::cout << "\nPress Enter to return to main menu...";
	std::cin.ignore();
	std::cin.get();

	mainMenu();
}

void GameLoop() {
    char move;
	int movesCount = 0;
	PrintHeader();

	while (true) {
		PrintBoard();
		std::cout << "\nMax Tile: " << FindMaxTileValue()
			<< "\nMoves: " << movesCount << "\n";
		if (CheckGameOver()) {
			HandleGameOver(movesCount);
			return;
		}

		PrintControls();
		std::cin >> move;
		std::cin.ignore();

		if (HandleCommands(move, movesCount)) {
			std::cout << "Returning to main menu...(press enter)\n";
			std::cin.get();
			mainMenu();
			return;
		}

		std::cout << "\n";
	}
}

bool HandleCommands(char move, int& movesCount) {

	
	
	if (move == 'q' || move == 'Q') {
		char choice;
		std::cout << "Are you sure you want to quit? (y/n): ";
		std::cin >> choice;
		std::cin.ignore();

		if (choice == 'y' || choice == 'Y') {
			SaveToLeaderboard(movesCount);
			return true;
		}
		else {
			std::cout << "Continuing game...\n";
			return false;  
		}
	}

	bool moved = ChooseMove(move);
	if (moved) {
		movesCount++;
		GenerateRandomTile();
		return false;
	}
	else {
		if (move == 'w' || move == 'a' || move == 's' || move == 'd' ||
			move == 'W' || move == 'A' || move == 'S' || move == 'D') {
			std::cout << "\nNothing happened! Try something different?\n";
		}
		else {
			std::cout << "\nInvalid input! Use w/a/s/d keys.\n";
		}
	}
	std::cout << "Press Enter to continue...";
	std::cin.get();

	return false;
}

