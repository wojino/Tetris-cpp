#ifndef TETRIS_MENU_HPP
#define TETRIS_MENU_HPP

#include "KeyboardHelpers.hpp"
#include "WindowHelpers.hpp"
#include "Tetris.hpp"
#include "Leaderboard.hpp"
#include "Option.hpp"

/* Modes */
enum class MODE {
    TETRIS,
    LEADERBOARD,
    OPTION
};

namespace MENU {
    void init();
    MODE selectMode();
}

#endif
