#include "KeyboardHelpers.hpp"

KEY KEYBOARD::keyInput() {
    KEY input = static_cast<KEY>(_getch());

    if (input == KEY::MAGIC_KEY) {
        input = static_cast<KEY>(_getch());
    }

    if ((input == KEY::q) || (input==KEY::Q)) {
        WINDOW::clrscr();
        exit(0);
    }

    return input;
}
