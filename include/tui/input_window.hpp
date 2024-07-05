#ifndef INPUT_WINDOW_HPP
#define INPUT_WINDOW_HPP

#include "window.hpp"

class InputWindow : public WindowBase
{
private:
    std::string input;
public:
    InputWindow(std::string WinName);
    std::string getInput() const; 
    void clear() ;
    void display() override;
    void update() override;
    char run() override;
};



#endif /* INSERT_WINDOW_HPP */