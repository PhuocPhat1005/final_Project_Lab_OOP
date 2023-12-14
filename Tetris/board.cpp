#include "board.h"
#include "piece.h"
#include "menu.h"

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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
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
void Board::ShowQueue() {
	for (int i = 1; i <= 3; ++i)
		pQueue[i]->PreShow(i);
}
void Board::UnShowQueue() {
	for (int i = 1; i <= 3; ++i)
		pQueue[i]->UnShow();
}
void Board::AddBoard(Piece* p) {
	pQueue[0]->UnShow();
	for (int i = 0; i < 4; ++i) {
		int _x = (p->getCMove(i).x - 1) / 2;
		int _y = p->getCMove(i).y - 1 - top;
		gameBoard[_y][_x] = p->getColor();
	}
}
bool Board::EndBoard(Piece* p) {
	for (int i = 0; i < 4; ++i) {
		if (p->getCMove(i).y <= top) {
			gotoxy(30, 6);
			cout << "end";
			return true;
		}
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
void Board::GeneratePiece() {
	int type = rand() % 7;//chon ngau nhien cac piece de dua vao hang doi
	//int type = 4;
	if (type == 0) {
		Piece* p1 = new PieceI;
		pQueue.push_back(p1);
	}
	else if (type == 1) {
		Piece* p1 = new PieceO;
		pQueue.push_back(p1);
	}
	else if (type == 2) {
		Piece* p1 = new PieceJ;
		pQueue.push_back(p1);
	}
	else if (type == 3) {
		Piece* p1 = new PieceL;
		pQueue.push_back(p1);
	}
	else if (type == 4) {
		Piece* p1 = new PieceT;
		pQueue.push_back(p1);
	}
	else if (type == 5) {
		Piece* p1 = new PieceZ;
		pQueue.push_back(p1);
	}
	else if (type == 6) {
		Piece* p1 = new PieceS;
		pQueue.push_back(p1);
	}
}
void Board::DeletePieces() {
	for (int i = 0; i < pQueue.size(); ++i) {
		delete pQueue[i];
	}
	pQueue.clear();
}
void Board::Hold() {
	GeneratePiece();
	pQueue[0]->PreShow(4);
	iter_swap(pQueue.begin(), pQueue.begin() + 4);
	pQueue[0]->PreShow(5);
}
void Board::UnHold() {
	pQueue[0]->PreShow(4);
	iter_swap(pQueue.begin(), pQueue.begin() + 4);
	pQueue[0]->PreShow(5);
}
void Board::Play() {
	ShowBorder();
	srand((unsigned)time(NULL));
	for (int i = 0; i < 4; ++i) {//hang doi gom 4 piece, cac piece se tuan tu roi xuong
		GeneratePiece();
	}
	ShowQueue();
	time_t originalTime = time(0);
	char keyboard = 'a';
	PauseGame* pauseGame = new PauseGame(false, 0);
	bool firstHold = true;

	while (true) {
		if (pQueue[0]->BottomCheck(*this)) {
			if (EndBoard(pQueue[0]))
				break;

			AddBoard(pQueue[0]);
			ScoreBoard();
			ShowBoard();

			delete pQueue[0];
			pQueue.erase(pQueue.begin());
			GeneratePiece();
			if (firstHold && pQueue.size() > 4)
				iter_swap(pQueue.begin() + 3, pQueue.begin() + 4);

			originalTime = time(0);
			pQueue[0]->PreShow();
			ShowQueue();
		}
		else {
			pQueue[0]->MoveDownTime(*this, originalTime);

			if (kbhit()) {
				keyboard = getch();

				if (keyboard == 'm' && pQueue[0]->RotateCheck(*this, 1)) {
					pQueue[0]->RotateRight();
				}
				else if (keyboard == 'n' && pQueue[0]->RotateCheck(*this, 3)) {
					pQueue[0]->RotateLeft();
				}
				else if (keyboard == 'd') {
					pQueue[0]->MoveRight(*this);
				}
				else if (keyboard == 'a') {
					pQueue[0]->MoveLeft(*this);
				}
				else if (keyboard == 's') {
					pQueue[0]->MoveDown(*this);
				}
				else if (keyboard == 'h' && firstHold) {
					firstHold = false;
					pQueue[0]->UnShow();
					Hold();
				}
				else if (keyboard == 'h' && !firstHold) {
					pQueue[0]->UnShow();
					UnHold();
				}
				else if (keyboard == 'p') {
					pauseGame->setCounting(pauseGame->getCounting() + 1);
					pauseGame->setIsPausing(true);

					pauseGame->MakeMenuTable();
					pauseGame->MakeTitle();
					pauseGame->ContentPauseGame();

					if (pauseGame->getCounting() >= 2)
					{
						pauseGame->setIsPausing(false);
						pauseGame->setCounting(0);
						pauseGame->UnshownPause();

						pQueue[0]->MoveDownTime(*this, originalTime);
					}
				}
				else if (keyboard == 'b') {
					DeletePieces();
					return;
				}
			}
		}
	}
}