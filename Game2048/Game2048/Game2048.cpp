/**
* Solution to course project #8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026

* @author --
* @idnumber ---
* @compiler VC

* <Used as a Main - holds all of the code>
*/
#include <iostream>
#include <fstream>
#include <ctime>

// Global constants

int board[10][10];
int N;
char username[101];

// declaration of functions

void mainMenu();
void StartNewGame();
void Instructions();
void Leaderboards();
void ExitGame() {};

void StartFormat();

bool MoveLeft();
bool MoveRight();
bool MoveUp();
bool MoveDown();
bool ChooseMove(char move);
void ReverseRow(int row[10]);
void ReverseColumn(int col[10]);

void GameLoop();
void CompressRowLeft(int row[10]);

bool IsBoardEqual(int board1[10][10], int board2[10][10]);
void CopyBoard(int source[10][10], int destination[10][10]);
void PrintBoard();
void PrintHeader();
void PrintControls();

void StrCopy(char dest[], const char src[]);
void SaveToLeaderboard(int movesCount);

void GenerateRandomTile();
int CheckLevelTile();
int FindMaxTileValue();

bool HandleCommands(char move, int& movesCount);
void HandleGameOver(int movesCount);
void SaveToLeaderboard(int movesCount);

int main()
{
	srand(time(0));
	

	Leaderboards();
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
			Instructions();
			break;
		case 3:
			Leaderboards();
			break;
		case 4:
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
			std::cout << board[i][j] << "\t";}
		std::cout << "\n";
	}
}

void CompressRowLeft(int row[10])
{
	int result[10] = { 0 };
	int write = 0;

	for (int i = 0; i < N; i++) {
		if (row[i] == 0)
			continue;

		if (result[write] == 0) {
			result[write] = row[i];
		}
		else if (result[write] == row[i]) {
			result[write] *= 2;
			write++;
		}
		else {
			write++;
			result[write] = row[i];
		}
	}

	for (int i = 0; i < N; i++)
		row[i] = result[i];
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

void ReverseRow(int row[10])
{
	for (int i = 0; i < N / 2; i++) {
		int tmp = row[i];
		row[i] = row[N - 1 - i];
		row[N - 1 - i] = tmp;
	}
}

void ReverseColumn(int col[10])
{
	for (int i = 0; i < N / 2; i++) {
		int tmp = col[i];
		col[i] = col[N - 1 - i];
		col[N - 1 - i] = tmp;
	}
}

bool MoveRight()
{
	int oldBoard[10][10];
	CopyBoard(board, oldBoard);

	for (int i = 0; i < N; i++) {
		ReverseRow(board[i]);
		CompressRowLeft(board[i]);
		ReverseRow(board[i]);
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

		for (int i = 0; i < N; i++)
			column[i] = board[i][j];

		ReverseColumn(column);
		CompressRowLeft(column);
		ReverseColumn(column);

		for (int i = 0; i < N; i++)
			board[i][j] = column[i];
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
}

bool HandleCommands(char move, int& movesCount) {
	if (move == 'q' || move == 'Q') {
		std::cout << "\nReturning to main menu...\n";
		return true;
	}

	if (ChooseMove(move)) {
		movesCount++;
		GenerateRandomTile();
		return false;
	}

	if (move != 'w' && move != 'a' && move != 's' && move != 'd' &&
		move != 'W' && move != 'A' && move != 'S' && move != 'D') {
		std::cout << "\nInvalid input!\n";
	}
	std::cout << "Press Enter to continue...";
	std::cin.get();

	return false;
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

		if (HandleCommands(move, movesCount))
			return;
		std::cout << "\n";
	}
}

void StrCopy(char dest[], const char src[]) {
	int i = 0;
	while (src[i] != '\0') {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int StrCmp(char a[], char b[]) {
	int i = 0;
	while (a[i] != '\0' && b[i] != '\0') {
		if (a[i] != b[i])
			return a[i] - b[i];
		i++;
	}
	return a[i] - b[i];
}

void swap(int& first, int& second) {
	int temp = first;
	first = second;
	second = temp;
}

void SwapStr(char a[], char b[]) {
	char tmp[101];
	StrCopy(tmp, a);
	StrCopy(a, b);
	StrCopy(b, tmp);
}

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
	std::cout << "Saved " << username << " to " << filename << "\n";
}



void Leaderboards() {
	std::ifstream file("4x4_leaderboard.txt");
    if (!file.is_open()) {
        return; }

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

