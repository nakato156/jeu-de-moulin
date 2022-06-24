#include <iostream>
#include <string>
#include <type_traits>
#include "Bot.cpp"

using namespace std;

string generarCodigoStr()
{
    string codigo;
    for (int i = 0; i < 6; i++) {

        int digitoUni = rand() % 2;

        if (digitoUni == 0) {

            char digitoC = 'A' + rand() % 28;
            codigo.push_back(digitoC);
        }
        else {

            int digito = rand() % 10;
            codigo.push_back(digito + '0');
        }
    }
    return codigo;
}

bool eliminarFicha(Tablero &tablero, int row, int col, Jugador player){
    col = userXYToTableroXY(row, col);
    if (col == -1) return false;
    row--;
    if ( !(tablero.Iam(row, col, player.color)) ) return false;
    player.fichas--;
    tablero.SetFicha(row, col, -1);
    return true;
}

void WhenMolino (Tablero &tablero, Jugador oponente){
    while(1){
        int eliminar_fila, eliminar_col;
        cout << "fila de la ficha a eliminar: ";
        cin >> eliminar_fila;
        cout << "columna de la ficha a eliminar: ";
        cin >> eliminar_col;
        bool eliminado = eliminarFicha(tablero, eliminar_fila, eliminar_col, oponente);
        if(eliminado) break;
        cout << "Vuelva a intentarlo." << endl;
    }
}

// template <typename T>
void Game(Jugador player1, Jugador player2){
    Tablero tablero;
    Jugador player, oponente;

    int isMove, row, col, *puntos = nullptr;
    char direccion;
    bool active_move = false;

    tablero.Show(1);

    for(int i = 0; ; i++){
        if(i%2 == 0){
            player = player1;
            oponente = player2;
        }else{
            player = player2;
            oponente = player1;
        }
        
        if(i == 17) {
            cout << "movida de fichas" << endl;
            active_move = true;
        }
        cout << "Turno de " << player.nombre << endl;
        player.PlayGame(tablero, active_move, player1);

        if(i > 1) {
            if(puntos != nullptr){
                int *n_puntos = puntoenhori(tablero);
                if(puntos[0] != n_puntos[0] || puntos[1] != n_puntos[1]){
                    puntos = n_puntos;
                    cout << "molino para " << player.nombre << endl;
                    WhenMolino(tablero, oponente);
                }
            }else puntos = puntoenhori(tablero);
        }
        tablero.Show(1);
    }
}
