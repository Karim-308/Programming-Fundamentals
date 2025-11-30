#ifndef APP_H
#define APP_H

#include <stdbool.h>

enum Key {
    KEY_NONE,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_HOME,
    KEY_END,
    KEY_ESC,
    KEY_BACKSPACE,
    KEY_ENTER,
    KEY_OTHER
};

enum MenuItem {
    MENU_NEW = 0,
    MENU_DISPLAY = 1,
    MENU_EXIT = 2
};

struct InputEvent {
    bool isCharacter;
    char value;
    Key key;
};

typedef struct InputEvent InputEvent;

void enableRawInput();
void disableRawInput();
InputEvent readInputEvent();
Key getKey();

#endif
