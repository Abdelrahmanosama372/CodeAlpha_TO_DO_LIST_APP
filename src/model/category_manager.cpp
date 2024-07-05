#include "category_manager.hpp"


void CategoryManager::setCategories(std::vector<std::string> &&_categories) {
    this->categories = std::move(_categories);
}

bool CategoryManager::isCategory(std::string& category) const {
    auto category_it = std::find(this->categories.begin(),
                            this->categories.end(),
                            category);
    if(category_it != this->categories.end()){
        return true;
    }else {
        return false;
    }
}

void CategoryManager::addCategory(std::string& category) {
    this->categories.push_back(category);
}

void CategoryManager::removeCategory(std::string& category) {
    auto category_it = std::remove(this->categories.begin(),
                            this->categories.end(),
                            category);
    if(category_it != this->categories.end()){
        this->categories.pop_back();
    }
}

std::vector<std::string> CategoryManager::getCategories() const {
    return this->categories;
}