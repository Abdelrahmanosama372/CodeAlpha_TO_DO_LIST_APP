#include "category_window.hpp"

CategoryWindow::CategoryWindow(std::string winName)
    : ScrollWindow(winName)
{ }

char CategoryWindow::run() {
    while (true)
    {
        this->isActiveWin = true;
        this->display();
        char command = getUserInput();
        switch (command)
        {
            case 'j': {
                this->goToNextRecord();
                break;
            }
            case 'k': {
                this->goToPrevRecord();
                break;
            }
            
            case 'K': 
            case 'J':
            case 'L':
            case 'H':
            case 'x':
            case 10:
                this->isActiveWin = false;
                return command;
        }
    }
}


void CategoryWindow::display() {
    WINDOW **win = this->getWin();
    int i=0;

    for(auto it = this->winBegin; it != this->winEnd; it++, i++) {
        if(it == this->CurrRecord  && isActiveWin) {
            wattron(*win, COLOR_PAIR(4));
        }
        mvwprintw(*win, i+1, 1, (*it).c_str()); 

        int rest_cols = this->getWinCols() - (*it).length(); // Calculate remaining columns

        if (rest_cols > 0) {
            std::string spaces(rest_cols - 2, ' '); 
            mvwprintw(*win, i+1, (*it).length()+1, "%s", spaces.c_str());
        }

        wattroff(*win, COLOR_PAIR(4));
    }
    wrefresh(*win);
}