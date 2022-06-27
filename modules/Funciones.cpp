#include <iostream>
#include <string>
#include <time.h>
#include "Bot.cpp"
#include "Menu.cpp"
#include "Tablero.cpp"

using namespace std;

void pantallaFinal(Jugador winner, Jugador losser);

string generarCodigoStr()
{
    srand(time(NULL));
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

bool InMolino(Tablero &tablero, int row, int col){
    int color = tablero[row][col].getColor();

    if ( tablero.checkRow(row, col, color) ) return true;
    else return tablero.checkCol(row, col, color);
}

template <typename T>
bool eliminarFicha(Tablero &tablero, int row, int col, T &oponente){
    col = userXYToTableroXY(row, col);
    if (col == -1) return false;
    row--;
    if ( tablero[row][col].getColor() != oponente->color) {
        cout << "La ficha le pertenece " << endl;
        return false;
    }
    if ( InMolino(tablero, row, col) ){
        cout << "La ficha forma un molino, no la puede eliminar" << endl; 
        return false;
    }
    tablero[row][col].reset();
    return true;
}

template <typename T>
void WhenMolino (Tablero &tablero, T &oponente){
    while(1){
        int eliminar_fila, eliminar_col;
        cout << "fila de la ficha a eliminar: ";
        cin >> eliminar_fila;
        cout << "columna de la ficha a eliminar: ";
        cin >> eliminar_col;
        bool eliminado = eliminarFicha(tablero, eliminar_fila, eliminar_col, oponente);
        if(eliminado) return;
        cout << "Vuelva a intentarlo." << endl;
    }
}

void Game(Bot player1, Jugador player2){
    Tablero tablero;

    int isMove, row, col, **puntos = nullptr;
    char direccion;
    bool active_move = false;

    tablero.Show(1);

    for(int i = 0; ; i++){
        if(i == 17) {
            cout << endl;
            cout << "MOVIDA DE FICHAS" << endl;
            active_move = true;
        }

        if ( player1.fichas == 2 || player2.fichas == 2) break;

        if(i%2 == 0){
            cout << "Turno de " << player1.nombre << endl;
            player1.PlayGame(tablero, active_move);
        }else{
            cout << "Turno de " << player2.nombre << endl;
            player2.PlayGame(tablero, active_move);
        }

        if(i > 1) {
            if(puntos != nullptr){
                int **n_puntos = puntoenhori(tablero);
                if(puntos[0] != n_puntos[0] || puntos[1] != n_puntos[1]){
                    puntos = n_puntos;
                    string nombre_player = i % 2 ? player2.nombre : player1.nombre;
                    cout << "molino para " << nombre_player << endl;
                    if ( i % 2 ) { 
                        Bot *player = &player1;
                        WhenMolino(tablero, player);
                        player1.fichas--;
                    }
                    else player1.Molino(tablero, player2);
                    puntos = puntoenhori(tablero);
                }
            }else puntos = puntoenhori(tablero);
            ahogamiento(tablero);
        }
        tablero.Show(0);
    }
}

void Game(Jugador player1, Jugador player2){
    Tablero tablero;
    Jugador *player, *oponente;

    int isMove, row, col, **puntos = nullptr;
    char direccion;
    bool active_move = false;

    tablero.Show(1);

    for(int i = 0; ; i++){
        if(i%2 == 0){
            player = &player1;
            oponente = &player2;
        }else{
            player = &player2;
            oponente = &player1;
        }
        if ( (*player).fichas == 2 || (*oponente).fichas == 2)
        {
            break;
        }
        cout << "fichas: " << (*player).fichas << endl;
        cout << "fichas oponente: " << (*oponente).fichas << endl;
        
        if(i == 17) {
            cout << "movida de fichas" << endl;
            active_move = true;
        }
        cout << "Turno de " << (*player).nombre << endl;
        (*player).PlayGame(tablero, active_move);

        tablero.Show(1);

        if(i > 1) {
            if(puntos != nullptr){
                int **n_puntos = puntoenhori(tablero);
                bool haymolino=false;
                //filas
                for (int i = 0; i < 8; i++)
                {
                    if (puntos[0][i] != n_puntos[0][i]) {
                        if (n_puntos[0][i] == 1) {
                            haymolino = true;
                            break;
                        }
                    }
                }
                //columnas
                for (int i = 0; i < 8; i++)
                {
                    if (puntos[1][i] != n_puntos[1][i]) {
                        if (n_puntos[1][i] == 1) {
                            haymolino = true;
                            break;
                        }
                    }
                }
                //diagonales
                for (int i = 0; i < 4; i++)
                {
                    if (puntos[2][i] != n_puntos[2][i]) {
                        if (n_puntos[2][i] == 1) {
                            haymolino = true;
                            break;
                        }
                    }
                }
                if(haymolino){
                    puntos = n_puntos;
                    cout << "molino para " << (*player).nombre << endl;
                    WhenMolino(tablero, oponente);
                    (*oponente).delFicha();
                    int **n_puntos = puntoenhori(tablero);
                    delete puntos;
                    puntos = n_puntos;
                }
                else {
                    puntos = puntoenhori(tablero);
                }
            }else puntos = puntoenhori(tablero);

            tablero.Show(1);
        }
    }
    if ( (*player).fichas == 2 ) pantallaFinal((*oponente), (*player));
    else pantallaFinal(*player, *oponente);

}

void pantallaFinal(Jugador winner, Jugador losser) {
    int variableini = generarNumWin();
    int loss = generarNumloss();
    cout<<"===============FELICIDADES GANASTE=============== " << endl;
    if (variableini==0)
    {
        cout << winner.nombre << " bien jugado" << endl;
    }
    else {
        cout << winner.nombre << " enhorabuena" << endl;
    }
    cout << "Estadisticas Ganador---------------"<<endl;
    cout << "Numero de fichas: "<< winner.fichas<<endl;
    cout << "Numero de movimientos: "<<winner.movimientos<<endl;
    cout << "=============== PERDEDOR =============== " << endl;
    if (loss == 0) {
        cout << losser.nombre << "mas suerte para la proxima :c" << endl;
    }
    else {
        cout << losser.nombre << "buen intento, pero no fue suficiente :(" << endl;
    }
    cout << "Estadisticas Perdedor---------------"<<endl;
    cout << "Numero de fichas: " << losser.fichas<<endl;
    cout << "Numero de movimientos: " << losser.movimientos<<endl;
}