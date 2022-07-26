//Projekt von Paul Schuh und Eric Trébuchon

#ifndef COLOR_H_
#define COLOR_H_

#include <iostream>

using namespace std;


#ifdef _WIN32

#include <windows.h>
void color(string color, string line, bool newLine = false) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int col = 7;

    if (color == "white") col = 15;
    else if (color == "light_blue") col = 176;
    else if (color == "blue") col = 159;
    else if (color == "yellow") col = 224;
    else if (color == "red") col = 207;
    else if (color == "grey") col = 8;

    SetConsoleTextAttribute(hConsole, col);
    cout << line;
    if (newLine) {
        cout << endl;
    }
    SetConsoleTextAttribute(hConsole, 7);
}


#else

void color(string color, string line, bool newLine = false) {
    string col = "\033[0m";

    if (color == "white") col = "\x1B[0;37m";
    else if (color == "light_blue") col = "\033[2;104;30m";
    else if (color == "blue") col = "\033[0;44;37m";
    else if (color == "yellow") col = "\033[2;43;30m";
    else if (color == "red") col = "\033[2;41;37m";
    else if (color == "grey") col = "\033[38;5;246m";

    cout << col << line << "\033[0m";
    if (newLine) {
        cout << endl;
    }
}

#endif

#endif  // COLOR_H_
