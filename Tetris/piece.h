#pragma once
#include "header.h"

class Piece {
protected:
	int state, color;
	vector<Coordinates> c;//1 piece gom 4 block
public:
	~Piece();
	int getColor();
	Coordinates getCMove(const int& i);
	virtual bool RotateCheck(const Board& b, int rot) = 0;//Tinh nang co roi: Kiem tra xem piece co quay duoc hay khong
	bool BottomCheck(const Board& b);
	//Tinh nang co roi (dang loi thoi gian): Kiem tra xem piece da cham day hay chua (cho 1 giay de nguoi choi di chuyen, xoay tuy thich),
	virtual void RotateRight();//Tinh nang co roi: Xoay theo chieu kim dong ho theo lenh nguoi choi
	virtual void RotateLeft();//Tinh nang co roi: Xoay nguoc chieu kim dong ho theo lenh nguoi choi
	void MoveRight(const Board& b);//Tinh nang co roi: Piece di chuyen sang phai theo lenh nguoi choi
	void MoveLeft(const Board& b);//Tinh nang co roi: Piece di chuyen sang trai theo lenh nguoi choi
	void MoveDown(const Board& b);//Tinh nang co roi: Piece di chuyen xuong duoi theo lenh nguoi choi
	void MoveDownTime(const Board& b, time_t& originalTime);//Tinh nang co roi: Piece tu roi xuong duoi theo thoi gian
	//Tinh nang muon co: choi cang nhieu diem thi piece roi cang nhanh
	void UnShow();//Tinh nang co roi: Boi den cho hien thi piece cu
	virtual void Show(int place = 0) = 0;//Tinh nang co roi: Hien thi piece
	//friend vector<Piece*> GeneratePiece();
};
void GeneratePiece(vector<Piece*> &p);
//Tinh nang co roi: Tao san 4 piece "xep hang" cho roi vao Board, neu co piece bi xoa thi them vao 1 piece moi
void deletePieces(vector<Piece*> &p);
//Tinh nang co roi: Sau khi 1 piece da duoc co dinh vao Board thi piece do bi xoa, choi thua hoac tat game thi 4 piece deu bi xoa


class PieceI : public Piece {
private:
public:
	PieceI();
	bool RotateCheck(const Board& b, int rot);
	void Show(int place = 0);
};

class PieceO : public Piece {
private:
public:
	PieceO();
	bool RotateCheck(const Board& b, int rot);
	void Show(int place = 0);
};

class PieceJ : public Piece {
private:
public:
	PieceJ();
	bool RotateCheck(const Board& b, int rot);
	void Show(int place = 0);
};

class PieceL : public Piece {
private:
public:
	PieceL();
	bool RotateCheck(const Board& b, int rot);
	void Show(int place = 0);
};

class PieceT : public Piece {
private:
public:
	PieceT();
	bool RotateCheck(const Board& b, int rot);
	void Show(int place = 0);
};

class PieceZ : public Piece {
private:
public:
	PieceZ();
	bool RotateCheck(const Board& b, int rot);
	void Show(int place = 0);
};

class PieceS : public Piece {
private:
public:
	PieceS();
	bool RotateCheck(const Board& b, int rot);
	void Show(int place = 0);
};