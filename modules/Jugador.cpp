#include <iostream>

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
    bool hardcore = false;
    int ultimaFicha[2];
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
