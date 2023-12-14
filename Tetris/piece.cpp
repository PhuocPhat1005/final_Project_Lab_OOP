#include "piece.h"
#include "board.h"

Piece::~Piece() {
	c.clear();
}
int Piece::getColor() {
	return color;
}
Coordinates Piece::getCMove(const int& i) {
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
	this->PreShow();
}
void Piece::RotateLeft() {
	state += 3;
	state %= 4;
	this->PreShow();
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
	this->PreShow();
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
	this->PreShow();
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
	this->PreShow();
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
		this->PreShow();
	}
}
void Piece::PreShow(int place) {
	UnShow();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	if (c.size() > 4) {
		iter_swap(c.begin(), c.begin() + c.size() - 1);
		c.erase(c.begin() + c.size() - 1);
	}
	if (place == 5) {
		iter_swap(c.begin(), c.begin() + c.size() - 1);
		//c.erase(c.begin() + c.size() - 1);
		c[0].x = 11;
		c[0].y = top + 1;
		gotoxy(30, 3);
		cout << c[0].x << "   " << c[0].y << "   ";
	}
	else if (place == 0) {
	}
	else if (place == 1) {
		c.push_back({ 30, top + 4 });
		iter_swap(c.begin(), c.begin() + c.size() - 1);
	}
	else if (place == 2) {
		c.push_back({ 30, top + 9 });
		iter_swap(c.begin(), c.begin() + c.size() - 1);
	}
	else if (place == 3) {
		c.push_back({ 30, top + 14 });
		iter_swap(c.begin(), c.begin() + c.size() - 1);
	}
	else if (place == 4) {
		c.push_back({ 30, 5 });
		iter_swap(c.begin(), c.begin() + c.size() - 1);
	}
}
void Piece::UnShow() {
	for (int i = 0; i < 4; ++i) {
		gotoxyPiece(c[i]);
		if (c[i].y > top)
			cout << "  ";
	}
}
void Piece::Show(int place) {
	for (int i = 0; i < 4; ++i) {
		if (place >= 1 && place <= 4) {
			gotoxyPiece(c[i]);
			cout << block;
		}
		else if (c[i].y > top && c[i].y < bottom) {
			gotoxyPiece(c[i]);
			cout << block;
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void Piece::Place(int place, Coordinates& cMove) {
	if (place == 4) {
		cMove.x = 30;
		cMove.y = 5;
	}
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
void PieceI::PreShow(int place) {
	this->Piece::PreShow(place);
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
	Show(place);
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
void PieceO::PreShow(int place) {
	this->Piece::PreShow(place);
	Coordinates cMove = c[0];
	c[0] = { cMove.x, cMove.y };
	c[1] = { cMove.x + 2, cMove.y };
	c[2] = { cMove.x, cMove.y - 1 };
	c[3] = { cMove.x + 2, cMove.y - 1 };
	Show(place);
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
void PieceJ::PreShow(int place) {
	this->Piece::PreShow(place);
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
	Show(place);
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
void PieceL::PreShow(int place) {
	this->Piece::PreShow(place);
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
	Show(place);
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
		/*{
			if (b.getG(c[0].x + 2, c[0].y) != 0 || b.getG(c[0].x + 4, c[0].y - 1) != 0)
				return false;;
			else{
				c[0].x -= 2;
				return true;
			}
		}*/
	}
	else if (s == 2) {
		if (b.getG(c[0].x, c[0].y) != 0 || b.getG(c[0].x - 2, c[0].y - 1) != 0 || b.getG(c[0].x + 2, c[0].y - 1) != 0 || b.getG(c[0].x, c[0].y - 1) != 0)
			return false;
	}
	else if (s == 3) {
		if (b.getG(c[0].x, c[0].y) != 0 || b.getG(c[0].x, c[0].y - 1) != 0 || b.getG(c[0].x, c[0].y - 2) != 0 || b.getG(c[0].x - 2, c[0].y - 1) != 0)
			return false;
		/*{
			if (b.getG(c[0].x - 2, c[0].y) != 0 || b.getG(c[0].x + 2, c[0].y - 1) != 0)
				return false;
			else {
				c[0].x += 2;
				return true;
			}
		}*/
	}
	return true;
}
void PieceT::PreShow(int place) {
	this->Piece::PreShow(place);
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
	Show(place);
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
void PieceZ::PreShow(int place) {
	this->Piece::PreShow(place);
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
	Show(place);
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
void PieceS::PreShow(int place) {
	this->Piece::PreShow(place);
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
	Show(place);
}