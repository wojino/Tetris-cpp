#include "KeyboardHelpers.hpp"
#include "WindowHelpers.hpp"
#include "Menu.hpp"
#include "Tetris.hpp"

int main() {
    WINDOW::init();
    
    MENU::init();

    _getch();

    return 0;
}