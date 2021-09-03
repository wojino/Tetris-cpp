#ifndef TETRIS_TETRIS_HPP
#define TETRIS_TETRIS_HPP

#include "KeyboardHelpers.hpp"
#include "WindowHelpers.hpp"

#include <random>
#include <ctime>

#define BOARD_SIZE_Y 22
#define BOARD_SIZE_X 10

#define BOARD_X 10
#define BOARD_Y 5

#define START_X 3
#define START_Y 0

#define BLOCK "[]"
#define BLOCK_SIZE 2

enum class TYPE {
    I, J, L, O, S, T, Z
};

enum class STATE {
    ON, OFF, FIX
};

enum class CONTROL {
    CCW, CW, LEFT, RIGHT, SOFTDROP, HARDDROP
};

typedef struct _Tetromino {
    COORD origin;
    TYPE type;
    int direction;
} Tetromino;

namespace TETRIS {
    extern int block[7][4][4][2];
    extern int wallkickNormal[2][4][5][2];
    extern int wallkickI[2][4][5][2];
    extern bool map[BOARD_SIZE_X][BOARD_SIZE_Y];

    /* Initialize */
    void init();

    /* Board */
    void drawBoard();

    /* Tetromino */
    void drawTetromino(Tetromino tetromino, STATE state);
    void mapTetromino(Tetromino tetromino, STATE state);
    void controlTetromino(Tetromino &tetromino, CONTROL control);
    Tetromino addTetromino(int x, int y, TYPE _type, int _direction);
    bool isPositionAvailable(Tetromino tetromino);
    bool isDownAvailable(Tetromino tetromino);

    /* Game */
    bool isGameContinue();

    /* Util */
    CONTROL keyToControl(KEY key);
    int* randomGenerator();
}

#endif
