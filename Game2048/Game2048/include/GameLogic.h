#ifndef GAMELOGIC_H
#define GAMELOGIC_H

extern int board[10][10];
extern int N;
extern char username[101];

void mainMenu();
void StartNewGame();
void GameLoop();


void GenerateRandomTile();
int CheckLevelTile();
int FindMaxTileValue();

bool HandleCommands(char move, int& movesCount);
void HandleGameOver(int movesCount);
bool CheckGameOver();

#endif
