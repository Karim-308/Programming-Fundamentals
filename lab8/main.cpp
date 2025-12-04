#include "Stack.h"
#include <iostream>

int main() {
    MyStack s(3);
    s.push(10);
    s.push(20);
    s.push(30);
    std::cout << "Stack s: " << s << '\n';
    std::cout << "Top element: " << s.peek() << '\n';

    std::cout << "Pop: " << s.pop() << '\n';
    std::cout << "Pop: " << s.pop() << '\n';
    std::cout << "Is empty? " << std::boolalpha << s.isEmpty() << '\n';

    s.push(40);
    s.push(50);
    s.push(60);
    s.push(70); // triggers resize, ensures growth works
    std::cout << "After pushes/resize, s: " << s << '\n';

    MyStack copy = s; // deep copy test
    std::cout << "Original top: " << s.peek() << '\n';
    std::cout << "Copy top: " << copy.peek() << '\n';
    std::cout << "Copy contents: " << copy << '\n';

    s.pop();
    std::cout << "After modifying original, copy top still: " << copy.peek() << '\n';
    std::cout << "Original now: " << s << '\n';
    std::cout << "Copy still: " << copy << '\n';

    while (!s.isEmpty()) {
        std::cout << "Original pop: " << s.pop() << '\n';
    }

    while (!copy.isEmpty()) {
        std::cout << "Copy pop: " << copy.pop() << '\n';
    }

    return 0;
}
