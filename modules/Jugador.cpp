#ifndef CODIGO_Jugador
#define CODIGO_Jugador
#include <iostream>
#include "Tablero.cpp"

using namespace std;
struct Jugador {
    Jugador() = default;
    Jugador(int color, string nombre, int fichas = 9, int movimientos = 0): 
    color(color), nombre(nombre), fichas(fichas), movimientos(movimientos) {}
    int turno;
    int color;
    string nombre;
    int fichas = 9;
    int movimientos = 0;
    int ultimaFicha[2];
    void PlayGame(Tablero *tablero, bool active_move = false){
        int row = 0, col = 0;
        while(1){
            if(active_move){
                leerFicha(row, col, "ingrese la fila de la ficha a mover: ", "ingrese la columna de la ficha a mover: ");
                int act_col = userXYToTableroXY(row, col); 
                int act_row = row-1;
                if( tablero->tablero[row][col].color != color ) {
                    cout << "La ficha no le corresponde";
                    continue;
                }
                char dir;
                cout << "a donde lo quiere mover? (w/a/s/d): ";
                cin >> dir;
                tablero->moveFicha(act_row, act_col, row, col, tolower(dir), color);
            }else{
                leerFicha(row, col, "ingrese la fila donde ira la ficha: ", "ingrese la columna donde ira la ficha: ");
                col = userXYToTableroXY(row, col); row--;
                if( tablero->isEmptyCell(row, col) ) break;
            }
        }
        tablero->SetFicha(row, col, color);
    }
    void leerFicha(int &row, int &col, string promt_row, string prompt_col){
        while(1){
            cout << promt_row;
            cin >> row;
            if (row>7 || row<0) continue;

            cout << prompt_col;
            cin >> col;
            if (row==4 && (col>0 && col<7)) break;
            else if (col>0 && col<4) break;
            cout << "valores incorrectos" << endl;
        }
    }
};

Jugador RegistrarJugador(int enable_color = 1, int ant_color = 0){
    int fichas, movimientos, color;
    string nombre;
    char _color;

    cout << "Ingrese su nombre: ";
    cin >> nombre;
    if(enable_color){
        cout << "color de ficha (R/A): ";
        cin >> _color;
        _color = toupper(_color);
        color = _color=='A';
    }else color = !ant_color;

    return Jugador( color, nombre );
}
#endif