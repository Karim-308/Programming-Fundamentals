#ifndef TERIMNAL_H_INCLUDED
#define TERIMNAL_H_INCLUDED

#ifdef _WIN32
#include<Windows.h>
#endif


typedef enum  {
    COLOR_BLACK = 30,
    COLOR_BLUE = 34,
    COLOR_GREEN = 32,
    COLOR_CYAN = 36,
    COLOR_PURPLE = 35,
    COLOR_RED = 31,
    COLOR_YELLOW = 33,
    COLOR_WHITE = 37,

} TerminalColor;

void goToXY (int x , int y);

void delay(int time);

void setColor(TerminalColor color);

void resetColor(void);


void clearScreen(void);
#endif // TERIMNAL_H_INCLUDED
