#include "done_window.hpp"

DoneWindow::DoneWindow(std::string winName)
    : ScrollWindow(winName)
{ }

char DoneWindow::run() {
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
            case 'L':
            case 'H':
            case 'x': 
            case 10:
                this->isActiveWin = false;
                return command;
        }
    }
}

void DoneWindow::display() {
    WINDOW **win = this->getWin();
    int i=0;

    for(auto it = this->winBegin; it != this->winEnd; it++, i++) {
        if(it == this->CurrRecord && isActiveWin) {
            wattron(*win, COLOR_PAIR(4));
        }

        auto str_idx = (*it).find('@');
        if(str_idx == std::string::npos) {
            mvwprintw(*win, i+1, 1, "%s", (*it).c_str());
        }else {
            mvwprintw(*win, i+1, 1, "%s", (*it).substr(0,str_idx).c_str());

            if(it == this->CurrRecord && isActiveWin) {
                wattron(*win, COLOR_PAIR(5));
                mvwprintw(*win, i+1, str_idx+1, "%s", (*it).substr(str_idx).c_str());
                wattroff(*win, COLOR_PAIR(5));
            }else {
                wattron(*win, COLOR_PAIR(3));
                mvwprintw(*win, i+1, str_idx+1, "%s", (*it).substr(str_idx).c_str());
                wattroff(*win, COLOR_PAIR(3));
            }
        }

        if(it == this->CurrRecord && isActiveWin) {
            wattron(*win, COLOR_PAIR(4));
        }

        int rest_cols = this->getWinCols() - (*it).length(); // Calculate remaining columns

        if (rest_cols > 0) {
            std::string spaces(rest_cols - 2, ' '); 
            mvwprintw(*win, i+1, (*it).length()+1, "%s", spaces.c_str());
        }

        wattroff(*win, COLOR_PAIR(4));      
    }

    wrefresh(*win);
}