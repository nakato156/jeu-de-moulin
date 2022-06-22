#include <iostream>
#include <windows.h>

using namespace std;

struct Ficha {
    public:
    int color, x, y;
    string repr;
    Ficha() = default;
    Ficha(int color, string repr) {
        this->color = color;
        this->repr = repr;
    }
    int getColor(){ return this->color; }
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
    void setCoordenate(int x, int y) {
        this->x = x;
        this->y = y;
    }  
};
