#ifndef PREVIEW_WINDOW_HPP
#define PREVIEW_WINDOW_HPP

#include "window.hpp"
#include "../model/todo.hpp"
#include <vector>

class PreviewWindow : public WindowBase
{
private:
    Todo todo;
public:
    PreviewWindow(std::string winName);
    void setTodo(Todo &&todo);
    void display() override;
    void update() override;
    char run();
};


#endif /* PREVIEW_WINDOW_HPP */