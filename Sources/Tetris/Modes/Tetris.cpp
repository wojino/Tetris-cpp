#include "Tetris.hpp"

int block[7][4][4][2] = {
    {   /* I block */
        {{0,1},{1,1},{2,1},{3,1}},
        {{2,0},{2,1},{2,2},{2,3}},
        {{0,2},{1,2},{2,2},{3,2}},
        {{1,0},{1,1},{1,2},{1,3}}
    },
    {   /* J block */
        {{0,0},{0,1},{1,1},{2,1}},
        {{1,0},{2,0},{1,1},{1,2}},
        {{0,1},{1,1},{2,1},{2,2}},
        {{1,0},{1,1},{0,2},{1,2}}
    },
    {   /* L block */
        {{2,0},{0,1},{1,1},{2,1}},
        {{1,0},{1,1},{1,2},{2,2}},
        {{0,1},{1,1},{2,1},{0,2}},
        {{0,0},{1,0},{1,1},{1,2}}
    },
    {   /* O block */
        {{1,0},{2,0},{1,1},{2,1}},
        {{1,0},{2,0},{1,1},{2,1}},
        {{1,0},{2,0},{1,1},{2,1}},
        {{1,0},{2,0},{1,1},{2,1}}
    },
    {   /* S block */
        {{1,0},{2,0},{0,1},{1,1}},
        {{1,0},{1,1},{2,1},{2,2}},
        {{1,1},{2,1},{0,2},{1,2}},
        {{0,0},{0,1},{1,1},{1,2}}
    },
    {   /* T block */
        {{1,0},{0,1},{1,1},{2,1}},
        {{1,0},{1,1},{2,1},{1,2}},
        {{0,1},{1,1},{2,1},{1,2}},
        {{1,0},{0,1},{1,1},{1,2}}
    },
    {   /* Z block */
        {{0,0},{1,0},{1,1},{2,1}},
        {{2,0},{1,1},{2,1},{1,2}},
        {{0,1},{1,1},{1,2},{2,2}},
        {{1,0},{0,1},{1,1},{0,2}}
    }
};

int wallkickNormal[2][4][5][2] = {
    {   /* CCW */
        {{ 0, 0},{ 1, 0},{ 1,-1},{ 0, 2},{ 1, 2}}, // 0 >> 3
        {{ 0, 0},{ 1, 0},{ 1, 1},{ 0,-2},{ 1,-2}}, // 1 >> 0
        {{ 0, 0},{-1, 0},{-1,-1},{ 0, 2},{-1, 2}}, // 2 >> 1
        {{ 0, 0},{-1, 0},{-1, 1},{ 0,-2},{-1,-2}}  // 3 >> 2
    },
    {   /* CW */
        {{ 0, 0},{-1, 0},{-1,-1},{ 0, 2},{-1, 2}}, // 0 >> 1
        {{ 0, 0},{ 1, 0},{ 1, 1},{ 0,-2},{ 1,-2}}, // 1 >> 2
        {{ 0, 0},{ 1, 0},{ 1,-1},{ 0, 2},{ 1, 2}}, // 2 >> 3
        {{ 0, 0},{-1, 0},{-1, 1},{ 0,-2},{-1,-2}}  // 3 >> 0
    }
    
};

int wallkickI[2][4][5][2] = {
    {   /* CCW */
        {{ 0, 0},{-1, 0},{ 2, 0},{-1,-2},{ 2, 1}}, // 0 >> 3
        {{ 0, 0},{ 2, 0},{-1, 0},{ 2,-1},{-1, 2}}, // 1 >> 0
        {{ 0, 0},{ 1, 0},{-2, 0},{ 1, 2},{-2, 1}}, // 2 >> 1
        {{ 0, 0},{-2, 0},{ 1, 0},{-2, 1},{ 1,-2}}  // 3 >> 2
    },
    {   /* CW */
        {{ 0, 0},{-2, 0},{ 1, 0},{-2, 1},{ 1,-2}}, // 0 >> 1
        {{ 0, 0},{-1, 0},{ 2, 0},{-1,-2},{ 2, 1}}, // 1 >> 2
        {{ 0, 0},{ 2, 0},{-1, 0},{ 2,-1},{-1, 2}}, // 2 >> 3
        {{ 0, 0},{ 1, 0},{-2, 0},{ 1, 2},{-2, 1}}  // 3 >> 0
    }
};

int map[BOARD_SIZE_X][BOARD_SIZE_Y] = {};

/* Initialize */
void TETRIS::init() {
    WINDOW::clrscr();
    TETRIS::drawBoard();

    Tetromino tetromino = TETRIS::addTetromino(0, 0, TYPE::S, 0);

    while(TETRIS::isGameContinue()) {
        KEY key = KEYBOARD::keyInput();
        CONTROL control = TETRIS::keyToControl(key);
        tetromino = TETRIS::controlTetromino(tetromino, control);
    }
}

/* Board */
void TETRIS::drawBoard() {
    int x = BOARD_X - 2;
    int y = BOARD_Y - 1;
    for(int i=0; i<(BOARD_SIZE_X+2)*BLOCK_SIZE; i+=BLOCK_SIZE) {
        WINDOW::print(x+i, y, BLOCK, COLOR::DARK_GRAY);
    }
    for(int i=0; i<(BOARD_SIZE_X+2)*BLOCK_SIZE; i+=BLOCK_SIZE) {
        WINDOW::print(x+i, y+BOARD_SIZE_Y+1, BLOCK, COLOR::DARK_GRAY);
    }
    for(int i=0; i<BOARD_SIZE_Y; i++) {
        WINDOW::print(x, y+i+1, BLOCK, COLOR::DARK_GRAY);
    }
    for(int i=0; i<BOARD_SIZE_Y; i++) {
        WINDOW::print(x+11*BLOCK_SIZE, y+i+1, BLOCK, COLOR::DARK_GRAY);
    }
}

/* Tetromino */
void TETRIS::drawTetromino(Tetromino tetromino, DRAW draw) {
    int x, y, i;

    switch(draw) {
        case DRAW::ON:
            for(i=0; i<4; i++) {
                x = BOARD_X + (tetromino.origin.X + block[static_cast<int>(tetromino.type)][tetromino.direction][i][0])*BLOCK_SIZE;
                y = BOARD_Y + tetromino.origin.Y + block[static_cast<int>(tetromino.type)][tetromino.direction][i][1];
                WINDOW::print(x, y, BLOCK);
            }
            break;
        
        case DRAW::OFF:
            for(i=0; i<4; i++) {
                x = BOARD_X + (tetromino.origin.X+ block[static_cast<int>(tetromino.type)][tetromino.direction][i][0])*BLOCK_SIZE;
                y = BOARD_Y + tetromino.origin.Y + block[static_cast<int>(tetromino.type)][tetromino.direction][i][1];
                WINDOW::print(x, y, BLANK);
            }
            break;   
    }
}

Tetromino TETRIS::controlTetromino(Tetromino tetromino, CONTROL control) {
    TETRIS::drawTetromino(tetromino, DRAW::OFF);
    Tetromino newTetromino = tetromino;

    switch(control) {
        case CONTROL::CCW:
            newTetromino.direction = (newTetromino.direction + 3) % 4;

            if(tetromino.type != TYPE::I) {
                for(int i=0; i<5; i++) {
                    newTetromino.origin.X = tetromino.origin.X + wallkickNormal[0][tetromino.direction][i][0];
                    newTetromino.origin.Y = tetromino.origin.Y + wallkickNormal[0][tetromino.direction][i][1];
                    if(TETRIS::isPositionAvailable(newTetromino)) {
                        break;
                    }
                }
            }
            else {
                for(int i=0; i<5; i++) {
                    newTetromino.origin.X = tetromino.origin.X + wallkickI[0][tetromino.direction][i][0];
                    newTetromino.origin.Y = tetromino.origin.Y + wallkickI[0][tetromino.direction][i][1];
                    if(TETRIS::isPositionAvailable(newTetromino)) {
                        break;
                    }
                }
            }
            
            
            break;
        
        case CONTROL::CW:
            newTetromino.direction = (newTetromino.direction + 1) % 4;

            if(tetromino.type != TYPE::I) {
                for(int i=0; i<5; i++) {
                    newTetromino.origin.X = tetromino.origin.X + wallkickNormal[1][tetromino.direction][i][0];
                    newTetromino.origin.Y = tetromino.origin.Y + wallkickNormal[1][tetromino.direction][i][1];
                    if(TETRIS::isPositionAvailable(newTetromino)) {
                        break;
                    }
                }
            }
            else {
                for(int i=0; i<5; i++) {
                    newTetromino.origin.X = tetromino.origin.X + wallkickI[1][tetromino.direction][i][0];
                    newTetromino.origin.Y = tetromino.origin.Y + wallkickI[1][tetromino.direction][i][1];
                    if(TETRIS::isPositionAvailable(newTetromino)) {
                        break;
                    }
                }
            }

            break;

        case CONTROL::LEFT:
            newTetromino.origin.X = newTetromino.origin.X - 1;

            if(!TETRIS::isPositionAvailable(newTetromino)) {
                newTetromino = tetromino;
            }

            break;

        case CONTROL::RIGHT:
            newTetromino.origin.X = newTetromino.origin.X + 1;

            if(!TETRIS::isPositionAvailable(newTetromino)) {
                newTetromino = tetromino;
            }
            
            break;
        
        case CONTROL::SOFTDROP:
            newTetromino.origin.Y = tetromino.origin.Y + 1;

            if(!TETRIS::isPositionAvailable(newTetromino)) {
                newTetromino = tetromino;
            }

            break;
        
        case CONTROL::HARDDROP:
            newTetromino.origin.Y = tetromino.origin.Y + 1;

            if(!TETRIS::isPositionAvailable(newTetromino)) {
                newTetromino = tetromino;
            }
            
            break;
    }

    TETRIS::drawTetromino(newTetromino, DRAW::ON);
    return newTetromino;
}

Tetromino TETRIS::addTetromino(int x, int y, TYPE _type, int _direction) {
    Tetromino tetromino;
    tetromino.origin = {static_cast<short>(x), static_cast<short>(y)};
    tetromino.type = _type;
    tetromino.direction = _direction;
    
    TETRIS::drawTetromino(tetromino, DRAW::ON);

    return tetromino;
}

bool TETRIS::isPositionAvailable(Tetromino tetromino) {
    for(int i=0; i<4; i++) {
        int x = tetromino.origin.X + block[static_cast<int>(tetromino.type)][tetromino.direction][i][0];
        int y = tetromino.origin.Y + block[static_cast<int>(tetromino.type)][tetromino.direction][i][1];
        
        if((x < 0) || (x >= BOARD_SIZE_X) || (y < 0) || (y >=BOARD_SIZE_Y)) {
            return FALSE;
        }
        
        if(map[x][y] == 1) {
            return FALSE;
        }
    }

    return TRUE;
}

/* Game */
bool TETRIS::isGameContinue() {
    return TRUE;
}

/* Util */
CONTROL TETRIS::keyToControl(KEY key) {
    switch(key) {
        case KEY::z:
        case KEY::Z:
            return CONTROL::CCW;
        
        case KEY::x:
        case KEY::X:
            return CONTROL::CW;
        
        case KEY::LEFT:
            return CONTROL::LEFT;
        
        case KEY::RIGHT:
            return CONTROL::RIGHT;
        
        case KEY::DOWN:
            return CONTROL::SOFTDROP;
        
        case KEY::UP:
            return CONTROL::HARDDROP;

        default:
            return CONTROL::SOFTDROP;

    }
}