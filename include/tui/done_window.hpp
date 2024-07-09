#ifndef DONE_WINDOW_HPP
#define DONE_WINDOW_HPP

#include "scroll_window.hpp"

class DoneWindow : public ScrollWindow
{
public:
    DoneWindow(std::string winName);
    char run() override;
    void display() override;
};

#endif /* DONE_WINDOW_HPP */