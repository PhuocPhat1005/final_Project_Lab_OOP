#include "piece.h"
#include "board.h"

Piece::~Piece(){
	c.clear();
}
int Piece::getColor() {
	return color;
}
Coordinates Piece::getCMove(const int &i) {
	return c[i];
}
bool Piece::BottomCheck(const Board& b) {
	for (int i = 0; i < 4; ++i) {
		if (b.getG(c[i].x, c[i].y + 1) != 0) {
			Sleep(1000);//Cho piece cham day 1 giay(tu do di chuyen trai phai, xoay) roi moi khoa toa do vao board
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
void GeneratePiece(vector<Piece*> &p) {
	int type = rand() % 7;//chon ngau nhien cac piece de dua vao hang doi
	if (type == 0) {
		Piece* p1 = new PieceI;
		p.push_back(p1);
	}
	else if (type == 1) {
		Piece* p1 = new PieceO;
		p.push_back(p1);
	}
	else if (type == 2) {
		Piece* p1 = new PieceJ;
		p.push_back(p1);
	}
	else if (type == 3) {
		Piece* p1 = new PieceL;
		p.push_back(p1);
	}
	else if (type == 4) {
		Piece* p1 = new PieceT;
		p.push_back(p1);
	}
	else if (type == 5) {
		Piece* p1 = new PieceZ;
		p.push_back(p1);
	}
	else if (type == 6) {
		Piece* p1 = new PieceS;
		p.push_back(p1);
	}
}
void deletePieces(vector<Piece*> &p) {
	for (int i = 0; i < p.size(); ++i) {
		delete p[i];
	}
	p.clear();
}


PieceI::PieceI() {
	color = 11; //Bright cyan
	state = 0;
	c.push_back({ 11, top });
	c.push_back({ 11, top + 1 });
	c.push_back({ 11, top + 2 });
	c.push_back({ 11, top + 3 });
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
void PieceI::Show(int place) {
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
	color = 14; //Yellow
	state = 0;
	c.push_back({ 9, top });
	c.push_back({ 11, top });
	c.push_back({ 9, top - 1 });
	c.push_back({ 11, top - 1 });
}
bool PieceO::RotateCheck(const Board& b, int rot) {
	return true;
}
void PieceO::Show(int place) {
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
	color = 1; //Blue
	state = 0;
	c.push_back({ 9, top });
	c.push_back({ 11, top });
	c.push_back({ 11, top - 1 });
	c.push_back({ 11, top - 2 });
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
void PieceJ::Show(int place) {
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
	color = 12; //Bright red
	state = 0;
	c.push_back({ 11, top });
	c.push_back({ 9, top });
	c.push_back({ 9, top - 1 });
	c.push_back({ 9, top - 2 });
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
void PieceL::Show(int place) {
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
	color = 5; //Purple
	state = 0;
	c.push_back({ 11, top });
	c.push_back({ 9, top });
	c.push_back({ 13, top });
	c.push_back({ 11, top - 1 });
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
void PieceT::Show(int place) {
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
	color = 4; //Red
	state = 0;
	c.push_back({ 11, top });
	c.push_back({ 9, top });
	c.push_back({ 11, top - 1 });
	c.push_back({ 13, top - 1 });
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
void PieceZ::Show(int place) {
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
	color = 10; //Bright green
	state = 0;
	c.push_back({ 9, top });
	c.push_back({ 11, top });
	c.push_back({ 9, top - 1 });
	c.push_back({ 7, top - 1 });
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
void PieceS::Show(int place) {
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