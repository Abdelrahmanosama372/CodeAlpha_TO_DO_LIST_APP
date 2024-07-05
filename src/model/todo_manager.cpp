#include "todo_manager.hpp"

/* declaration of helper functions */
std::vector<std::string> splitString(const std::string& str, char delimiter);

 /* private functions */
void TodoManager::sortTodos(std::vector<Todo> &todos) {
    std::sort(todos.begin(),todos.end());
}


/* public functions */
void TodoManager::addTodo(Todo &&todo) {
    std::string todoName = todo.getName();
    this->todosMap.emplace(todoName,std::move(todo));
}

void TodoManager::addTodo(const std::string &todo) {

    std::string todoName;
    std::string description;
    std::string category;
    TodoPriority priority = TodoPriority::None;
   
    std::vector<std::string> todoStrSplit = splitString(todo, ' ');

    for (auto it = todoStrSplit.begin() + 1; it != todoStrSplit.end(); it++)
    {
        if((*it)[0] == '@'){
            todoName = std::accumulate(todoStrSplit.begin(),it,std::string(),
                [](const std::string & str1, const std::string & str2)
                {
                    return str1 + (str1.length() > 0 ? " " : "") + str2;
                });
            category = (*it).substr(1);
        }else if ((*it)[0] == '#'){
            if((*it).size() > 1){
                switch ((*it)[1])
                {
                case 'H':
                case 'h':
                    priority = TodoPriority::High;
                    break;

                case 'M':
                case 'm':
                    priority = TodoPriority::High;
                    break;

                case 'L':
                case 'l':
                    priority = TodoPriority::High;
                    break;
                }
            }
        }else if((*it)[0] == '|') {
            description = std::accumulate(it+1,todoStrSplit.end(),std::string(),
                [](const std::string & str1, const std::string & str2)
                {
                    return str1 + (str1.length() > 0 ? " " : "") + str2;
                });
        }
    }

    Todo todoToAdd(todoName, description, category, priority);
    addTodo(std::move(todoToAdd));
}

void TodoManager::markTodoDone(const std::string &todoName) {
    if(this->todosMap.find(todoName) != todosMap.end()){
        todosMap[todoName].setTodoDone();
    }
}


void TodoManager::deleteTodo(const std::string& todoName) {
    auto map_it = this->todosMap.find(todoName);
    if(map_it != this->todosMap.end())
        this->todosMap.erase(map_it);
}

Todo TodoManager::getTodo(const std::string& todoName) {
    auto map_it = this->todosMap.find(todoName);
    if (map_it != this->todosMap.end())
        return map_it->second; 
}

std::string TodoManager::getTodoName(const std::string& todo) {
    std::string todoName = splitString(todo,'@')[0];
    
    // remove spaces at end of name
    while (todoName[todoName.size() - 1] == ' ')
        todoName.pop_back();
    
    return todoName;
}

std::pair<std::vector<std::string>,std::vector<std::string>> 
    TodoManager::getTodosByCategory(const std::string& category){

    std::vector<Todo> doneTodos;
    std::vector<Todo> notDoneTodos; 

    for(const auto &todoPair : this->todosMap){
        if(category == "All Tasks" || todoPair.second.getCategory() == category) {
            if(todoPair.second.hasDone())
                doneTodos.push_back(todoPair.second);
            else 
                notDoneTodos.push_back(todoPair.second);
        }
    }

    sortTodos(doneTodos);
    sortTodos(notDoneTodos);

    std::vector<std::string> doneTodosStrPair;
    doneTodosStrPair.reserve(doneTodos.size());
    for(auto &todo : doneTodos){
        doneTodosStrPair.push_back(std::move(todo.todoToString()));
    }

    std::vector<std::string> notDoneTodosStrPair;
    notDoneTodosStrPair.reserve(notDoneTodos.size());
        for(auto &todo : notDoneTodos){
        notDoneTodosStrPair.push_back(std::move(todo.todoToString()));
    }

    return {notDoneTodosStrPair, doneTodosStrPair};
}

unsigned int TodoManager::getDoneTodosNum() const {
    return this->doneTodosNum;
}
unsigned int TodoManager::getTodosNum() const {
    return this->todosNum;
}

/* helper functions */
std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> stringSplit;
    size_t start = 0;
    size_t end = 0;
    while ((end = str.find(delimiter, start)) != std::string::npos) {
        if (end > start) {
            stringSplit.push_back(str.substr(start, end - start));
        }
        start = end + 1;
    }
    if (start < str.size()) {
        stringSplit.push_back(str.substr(start));
    }
    return stringSplit;
}


