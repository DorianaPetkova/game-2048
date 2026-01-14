#ifndef MOVINGLOGIC_H
#define MOVINGLOGIC_H

bool MoveLeft();
bool MoveRight();
bool MoveUp();
bool MoveDown();
bool ChooseMove(char move);
void CompressRowLeft(int row[10]);

#endif