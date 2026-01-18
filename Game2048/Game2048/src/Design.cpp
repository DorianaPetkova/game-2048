/**
* Solution to course project #8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026

* @author Doriana Petkova
* @idnumber 0MI0600627
* @compiler VC

* <Used as header for all design related functions>
*/

#include <iostream>
#include "../include/GameLogic.h"
#include "../include/Design.h"

void StartFormat()
{
	std::cout << "\n";
	std::cout << "  -------------------\n";
	std::cout << "  |    2048 GAME    |\n";
	std::cout << "  -------------------\n\n";
	std::cout << "1. Start New Game\n";
	std::cout << "2. Instructions\n";
	std::cout << "3. Leaderboards\n";
	std::cout << "4. Exit\n";
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

void PrintHeader()
{
	std::cout << "\n\n";
	std::cout << "=== 2048 GAME ===\n";
	std::cout << "Player: " << username << "  |  Board: " << N << "x" << N << "\n";
	std::cout << "===================================\n\n";
}

void PrintControls()
{
	std::cout << "\n===================================\n";
	std::cout << "Controls:\n";
	std::cout << "  w = Move Up\n";
	std::cout << "  a = Move Left\n";
	std::cout << "  s = Move Down\n";
	std::cout << "  d = Move Right\n";
	std::cout << "  q = Quit to Menu\n";
	std::cout << "===================================\n";
	std::cout << "Enter move: ";
}

void ShowNoLeaderboardMessage() {

	std::cout << "No leaderboard for this board size.\n";
	std::cout << "Press Enter to return to main menu.\n";
	std::cin.ignore();
	std::cin.get();
	mainMenu();
}

void PrintLeaderboardHeader(int boardSize) {
	std::cout << "\n===== LEADERBOARD "
		<< boardSize << "x" << boardSize << " =====\n";
	std::cout << "Number\tName\tScore\tMoves\n";

}