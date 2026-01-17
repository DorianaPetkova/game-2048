/**
* Solution to course project #8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026

* @author --
* @idnumber ---
* @compiler VC

* <Used as header for all leaderboard related functions>
*/


#include <iostream>
#include "../include/Leaderboard.h"
#include <iostream>
#include <fstream>
#include "../include/GameLogic.h"
#include "../include/HelperFunctions.h"

void SaveToLeaderboard(int movesCount)
{
	char filename[32];
	if (N < 10) {
		filename[0] = '0' + N;
		filename[1] = 'x';
		filename[2] = '0' + N;
		filename[3] = '_';
		const char text[] = "leaderboard.txt";
		int pos = 4;
		for (int i = 0; text[i] != '\0'; i++)
			filename[pos++] = text[i];
		filename[pos] = '\0';
	}
	else {
		const char text[] = "10x10_leaderboard.txt";
		int i = 0;
		while (text[i] != '\0') {
			filename[i] = text[i];
			i++;
		}
		filename[i] = '\0';
	}
	char names[100][101];
	int scores[100];
	int moves[100];
	int count = 0;

	std::ifstream in(filename);
	while (in >> names[count] >> scores[count] >> moves[count]) {
		count++;
	}
	in.close();

	int newScore = FindMaxTileValue();
	bool found = false;

	// 2️⃣ Update if username exists
	for (int i = 0; i < count; i++) {
		if (StrCmp(names[i], username) == 0) {
			if (newScore > scores[i]) {
				scores[i] = newScore;
				moves[i] = movesCount;
			}
			found = true;
			break;
		}
	}
	if (!found) {
		StrCopy(names[count], username);
		scores[count] = newScore;
		moves[count] = movesCount;
		count++;
	}

	std::ofstream out(filename);
	for (int i = 0; i < count; i++) {
		out << names[i] << " " << scores[i] << " " << moves[i] << "\n";
	}
	out.close();

	std::cout << "Saved " << username << "'s score!\n";
}

int ChooseBoard()
{
	std:: cout<<"Please select a board you'd like to see the results for:"
		<<"\n1. 4x4"
		<<"\n2. 5x5"
		<<"\n3. 6x6"
		<<"\n4. 7x7"
		<<"\n5. 8x8"
		<<"\n6. 9x9"
		<<"\n7. 10x10"
		<< "\nYour choice(number, not row size): ";
	int choice;
	std::cin >> choice;
	return choice+3;
}



void Leaderboards() {

	int boardSize = ChooseBoard();
	char filename[64];

	if (boardSize < 10) {
		filename[0] = '0' + boardSize;
		filename[1] = 'x';
		filename[2] = '0' + boardSize;
		filename[3] = '_';
		const char text[] = "leaderboard.txt";
		int pos = 4;
		for (int i = 0; text[i] != '\0'; i++)
			filename[pos++] = text[i];
		filename[pos] = '\0';
	}
	else {
		const char text[] = "10x10_leaderboard.txt";
		int i = 0;
		while (text[i] != '\0') {
			filename[i] = text[i];
			i++;
		}
		filename[i] = '\0';
	}

	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cout << "No leaderboard for this board size.\n";
		std::cout << "Press enter to return to main menu.\n\n";
		std::cin.ignore();
		std::cin.get();
		mainMenu();
		return;
	}

	char names[100][101];
	int scores[100];
	int moves[100];
	int count = 0;

	while (file >> names[count] >> scores[count] >> moves[count]) {
		count++;
		if (count >= 100) break;
	}
	file.close();

	SortLeaderboard(names, scores, moves, count);

	std::cout << "\n===== LEADERBOARD "
		<< boardSize << "x" << boardSize << " =====\n";
	std::cout << "Number\tName\tScore\tMoves\n";
	int limit = (count < 5) ? count : 5;
	for (int i = 0; i < limit; i++) {
		std::cout << (i + 1) << ".\t"
			<< names[i] << "\t"
			<< scores[i] << "\t"
			<< moves[i] << "\n";
	}

	std::cout << "\nPress Enter to return to main menu...";
	std::cin.ignore();
	std::cin.get();

	mainMenu();
	
}

void SortLeaderboard(char names[][101], int scores[], int moves[], int count)
{
	for (int i = 0; i < count - 1; i++) {
		for (int j = i + 1; j < count; j++) {

			bool shouldSwap = false;

			if (scores[j] > scores[i]) {
				shouldSwap = true;
			}
			else if (scores[j] == scores[i] && moves[j] < moves[i]) {
				shouldSwap = true;
			}

			if (shouldSwap) {
				swap(scores[i], scores[j]);
				swap(moves[i], moves[j]);
				SwapStr(names[i], names[j]);
			}
		}
	}
}
