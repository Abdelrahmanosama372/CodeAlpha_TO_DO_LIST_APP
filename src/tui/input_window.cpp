#include "input_window.hpp"
#include <fstream>

InputWindow::InputWindow(std::string winName)
    : WindowBase(winName)
{ }

std::string InputWindow::getInput() const {
    return this->input;
}

void InputWindow::clear() {
    this->input.clear();
}

void InputWindow::display() {
    WINDOW **win = this->getWin();
    unsigned int inputSize = this->input.size();
    unsigned int winCols = this->getWinCols();

    if(inputSize == 0){
        mvwprintw(*win, 1, 1, "%*s", winCols - 1, " ");
    }else if(inputSize <= winCols){
        mvwprintw(*win, 1, 1, this->input.c_str());
    }else {
        mvwprintw(*win, 1, 1, this->input.substr(inputSize - winCols).c_str());
    }
   
    wrefresh(*win);
}

void InputWindow::update() {
    this->display();
}

char InputWindow::run() {
    char ch = getUserInput();
    while (ch != 10) // user didn't press enter
    {
        this->input += ch;
        this->display();
        ch = getUserInput();
    }
    return 'i';
}