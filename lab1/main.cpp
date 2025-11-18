#include <iostream>
#include "terminal.h"

using namespace std;

void drawBox(int x, int y, int width, int height, TerminalColor color) {
    setColor(color);
    // Top border
    goToXY(x, y);
    cout << "+";
    for(int i = 0; i < width - 2; i++) cout << "-";
    cout << "+";

    // Side borders
    for(int i = 1; i < height - 1; i++) {
        goToXY(x, y + i);
        cout << "|";
        goToXY(x + width - 1, y + i);
        cout << "|";
    }

    // Bottom border
    goToXY(x, y + height - 1);
    cout << "+";
    for(int i = 0; i < width - 2; i++) cout << "-";
    cout << "+";
    resetColor();
}

void animatedTitle() {
    string title = "TERMINAL DRAWER DEMO";
    TerminalColor colors[] = {COLOR_RED, COLOR_YELLOW, COLOR_GREEN, COLOR_CYAN, COLOR_BLUE};

    for(int wave = 0; wave < 3; wave++) {
        for(int i = 0; i < title.length(); i++) {
            goToXY(30 + i * 2, 3);
            setColor(colors[(i + wave) % 5]);
            cout << title[i];
            cout.flush();
            delay(50);
        }
    }
    resetColor();
}

void colorSpectrum() {
    goToXY(25, 7);
    setColor(COLOR_WHITE);
    cout << "Color Spectrum Display:";

    TerminalColor colors[] = {COLOR_RED, COLOR_YELLOW, COLOR_GREEN, COLOR_CYAN, COLOR_BLUE, COLOR_WHITE};
    string names[] = {"RED", "YELLOW", "GREEN", "CYAN", "BLUE", "WHITE"};

    for(int i = 0; i < 6; i++) {
        goToXY(30, 9 + i);
        setColor(colors[i]);
        cout << "████████ " << names[i];
        delay(200);
    }
    resetColor();
}

void bouncingText() {
    goToXY(25, 17);
    setColor(COLOR_WHITE);
    cout << "Bouncing Animation:";

    string text = "*** BOUNCE ***";
    TerminalColor colors[] = {COLOR_RED, COLOR_YELLOW, COLOR_GREEN, COLOR_CYAN};

    // Bounce horizontally
    for(int repeat = 0; repeat < 2; repeat++) {
        for(int x = 20; x < 50; x += 2) {
            goToXY(x, 19);
            cout << "              ";  // Clear previous
            goToXY(x, 19);
            setColor(colors[x % 4]);
            cout << text;
            cout.flush();
            delay(50);
        }
        for(int x = 50; x >= 20; x -= 2) {
            goToXY(x, 19);
            cout << "              ";  // Clear previous
            goToXY(x, 19);
            setColor(colors[x % 4]);
            cout << text;
            cout.flush();
            delay(50);
        }
    }
    resetColor();
}

void drawPattern() {
    goToXY(25, 22);
    setColor(COLOR_WHITE);
    cout << "Colorful Pattern:";

    TerminalColor colors[] = {COLOR_RED, COLOR_YELLOW, COLOR_GREEN, COLOR_CYAN, COLOR_BLUE};

    for(int row = 0; row < 5; row++) {
        for(int col = 0; col < 20; col++) {
            goToXY(30 + col * 2, 24 + row);
            setColor(colors[(row + col) % 5]);
            cout << "█";
            cout.flush();
            delay(20);
        }
    }
    resetColor();
}

int main()
{
    clearScreen();

    // Animated title
    animatedTitle();
    delay(500);

    // Draw a decorative box around the title
    drawBox(25, 2, 50, 3, COLOR_CYAN);
    delay(300);

    // Show color spectrum
    colorSpectrum();
    delay(500);

    // Bouncing animation
    bouncingText();
    delay(500);

    // Draw colorful pattern
    drawPattern();
    delay(500);

    // Final message
    goToXY(25, 31);
    setColor(COLOR_GREEN);
    cout << "Demo Complete! Press any key...";
    resetColor();

    goToXY(0, 33);
    cin.get();

    clearScreen();
    goToXY(0, 0);

    return 0;
}

