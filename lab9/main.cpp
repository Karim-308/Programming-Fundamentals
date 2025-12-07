#include <iostream>
#include <string>
#include "Value.h"
#include "Multilist.h"

using namespace std;
int main() {
    Value val1("Karim iBRAHIM");
    Value* val2 = new Value("opnes source intake 46");
    Value val3;
    val3 = Value("true");


    cout << val1 << endl;

    cout << *val2 << endl;

    if (val3.isBoolean()) {
        cout << "val3: " <<val3.getData()<<" is boolean" << endl;
    } else {
        cout << "val3: " <<val3.getData()<<" is not  a boolean" << endl;
    }

    cout<< typeid(val1).name() << endl;
    cout<< val1.getType() << endl;

    Value val4("1234.648484668465465");
    string type = val4.getType();
    if (type == "int") {
        cout << "integer" << endl;
    } else if (type == "float") {
        cout << "float" << endl;
    } else if (type == "double") {
        cout << "double" << endl;
    } else if (type == "bool") {
        cout << "boolean" << endl;
    } else if (type == "char") {
        cout << "char" << endl;
    } else if (type == "string") {
        cout << "string" << endl;
    } else {
        cout << "unknown type" << endl;
    }

    Multilist mylist;
    mylist.push("true"); cout << "Value data: " << val1 << endl;
    mylist.push("777777777");
    mylist.push(val1.getData());
    mylist.push("45.67");
    mylist.push("A");
    
    mylist.insertAt(2, val2->getData());
    mylist.removeAt(4);

    mylist.display();

    cout << "Popped: " << mylist.pop() << endl;

    cout << "element at index 1: " << mylist[1] << endl;

    cout << "Full list: " << mylist << endl;


    delete val2;
    return 0;
}
