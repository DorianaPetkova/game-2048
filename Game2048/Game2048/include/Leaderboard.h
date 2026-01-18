#ifndef LEADERBOARD_H
#define LDEARBOARD_H

void Leaderboards();
void SaveToLeaderboard(int movesCount);
int ChooseBoard();
void SortLeaderboard(char names[][101], int scores[], int moves[], int count);

void BuildLeaderboardFilename(int boardSize, char filename[]);
int LoadLeaderboard(
	const char filename[],
	char names[][101],
	int scores[],
	int moves[]
);

void WriteLeaderboard(
	const char filename[],
	char names[][101],
	int scores[],
	int moves[],
	int count
);

void UpdatePlayerResult(
	char names[][101],
	int scores[],
	int moves[],
	int& count,
	int newScore,
	int newMoves
);

void PrintLeaderboardEntries(
	char names[][101],
	int scores[],
	int moves[],
	int count
);

#endif