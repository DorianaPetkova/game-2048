#ifndef LEADERBOARD_H
#define LDEARBOARD_H

void Leaderboards();
void SaveToLeaderboard(int movesCount);
int ChooseBoard();
void SortLeaderboard(char names[][101], int scores[], int moves[], int count);

#endif