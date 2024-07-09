#ifndef CATEGORY_WINDOW_HPP
#define CATEGORY_WINDOW_HPP

#include "scroll_window.hpp"

class CategoryWindow : public ScrollWindow
{
public:
    CategoryWindow(std::string winName);
    char run() override;
    void display() override;
};

#endif /* CATEGORY_WINDOW_HPP */