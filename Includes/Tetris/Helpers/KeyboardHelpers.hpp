#ifndef KEYBOARD_HELPERS_HPP
#define KEYBOARD_HELPERS_HPP

#include "WindowHelpers.hpp"

#include <conio.h>
#include <windows.h>
#include <string>
#include <cstdio>

/* Keys */
enum class KEY {
    MAGIC_KEY = 224,
    UP = 72,
    LEFT = 75,
    RIGHT = 77,
    DOWN = 80,
    q = 113,
    Q = 81,
    z = 122,
    Z = 90
};

namespace KEYBOARD {
    int keyInput();
}

#endif