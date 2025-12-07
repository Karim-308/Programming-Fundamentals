#include "Stack.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int main() {
    
    MyStack stack;


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

   MyStack stack2(3);
   stack2.push(51);
   stack2.push(52);
   stack2.push(53);

   cout <<stack2.isFull()<<endl;
   cout<< stack2.size()<<endl;
   cout<< stack2.peek()<<endl;

   stack= stack2;

   cout<<stack<<endl;




    return 0;
}
