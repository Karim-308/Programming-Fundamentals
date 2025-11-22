#include <iostream>
#include "terminal.h"

using namespace std;

void drawBox(int x, int y, int width, int height, TerminalColor color) {

    if (width < 2) width = 2;
    if (height < 2) height = 2;

    setColor(color);

    // top
    goToXY(x, y);
    cout << "*";
    for (int i = 0; i < width - 2; ++i) {
        cout << "-";
        delay(30);
    }
    cout << "*";

    // sides
    for (int i = 1; i < height - 1; ++i) {
        goToXY(x, y + i);
        cout << "|";
        goToXY(x + width - 1, y + i);
        cout << "|";
        
        if (i < height - 2) delay(30);
    }

    // bottom
    goToXY(x, y + height - 1);
    cout << "*";
    for (int i = 0; i < width - 2; ++i) {
        cout << "-";
        delay(30);
    }
    cout << "*";

    
    goToXY(x + (width - 8) / 2, y + height / 2);
    cout<< "Hi Eng. Mina!";

    resetColor();
}


int main()
{
    clearScreen();

    goToXY(20, 5);
    setColor(COLOR_CYAN);
    cout << "Lets Draw in the Terminal!";
    delay(500);

    drawBox(20, 10, 30, 5, COLOR_RED);

    goToXY(20, 17);
    setColor(COLOR_GREEN);
    cout << "Demo Complete! Press any key...";
    resetColor();

    goToXY(0, 20);
    cin.get();

    clearScreen();

    return 0;
}

