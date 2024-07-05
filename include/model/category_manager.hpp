#ifndef CATEGORY_MANAGER_HPP
#define CATEGORY_MANAGER_HPP

#include <iostream>
#include <vector>
#include <algorithm>

class CategoryManager
{
private:
    std::vector<std::string> categories;
public:
    CategoryManager() = default;
    void setCategories(std::vector<std::string> &&_categories);
    bool isCategory(std::string& category) const;
    void addCategory(std::string& category);
    void removeCategory(std::string& category);
    std::vector<std::string> getCategories() const;
};





#endif /* CATEGORY_MANAGER_HPP */