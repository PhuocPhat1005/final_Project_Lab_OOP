#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <cmath>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;
#define block (char)219<<(char)219;
const int top = 5;
const int bottom = top + 1 + 20;

class Coordinates;
void gotoxy(int x, int y);
void gotoxyPiece(Coordinates co);
class Board;
class Piece;

class Coordinates {
public:
	int x, y;
	Coordinates(int _x = 0, int _y = 0);
};

void clearScreen();