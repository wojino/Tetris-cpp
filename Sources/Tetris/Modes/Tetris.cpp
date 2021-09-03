#include "Tetris.hpp"


int TETRIS::block[7][4][4][2] = {
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

int TETRIS::wallkickNormal[2][4][5][2] = {
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

int TETRIS::wallkickI[2][4][5][2] = {
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

bool TETRIS::map[BOARD_SIZE_X][BOARD_SIZE_Y] = {false};

/* Initialize */
void TETRIS::init() {
    WINDOW::clrscr();
    TETRIS::drawBoard();

    int n=0;
    int* randomArray = TETRIS::randomGenerator();
    
    Tetromino tetromino = TETRIS::addTetromino(START_X, START_Y, static_cast<TYPE>(randomArray[n]), 0);
    
    while(TETRIS::isGameContinue()) {
        KEY key = KEYBOARD::keyInput();
        CONTROL control = TETRIS::keyToControl(key);

        if(control == CONTROL::HARDDROP) {
            TETRIS::controlTetromino(tetromino, control);
            TETRIS::drawTetromino(tetromino, STATE::FIX);
            TETRIS::mapTetromino(tetromino, STATE::FIX);

            n++;
            tetromino = TETRIS::addTetromino(START_X, START_Y, static_cast<TYPE>(randomArray[n]), 0);
        }
        else if((!TETRIS::isDownAvailable(tetromino)) && (control == CONTROL::SOFTDROP)) {
            TETRIS::drawTetromino(tetromino, STATE::FIX);
            TETRIS::mapTetromino(tetromino, STATE::FIX);

            n++;
            tetromino = TETRIS::addTetromino(START_X, START_Y, static_cast<TYPE>(randomArray[n]), 0);
        }
        else {
            TETRIS::controlTetromino(tetromino, control);
        }
    }
    
}

/* Board */
void TETRIS::drawBoard() {
    int x = BOARD_X - 2;
    int y = BOARD_Y + 1;
    // up
    for(int i=0; i<(BOARD_SIZE_X+2)*BLOCK_SIZE; i+=BLOCK_SIZE) {
        WINDOW::print(x+i, y, BLOCK, COLOR::DARK_GRAY);
    }
    // down
    for(int i=0; i<(BOARD_SIZE_X+2)*BLOCK_SIZE; i+=BLOCK_SIZE) {
        WINDOW::print(x+i, y+BOARD_SIZE_Y-1, BLOCK, COLOR::DARK_GRAY);
    }
    // left
    for(int i=0; i<BOARD_SIZE_Y-2; i++) {
        WINDOW::print(x, y+i+1, BLOCK, COLOR::DARK_GRAY);
    }
    // right
    for(int i=0; i<BOARD_SIZE_Y-2; i++) {
        WINDOW::print(x+11*BLOCK_SIZE, y+i+1, BLOCK, COLOR::DARK_GRAY);
    }
}

/* Tetromino */
void TETRIS::drawTetromino(Tetromino tetromino, STATE state) {
    int x, y, i;

    switch(state) {
        case STATE::ON:
            for(i=0; i<4; i++) {
                x = BOARD_X + (tetromino.origin.X + block[static_cast<int>(tetromino.type)][tetromino.direction][i][0])*BLOCK_SIZE;
                y = BOARD_Y + tetromino.origin.Y + block[static_cast<int>(tetromino.type)][tetromino.direction][i][1];
                if(y < BOARD_Y+2) continue;
                WINDOW::print(x, y, BLOCK);
            }
            break;
        
        case STATE::OFF:
            for(i=0; i<4; i++) {
                x = BOARD_X + (tetromino.origin.X+ block[static_cast<int>(tetromino.type)][tetromino.direction][i][0])*BLOCK_SIZE;
                y = BOARD_Y + tetromino.origin.Y + block[static_cast<int>(tetromino.type)][tetromino.direction][i][1];
                if(y < BOARD_Y+2) continue;
                WINDOW::print(x, y, BLANK);
            }
            break;
        
        case STATE::FIX:
            for(i=0; i<4; i++) {
                x = BOARD_X + (tetromino.origin.X+ block[static_cast<int>(tetromino.type)][tetromino.direction][i][0])*BLOCK_SIZE;
                y = BOARD_Y + tetromino.origin.Y + block[static_cast<int>(tetromino.type)][tetromino.direction][i][1];
                if(y < BOARD_Y+2) continue;
                WINDOW::print(x, y, BLOCK, COLOR::DARK_BLUE);
            }
            break;
    }
}

void TETRIS::mapTetromino(Tetromino tetromino, STATE state) {
    int x, y, i;

    switch(state) {
        case STATE::ON:
            for(i=0; i<4; i++) {
                x = tetromino.origin.X + block[static_cast<int>(tetromino.type)][tetromino.direction][i][0];
                y = tetromino.origin.Y + block[static_cast<int>(tetromino.type)][tetromino.direction][i][1];
                map[x][y] = true;
            }
            break;
        
        case STATE::OFF:
            for(i=0; i<4; i++) {
                x = tetromino.origin.X + block[static_cast<int>(tetromino.type)][tetromino.direction][i][0];
                y = tetromino.origin.Y + block[static_cast<int>(tetromino.type)][tetromino.direction][i][1];
                map[x][y] = false;
            }
            break;
        
        case STATE::FIX:
            for(i=0; i<4; i++) {
                x = tetromino.origin.X + block[static_cast<int>(tetromino.type)][tetromino.direction][i][0];
                y = tetromino.origin.Y + block[static_cast<int>(tetromino.type)][tetromino.direction][i][1];
                map[x][y] = true;
            }
            break;
    }
}

void TETRIS::controlTetromino(Tetromino &tetromino, CONTROL control) {
    TETRIS::drawTetromino(tetromino, STATE::OFF);
    TETRIS::mapTetromino(tetromino, STATE::OFF);
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
            newTetromino.origin.Y = newTetromino.origin.Y + 1;

            if(!TETRIS::isPositionAvailable(newTetromino)) {
                newTetromino = tetromino;
            }

            break;
        
        case CONTROL::HARDDROP:
            newTetromino.origin.Y = newTetromino.origin.Y + 1;

            if(!TETRIS::isPositionAvailable(newTetromino)) {
                newTetromino = tetromino;
            }
            
            break;
    }

    tetromino = newTetromino;
    TETRIS::drawTetromino(tetromino, STATE::ON);
    TETRIS::mapTetromino(tetromino, STATE::ON);
}

Tetromino TETRIS::addTetromino(int x, int y, TYPE _type, int _direction) {
    Tetromino tetromino;
    tetromino.origin = {static_cast<short>(x), static_cast<short>(y)};
    tetromino.type = _type;
    tetromino.direction = _direction;
    
    TETRIS::drawTetromino(tetromino, STATE::ON);
    TETRIS::mapTetromino(tetromino, STATE::ON);

    return tetromino;
}

bool TETRIS::isPositionAvailable(Tetromino tetromino) {
    for(int i=0; i<4; i++) {
        int x = tetromino.origin.X + block[static_cast<int>(tetromino.type)][tetromino.direction][i][0];
        int y = tetromino.origin.Y + block[static_cast<int>(tetromino.type)][tetromino.direction][i][1];
        
        if((x < 0) || (x >= BOARD_SIZE_X) || (y < 0) || (y >=BOARD_SIZE_Y)) {
            return false;
        }
        if(map[x][y] == 1) {
            return false;
        }
    }

    return true;
}

bool TETRIS::isDownAvailable(Tetromino tetromino) {
    Tetromino newTetromino = tetromino;
    newTetromino.origin.Y = tetromino.origin.Y+1;
    
    TETRIS::mapTetromino(tetromino, STATE::OFF);
    if(TETRIS::isPositionAvailable(newTetromino)) {
        TETRIS::mapTetromino(tetromino, STATE::ON);
        return true;
    }
    else {
        TETRIS::mapTetromino(tetromino, STATE::ON);
        return false;
    }
}   

/* Game */
bool TETRIS::isGameContinue() {
    return true;
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

int* TETRIS::randomGenerator() {
    static int randomArray[1000];
    time_t t;
    t = time(NULL);
    std::mt19937 gen(t);
    std::uniform_int_distribution<int> dis(0, 6);

    for(int i=0; i<1000; i++) {
        randomArray[i] = dis(gen);
    }
    return randomArray;
}
