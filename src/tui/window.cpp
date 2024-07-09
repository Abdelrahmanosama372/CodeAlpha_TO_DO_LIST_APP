#include "window.hpp"

WindowBase::WindowBase(std::string winName)
    : winName(winName), win(nullptr)
{ }

void WindowBase::setWin(unsigned int rows, unsigned int cols, unsigned int yPos, unsigned int xPos) {
    if(this->win)
        delwin(this->win);
    
    this->win = newwin(rows, cols, yPos, xPos);
    wbkgd(this->win, COLOR_PAIR(1));
    box(win,0,0);
    mvwprintw(this->win, 0, 1, this->winName.c_str());
    wrefresh(this->win);

    this->winRows = rows;
    this->winCols = cols;
}

void WindowBase::clearWin() {
    if(this->win) {
        wclear(this->win);
        box(this->win,0,0);
        mvwprintw(this->win, 0, 1, this->getWinName().c_str());
        wrefresh(this->win);
    }
}

WINDOW** WindowBase::getWin() {
    return &(this->win);
}

std::string WindowBase::getWinName() const {
    return this->winName;
}

unsigned int WindowBase::getWinRows() const {
    return this->winRows;
}

unsigned int WindowBase::getWinCols() const {
    return this->winCols;
}

char WindowBase::getUserInput() const {
    return wgetch(this->win);
}

void WindowBase::winHighlight() {
    if(this->win) {
        wattron(this->win, COLOR_PAIR(2));
        box(this->win,0,0);
        mvwprintw(this->win, 0, 1, this->getWinName().c_str());
        wattroff(this->win, COLOR_PAIR(2));
        wrefresh(this->win);
    }
}

void WindowBase::winUnHighlight() {
    if(this->win) {
        box(this->win,0,0);
        mvwprintw(this->win, 0, 1, this->getWinName().c_str());
        wrefresh(this->win);
    }
}

char WindowBase::run() {
    return 0;
}

void WindowBase::display() {
    
}

void WindowBase::update() {

}

WindowBase::~WindowBase(){ 
    delwin(this->win);
}