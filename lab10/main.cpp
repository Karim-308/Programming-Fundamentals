#include <iostream>

#include "string.h"

int main() {
    MyString empty;
    std::cout << "Default constructor: \"" << empty.get() << "\"\n";

    MyString greeting("Hello");
    std::cout << "const char* constructor: \"" << greeting.get() << "\"\n";

    MyString copied(greeting);
    std::cout << "Copy constructor: \"" << copied.get() << "\"\n";

    MyString assigned;
    assigned = greeting;
    std::cout << "Assignment operator: \"" << assigned.get() << "\"\n";

    greeting[0] = 'Y';
    std::cout << "operator[]: \"" << greeting.get() << "\"\n";

    std::cout << "length(\"Sample\") = " << MyString::length("Sample") << '\n';

    char buffer[32];
    MyString::copy(buffer, "Karim");
    std::cout << "copy(): \"" << buffer << "\"\n";

    MyString::concat(buffer, "IBrahim");
    std::cout << "concat(): \"" << buffer << "\"\n";

    MyString combined("Hello ");
    combined += MyString("World");
    std::cout << "operator+=: \"" << combined.get() << "\"\n";

    MyString plusResult = MyString("Foo ") + MyString("Bar");
    std::cout << "operator+: \"" << plusResult.get() << "\"\n";

    std::cout << "get(): \"" << plusResult.get() << "\"\n";
    std::cout << "size(): " << plusResult.size() << '\n';

    return 0;
}
