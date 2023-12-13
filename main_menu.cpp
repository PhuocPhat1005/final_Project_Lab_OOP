//#include "Menu.cpp"
//
//int main()
//{
//    system("cls");
//    Menu* menu = new Menu;
//    menu->MakeTitle();
//    menu->MakeMenuTable();
//
//    Credits* credits = NULL;
//
//    bool is_in_menu = true;
//    bool is_quit = false;
//    char keyboard = '\0';
//
//    /* Di chuyen len xuong trong Menu bang phim W (di len), S (di xuong) */
//    while (!is_quit)
//    {
//        if (kbhit())
//        {
//            keyboard = getch();
//
//            if (keyboard == 'q')
//                is_quit = true;
//            else if (keyboard == 's' && is_in_menu)
//            {
//                menu->UpdateMenuTable(true);
//                menu->MakeMenuTable();
//            }
//            else if (keyboard == 'w' && is_in_menu)
//            {
//                menu->UpdateMenuTable(false);
//                menu->MakeMenuTable();
//            }
//            else if (keyboard == char(32) && is_in_menu)
//            {
//                int choice = menu->getChoiceFromMenu();
//                if (choice == 0) // play game
//                {
//                    is_in_menu = false;
//                }
//                else if (choice == 1) // score board
//                {
//                    is_in_menu = false;
//                }
//                else if (choice == 2) // credits
//                {
//                    system("cls");
//                    is_in_menu = false;
//
//                    credits = new Credits;
//                    credits->MakeTitle();
//                    credits->MakeMenuTable();
//
//                    credits->ContentCredits();
//                }   
//                else if (choice == 3) // quit game
//                {
//                    is_quit = true;
//                }
//            }
//            else if (keyboard == 'r') // khi vo bat ki cua so nao thi nhan r de quay lai main menu.
//            {
//                if (credits != NULL)
//                {
//                    delete credits;
//                    credits = NULL;
//                }
//                system("cls");
//                is_in_menu = true;
//                menu->MakeTitle();
//                menu->MakeMenuTable();
//            }
//        }
//    }
//
//    delete menu;
//    menu = NULL;
//
//    return 0;
//}