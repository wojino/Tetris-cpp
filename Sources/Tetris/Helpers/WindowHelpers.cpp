#include "WindowHelpers.hpp"

void WINDOW::gotoxy(int x, int y) {
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void WINDOW::setColor(COLOR color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(color));
}

void WINDOW::print(int x, int y, std::string str, COLOR color) {
    WINDOW::gotoxy(x, y);
    WINDOW::setColor(color);
    std::cout << str;
}

void WINDOW::init() {
    // set console title
    SetConsoleTitle(TITLE);

    // set console size
    char setSizeCommand[30];
    sprintf(setSizeCommand, "mode con: cols=%d lines=%d", WINDOW_SIZE_COL, WINDOW_SIZE_ROW);
    system(setSizeCommand);

    // set cursor invisible
    WINDOW::setCursorInvisible();
}

void WINDOW::clrscr() {
    system("cls");
}

void WINDOW::setCursorInvisible() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = 0;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(consoleHandle , &ConsoleCursor);
}

int WINDOW::selectMenu(int menuSize, std::string menu[]) {
    for(int i=0; i<menuSize; i++) {
        WINDOW::print(MENU_LINE_X, MENU_LINE_Y + (i * MENU_LINE_INTERVAL), menu[i]);
    }
    COORD cursor;
    cursor.X = MENU_LINE_X-2;
    cursor.Y = MENU_LINE_Y;
    
    int pos = 0, newpos = 0;
    WINDOW::print(cursor.X, cursor.Y, CURSOR);

    while(true) {
        switch(KEYBOARD::keyInput()) {
            case KEY::DOWN:
                if(pos == menuSize - 1) {
                    newpos = 0;
                    break;
                }
                newpos += 1;
                break;
            
            case KEY::UP:
                if(pos == 0) {
                    newpos = menuSize - 1;
                    break;
                }
                newpos -= 1;
                break;

            case KEY::z:
            case KEY::Z:
                return pos;

            default:
                break;
        }

        WINDOW::print(cursor.X, cursor.Y + (pos * MENU_LINE_INTERVAL), BLANK);
        WINDOW::print(cursor.X, cursor.Y + (newpos * MENU_LINE_INTERVAL), CURSOR);

        pos = newpos;
    }
    
}
