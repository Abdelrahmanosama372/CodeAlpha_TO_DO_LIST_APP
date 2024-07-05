#include "tui_manager.hpp"
#define spacing 1
#define inputWinSize 3

#define COLOR_BLUE_CUSTOM   10
#define COLOR_SKY_CUSTOM    11
#define COLOR_GRAY_CUSTOM   12

static TodoController* todoControllerInstance = nullptr;

TuiManager::TuiManager(TodoController &_todoController) 
    : todoController(_todoController) {
    // Set up the signal handler for window resize
    std::signal(SIGWINCH, TuiManager::handle_winsResize);
}


void TuiManager::tuiIntialize(std::array<std::shared_ptr<WindowBase>,5> &&_wins) {
    // Initialize ncurses
    initscr();

    // start color and init TUI colors
    start_color();
    init_color(COLOR_BLUE_CUSTOM, 27, 97, 292);
    init_color(COLOR_SKY_CUSTOM, 31, 513, 584);
    init_color(COLOR_GRAY_CUSTOM, 921, 956, 964);

    init_pair(1, COLOR_SKY_CUSTOM, COLOR_BLUE_CUSTOM);
    init_pair(2, COLOR_GRAY_CUSTOM, COLOR_SKY_CUSTOM);
   

    // apply a background color for the stdscr
    wbkgd(stdscr, COLOR_PAIR(1));
    refresh();


    noecho();

    if (has_colors() == FALSE) {
        wprintw(stdscr,"Your terminal does not support color\n");
        endwin();
        exit(1);
    }

   

    
    this->wins = std::move(_wins);
    resizeAllWins();
    updateAllWins();

    this->currWinIt = this->wins.begin()+1;

    // refresh();
    // notify sys begin
}

void TuiManager::tuiRun() {
    if(this->currWinIt < this->wins.begin())
        this->currWinIt = this->wins.begin();

    if(this->currWinIt >= this->wins.end())
        this->currWinIt = this->wins.end() - 1;

    char ch = (*this->currWinIt)->run();

    switch (ch)
    {
        case 'L':
            this->currWinIt++;
            break;

        case 'H':
            this->currWinIt--;
            break;
        
        case 'K':
            this->currWinIt-=2;
            break;

        case 'J':
            this->currWinIt+=2;
            break;

        case 'i':
            todoController.handleInsertion();
            this->currWinIt++;
            break;

        case 'd':
            todoController.handleDone();
            break;
    
        case 'x':
            todoController.handleDeletion(*currWinIt);
            break;

        case 10: 
            if(this->currWinIt == this->wins.end()-1) { // check if this enter is form category Window 
                todoController.handlePreviewCategory();
            }else {
                todoController.handlePreviewTodo(*currWinIt);
            }
            break;
    }
}

TuiManager& TuiManager::getTuiManager(TodoController &_todoController) {
    if (!todoControllerInstance) {
        todoControllerInstance = &_todoController;
    }
    static TuiManager tuiManager(*todoControllerInstance);
    return tuiManager;
}

void TuiManager::handle_winsResize(int sig) {
    TuiManager &tuiManager = TuiManager::getTuiManager(*todoControllerInstance);
    tuiManager.resizeAllWins();
    tuiManager.updateAllWins();
}

void TuiManager::resizeAllWins() {
    // get terminal size
    int yMax, xMax;
    while (true)
    {
        getmaxyx(stdscr, xMax, yMax);
        if(xMax < 20 || yMax < 70) {
            wprintw(stdscr, "Please enlarge the terminal window to at least 20 rows and 70 columns and enter any character %d %d\n",yMax,xMax);
            getch();
            refresh();
        }else {
            break;
        }
    }

    // input win
    this->wins[0]->setWin(3,yMax,0,0);

    int xRest = xMax - inputWinSize - 2*spacing;
    int yRest = yMax - spacing;

    // todo win
    this->wins[1]->setWin(xRest/2, yRest/2, inputWinSize + spacing, 0);

    // preview win
    this->wins[2]->setWin(xRest/2, yRest/2, inputWinSize + spacing, yRest/2 + spacing);

    // done win
    this->wins[3]->setWin(xRest/2, yRest/2,  inputWinSize + spacing + xRest/2 + spacing, 0);

    // category win
    this->wins[4]->setWin(xRest/2, yRest/2, inputWinSize + spacing + xRest/2 + spacing, yRest/2 + spacing);

    // this->wins[1]->run();
}


void TuiManager::updateAllWins() {
    for(auto &win : this->wins){
        win->update();
    }
}


void tuiRun(){

}
TuiManager::~TuiManager()
{
    // End ncurses session
    endwin();
}