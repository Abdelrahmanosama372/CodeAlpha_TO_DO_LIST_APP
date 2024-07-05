#ifndef TODO_CONTROLLER_HPP
#define TODO_CONTROLLER_HPP

#include <memory>

#include "todo_manager.hpp"
#include "category_manager.hpp"
#include "window.hpp"
#include "input_window.hpp"
#include "todo_window.hpp"
#include "preview_window.hpp"
#include "done_window.hpp"
#include "category_window.hpp"
#include "nlohmann/json.hpp"
#include <fstream>

class TodoController
{
private:
    TodoManager &todoManager;
    CategoryManager &categoryManager;
    std::shared_ptr<InputWindow> inputWin; 
    std::shared_ptr<TodoWindow> todoWin;
    std::shared_ptr<PreviewWindow> previewWin;
    std::shared_ptr<DoneWindow> doneWin;
    std::shared_ptr<CategoryWindow> categoryWin;
public:
    TodoController(TodoManager &_todoManager, CategoryManager &_categoryManager,
        std::array<std::shared_ptr<WindowBase>,5> &wins);

    void loadFromFile(const std::string& fileName);

    void handleInsertion();
    void handleDone();
    void handlePreviewCategory();
    void handlePreviewTodo(std::shared_ptr<WindowBase> win);
    void handleDeletion(std::shared_ptr<WindowBase> win);
};


#endif /* TODO_CONTROLLER_HPP */