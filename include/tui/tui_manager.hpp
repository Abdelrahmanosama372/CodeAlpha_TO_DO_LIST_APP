#ifndef TUI_MANAGER_HPP
#define TUI_MANAGER_HPP

#include "window.hpp"
#include "todo_controller.hpp"
#include "todo_window.hpp"
#include <csignal>
#include <memory>

class TuiManager
{
private:
    std::array<std::shared_ptr<WindowBase>,5> wins;
    std::array<std::shared_ptr<WindowBase>,5>::iterator currWinIt;
    TodoController &todoController;

    static void handle_winsResize(int sig);
    void resizeAllWins();
    void updateAllWins();
    TuiManager(TodoController &_todoController);
public:
    static TuiManager& getTuiManager(TodoController &_todoController);
    void tuiIntialize(std::array<std::shared_ptr<WindowBase>,5> &&_wins);
    void tuiRun();
    ~TuiManager();
};


#endif /* TUI_MANAGER_HPP */ 
