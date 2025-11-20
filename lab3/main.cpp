#include <iostream>
#include "app.h"
using namespace std;


int main() {
    cout << "Please enter the size of the square: ";
    int size;
    cin >> size;

    if (size <= 0 || size % 2 == 0 || !cin) {
        cout << "Invalid size. Size must be an odd integer higher than zero" << endl;
        return 1;
    }

    drawMagicSquare(size);
    return 0;
}


