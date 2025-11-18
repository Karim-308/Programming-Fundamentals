#include "app.h"
#include "../lab1/terminal.h"

#include <iostream>
using namespace std;

int main() {
    MenuItem currentSelection = MENU_NEW;
    bool running = true;

    while (running) {
        drawMenu(currentSelection);
        Key key = getKey();

        switch (key) {
            case KEY_UP:
                currentSelection = static_cast<MenuItem>((currentSelection - 1 + 3) % 3);
                break;

            case KEY_DOWN:
                currentSelection = static_cast<MenuItem>((currentSelection + 1) % 3);
                break;

            case KEY_RIGHT:
                if (currentSelection == MENU_NEW)
                    screenNew();
                else if (currentSelection == MENU_DISPLAY)
                    screenDisplay();
                else if (currentSelection == MENU_EXIT)
                    exitScreen();
                break;

            case KEY_ESC:
                exitScreen();
                break;

            case KEY_HOME:
                currentSelection = MENU_NEW;
                break;

            case KEY_END:
                currentSelection = MENU_EXIT;
                break;

            default:
                break;
        }
    }

    return 0;
}
