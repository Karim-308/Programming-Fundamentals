#include "stringlib.h"
#include <iostream>
using namespace std;

int main() {

char a[100];
char b[100];
char c[100];

    cout << "Enter string a: ";
    cin.getline(a, sizeof(a));
    if (!cin) return 1;
    cout << "Enter string b: ";
    cin.getline(b, sizeof(b));
    if (!cin) return 1;
    cout << "Enter string c: ";
    cin.getline(c, sizeof(c));
    if (!cin) return 1;

    cout<< " string a: " << a << endl;
    cout<< " string b: " << b << endl;
    cout<< " string c: " << c << endl;


    cout << "## str_len ##" << endl;
    cout << "Length of a: " << str_len(a) << endl;
    cout << "Length of b: " << str_len(b) << endl;
    cout << "Length of c: " << str_len(c) << endl;


    cout << "## str_compare ##" << endl;
    int cmpare_result = str_compare(a,b);
    if (cmpare_result == 0) cout << "a is equal to b" <<endl;
    else if (cmpare_result < 0) cout << "a is less than b" << endl;
    else cout << "a is greater than b" << endl;
    

    cout << "## str_cpy ##" << endl;
    char copyResult[20];
    if (str_cpy(copyResult, a, sizeof(copyResult)) == 0)
        cout << "Copy of a in capacity of 40: " << copyResult << endl;
    else
        cout << "Failed to copy in an insufficient capacity of size(40)" << endl;

    char smallCopy[3];
    if (str_cpy(smallCopy, a, sizeof(smallCopy)) == 0)
        cout << "Copy of a in a capacity of 3" << smallCopy << endl;
    else
        cout << "Failed to copy in an insufficient capacity of size(3)" << endl;


    cout << "## str_concat ##" << endl;
    char concatResult[200];
    str_cpy(concatResult, a, 200);
    if (str_concat(concatResult, b, 200) == 0)
        cout << "Concatenation of a and b: " << concatResult << endl;
    else
        cout << "Concatenation failed due to insufficient capacity." << endl;



    cout << "## str_toLower ##" << endl;
    str_toLower(a);
    cout << "a in lowercase: " << a << endl;
    cout << "## str_toUpper ##" << endl;



    str_toUpper(b);
    cout << "b in uppercase: " << b << endl;    




    
    return 0;
}
