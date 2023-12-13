// #include "header.h"
// #include "board.h"
// #include "piece.h"

// #include "Menu.h"

#include "board.cpp"
#include "piece.cpp"
#include "Menu.cpp"
#include "source.cpp"

int playingMainGame()
{
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

	bool is_pausing = false;
	PauseGame* pauseGame = NULL;

    while (true) {
		while (is_pausing)
		{
			if (pauseGame == NULL)
			{
				pauseGame = new PauseGame; 
				pauseGame->MakeTitle();
				pauseGame->ContentPauseGame();
			}
			keyboard = getch();
			if (keyboard == 'p')
			{
				is_pausing = false;
				pauseGame->unshownPause();
				break;
			}
		}
		if (is_pausing == false)
		{
			if (pauseGame)
			{
				delete pauseGame;
				pauseGame = NULL;
			}
		}

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
                else if (keyboard == 'p') {
					is_pausing = true;
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

int main() 
{
    system("cls");
    Menu* menu = new Menu;
    menu->MakeTitle();
    menu->MakeMenuTable();

    Credits* credits = NULL;
    QuitGame* quitGame = NULL;

    bool is_in_menu = true;
    bool is_quit = false;
    char keyboard = '\0';

    /* Di chuyen len xuong trong Menu bang phim W (di len), S (di xuong) */
    while (!is_quit)
    {
        if (kbhit())
        {
            keyboard = getch();

            if (keyboard == 'q')
                is_quit = true;
            else if (keyboard == 's' && is_in_menu)
            {
                menu->UpdateMenuTable(true);
                menu->MakeMenuTable();
            }
            else if (keyboard == 'w' && is_in_menu)
            {
                menu->UpdateMenuTable(false);
                menu->MakeMenuTable();
            }
            else if (keyboard == char(32) && is_in_menu)
            {
                int choice = menu->getChoiceFromMenu();
                if (choice == 0) // play game
                {
                    is_in_menu = false;
                    system("cls");
                    playingMainGame();
                }
                else if (choice == 1) // score board
                {
                    is_in_menu = false;
                }
                else if (choice == 2) // credits
                {
                    system("cls");
                    is_in_menu = false;

                    credits = new Credits;
                    credits->MakeTitle();
                    credits->MakeMenuTable();

                    credits->ContentCredits();
                }
                else if (choice == 3) // quit game
                {
                    is_quit = true;
                    system("cls");
                    quitGame = new QuitGame;
                    quitGame->MakeTitle();
                    quitGame->ContentQuitGame();
                }
            }
            else if (keyboard == 'r') // khi vo bat ki cua so nao thi nhan r de quay lai main menu.
            {
                if (credits != NULL)
                {
                    delete credits;
                    credits = NULL;
                }
                if (quitGame != NULL)
                {
                    delete quitGame;
                    quitGame = NULL;
                }
                system("cls");
                is_in_menu = true;
                menu->MakeTitle();
                menu->MakeMenuTable();
            }
        }
    }

    delete menu;
    menu = NULL;

    return 0;
}