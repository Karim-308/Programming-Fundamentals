#include <iostream>
#include <string>
#include "Value.h"

using namespace std;
int main() {
    Value val1("Karim iBRAHIM");
    Value* val2 = new Value("opnes source intake 46");
    Value val3;

    cout << "Value data: " << val1 << endl;
    cout << "Value data: " << *val2 << endl;
    cout << "Value data: " << val3 << endl;

    delete val2;
    return 0;
}