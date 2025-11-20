#include <iostream>
using namespace std;


int str_len(char str[]){
    int  length =0;
    for (int i=0; str[i]!='\0'; i++){
        length++;
    }
    return length;
}


void str_toLower(char str[]){
    int size = str_len(str);
    while (size--){
        if (str[size] >= 'A' && str[size]<= 'Z')
        str[size] += 32;
    }
}


void str_toUpper(char str[]){
    int size = str_len(str);
    while (size--){
        if (str[size] >= 'a' && str[size]<= 'z')
        str[size] -= 32;
    }
}


int str_cpy(char str1[] , char str2 [],int capacity){
    int sizeString2 = str_len(str2);
    if ( sizeString2 + 1 > capacity ) return -1;
    for (int i = 0 ; i<sizeString2 ; i++){
        str1[i] = str2[i];
    } 
    str1[sizeString2] = '\0';

    return 0; 
}

int str_compare(char str1[], char str2[]){
    int lengthString1 = str_len(str1);
    int lengthString2 = str_len(str2);
    if (lengthString1 < lengthString2) return -1;
    else if (lengthString1 > lengthString2) return 1;

    for (int i = 0; str1[i] != '\0'; i++) {
        if (str1[i] < str2[i]) return -1;
        if (str1[i] > str2[i]) return 1;
    }
    return 0;
}


int str_concat(char str1[], char str2[] , int capacity){
    int sizeString1 = str_len(str1);
    int sizeString2 = str_len(str2);
    if (sizeString1 + sizeString2 + 1 > capacity) return -1;
    for (int i = 0 ; i<sizeString2 ; i++){
        str1[sizeString1 + i] = str2[i];
    }
    str1[sizeString1 + sizeString2] = '\0';
    
    return 0;
}
