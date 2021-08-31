#ifndef WINDOW_HELPERS_HPP
#define WINDOW_HELPERS_HPP

#include "KeyboardHelpers.hpp"

#include <conio.h>
#include <windows.h>
#include <string>
#include <cstdio>
#include <cstdint>

/* Window constants */
#define TITLE "Tetris-CPP"
#define WINDOW_SIZE_COL 100
#define WINDOW_SIZE_ROW 50

/* Menu line constants */
#define MENU_LINE_X 5
#define MENU_LINE_Y 10
#define MENU_LINE_INTERVAL 2

/* Symbols */
#define CURSOR '>'
#define BLANK ' '

/* Colors */
enum class COLOR {
    BLACK,
    DARK_BLUE,
    DARK_GREEN,
    DARK_SKYBLUE,
    DARK_RED,
    DARK_VOILET,
    DAKR_YELLOW,
    GRAY,
    DARK_GRAY,
    BLUE,
    GREEN,
    SKYBLUE,
    RED,
    VIOLET,
    YELLOW,
    WHITE
};

namespace WINDOW {
    void gotoxy(int x, int y);
    void setColor(COLOR color);
    void printLeft(int x, int y, std::string str, COLOR color = COLOR::WHITE);
    void printRight(int x, int y, std::string str, COLOR color = COLOR::WHITE);
    void printChar(int x, int y, char ch, COLOR color = COLOR::WHITE);

    void init();
    void clrscr();

    int choiceMenu(int menuSize, std::string menu[]);
}

#endif