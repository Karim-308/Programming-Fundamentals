#include "app.h"
#include "screens.h"

int main() {
    MenuItem currentSelection = MENU_NEW;

    while (true) {
        drawMenu(currentSelection);
        Key key = getKey();

        switch (key) {
            case KEY_UP:
                currentSelection = static_cast<MenuItem>((currentSelection - 1 + 5) % 5);
                break;

            case KEY_DOWN:
                currentSelection = static_cast<MenuItem>((currentSelection + 1) % 5);
                break;

            case KEY_RIGHT:
                if (currentSelection == MENU_NEW)
                    screenNew();
                else if (currentSelection == MENU_DISPLAY)
                    screenDisplay();
                else if (currentSelection == MENU_SWAP)
                    screenSwap();
                else if (currentSelection == MENU_2D)
                    screen2D();
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
