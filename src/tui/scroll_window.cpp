#include "scroll_window.hpp"

ScrollWindow::ScrollWindow(std::string winName)
    : WindowBase(winName)
{ }

void ScrollWindow::setRecords(std::vector<std::string> &&_records) {
    this->records = std::move(_records);
    this->CurrRecord = this->records.end(); // to be valid refrence
}

void ScrollWindow::setWinFrame() {
    this->winBegin = this->records.begin();

    if(CurrRecord == this->records.end())
        this->CurrRecord = this->records.begin();

    if(this->getWinRows() < this->records.size() + 2 ){
        if(this->CurrRecord == this->records.begin())
            this->winEnd = this->records.begin() + this->getWinRows() - 2;
    }else {
        this->winEnd = this->records.end();
    }
}

void ScrollWindow::incrementWinFrame() {
    if(this->winEnd == this->records.end()){
        return;
    }else {
        this->winBegin++;
        this->winEnd++;
    }
}
void ScrollWindow::decrementWinFrame() {
    if(this->winBegin == this->records.begin()){
        return;
    }else {
        this->winBegin--;
        this->winEnd--;
    }
}

void ScrollWindow::goToNextRecord() {
    if(this->CurrRecord == this->winEnd - 1) {
        // we are at end of window
        this->incrementWinFrame();
    }

    if(!(this->CurrRecord == this->winEnd - 1))
        this->CurrRecord++;
}

void ScrollWindow::goToPrevRecord() {
    if(this->CurrRecord == this->records.begin()){
        return;
    }

    if(this->CurrRecord == this->winBegin) {
        // we are at begin of window
        this->decrementWinFrame();
    }
    this->CurrRecord--;
}

std::string ScrollWindow::getCurrRecord() const {
    return *CurrRecord;
}

void ScrollWindow::deleteCurrRecord() {
    std::vector<std::string>::iterator nextRecord;

    if(this->CurrRecord == this->records.begin()){
        nextRecord = this->CurrRecord + 1;
    }else {
        nextRecord = this->CurrRecord - 1;
    }

    this->records.erase(this->CurrRecord);
    this->CurrRecord = nextRecord;

    // clear win
    this->clearWin();
}

void ScrollWindow::addRecord(const std::string &record) {
    int distance = std::distance(this->records.begin(),this->CurrRecord);
    this->records.push_back(record);
    
    // update the itertors
    this->winBegin = this->records.begin();
    this->CurrRecord = this->records.begin();
}

void ScrollWindow::display() {
    WINDOW **win = this->getWin();
    int i=0;

    wbkgd(*win, COLOR_PAIR(2));
    wattron(*win, COLOR_PAIR(2));

    for(auto it = this->winBegin; it != this->winEnd; it++, i++) {
        if(it == this->CurrRecord) {
            wattron(*win, A_REVERSE);
        }
        mvwprintw(*win, i+1, 1, (*it).c_str());
        wclrtoeol(*win);
        wattroff(*win, A_REVERSE);        
    }

    wattroff(*win, COLOR_PAIR(2));
    wrefresh(*win);
}


void ScrollWindow::update() {
    setWinFrame();
    display();
}