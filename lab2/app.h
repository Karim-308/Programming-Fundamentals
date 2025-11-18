#ifndef APP_H
#define APP_H

#include <string>

enum Key {
    KEY_NONE,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_HOME,
    KEY_END,
    KEY_ESC,
    KEY_OTHER
};

Key readLinuxKey();
Key readWindowsKey();
Key getKey();


enum MenuItem {
    MENU_NEW = 0,
    MENU_DISPLAY = 1,
    MENU_EXIT = 2
};

void drawButton(int y, const std::string& label , bool selected);
void drawMenu(MenuItem current);


void showSubScreen(const char* title);

void screenNew();
void screenDisplay();
void exitScreen();

#endif
