#pragma once
#include "header.h"

class Piece {
protected:
	int state;//1 piece gom 4 trang thai, block I voi O cung tinh la co 4 luon de tien lap trinh
	int color;//mau sac cua tung piece
	vector<Coordinates> c;//1 piece gom 4 block
public:
	~Piece();
	int getColor();
	Coordinates getCMove(const int& i);
	virtual bool RotateCheck(const Board& b, int rot) = 0;
	//Tinh nang co roi: Kiem tra xem piece co quay duoc hay khong
	bool BottomCheck(const Board& b);
	//Tinh nang co roi (dang loi thoi gian): Kiem tra xem piece da cham day hay chua (cho 1 giay de nguoi choi di chuyen, xoay tuy thich),
	virtual void RotateRight();
	//Tinh nang co roi: Piece xoay 90 do theo chieu kim dong ho theo lenh nguoi choi
	virtual void RotateLeft();
	//Tinh nang co roi: Piece xoay 90 do nguoc chieu kim dong ho theo lenh nguoi choi
	void MoveRight(const Board& b);
	//Tinh nang co roi: Piece di chuyen sang phai theo lenh nguoi choi
	void MoveLeft(const Board& b);
	//Tinh nang co roi: Piece di chuyen sang trai theo lenh nguoi choi
	void MoveDown(const Board& b);
	//Tinh nang co roi: Piece di chuyen xuong duoi theo lenh nguoi choi
	void MoveDownTime(const Board& b, time_t& originalTime);
	//Tinh nang co roi: Piece tu roi xuong duoi theo thoi gian
	//Tinh nang muon co: choi cang nhieu diem thi piece roi cang nhanh
	virtual void PreShow(int place = 0);
	//Tinh nang co roi: Hien thi piece
	void UnShow();
	//Tinh nang co roi: Boi den cho hien thi piece cu
	void Show(int place = 0);
	//Tinh nang co roi: Hien thi piece
	void Place(int place, Coordinates& cMove);
};

class PieceI : public Piece {
private:
public:
	PieceI();
	bool RotateCheck(const Board& b, int rot);
	void PreShow(int place = 0);
};

class PieceO : public Piece {
private:
public:
	PieceO();
	bool RotateCheck(const Board& b, int rot);
	void PreShow(int place = 0);
};

class PieceJ : public Piece {
private:
public:
	PieceJ();
	bool RotateCheck(const Board& b, int rot);
	void PreShow(int place = 0);
};

class PieceL : public Piece {
private:
public:
	PieceL();
	bool RotateCheck(const Board& b, int rot);
	void PreShow(int place = 0);
};

class PieceT : public Piece {
private:
public:
	PieceT();
	bool RotateCheck(const Board& b, int rot);
	void PreShow(int place = 0);
};

class PieceZ : public Piece {
private:
public:
	PieceZ();
	bool RotateCheck(const Board& b, int rot);
	void PreShow(int place = 0);
};

class PieceS : public Piece {
private:
public:
	PieceS();
	bool RotateCheck(const Board& b, int rot);
	void PreShow(int place = 0);
};