#ifndef TODO_MANAGER_HPP
#define TODO_MANAGER_HPP

#include "todo.hpp"
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <numeric>

class TodoManager
{
private:
    std::unordered_map<std::string, Todo> todosMap;
    unsigned int doneTodosNum;
    unsigned int todosNum;

    void sortTodos(std::vector<Todo> &todos);
public:
    void addTodo(Todo &&todo);
    void addTodo(const std::string &todo);

    void markTodoDone(const std::string &todoName);

    void deleteTodo(const std::string& todoName);

    Todo getTodo(const std::string& todoName);

    std::string getTodoName(const std::string& todo);

    unsigned int getDoneTodosNum() const;
    unsigned int getTodosNum() const;

    
    std::pair<std::vector<std::string>,std::vector<std::string>> 
        getTodosByCategory(const std::string& category);

    void print(){
        for(auto &pair: todosMap) {
            std::cout << pair.first << " " << pair.second.getName() << std::endl;
        }
    }
    
};




#endif /* TODO_MANAGER_HPP */