#ifndef TODO_HPP
#define TODO_HPP

#include <iostream>
#include <chrono>

enum class TodoPriority {
    High, 
    Medium,
    Low,
    None,
};

class Todo
{
private:
    std::string name;
    std::string description;
    std::string category;
    std::string creationDate;
    TodoPriority priority;
    bool isDone;

public:
    Todo() = default;
    Todo(std::string _name, std::string _description, std::string _category,
        TodoPriority _priority);
    Todo(std::string _name, std::string _description, std::string _category,
        TodoPriority _priority, bool _isDone, std::string _creationDate);

    std::string getDescription() const;
    std::string getName() const;
    std::string getCategory() const;
    std::string getCreationDate() const;
    std::string getPriority() const;

    void  setName(const std::string &_name);
    void  setDescription(const std::string &_description);
    void  setCategory(const std::string &_category);
    void  setCreationDate(const std::string &_creationDate);
    void  setPriority(const std::string &_priority);
    void  setIsDone(bool _isDone);

    bool hasDone() const;
    void setTodoDone(); 

    bool operator<(const Todo &) const;

    std::string todoToString() const;

    Todo(const Todo &) noexcept = default ;
    Todo(Todo &&) = default;

    Todo operator=(const Todo &) = delete;
    Todo& operator=(Todo &&) noexcept = default;
};



#endif // TODO_HPP
