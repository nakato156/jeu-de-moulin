#include <iostream>
#include <windows.h>

using namespace std;

struct Ficha {
    Ficha() = default;
    Ficha(int color, string repr): color(color), repr(repr) {}
    int color;
    string repr;
    public:
    void imprimir(){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if(color == -1){
            cout << "O";
            return;
        }
        int color_letra =  !color ? FOREGROUND_RED : FOREGROUND_BLUE;
        SetConsoleTextAttribute(hConsole, color_letra);
        cout << repr;
        SetConsoleTextAttribute(hConsole, 7);
    }
};
