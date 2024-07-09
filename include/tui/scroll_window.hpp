#ifndef SCROLL_WINDOW_HPP
#define SCROLL_WINDOW_HPP

#include "window.hpp"
#include <vector>

class ScrollWindow : public WindowBase
{
protected:
    std::vector<std::string> records;
    std::vector<std::string>::iterator winBegin;
    std::vector<std::string>::iterator winEnd;
    std::vector<std::string>::iterator CurrRecord; // set to begin()
    bool isActiveWin;
public:
    ScrollWindow(std::string winName);
    void setRecords(std::vector<std::string> &&_records);
    void setWinFrame();

    void incrementWinFrame();
    void decrementWinFrame();

    void goToNextRecord();
    void goToPrevRecord();

    std::string getCurrRecord() const;
    void deleteCurrRecord();
    void addRecord(const std::string &record);
    
    void update() override;
};


#endif /* SCROLLABLE_WINDOW */