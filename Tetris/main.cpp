#include "header.h"
#include "board.h"
#include "piece.h"

int main() {
	Board b;
	b.ShowBorder();
	Coordinates cMove(11, top + 1);
	PieceZ p1;
	p1.Show();

	time_t originalTime = time(0);
	char keyboard = 'a';
	while (true) {
		p1.MoveDownTime(b, originalTime);
		//p1.Show();
		if (kbhit()) {
			keyboard = getch();

			if (keyboard == 'm' && p1.RotateCheck(b, 1)) {
				p1.RotateRight();
			}
			else if (keyboard == 'n' && p1.RotateCheck(b, 3)) {
				p1.RotateLeft();
			}
			else if (keyboard == 'd') {
				p1.MoveRight(b);
			}
			else if (keyboard == 'a') {
				p1.MoveLeft(b);
			}
			else if (keyboard == 's') {
				p1.MoveDown(b);
			}
			else if (keyboard == 'b') {
				break;
			}
		}
	}
	return 0;
}