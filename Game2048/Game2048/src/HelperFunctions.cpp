#include <iostream>
#include "../include/GameLogic.h"
#include "../include/HelperFunctions.h"



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