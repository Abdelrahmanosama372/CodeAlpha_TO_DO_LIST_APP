#include "preview_window.hpp"

PreviewWindow::PreviewWindow(std::string winName)
    : WindowBase(winName)
{ }

void PreviewWindow::setTodo(Todo &&_todo) {
    this->todo = std::move(_todo);
}

void PreviewWindow::display() {


    WINDOW **win = this->getWin();
    unsigned int winCols = this->getWinCols();
    unsigned int winRows = this->getWinRows();

    std::vector<std::string> previewData;

    if(this->todo.getName().empty()){
       previewData = {
            std::string("Todo: "),
            std::string("Description: "),
            std::string("Priority: "),
            std::string("Category: "),
            std::string("Creation date: "),
        };
    }else {
        previewData = {
            std::string("Todo: ") + this->todo.getName(),
            std::string("Description: ") + this->todo.getDescription(),
            std::string("Priority: ") + this->todo.getPriority(),
            std::string("Category: ") + this->todo.getCategory(),
            std::string("Creation date: ") + this->todo.getCreationDate(),
        };
    }

    wbkgd(*win, COLOR_PAIR(2));
    wattron(*win, COLOR_PAIR(2));
    
    int currRow = 0;
   for (const auto& str : previewData)
    {
        std::size_t i = 0;
        while (i < str.length())
        {
            mvwprintw(*win, currRow + 1, 1, str.substr(i, winCols).c_str());
            wclrtoeol(*win);
            i += winCols;
            currRow++;
        }
    } 
    wattroff(*win, COLOR_PAIR(2));
    wrefresh(*win);
}

void PreviewWindow::update() {
    this->display();
}

char PreviewWindow::run() {
    while (true)
    {
        char command = getUserInput();
        switch (command)
        {
            case 'K': 
            case 'J':
            case 'H':
            case 'L':
            case 'q':
                return command;
        }
    }
}

