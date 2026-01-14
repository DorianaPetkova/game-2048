#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

void ReverseRow(int row[10]);
void ReverseColumn(int col[10]);

bool IsBoardEqual(int board1[10][10], int board2[10][10]);
void CopyBoard(int source[10][10], int destination[10][10]);
void PrintBoard();

void StrCopy(char dest[], const char src[]);
int StrCmp(char a[], char b[]);
void swap(int& first, int& second);
void SwapStr(char a[], char b[]);

#endif