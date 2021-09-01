#include "Menu.hpp"

void MENU::init() {
    WINDOW::clrscr();

    switch(MENU::selectMode()) {
        case MODE::TETRIS:
            TETRIS::init();
            break;
        
        case MODE::LEADERBOARD:
            LEADERBOARD::init();
            break;
        
        case MODE::OPTION:
            OPTION::init();
            break;
    }
}

MODE MENU::selectMode() {
    std::string mode[5] = {"1. Tetris", "2. Leaderboard", "3. Option"};    

    return static_cast<MODE>(WINDOW::selectMenu(3, mode));
}
