#include "../lab1/terminal.h"

#include <iostream>
#include <iomanip>
using namespace std;

void drawMagicSquare(int size){
    clearScreen();

    const int cellWidth = 5; // spacing
    int row = 0;
    int col = size / 2;

    for (int num = 1; num <= size * size; ++num) {
        
        goToXY( col * cellWidth ,row + 1); // +1 to leave a small top margin
        cout << setw(4) << num;
        cout.flush();

        if (num % size == 0) {
            // if element is multiple of size, move down
            row = (row + 1) % size;
        } else {
            // Move up and right, and warp around.
            row = (row - 1 + size) % size;
            col = (col + 1) % size;
        }

        delay(150);
    }

    //goToXY(0, size + 2);
    cout << endl;
}