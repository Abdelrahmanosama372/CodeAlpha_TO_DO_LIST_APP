#ifndef TODO_WINDOW_HPP
#define TODO_WINDOW_HPP

#include "scroll_window.hpp"

class TodoWindow : public ScrollWindow
{
public:
    TodoWindow(std::string winName);
    char run() override;
    void display() override;
};


#endif /* TODO_WINDOW_HPP */