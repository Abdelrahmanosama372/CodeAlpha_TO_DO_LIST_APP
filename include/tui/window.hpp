#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <ncurses.h>

class WindowBase
{
private:
    WINDOW *win;
    std::string winName;
    unsigned int winRows;
    unsigned int winCols;

public:
    WindowBase(std::string winName);
    virtual ~WindowBase();
    
    void setWin(unsigned int rows, unsigned int cols, unsigned int yPos, unsigned int xPos);
    void clearWin();

    WINDOW** getWin();

    std::string getWinName() const;
    unsigned int getWinRows() const;
    unsigned int getWinCols() const;
    
    char getUserInput() const;

    virtual char run();
    virtual void display();
    virtual void update();
};


#endif /* WINDOW_HPP */