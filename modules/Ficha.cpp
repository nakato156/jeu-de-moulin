#include <iostream>
#include <windows.h>

using namespace std;

struct Ficha {
    int color = -1, x, y;
    bool block;
    string repr = "O";
    int getColor(){ return color; }
    void setColor(int _color) { color = _color; }
    void reset(){
        color = -1;
        block = false;
        x = 0; y = 0;
    }
    void imprimir(){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if(color == -1){
            cout << "O";
            return;
        }
        int color_letra =  !color ? FOREGROUND_RED : FOREGROUND_BLUE;
        if(color == 2) color_letra = FOREGROUND_GREEN;
        SetConsoleTextAttribute(hConsole, color_letra);
        cout << repr;
        SetConsoleTextAttribute(hConsole, 7);
    }
    void setCoordenate(int _x, int _y) {
        x = _x;
        y = _y;
    }  
};
