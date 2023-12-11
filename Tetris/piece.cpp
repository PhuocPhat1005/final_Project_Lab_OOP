#include "piece.h"
#include "board.h"

Piece::~Piece() {
	delete[] c;
}
Coordinates* Piece::getCMove() {
	Coordinates* result = new Coordinates[4];
	for (int i = 0; i < 4; ++i) {
		result[i] = c[i];
	}
	return result;
}
bool Piece::BottomCheck(const Board& b) {
	for (int i = 0; i < 4; ++i) {
		if (b.getG(c[i].x, c[i].y + 1) != 0) {
			Sleep(1000);
			return true;
		}
	}
	return false;
}
void Piece::RotateRight() {
	state++;
	state %= 4;
	this->Show();
}
void Piece::RotateLeft() {
	state += 3;
	state %= 4;
	this->Show();
}
void Piece::MoveRight(const Board& b) {
	for (int i = 0; i < 4; ++i) {
		if (b.getG(c[i].x + 2, c[i].y) != 0)
			return;
	}
	this->UnShow();
	for (int i = 0; i < 4; ++i) {
		c[i].x += 2;
	}
	this->Show();
}
void Piece::MoveLeft(const Board& b) {
	for (int i = 0; i < 4; ++i) {
		if (b.getG(c[i].x - 2, c[i].y) != 0)
			return;
	}
	this->UnShow();
	for (int i = 0; i < 4; ++i) {
		c[i].x -= 2;
	}
	this->Show();
}
void Piece::MoveDown(const Board& b) {
	for (int i = 0; i < 4; ++i) {
		if (b.getG(c[i].x, c[i].y + 1) != 0)
			return;
	}
	this->UnShow();
	for (int i = 0; i < 4; ++i) {
		c[i].y++;
	}
	this->Show();
}
void Piece::MoveDownTime(const Board& b, time_t& originalTime) {
	time_t nowTime = time(0);
	double timeLeft = difftime(nowTime, originalTime);
	if (timeLeft == 1.0) {
		originalTime = time(0);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		for (int i = 0; i < 4; ++i) {
			if (b.getG(c[i].x, c[i].y + 1) != 0)
				return;
		}
		this->UnShow();
		for (int i = 0; i < 4; ++i) {
			c[i].y++;
		}
		this->Show();
	}
}
void Piece::UnShow() {
	for (int i = 0; i < 4; ++i) {
		gotoxyPiece(c[i]);
		if (c[i].y > top)
			cout << "  ";
	}
}


PieceI::PieceI() {
	c = new Coordinates[4];
	color = 11; //Bright cyan
	state = 0;
	c[0] = { 11, top + 1 };
	c[1] = { 11, top + 2 };
	c[2] = { 11, top + 3 };
	c[3] = { 11, top + 4 };
}
bool PieceI::RotateCheck(const Board& b, int rot) {
	int s = state + rot;
	s %= 4;
	if (s % 2 == 0) {
		for (int i = 0; i < 4; ++i) {
			if (b.getG(c[0].x, c[0].y - i) != 0)
				return false;
		}
	}
	else {
		for (int i = 0; i < 4; ++i) {
			if (b.getG(c[0].x - 2 + 2 * i, c[0].y) != 0)
				return false;
		}
	}
	return true;
}
void PieceI::Show() {
	UnShow();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	Coordinates cMove = c[0];
	if (state % 2 == 0) {
		c[0] = { cMove.x, cMove.y };
		c[1] = { cMove.x, cMove.y - 1 };
		c[2] = { cMove.x, cMove.y - 2 };
		c[3] = { cMove.x, cMove.y - 3 };
	}
	else {
		c[0] = { cMove.x, cMove.y };
		c[1] = { cMove.x - 2, cMove.y };
		c[2] = { cMove.x + 2, cMove.y };
		c[3] = { cMove.x + 4, cMove.y };
	}
	for (int i = 0; i < 4; ++i) {
		gotoxyPiece(c[i]);
		if (c[i].y > top && c[i].y < bottom)
			cout << block;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


PieceO::PieceO() {
	c = new Coordinates[4];
	color = 14; //Yellow
	state = 0;
	c[0] = { 9, top + 1 };
	c[1] = { 11, top + 1 };
	c[2] = { 9, top };
	c[3] = { 11, top };
}
bool PieceO::RotateCheck(const Board& b, int rot) {
	return true;
}
void PieceO::Show() {
	UnShow();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	Coordinates cMove = c[0];
	c[0] = { cMove.x, cMove.y };
	c[1] = { cMove.x + 2, cMove.y };
	c[2] = { cMove.x, cMove.y - 1 };
	c[3] = { cMove.x + 2, cMove.y - 1 };
	for (int i = 0; i < 4; ++i) {
		gotoxyPiece(c[i]);
		if (c[i].y > top && c[i].y < bottom)
			cout << block;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


PieceJ::PieceJ() {
	c = new Coordinates[4];
	color = 1; //Blue
	state = 0;
	c[0] = { 9, top + 1 };
	c[1] = { 11, top + 1 };
	c[2] = { 11, top };
	c[3] = { 11, top - 1 };
}
bool PieceJ::RotateCheck(const Board& b, int rot) {
	int s = state + rot;
	s %= 4;
	if (s == 0) {
		if (b.getG(c[0].x, c[0].y) != 0 || b.getG(c[0].x + 2, c[0].y) != 0 || b.getG(c[0].x + 2, c[0].y - 1) != 0 || b.getG(c[0].x + 2, c[0].y - 2) != 0)
			return false;
	}
	else if (s == 1) {
		if (b.getG(c[0].x, c[0].y) != 0 || b.getG(c[0].x + 2, c[0].y) != 0 || b.getG(c[0].x + 4, c[0].y) != 0 || b.getG(c[0].x, c[0].y - 1) != 0)
			return false;
	}
	else if (s == 2) {
		if (b.getG(c[0].x, c[0].y) != 0 || b.getG(c[0].x, c[0].y - 1) != 0 || b.getG(c[0].x, c[0].y - 2) != 0 || b.getG(c[0].x + 2, c[0].y - 2) != 0)
			return false;
	}
	else if (s == 3) {
		if (b.getG(c[0].x, c[0].y) != 0 || b.getG(c[0].x, c[0].y - 1) != 0 || b.getG(c[0].x - 2, c[0].y - 1) != 0 || b.getG(c[0].x - 4, c[0].y - 1) != 0)
			return false;
	}
	return true;
}
void PieceJ::Show() {
	UnShow();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	Coordinates cMove = c[0];
	if (state == 0) {
		c[0] = { cMove.x, cMove.y };
		c[1] = { cMove.x + 2, cMove.y };
		c[2] = { cMove.x + 2, cMove.y - 1 };
		c[3] = { cMove.x + 2, cMove.y - 2 };
	}
	else if (state == 1) {
		c[0] = { cMove.x, cMove.y };
		c[1] = { cMove.x + 2, cMove.y };
		c[2] = { cMove.x + 4, cMove.y };
		c[3] = { cMove.x, cMove.y - 1 };
	}
	else if (state == 2) {
		c[0] = { cMove.x, cMove.y };
		c[1] = { cMove.x, cMove.y - 1 };
		c[2] = { cMove.x, cMove.y - 2 };
		c[3] = { cMove.x + 2, cMove.y - 2 };
	}
	else if (state == 3) {
		c[0] = { cMove.x, cMove.y };
		c[1] = { cMove.x, cMove.y - 1 };
		c[2] = { cMove.x - 2, cMove.y - 1 };
		c[3] = { cMove.x - 4, cMove.y - 1 };
	}
	for (int i = 0; i < 4; ++i) {
		gotoxyPiece(c[i]);
		if (c[i].y > top && c[i].y < bottom)
			cout << block;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


PieceL::PieceL() {
	c = new Coordinates[4];
	color = 12; //Bright red
	state = 0;
	c[0] = { 11, top + 1 };
	c[1] = { 9, top + 1 };
	c[2] = { 9, top };
	c[3] = { 9, top - 1 };
}
bool PieceL::RotateCheck(const Board& b, int rot) {
	int s = state + rot;
	s %= 4;
	if (s == 0) {
		if (b.getG(c[0].x, c[0].y) != 0 || b.getG(c[0].x - 2, c[0].y) != 0 || b.getG(c[0].x - 2, c[0].y - 1) != 0 || b.getG(c[0].x - 2, c[0].y - 2) != 0)
			return false;
	}
	else if (s == 1) {
		if (b.getG(c[0].x, c[0].y) != 0 || b.getG(c[0].x, c[0].y - 1) != 0 || b.getG(c[0].x + 2, c[0].y - 1) != 0 || b.getG(c[0].x + 4, c[0].y - 1) != 0)
			return false;
	}
	else if (s == 2) {
		if (b.getG(c[0].x, c[0].y) != 0 || b.getG(c[0].x, c[0].y - 1) != 0 || b.getG(c[0].x, c[0].y - 2) != 0 || b.getG(c[0].x - 2, c[0].y - 2) != 0)
			return false;
	}
	else if (s == 3) {
		if (b.getG(c[0].x, c[0].y) != 0 || b.getG(c[0].x - 2, c[0].y) != 0 || b.getG(c[0].x - 4, c[0].y) != 0 || b.getG(c[0].x, c[0].y - 1) != 0)
			return false;
	}
	return true;
}
void PieceL::Show() {
	UnShow();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	Coordinates cMove = c[0];
	if (state == 0) {
		c[0] = { cMove.x, cMove.y };
		c[1] = { cMove.x - 2, cMove.y };
		c[2] = { cMove.x - 2, cMove.y - 1 };
		c[3] = { cMove.x - 2, cMove.y - 2 };
	}
	else if (state == 1) {
		c[0] = { cMove.x, cMove.y };
		c[1] = { cMove.x, cMove.y - 1 };
		c[2] = { cMove.x + 2, cMove.y - 1 };
		c[3] = { cMove.x + 4, cMove.y - 1 };
	}
	else if (state == 2) {
		c[0] = { cMove.x, cMove.y };
		c[1] = { cMove.x, cMove.y - 1 };
		c[2] = { cMove.x, cMove.y - 2 };
		c[3] = { cMove.x - 2, cMove.y - 2 };
	}
	else if (state == 3) {
		c[0] = { cMove.x, cMove.y };
		c[1] = { cMove.x - 2, cMove.y };
		c[2] = { cMove.x - 4, cMove.y };
		c[3] = { cMove.x, cMove.y - 1 };
	}
	for (int i = 0; i < 4; ++i) {
		gotoxyPiece(c[i]);
		if (c[i].y > top && c[i].y < bottom)
			cout << block;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


PieceT::PieceT() {
	c = new Coordinates[4];
	color = 5; //Purple
	state = 0;
	c[0] = { 11, top + 1 };
	c[1] = { 9, top + 1 };
	c[2] = { 13, top + 1 };
	c[3] = { 11, top };
}
bool PieceT::RotateCheck(const Board& b, int rot) {
	int s = state + rot;
	s %= 4;
	if (s == 0) {
		if (b.getG(c[0].x, c[0].y) != 0 || b.getG(c[0].x - 2, c[0].y) != 0 || b.getG(c[0].x + 2, c[0].y) != 0 || b.getG(c[0].x, c[0].y - 1) != 0)
			return false;
	}
	else if (s == 1) {
		if (b.getG(c[0].x, c[0].y) != 0 || b.getG(c[0].x, c[0].y - 1) != 0 || b.getG(c[0].x, c[0].y - 2) != 0 || b.getG(c[0].x + 2, c[0].y - 1) != 0)
			return false;
	}
	else if (s == 2) {
		if (b.getG(c[0].x, c[0].y) != 0 || b.getG(c[0].x - 2, c[0].y - 1) != 0 || b.getG(c[0].x + 2, c[0].y - 1) != 0 || b.getG(c[0].x, c[0].y - 1) != 0)
			return false;
	}
	else if (s == 3) {
		if (b.getG(c[0].x, c[0].y) != 0 || b.getG(c[0].x, c[0].y - 1) != 0 || b.getG(c[0].x, c[0].y - 2) != 0 || b.getG(c[0].x - 2, c[0].y - 1) != 0)
			return false;
	}
	return true;
}
void PieceT::Show() {
	UnShow();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	Coordinates cMove = c[0];
	if (state == 0) {
		c[0] = { cMove.x, cMove.y };
		c[1] = { cMove.x - 2, cMove.y };
		c[2] = { cMove.x + 2, cMove.y };
		c[3] = { cMove.x, cMove.y - 1 };
	}
	else if (state == 1) {
		c[0] = { cMove.x, cMove.y };
		c[1] = { cMove.x, cMove.y - 1 };
		c[2] = { cMove.x, cMove.y - 2 };
		c[3] = { cMove.x + 2, cMove.y - 1 };
	}
	else if (state == 2) {
		c[0] = { cMove.x, cMove.y };
		c[1] = { cMove.x - 2, cMove.y - 1 };
		c[2] = { cMove.x + 2, cMove.y - 1 };
		c[3] = { cMove.x, cMove.y - 1 };
	}
	else if (state == 3) {
		c[0] = { cMove.x, cMove.y };
		c[1] = { cMove.x, cMove.y - 1 };
		c[2] = { cMove.x, cMove.y - 2 };
		c[3] = { cMove.x - 2, cMove.y - 1 };
	}
	for (int i = 0; i < 4; ++i) {
		gotoxyPiece(c[i]);
		if (c[i].y > top && c[i].y < bottom)
			cout << block;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


PieceZ::PieceZ() {
	c = new Coordinates[4];
	color = 4; //Red
	state = 0;
	c[0] = { 11, top + 1 };
	c[1] = { 9, top + 1 };
	c[2] = { 11, top };
	c[3] = { 13, top };
}
bool PieceZ::RotateCheck(const Board& b, int rot) {
	int s = state + rot;
	s %= 4;
	if (s % 2 == 0) {
		if (b.getG(c[0].x, c[0].y) != 0 || b.getG(c[0].x - 2, c[0].y) != 0 || b.getG(c[0].x, c[0].y - 1) != 0 || b.getG(c[0].x + 2, c[0].y - 1) != 0)
			return false;
	}
	else if (s % 2 == 1) {
		if (b.getG(c[0].x, c[0].y) != 0 || b.getG(c[0].x, c[0].y - 1) != 0 || b.getG(c[0].x - 2, c[0].y - 1) != 0 || b.getG(c[0].x - 2, c[0].y - 2) != 0)
			return false;
	}
	return true;
}
void PieceZ::Show() {
	UnShow();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	Coordinates cMove = c[0];
	if (state % 2 == 0) {
		c[0] = { cMove.x, cMove.y };
		c[1] = { cMove.x - 2, cMove.y };
		c[2] = { cMove.x, cMove.y - 1 };
		c[3] = { cMove.x + 2, cMove.y - 1 };
	}
	else if (state % 2 == 1) {
		c[0] = { cMove.x, cMove.y };
		c[1] = { cMove.x, cMove.y - 1 };
		c[2] = { cMove.x - 2, cMove.y - 1 };
		c[3] = { cMove.x - 2, cMove.y - 2 };
	}
	for (int i = 0; i < 4; ++i) {
		gotoxyPiece(c[i]);
		if (c[i].y > top && c[i].y < bottom)
			cout << block;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


PieceS::PieceS() {
	c = new Coordinates[4];
	color = 10; //Bright green
	state = 0;
	c[0] = { 9, top + 1 };
	c[1] = { 11, top + 1 };
	c[2] = { 9, top };
	c[3] = { 7, top };
}
bool PieceS::RotateCheck(const Board& b, int rot) {
	int s = state + rot;
	s %= 4;
	if (s % 2 == 0) {
		if (b.getG(c[0].x, c[0].y) != 0 || b.getG(c[0].x + 2, c[0].y) != 0 || b.getG(c[0].x, c[0].y - 1) != 0 || b.getG(c[0].x - 2, c[0].y - 1) != 0)
			return false;
	}
	else if (s % 2 == 1) {
		if (b.getG(c[0].x, c[0].y) != 0 || b.getG(c[0].x, c[0].y - 1) != 0 || b.getG(c[0].x + 2, c[0].y - 1) != 0 || b.getG(c[0].x + 2, c[0].y - 2) != 0)
			return false;
	}
	return true;
}
void PieceS::Show() {
	UnShow();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	Coordinates cMove = c[0];
	if (state % 2 == 0) {
		c[0] = { cMove.x, cMove.y };
		c[1] = { cMove.x + 2, cMove.y };
		c[2] = { cMove.x, cMove.y - 1 };
		c[3] = { cMove.x - 2, cMove.y - 1 };
	}
	else if (state % 2 == 1) {
		c[0] = { cMove.x, cMove.y };
		c[1] = { cMove.x, cMove.y - 1 };
		c[2] = { cMove.x + 2, cMove.y - 1 };
		c[3] = { cMove.x + 2, cMove.y - 2 };
	}
	for (int i = 0; i < 4; ++i) {
		gotoxyPiece(c[i]);
		if (c[i].y > top && c[i].y < bottom)
			cout << block;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}