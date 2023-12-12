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
	void ShowBorder();//Tinh nang co roi: Hien thi khung vien | Tinh nang muon them: Hien cac thong tin ve nguoi choi
	void ShowBoard();//Tinh nang co roi: Hien thi banh choi gom nhung block da bi co dinh
	void ShowQueue(vector<Piece*> p);//Tinh nang muon them: Hien cac 3 piece dang "xep hang" doi roi vao game
	void AddBoard(Piece* p);
	//Tinh nang co roi (dang loi thoi gian): Kiem tra xem piece da cham day hay chua (cho 1 giay de nguoi choi di chuyen, xoay tuy thich),
	//neu cham day roi thi chuan bi co dinh vao Board
	bool EndBoard(Piece* p);//Tinh nang co roi : Kiem tra viec choi thua (co block tran ra ngoai)
	//Tinh nang co roi (dang loi thoi gian): Kiem tra xem piece da cham day hay chua (cho 1 giay de nguoi choi di chuyen, xoay tuy thich),
	//neu cham day roi thi chuan bi co dinh vao Board thong qua AddBoard
	void ScoreBoard();//Tinh nang co roi: Hang nao full roi thi xoa hang do
	//Tinh nang muon them: xoa 1 hang +10 diem, xoa 4 hang +50 diem va thong bao TETRIS
};
