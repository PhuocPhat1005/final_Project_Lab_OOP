#pragma once
#include "header.h"

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
    int getChoiceFromMenu() const;

    virtual void MakeTitle();
    virtual void MakeMenuTable();

    void UpdateMenuTable(const bool&);
};

class Credits : public Menu
{
public:
    Credits();
    ~Credits();

    void MakeTitle();
    void MakeMenuTable();

    void ContentCredits();
};

class QuitGame : public Menu
{
public:
    QuitGame();
    ~QuitGame();

    void MakeTitle();
    void MakeMenuTable();

    void ContentQuitGame();
};

class PauseGame : public Menu
{
private:
    bool is_pausing;
    int counting;
public:
    PauseGame(const bool&, const int&);
    ~PauseGame();

    void setIsPausing();
    void setCounting(const int&);

    bool getIsPausing() const;
    int getCounting() const;

    void MakeTitle();
    void MakeMenuTable();

    void ContentPauseGame();
    void UnshownPause();

    void PlayPausing();
};

class GameOver : public Menu
{
public:
    GameOver();
    ~GameOver();

    void MakeTitle();
    void MakeMenuTable();
};