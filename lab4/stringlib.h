#ifndef STRINGLIB_H
#define STRINGLIB_H

int str_len(char str[]);
int str_compare(char str1[], char str2[]);
int str_cpy(char str1[], char str2[],int capacity);
int str_concat(char str1[], char str2[] , int capacity);
void str_toLower(char str[]);
void str_toUpper(char str[]);

#endif // STRINGLIB_H