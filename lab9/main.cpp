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

    Value val4("1234.6484846684654655551151651665");
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
    mylist.push("P");
    mylist.push(val2);

    
    mylist.insertAt(2, val2->getData());
    mylist.removeAt(4);

    mylist.display();

    cout << "Popped: " << mylist.pop() << endl;

    cout << "element at index 1: " << mylist[1] << endl;

    cout << "Full list: " << mylist << endl;

    Multilist mylist2;
    mylist2[0]= 84;
    mylist2[1]= true;
    mylist2[2] = 6666.99;
    mylist2[4] = 'S';
    mylist2[5] =  "LOlo";
    string val5 = "Mina";
    mylist2[6] =val5;
    cout<< mylist2<<endl;

    for (int i = 0 ; i<mylist2.getSize() ;i++)
    cout<<mylist2[i].getType()<<endl;

    delete val2;
    return 0;
}
