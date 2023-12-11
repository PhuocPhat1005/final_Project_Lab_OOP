#pragma once
#include "header.h"

class Piece {
protected:
	int state, color;
	vector<Coordinates> c;
public:
	~Piece();
	vector<Coordinates> getCMove();
	virtual bool RotateCheck(const Board& b, int rot) = 0;
	bool BottomCheck(const Board& b);
	virtual void RotateRight();
	virtual void RotateLeft();
	void MoveRight(const Board& b);
	void MoveLeft(const Board& b);
	void MoveDown(const Board& b);
	void MoveDownTime(const Board& b, time_t& originalTime);
	void UnShow();
	virtual void Show() = 0;
};

class PieceI : public Piece {
private:
public:
	PieceI();
	bool RotateCheck(const Board& b, int rot);
	void Show();
};

class PieceO : public Piece {
private:
public:
	PieceO();
	bool RotateCheck(const Board& b, int rot);
	void Show();
};

class PieceJ : public Piece {
private:
public:
	PieceJ();
	bool RotateCheck(const Board& b, int rot);
	void Show();
};

class PieceL : public Piece {
private:
public:
	PieceL();
	bool RotateCheck(const Board& b, int rot);
	void Show();
};

class PieceT : public Piece {
private:
public:
	PieceT();
	bool RotateCheck(const Board& b, int rot);
	void Show();
};

class PieceZ : public Piece {
private:
public:
	PieceZ();
	bool RotateCheck(const Board& b, int rot);
	void Show();
};

class PieceS : public Piece {
private:
public:
	PieceS();
	bool RotateCheck(const Board& b, int rot);
	void Show();
};