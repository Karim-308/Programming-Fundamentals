#include <iostream>
#include "app.h"
using namespace std;


int main() {
    cout << "Please enter the size of the square: ";
    int size;
    cin >> size;

    if (size <= 0 || size % 2 == 0) {
        cout << "Invalid size. Please enter an odd size and higher than zero" << endl;
        return 1;
    }

    drawMagicSquare(size);
    return 0;
}


