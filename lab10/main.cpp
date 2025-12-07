#include <iostream>

#include "string.h"
using namespace std;

int main() {
    MyString string1 = "Karim Ibrahim saad";
    cout << string1.get() << endl;
    string1[0] = 'B';
    cout << string1.get() << endl;
    string1[4] = 'O';
    cout << string1.get() << endl;
    string1.remove(4);
    cout << string1.get() << endl;
    cout << string1.length() << endl;

    MyString string2;
    cout << string2.length() << endl;

    string2 += "MINA CODES";
    MyString string3 = string2 + " "+ string1;
    cout << string3.get() << endl;
    
    MyString string4 = string3;
    MyString string5(string4);
   
    string5[0] = 'X';
    cout << string5.get() << endl;
    cout << string4.get() << endl;

    



    return 0;
}
