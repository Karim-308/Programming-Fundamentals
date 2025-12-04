#include <any>
#include <iostream>
#include <string>

#include "MultiList.h"
int main() {
    MultiList list;

    std::cout << "Pushing 42 \"hello\" 3.14 true\n";
    list.push(42);
    list.push(std::string("Mina"));
    list.push(3.14);
    list.push(true);
    list.print();

    std::cout << "Inserting 'Karim' at index 2...\n";
    list.insert(2, std::string("Karim"));
    list.print();

    std::cout << "get(0): " << std::any_cast<int>(list.get(0)) << '\n';
    std::cout << "operator[](2): " << std::any_cast<std::string>(list[2]) << '\n';
    list[0] = 100;
    std::cout << "After modifying index 0 via operator[]: "
              << std::any_cast<int>(list.get(0)) << '\n';

    std::cout << "Current size: " << list.size() << '\n';

    std::cout << "Popping last element...\n";
    bool popped = std::any_cast<bool>(list.pop());
    std::cout << "Popped: " << (popped ? "true" : "false") << '\n';
    list.print();

    std::cout << "Removing element at index 1...\n";
    list.remove(1);
    list.print();

    std::cout << "Clearing list...\n";
    list.clear();
    std::cout << "Size after clear: " << list.size() << '\n';
    list.print();

    return 0;
}
