#include "terminal.h"
#include <stdio.h>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include<Windows.h>
#endif


void goToXY (int x , int y){
    #ifdef _WIN32
        COORD cursor;cursor.X=x;cursor.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cursor);
    #else
        printf("\033[%d;%dH",y+1,x+1);
        fflush(stdout);
    #endif

}



void setColor(TerminalColor color){
    #ifdef _WIN32

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
          int winColor;
                switch(color) {
                    case COLOR_RED:    winColor = FOREGROUND_RED; break;
                    case COLOR_BLUE:   winColor = FOREGROUND_BLUE; break;
                    case COLOR_GREEN:  winColor = FOREGROUND_GREEN; break;
                    case COLOR_YELLOW: winColor = FOREGROUND_RED | FOREGROUND_GREEN; break;
                    case COLOR_CYAN:   winColor = FOREGROUND_GREEN | FOREGROUND_BLUE; break;
                    case COLOR_WHITE:  winColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
                    default:   winColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;}
                SetConsoleTextAttribute(hConsole,winColor);
    #else
        printf("\e[1;%dm",color);
        fflush(stdout);
    #endif
}


void delay(int time){
    #ifdef _WIN32
        Sleep(time);
    #else
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
    #endif

}


void resetColor(void){
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        // White = RED + GREEN + BLUE combined
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    #else
        printf("\033[0m");
        fflush(stdout);
    #endif

}

void clearScreen(void){
    #ifdef _WIN32
        system("cls");

    #else
        printf("\033[2J");
        printf("\033[H");
        fflush(stdout);

    #endif // _WIN32
}



