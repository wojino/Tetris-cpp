#ifndef TETRIS_TETRIS_HPP
#define TETRIS_TETRIS_HPP

#include "KeyboardHelpers.hpp"
#include "WindowHelpers.hpp"

#define BOARD_SIZE_Y 20
#define BOARD_SIZE_X 10

#define BOARD_X 10
#define BOARD_Y 5

#define BLOCK "[]"
#define BLOCK_SIZE 2

enum class TYPE {
    I, J, L, O, S, T, Z
};

enum class DRAW {
    ON, OFF
};

enum class CONTROL {
    CCW, CW, LEFT, RIGHT, SOFTDROP, HARDDROP
};


// https://tetris.fandom.com/wiki/SRS#Spawn_Orientation_and_Location
extern int block[7][4][4][2];
extern int wallkickNormal[2][4][5][2];
extern int wallkickI[2][4][5][2];
extern int map[BOARD_SIZE_X][BOARD_SIZE_Y];


typedef struct _Tetromino {
    COORD origin;
    TYPE type;
    int direction;

    _Tetromino(COORD _origin, TYPE _type, int _direction):
        origin{_origin}, type{_type}, direction{_direction} {}
    
    _Tetromino():
        origin{{}}, type{TYPE::I}, direction{0} {}

} Tetromino;

namespace TETRIS {
    /* Initialize */
    void init();

    /* Board */
    void drawBoard();

    /* Tetromino */
    void drawTetromino(Tetromino tetromino, DRAW draw);
    Tetromino controlTetromino(Tetromino tetromino, CONTROL control);
    Tetromino addTetromino(int x, int y, TYPE _type, int _direction);
    bool isPositionAvailable(Tetromino tetromino);
    /* Game */
    bool isGameContinue();
    // bool isLineClear(int n);

    /* Util */
    CONTROL keyToControl(KEY key);
}

#endif
