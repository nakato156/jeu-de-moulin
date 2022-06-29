#include <iostream>
#include <windows.h>

using namespace std;

struct Ficha {
    int color = -1, x, y; //por defecto el color es -1 = blanco
    bool block;//almacena si esta bloqueada o no(ahogada)
    string repr = "O"; //como se mostrara la ficha
    int getColor(){ return color; }//retorna color de la ficha
    void setColor(int _color) { color = _color; }//establece un nuevo color
    void reset(){//resetea todos los atributos
        color = -1;
        block = false;
        x = 0; y = 0;
    }
    void imprimir(){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//establece comunicacion con la consola
        if(color == -1){//si el color es -1 se imprimi la "O"o la representacion de la ficha
            cout << repr;
            return;
        }
        int color_letra =  !color ? FOREGROUND_RED : FOREGROUND_BLUE;//al entrar a esa condicion establece el color, si esa condicion es 0 se coloca el rojo
        //de lo contrario el azul
        if(color == 2) color_letra = FOREGROUND_GREEN;//si el color es 2 el color de la letra sera verde
        SetConsoleTextAttribute(hConsole, color_letra);
        cout << repr;//imprime el color en la consola
        SetConsoleTextAttribute(hConsole, 7);//es blanco en la consola
    }
    void setCoordenate(int _x, int _y) {//establece la coordenada, pero no se termino usando xD
        x = _x;
        y = _y;
    }  
};
