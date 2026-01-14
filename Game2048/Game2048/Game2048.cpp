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
#include <Windows.h>

#include "./include/GameLogic.h"
#include "./include/MovingLogic.h"
#include "./include/Leaderboard.h"
#include "./include/HelperFunctions.h"
#include "./include/Design.h"


int main()
{
	srand(time(0));
	
	mainMenu();
	return 0;
}