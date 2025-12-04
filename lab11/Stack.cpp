#include <ostream>
#include <stdexcept>
#include <utility>

template <typename T>
MyStack<T>::MyStack(int capacity)
    : data(nullptr), capacity(capacity > 0 ? capacity : 1), top(-1) {
    data = new T[this->capacity];
}

template <typename T>
MyStack<T>::MyStack() : MyStack(10) {}

template <typename T>
MyStack<T>::MyStack(const MyStack& other)
    : data(new T[other.capacity]), capacity(other.capacity), top(other.top) {
    for (int i = 0; i <= top; ++i) {
        data[i] = other.data[i];
    }
}

template <typename T>
MyStack<T>& MyStack<T>::operator=(const MyStack& other) {
    if (this == &other) {
        return *this;
    }
    T* newData = new T[other.capacity];
    for (int i = 0; i <= other.top; ++i) {
        newData[i] = other.data[i];
    }
    delete[] data;
    data = newData;
    capacity = other.capacity;
    top = other.top;
    return *this;
}

template <typename T>
MyStack<T>::MyStack(MyStack&& other) noexcept
    : data(other.data), capacity(other.capacity), top(other.top) {
    other.data = nullptr;
    other.capacity = 0;
    other.top = -1;
}

template <typename T>
MyStack<T>& MyStack<T>::operator=(MyStack&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    delete[] data;
    data = other.data;
    capacity = other.capacity;
    top = other.top;
    other.data = nullptr;
    other.capacity = 0;
    other.top = -1;
    return *this;
}

template <typename T>
MyStack<T>::~MyStack() {
    delete[] data;
}

template <typename T>
void MyStack<T>::resize() {
    int newCapacity = capacity > 0 ? capacity * 2 : 1;
    T* temp = new T[newCapacity];
    for (int i = 0; i <= top; ++i) {
        temp[i] = data[i];
    }
    delete[] data;
    data = temp;
    capacity = newCapacity;
}

template <typename T>
void MyStack<T>::push(const T& value) {
    if (isFull()) {
        resize();
    }
    data[++top] = value;
}

template <typename T>
void MyStack<T>::push(T&& value) {
    if (isFull()) {
        resize();
    }
    data[++top] = std::move(value);
}

template <typename T>
T MyStack<T>::pop() {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    return data[top--];
}

template <typename T>
const T& MyStack<T>::peek() const {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    return data[top];
}

template <typename T>
bool MyStack<T>::isEmpty() const {
    return top == -1;
}

template <typename T>
bool MyStack<T>::isFull() const {
    return top == capacity - 1;
}

template <typename T>
int MyStack<T>::size() const {
    return top + 1;
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const MyStack<U>& stack) {
    os << "[";
    for (int i = stack.top; i >= 0; --i) {
        os << stack.data[i];
        if (i > 0) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
