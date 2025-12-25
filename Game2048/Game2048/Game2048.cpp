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


int main()
{
	mainMenu();

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