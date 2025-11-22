#include "swap.h"

void swapByAdress(int *num1, int *num2){
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}
void swapXOR(int *num1, int *num2){
    if (num1 != num2) {
    //  10      11
        *num1 = *num1 ^ *num2; // 10 ^ 11 = 01 --> num1
        *num2 = *num1 ^ *num2; // 01 ^ 11 = 10 --> num2
        *num1 = *num1 ^ *num2; // 01 ^ 10 = 11 --> num1
    }
}
void swapByAddSub(int *num1, int *num2){
    
    *num1 = *num1 + *num2; 
    *num2 = *num1 - *num2; 
    *num1 = *num1 - *num2; 
}
void swapByMultiplyDivide(int *num1, int *num2){
    if (*num1 != 0 && *num2 != 0) {
        
        *num1 = (*num1) * (*num2); 
        *num2 = (*num1) / (*num2); 
        *num1 = (*num1) / (*num2); 
    }
}