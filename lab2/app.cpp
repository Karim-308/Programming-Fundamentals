#include "app.h"
#include <iostream>
#include <string>
#include "../lab1/terminal.h"

#ifdef __linux__
#include <termios.h>
#include <unistd.h>
#elif defined(_WIN32)
#include <conio.h>
#endif


using namespace std;



#ifdef __linux__

struct RawMode {
    termios oldTerminalSettings;

    RawMode() {
        tcgetattr(STDIN_FILENO, &oldTerminalSettings);
        termios newTerminalSettings = oldTerminalSettings;
        newTerminalSettings.c_lflag &= ~(ICANON | ECHO);   // raw input, no echo
        newTerminalSettings.c_cc[VMIN] = 0;                // return even if no byte is available
        newTerminalSettings.c_cc[VTIME] = 1;               // let read() time out quickly
        tcsetattr(STDIN_FILENO, TCSANOW, &newTerminalSettings);
    }

    ~RawMode() {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldTerminalSettings);
    }
};

#endif



#ifdef __linux__
Key readLinuxKey() {
    unsigned char c;

    
    if (read(STDIN_FILENO, &c, 1) != 1)
        return KEY_NONE;

    // 27 is ESC
    if (c == 27) {
        
        unsigned char seq[2];

        // If no more bytes then input is an ESC
        if (read(STDIN_FILENO, &seq[0], 1) != 1)
            return KEY_ESC;

        if (read(STDIN_FILENO, &seq[1], 1) != 1)
            return KEY_ESC; 

        // If there is 2 bytes then the format is  ESC [ X
        if (seq[0] == '[') {
            switch (seq[1]) {
                case 'A': return KEY_UP;
                case 'B': return KEY_DOWN;
                case 'C': return KEY_RIGHT;
                case 'D': return KEY_LEFT;
                case 'H': return KEY_HOME;
                case 'F': return KEY_END;
                default: return KEY_OTHER;
            }
        }

        return KEY_OTHER;
    }

    return KEY_OTHER;
}
#endif

#ifdef _WIN32
Key readWindowsKey() {
    if (!_kbhit())
        return KEY_NONE;

    int c = _getch();

    // Arrow keys and other control keys are reported as two-step codes
    if (c == 0 || c == 224) {
        int code = _getch();
        switch (code) {
            case 72: return KEY_UP;
            case 80: return KEY_DOWN;
            case 75: return KEY_LEFT;
            case 77: return KEY_RIGHT;
            case 71: return KEY_HOME;
            case 79: return KEY_END;
            default: return KEY_OTHER;
        }
    }

    if (c == 27)
        return KEY_ESC;

    return KEY_OTHER;
}
#endif



Key getKey() {
#ifdef __linux__
    static RawMode raw;   // enabling raw mode once
    return readLinuxKey();
#elif defined(_WIN32)
    return readWindowsKey();
#else
    return KEY_NONE;
#endif
}

void drawButton(int y, std::string label , bool selected){

    goToXY(20, y);

    if (selected) {
        setColor(COLOR_YELLOW);
        cout << "->" << "{ "<< label << "}";
        resetColor();
    } else {
        cout << "{ " << label << " }";
}


}

void drawMenu(MenuItem current) {
    
    clearScreen();
    goToXY(20, 5);
    cout << "Main Menu";

    drawButton(7, "New Screen", current == MENU_NEW);
    drawButton(9, "Display Screen", current == MENU_DISPLAY);
    drawButton(11, "Exit", current == MENU_EXIT);

    goToXY(0, 15);
}


void showSubScreen(const char* title){
    clearScreen();
    goToXY(20, 5);
    cout << title;
    goToXY(20, 7);
    cout << "Press <- or Home to return to main menu...";

    goToXY(20, 9);
    //getKey();
}

void screenDisplay() {
    showSubScreen("DISPLAY SCREEN");

    while (true) {
        Key k = getKey();
        if (k == KEY_HOME || k == KEY_LEFT)
            return;
        if (k == KEY_ESC)
            exitScreen();
    }
}
void screenNew() {
    showSubScreen("NEW SCREEN");

    while (true) {
        Key k = getKey();
        if (k == KEY_HOME || k == KEY_LEFT)
            return;
        if (k == KEY_ESC)
            exitScreen();
    }
}



void exitScreen() {
    clearScreen();
    goToXY(20, 5);
    cout << "Bye Bye!";
    goToXY(28, 5);
    delay(1500);
    clearScreen();
    exit(0);
}
