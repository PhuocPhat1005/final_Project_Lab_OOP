#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

using namespace std;

void gotoxy(short x, short y) { 
    COORD pos = {x, y}; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

class Menu
{
protected:
    int col, row;
    vector<vector<string>> menuTable;

public:
    Menu();
    virtual ~Menu();

    void setRow(const int&);
    void setCol(const int&);
    void setTable(const vector<vector<string>>&);

    int getRow() const;
    int getCol() const;
    vector<vector<string>> getTable() const;

    void printChoiceBoard(const int&, const int&);
    virtual int getChoiceFromMenu() const;

    virtual void MakeTitle();
    virtual void MakeMenuTable();
    virtual void UpdateMenuTable(const bool&);
};

class Credits : public Menu
{
public:
    Credits();
    ~Credits();

    int getChoiceForMenu() const;

    void MakeTitle();
    void MakeMenuTable();
    void UpdateMenuTable(const bool&);

    void ContentCredits();
};