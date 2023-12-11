#include "Menu.h"

Menu::Menu()
{
    row = 4;
    col = 2;
    for (int i = 0; i < row; i++)
    {
        vector<string> temp;
        for (int j = 0; j < col; j++)
        {
            temp.push_back("  ");
        }
        menuTable.push_back(temp);
        temp.clear();
    }

    menuTable[0][0] = ">>";

    for (int i = 0; i < row; i++)
    {
        if (i == 0)
            menuTable[i][1] = "PLAY GAME";
        else if (i == 1)
            menuTable[i][1] = "SCORE BOARD";
        else if (i == 2)
            menuTable[i][1] = "CREDITS";
        else if (i == 3)
            menuTable[i][1] = "QUIT GAME";
    }
}

Menu::~Menu()
{
    for (int i = 0; i < menuTable.size(); i++)
        menuTable[i].clear();
    menuTable.clear();
}

void Menu::setRow(const int& r)
{
    row = r;
}

void Menu::setCol(const int& c)
{
    col = c;
}

void Menu::setTable(const vector<vector<string>>& table)
{
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 0; j < table[i].size(); j++)
        {
            menuTable[i][j] = table[i][j];
        }
    }
}

int Menu::getRow() const
{
    return row;
}

int Menu::getCol() const
{
    return col;
}

vector<vector<string>> Menu::getTable() const
{
    return menuTable;
}

void Menu::MakeTitle()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(20, 5);
    cout << ".----------------.  .----------------.  .----------------.  .----------------.  .----------------.   .----------------.  .----------------.  .----------------.  .----------------."; 
    gotoxy(20, 6);
    cout << "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. | | .--------------. || .--------------. || .--------------. || .--------------. |";
    gotoxy(20, 7);
    cout << "| |  _________   | || |  _________   | || |  _______     | || |     _____    | || |    _______   | | | |    ______    | || |      __      | || | ____    ____ | || |  _________   | |";
    gotoxy(20, 8);
    cout << "| | |  _   _  |  | || | |_   ___  |  | || | |_   __ \\    | || |    |_   _|   | || |   /  ___  |  | | | |  .' ___  |   | || |     /  \\     | || ||_   \\  /   _|| || | |_   ___  |  | |";
    gotoxy(20, 9);
    cout << "| | |_/ | | \\_|  | || |   | |_  \\_|  | || |   | |__) |   | || |      | |     | || |  |  (__ \\_|  | | | | / .'   \\_|   | || |    / /\\ \\    | || |  |   \\/   |  | || |   | |_  \\_|  | |";
    gotoxy(20, 10);
    cout << "| |     | |      | || |   |  _|  _   | || |   |  __ /    | || |      | |     | || |   '.___`-.   | | | | | |    ____  | || |   / ____ \\   | || |  | |\\  /| |  | || |   |  _|  _   | |";
    gotoxy(20, 11);
    cout << "| |    _| |_     | || |  _| |___/ |  | || |  _| |  \\ \\_  | || |     _| |_    | || |  |`\\____) |  | | | | \\ `.___]  _| | || | _/ /    \\ \\_ | || | _| |_\\/_| |_ | || |  _| |___/ |  | |";
    gotoxy(20, 12);
    cout << "| |   |_____|    | || | |_________|  | || | |____| |___| | || |    |_____|   | || |  |_______.'  | | | |  `._____.'   | || ||____|  |____|| || ||_____||_____|| || | |_________|  | |";
    gotoxy(20, 13);
    cout << "| |              | || |              | || |              | || |              | || |              | | | |              | || |              | || |              | || |              | |";
    gotoxy(20, 14);
    cout << "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' | | '--------------' || '--------------' || '--------------' || '--------------' |";
    gotoxy(20, 15);
    cout << "'----------------'  '----------------'  '----------------'  '----------------'  '----------------'   '----------------'  '----------------'  '----------------'  '----------------' ";

    cout << endl;
}

void Menu::MakeMenuTable()
{
    for (int i = 0; i < row; i++)
        printChoiceBoard(100, 20 + 5 * i);

    for (int i = 0; i < row; i++)
    {
        gotoxy(100, 20 + 5 * i);
        for (int j = 0; j < col; j++)
        {
            cout << menuTable[i][j] << " ";
        }
        cout << endl;
    }
}

void Menu::UpdateMenuTable(const bool& stateDown)
{
    int x_pos;
    bool flag = true;
    for (int i = 0; i < row && flag; i++)
    {
        for (int j = 0; j < col && flag; j++)
        {
            if (menuTable[i][j] == ">>")
            {  
                if (stateDown)
                    x_pos = i + 1;
                else
                    x_pos = i - 1;

                if (x_pos >= row)
                    x_pos = 0;
                else if (x_pos < 0)
                    x_pos = row - 1;
                    
                menuTable[i][j] = "  ";
                flag = false;
            }
        }
    }
    if (!flag)
        menuTable[x_pos][0] = ">>";
}

int Menu::getChoiceFromMenu() const
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (menuTable[i][j] == ">>")
                return i;
}

void Menu::printChoiceBoard(const int& directX, const int& directY)
{
    //  print upper board
    gotoxy(directX - 5, directY - 1);
    cout << char(201);
    for (int i = 0; i < 21; i++)
        cout << char(205);
    cout << char(187); 
    // print middle board
    for (int i = 0; i < 3; i++)
    {
        gotoxy(directX - 5, directY + i);
        cout << char(186);

        gotoxy(directX + 17, directY + i);
        cout << char(186);
        
    }

    //print bottom box
    gotoxy(directX - 5, directY + 2);
    cout << char(200);
    for (int i = 0; i < 21; i++)
    {
        cout << char(205);
    }
    cout << char(188); 
}

/*==================== CREDITS ====================*/

Credits::Credits()
{
    row = 1;
    col = 2;
    for (int i = 0; i < row; i++)
    {
        vector<string> temp;
        for (int j = 0; j < col; j++)
        {
            temp.push_back("  ");
        }
        menuTable.push_back(temp);
        temp.clear();
    }

    menuTable[0][0] = ">>";
    menuTable[0][1] = "RETURN";
}

Credits::~Credits()
{
    for (int i = 0; i < menuTable.size(); i++)
        menuTable[i].clear();
    menuTable.clear();
}

int Credits::getChoiceForMenu() const
{
    return 0;
}

void Credits::MakeTitle()
{
    gotoxy(75, 5);
    cout << "______     ______     ______     _____     __     ______   ______ ";   
    gotoxy(75, 6);
    cout << "/\\  ___\\   /\\  == \\   /\\  ___\\   /\\  __-.  /\\ \\   /\\__  _\\ /\\  ___\\  "; 
    gotoxy(75, 7);
    cout << "\\ \\ \\____  \\ \\  __<   \\ \\  __\\   \\ \\ \\/\\ \\ \\ \\ \\  \\/_/\\ \\/ \\ \\___  \\  ";
    gotoxy(75, 8);
    cout << "\\ \\_____\\  \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\____-  \\ \\_\\    \\ \\_\\  \\/\\_____\\ ";
    gotoxy(75, 9);
    cout << "\\/_____/   \\/_/ /_/   \\/_____/   \\/____/   \\/_/     \\/_/   \\/_____/ ";
}

void Credits::MakeMenuTable()
{
    for (int i = 0; i < row; i++)
        printChoiceBoard(10, 40 + 5 * i);

    for (int i = 0; i < row; i++)
    {
        gotoxy(10, 40 + 5 * i);
        for (int j = 0; j < col; j++)
        {
            cout << menuTable[i][j] << " ";
        }
        cout << endl;
    }
}

void Credits::UpdateMenuTable(const bool& stateDown)
{
    int x_pos;
    bool flag = true;
    for (int i = 0; i < row && flag; i++)
    {
        for (int j = 0; j < col && flag; j++)
        {
            if (menuTable[i][j] == ">>")
            {  
                if (stateDown)
                    x_pos = i + 1;
                else
                    x_pos = i - 1;

                if (x_pos >= row)
                    x_pos = 0;
                else if (x_pos < 0)
                    x_pos = row - 1;
                    
                menuTable[i][j] = "  ";
                flag = false;
            }
        }
    }
    if (!flag)
        menuTable[x_pos][0] = ">>";
}

void Credits::ContentCredits()
{
    gotoxy(80, 15);
    cout << "22127174" << setw(50) << setfill('.') << "NGO VAN KHAI";
    gotoxy(80, 18);
    cout << "22127322" << setw(50) << setfill('.') << "LE PHUOC PHAT";
    gotoxy(80, 21);
    cout << "22127388" << setw(50) << setfill('.') << "TO QUOC THANH";
    gotoxy(80, 24);
    cout << "22127441" << setw(50) << setfill('.') << "THAI HUYEN TUNG";

    gotoxy(90, 30);
    cout << "Press R to return to main menu. Thanks!";
}