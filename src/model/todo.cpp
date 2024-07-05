#include "todo.hpp"


Todo::Todo(std::string _name, std::string _description, std::string _category,
    TodoPriority _priority, bool _isDone, std::string _creationDate)
    : name(_name), description(_description), category(_category),
      priority(_priority), isDone(_isDone), creationDate(_creationDate)
    
{ }

Todo::Todo(std::string _name, std::string _description, std::string _category,
    TodoPriority _priority)
    : name(_name), description(_description), 
      category(_category), priority(_priority), isDone(false)
{ 
    const std::chrono::year_month_day ymd = std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());
    std::string day = std::to_string(static_cast<unsigned int>(ymd.day()));
    std::string month = std::to_string(static_cast<unsigned int>(ymd.month()));
    std::string year = std::to_string(static_cast<int>(ymd.year()));

    this->creationDate = day+"-"+month+"-"+year;
}


std::string Todo::getDescription() const {
    return this->description;
}

std::string Todo::getName() const {
    return this->name;
}

std::string Todo::getCategory() const {
    return this->category;
}
std::string Todo::getCreationDate() const {
    return this->creationDate;
}

std::string Todo::getPriority() const {
    switch (this->priority)
    {
    case TodoPriority::None:
        return "None";
    case TodoPriority::Low:
        return "Low";
    case TodoPriority::Medium:
        return "Medium";
    case TodoPriority::High:
        return "High";
    }
}

void Todo::setName(const std::string &_name) {
    this->name = _name;
}
void Todo::setDescription(const std::string &_description) {
    this->description = _description;
}

void Todo::setCategory(const std::string &_category) {
    this->category = _category;
}

void Todo::setCreationDate(const std::string &_creationDate) {
    this->creationDate = _creationDate;
}

void Todo::setPriority(const std::string &_priority){
    switch (_priority[0])
    {
    case 'N':
    case 'n':
        this->priority = TodoPriority::None;
        break;
    case 'L':
    case 'l':
        this->priority = TodoPriority::Low;
        break;
    case 'M':
    case 'm':
        this->priority = TodoPriority::Medium;
        break;
    case 'H':
    case 'h':
        this->priority = TodoPriority::High;
        break;
    }
}

void Todo::setIsDone(bool _isDone) {
    this->isDone = _isDone;
}

bool Todo::hasDone() const {
    return this->isDone;
}

void Todo::setTodoDone() {
    this->isDone = true;
}

bool Todo::operator<(const Todo & otherTodo) const {
    return this->priority < otherTodo.priority;
}

std::string Todo::todoToString() const {
    return this->name + std::string(" @") + this->category;
}
