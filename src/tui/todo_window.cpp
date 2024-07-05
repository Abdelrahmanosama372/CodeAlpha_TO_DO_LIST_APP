#include "todo_window.hpp"

TodoWindow::TodoWindow(std::string winName)
    : ScrollWindow(winName)
{ }

char TodoWindow::run() {

    this->setWinFrame();
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
            case 10:
            case 'd':
            case 'x':
            case 'i':
            case 'K': 
            case 'J':
            case 'L':
            case 'H':
            case 'q':
            
                return command;
        }
    }
}