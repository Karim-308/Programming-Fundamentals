#include "Stack.h"
#include "../lab7/Complex.h"

#include <iostream>
#include <string>

int main() {
    // int
    MyStack<int> numbers;
    for (int value : {1, 2, 3, 4, 5}) {
        numbers.push(value);
    }
    std::cout << "numbers: " << numbers << '\n';
    std::cout << "numbers pop: " << numbers.pop() << '\n';
    std::cout << "numbers peek: " << numbers.peek() << '\n';

    // string
    MyStack<std::string> words;
    words.push("hello");
    words.push(", ");
    words.push("world");
    std::cout << "words: " << words << '\n';
    std::cout << "words pop: " << words.pop() << '\n';
    std::cout << "words peek: " << words.peek() << '\n';

    // bool
    MyStack<bool> flags;
    flags.push(true);
    flags.push(false);
    flags.push(true);
    std::cout << "flags: " << flags << '\n';
    std::cout << "flags pop: " << std::boolalpha << flags.pop() << '\n';
    std::cout << "flags peek: " << flags.peek() << '\n';

    // Complex
    MyStack<Complex> complexNumbers;
    complexNumbers.push(Complex(1.0f, 2.0f));
    complexNumbers.push(Complex(0.0f, -3.5f));
    complexNumbers.push(Complex(4.2f, 1.1f));
    std::cout << "complexNumbers: " << complexNumbers << '\n';
    std::cout << "complexNumbers pop: " << complexNumbers.pop() << '\n';
    std::cout << "complexNumbers peek: " << complexNumbers.peek() << '\n';

    return 0;
}
