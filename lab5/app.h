#ifndef APP_H
#define APP_H

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

enum MenuItem {
    MENU_NEW = 0,
    MENU_DISPLAY = 1,
    MENU_SWAP = 2,
    MENU_2D = 3,
    MENU_EXIT = 4
};

Key getKey();

#endif
