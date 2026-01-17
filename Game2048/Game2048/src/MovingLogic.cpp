/**
* Solution to course project #8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026

* @author --
* @idnumber ---
* @compiler VC

* <Used as header for all moving related functions>
*/



#include <iostream>
#include "../include/GameLogic.h"
#include "../include/MovingLogic.h"
#include "../include/HelperFunctions.h"


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
