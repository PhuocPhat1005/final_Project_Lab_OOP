#include "header.h"
#include "board.h"
#include "piece.h"

int main() {
	Board b;
	b.ShowBorder();
	Coordinates cMove(11, top + 1);

	vector<Piece*> p;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 4; ++i) {//hang doi gom 4 piece, cac piece se tuan tu roi xuong
		GeneratePiece(p);
	}

	time_t originalTime = time(0);
	char keyboard = 'a';
	while (true) {
		if (p[0]->BottomCheck(b)) {
			if (b.EndBoard(p[0]))
				break;

			p[0]->UnShow();
			b.AddBoard(p[0]);
			b.ScoreBoard();
			b.ShowBoard();

			Sleep(1500);
			delete p[0];
			p.erase(p.begin());
			GeneratePiece(p);

			originalTime = time(0);
			p[0]->Show();
		}
		else {
			p[0]->MoveDownTime(b, originalTime);

			if (kbhit()) {
				keyboard = getch();

				if (keyboard == 'm' && p[0]->RotateCheck(b, 1)) {
					p[0]->RotateRight();
				}
				else if (keyboard == 'n' && p[0]->RotateCheck(b, 3)) {
					p[0]->RotateLeft();
				}
				else if (keyboard == 'd') {
					p[0]->MoveRight(b);
				}
				else if (keyboard == 'a') {
					p[0]->MoveLeft(b);
				}
				else if (keyboard == 's') {
					p[0]->MoveDown(b);
				}
				else if (keyboard == 'b') {
					break;
				}
			}
		}
	}

	deletePieces(p);

	return 0;
}