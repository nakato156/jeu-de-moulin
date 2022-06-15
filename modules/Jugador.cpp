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
