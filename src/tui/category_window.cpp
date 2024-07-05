#include "category_window.hpp"

CategoryWindow::CategoryWindow(std::string winName)
    : ScrollWindow(winName)
{ }

char CategoryWindow::run() {
    while (true)
    {
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
                return command;
        }
    }
}