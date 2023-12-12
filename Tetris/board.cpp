#include "board.h"
#include "piece.h"

Board::Board() {
	width = 10;
	height = 20;
	for (int i = 0; i < height; ++i) {
		vector<int> v(width, 0);
		gameBoard.push_back(v);
	}
}
Board::~Board() {
	for (int i = 0; i < height; ++i) {
		gameBoard[i].clear();
	}
	gameBoard.clear();
}
int Board::getG(int x, int y) const {
	x = (x - 1) / 2;
	y = y - 1 - top;
	if (y < 0)
		return 0;
	if (x < 0 || x >= width || y >= height)
		return -1;
	return gameBoard[y][x];
}
void Board::ShowBorder() {
	gotoxy(0, top);
	cout << (char)201;
	for (int i = 0; i < width * 2; ++i) {
		gotoxy(1 + i, top);
		cout << (char)205;
	}
	gotoxy(1 + width * 2, top);
	cout << (char)187;

	for (int i = 0; i < height; ++i) {
		gotoxy(0, top + 1 + i);
		cout << (char)186;
		gotoxy(1 + width * 2, top + 1 + i);
		cout << (char)186;
	}

	gotoxy(0, bottom);
	cout << (char)200;
	for (int i = 0; i < width * 2; ++i) {
		gotoxy(1 + i, bottom);
		cout << (char)205;
	}
	gotoxy(1 + width * 2, bottom);
	cout << (char)188;
}
void Board::ShowBoard() {
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			gotoxy(1 + 2 * i, 1 + top + j);
			if (gameBoard[j][i] != 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gameBoard[j][i]);
				cout << block;
			}
			else
				cout << "  ";
		}
	}
}
void Board::ShowQueue(vector<Piece*> p) {

}
void Board::AddBoard(Piece* p) {
	for (int i = 0; i < 4; ++i) {
		int _x = (p->getCMove(i).x - 1) / 2;
		int _y = p->getCMove(i).y - 1 - top;
		gameBoard[_y][_x] = p->getColor();
	}
}
bool Board::EndBoard(Piece* p) {
	for (int i = 0; i < 4; ++i) {
		if (p->getCMove(i).y <= top)
			return true;
	}
	return false;
}
void Board::ScoreBoard() {
	vector<vector<int>> gameBoard2(height, vector<int>(width, 0));
	bool fullRow = true;
	int countH = height - 1;
	for (int j = height - 1; (j >= 0) && (countH >= 0); --j) {
		fullRow = true;
		for (int i = 0; i < width; ++i) {
			fullRow = true;
			if (gameBoard[j][i] == 0) {
				fullRow = false;
				i = width;
			}
		}
		if (!fullRow) {
			gameBoard2[countH--] = gameBoard[j];
		}
	}
	gameBoard = gameBoard2;
}