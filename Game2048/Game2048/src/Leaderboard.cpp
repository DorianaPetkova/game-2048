#include <iostream>
#include "../include/Leaderboard.h"
#include <iostream>
#include <fstream>
#include "../include/GameLogic.h"

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
		filename[0] = '1';
		filename[1] = '0';
		filename[2] = 'x';
		filename[3] = '1';
		filename[4] = '0';
		filename[5] = '_';
		const char text[] = "leaderboard.txt";
		int pos = 6;
		for (int i = 0; text[i] != '\0'; i++)
			filename[pos++] = text[i];
		filename[pos] = '\0';
	}


	std::ofstream file(filename, std::ios::app);
	if (!file.is_open()) {
		std::cout << "Error opening leaderboard file!\n";
		return;
	}

	file << username << " " << FindMaxTileValue() << " " << movesCount << "\n";
	file.close();
	std::cout << "Saved " << username << "'s score!"<< "\n";
}



void Leaderboards() {
	std::ifstream file("4x4_leaderboard.txt");
	if (!file.is_open()) {
		return;
	}

	std::cout << "===== LEADERBOARD 4x4 =====\n";
	std::cout << "Name\tScore\tMoves\n";


	char line[256];
	int count = 0;
	while (file.getline(line, 256)) {
		char name[101];
		int score = 0, moves = 0;
		int i = 0, j = 0;


		while (line[i] != ' ' && line[i] != '\0' && j < 100) {
			name[j++] = line[i++];
		}
		name[j] = '\0';
		if (line[i] == ' ') i++;
		score = 0;
		while (line[i] >= '0' && line[i] <= '9') {
			score = score * 10 + (line[i] - '0');
			i++;
		}
		if (line[i] == ' ') i++;
		moves = 0;
		while (line[i] >= '0' && line[i] <= '9') {
			moves = moves * 10 + (line[i] - '0');
			i++;
		}
		std::cout << name << "\t" << score << "\t" << moves << "\n";

		count++;
		if (count >= 5) break;
	}

	file.close();
	std::cin.ignore();
	std::cin.get();
}

