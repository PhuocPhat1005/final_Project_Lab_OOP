#pragma once
#include "header.h"

class Board {
private:
	int width, height;
	vector<vector<int>> gameBoard;
public:
	Board();
	~Board();
	int getG(int x, int y) const;
	void ShowBorder();
	void ShowBoard();
	void ScoreBoard();
};
