#include "Stack.h"
#include "../lab7/Complex.h"

#include <iostream>
#include <string>

int main() {
  
     MyStack<int> stack;
   MyStack<float> stack2(5);
   MyStack<Complex> stack3;


   try {
       stack.pop();
   } catch (const std::underflow_error& e) {
       cout <<e.what() << endl;
   }

    stack.push(308);
    stack.push(2002);
    stack.push(9798798);
    cout << stack << endl;

   cout<< stack.peek();
   stack.pop();
   stack.pop();
   stack.pop();
   cout << stack.isEmpty() << endl;

   try {
       stack.pop();
   } catch (const std::underflow_error& e) {
       cout <<e.what() << endl;
   }


   stack2.push(5.1555f);
   stack2.push(2.71f);
   cout << stack2 << endl;


   stack3.push(Complex(80, 8));
   stack3.push(Complex(3, 5.8));
   cout << stack3 << endl;

   stack3.pop();
   stack3.pop();
   ///stack3.pop();

    return 0;
}
