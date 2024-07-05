#include "tui_manager.hpp"
#include "todo_window.hpp"
#include "preview_window.hpp"
#include "input_window.hpp"
#include "done_window.hpp"
#include "category_window.hpp"
#include "todo_controller.hpp"
#include <chrono>

int main(int argc, char const *argv[])
{
    TodoManager todoManager;
    CategoryManager categoryManager;

    std::array<std::shared_ptr<WindowBase>,5> wins = {
        std::make_shared<InputWindow>(InputWindow("Input")),
        std::make_shared<TodoWindow>(TodoWindow("Todo")),
        std::make_shared<PreviewWindow>(PreviewWindow("Preview")),
        std::make_shared<DoneWindow>(DoneWindow("Done")),
        std::make_shared<CategoryWindow>(CategoryWindow("Category")),
    };

    TodoController todoController(todoManager,categoryManager,wins);
    todoController.loadFromFile("/home/abdelrahman/workspaces/codeAlpha/to-do-list/build/todoApp.json");

    TuiManager &tuiManager = TuiManager::getTuiManager(todoController);
    tuiManager.tuiIntialize(std::move(wins));

    while (1)
    {
        tuiManager.tuiRun();
    }
    
    return 0;
}
