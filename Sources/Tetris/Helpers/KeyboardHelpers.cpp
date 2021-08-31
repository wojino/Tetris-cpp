#include "KeyboardHelpers.hpp"

int KEYBOARD::keyInput() {
    int input = _getch();

    if (static_cast<KEY>(input) == KEY::MAGIC_KEY) {
        input = _getch();
    }

    if ((static_cast<KEY>(input) == KEY::q) || (static_cast<KEY>(input) ==KEY::Q)) {
        WINDOW::clrscr();
        exit(0);
    }

    return input;
}