#include "done_window.hpp"

DoneWindow::DoneWindow(std::string winName)
    : ScrollWindow(winName)
{ }

char DoneWindow::run() {
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
            case 'L':
            case 'H':
            case 'x': 
            case 10:
                return command;
        }
    }
}