#include "todo_controller.hpp"

TodoController::TodoController(TodoManager &_todoManager, CategoryManager &_categoryManager,
    std::array<std::shared_ptr<WindowBase>,5> &wins)
    : todoManager(_todoManager), categoryManager(_categoryManager)
{
    // since the order of the todos is constant 
    // so every element in array is know to which it can be casted 
    // so static casting is used
    this->inputWin = std::static_pointer_cast<InputWindow>(wins[0]);
    this->todoWin = std::static_pointer_cast<TodoWindow>(wins[1]);
    this->previewWin = std::static_pointer_cast<PreviewWindow>(wins[2]);
    this->doneWin = std::static_pointer_cast<DoneWindow>(wins[3]);
    this->categoryWin = std::static_pointer_cast<CategoryWindow>(wins[4]);
}

void TodoController::loadFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << fileName << std::endl;
        exit(1);
    }

    nlohmann::json j;
    file >> j;

    // parse categories
    if (j.contains("categories")) {
        this->categoryManager.setCategories(std::move(j["categories"].get<std::vector<std::string>>()));
    }


    // Parse todos
    if (j.contains("todos")) {
        for (const auto& item : j["todos"]) {
            Todo todo;
            todo.setName((item["name"].get<std::string>()));
            todo.setDescription(item["description"].get<std::string>());
            todo.setCategory(item["category"].get<std::string>());
            todo.setCreationDate(item["creation_date"].get<std::string>());
            todo.setPriority(item["priority"].get<std::string>());
            todo.setIsDone(item["is_done"].get<bool>());
            todoManager.addTodo(std::move(todo));
        }
    }

    // set records for scroll windows
    this->categoryWin->setRecords(std::move(this->categoryManager.getCategories()));

    auto recordsPair = this->todoManager.getTodosByCategory("All Tasks");
    this->todoWin->setRecords(std::move(recordsPair.first));
    this->doneWin->setRecords(std::move(recordsPair.second));

    file.close();
}

void TodoController::handleInsertion() {
    std::string todo = this->inputWin->getInput();

    if (todo.empty())
        return;

    todoManager.addTodo(todo);
    this->inputWin->clear();
    this->inputWin->update();

    std::string todoName = todoManager.getTodoName(todo);
    this->todoWin->addRecord(todoManager.getTodo(todoName).todoToString());
    // this->todoWin->update();
}

void TodoController::handleDone() {
    std::string todo = this->todoWin->getCurrRecord();
    todoManager.markTodoDone(todo);
    this->todoWin->deleteCurrRecord();
    this->doneWin->addRecord(todo);
    this->doneWin->update();
}

void TodoController::handlePreviewCategory() {
    auto recordsPair = this->todoManager.getTodosByCategory(this->categoryWin->getCurrRecord());
    this->todoWin->setRecords(std::move(recordsPair.first));
    this->doneWin->setRecords(std::move(recordsPair.second));
    
    this->todoWin->clearWin();
    this->doneWin->clearWin();

    this->todoWin->update();
    this->doneWin->update();
}

void TodoController::handlePreviewTodo(std::shared_ptr<WindowBase> win) {
    std::shared_ptr<ScrollWindow> scrollWin = std::static_pointer_cast<ScrollWindow>(win);
    std::string todoName = todoManager.getTodoName(scrollWin->getCurrRecord());
    Todo todo = todoManager.getTodo(todoName);
    this->previewWin->setTodo(std::move(todo));
    this->previewWin->update();
}

void TodoController::handleDeletion(std::shared_ptr<WindowBase> win) {
    std::shared_ptr<ScrollWindow> scrollWin = std::static_pointer_cast<ScrollWindow>(win);
    scrollWin->deleteCurrRecord();
    scrollWin->update();
}