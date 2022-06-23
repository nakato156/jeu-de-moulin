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

int piernitasCalientes(Tablero& tablero) {
    //validaciones del cuadrado mas grande, incluyendo lineas de en medio
    if (tablero[0][3].color !=-1) {
        if (tablero[0][0].color !=-1 && tablero[0][6].color!=-1 && tablero[1][3].color !=-1) {
            if (tablero[0][3].color == 1) {
                cout << "la ficha del azul en la posicion 1, 2 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 1, 2 ta atascada pe" << endl;
            }
        }
    }
    if (tablero[3][0].color != -1) {
        if (tablero[0][0].color != -1 && tablero[6][0].color != -1 && tablero[3][1].color != -1) {
            if (tablero[3][0].color == 1) {
                cout << "la ficha del azul en la posicion 3, 1 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 3, 1  ta atascada pe" << endl;
            }
        }
    }
    if (tablero[6][3].color != -1) {
        if (tablero[6][0].color != -1 && tablero[6][6].color != -1 && tablero[1][3].color != -1) {
            if (tablero[6][3].color == 1) {
                cout << "la ficha del azul en la posicion 6, 3 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 6, 3 ta atascada pe" << endl;
            }
        }
    }
    if (tablero[3][6].color != -1) {
        if (tablero[0][6].color != -1 && tablero[6][6].color != -1 && tablero[3][5].color != -1) {
            if (tablero[3][6].color == 1) {
                cout << "la ficha del azul en la posicion 3, 6 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 3, 6 ta atascada pe" << endl;
            }
        }
    }
    //esquinas del cuadrado grande
    if (tablero[0][0].color != -1) {
        if (tablero[0][3].color != -1 && tablero[3][0].color != -1) {
            if (tablero[0][0].color == 1) {
                cout << "la ficha del azul en la posicion 1, 1 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 1, 1 ta atascada pe" << endl;
            }
        }
    }
    if (tablero[6][0].color != -1) {
        if (tablero[6][3].color != -1 && tablero[3][0].color != -1) {
            if (tablero[6][0].color == 1) {
                cout << "la ficha del azul en la posicion 7, 1 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 7, 1 ta atascada pe" << endl;
            }
        }
    }
    if (tablero[6][6].color != -1) {
        if (tablero[6][3].color != -1 && tablero[3][6].color != -1) {
            if (tablero[6][6].color == 1) {
                cout << "la ficha del azul en la posicion 7, 3 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 7, 3 ta atascada pe" << endl;
            }
        }
    }
    if (tablero[0][6].color != -1) {
        if (tablero[0][3].color != -1 && tablero[3][6].color != -1) {
            if (tablero[0][6].color == 1) {
                cout << "la ficha del azul en la posicion 1, 3 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 1, 3 ta atascada pe" << endl;
            }
        }
    }
 
    //cuadrado de en medio pe
 
    if (tablero[1][3].color != -1) {
        if (tablero[1][1].color != -1 && tablero[1][5].color != -1 && tablero[2][3].color != -1 && tablero[0][3].color != -1) {
            if (tablero[1][3].color == 1) {
                cout << "la ficha del azul en la posicion 2, 3 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 2, 3 ta atascada pe" << endl;
            }
        }
    }
    if (tablero[3][1].color != -1) {
        if (tablero[1][1].color != -1 && tablero[5][1].color != -1 && tablero[3][0].color != -1 && tablero[3][2].color != -1) {
            if (tablero[3][1].color == 1) {
                cout << "la ficha del azul en la posicion 4, 2 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 4, 2  ta atascada pe" << endl;
            }
        }
    }
    if (tablero[5][3].color != -1) {
        if (tablero[5][1].color != -1 && tablero[5][5].color != -1 && tablero[4][3].color != -1 && tablero[6][3].color != -1) {
            if (tablero[5][3].color == 1) {
                cout << "la ficha del azul en la posicion 6, 2 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 6, 2  ta atascada pe" << endl;
            }
        }
    }
    if (tablero[3][5].color != -1) {
        if (tablero[1][5].color != -1 && tablero[5][5].color != -1 && tablero[3][4].color != -1 && tablero[3][6].color != -1) {
            if (tablero[3][5].color == 1) {
                cout << "la ficha del azul en la posicion 4, 5 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 4, 5  ta atascada pe" << endl;
            }
        }
    }
    //esquinas del cuadrado mediano pe
    if (tablero[1][1].color != -1) {
        if (tablero[1][3].color != -1 && tablero[3][1].color != -1) {
            if (tablero[1][1].color == 1) {
                cout << "la ficha del azul en la posicion 2, 1 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 2, 1 ta atascada pe" << endl;
            }
        }
    }
    if (tablero[5][1].color != -1) {
        if (tablero[3][1].color != -1 && tablero[5][3].color != -1) {
            if (tablero[5][1].color == 1) {
                cout << "la ficha del azul en la posicion 6, 1 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 6, 1 ta atascada pe" << endl;
            }
        }
    }
    if (tablero[5][5].color != -1) {
        if (tablero[3][5].color != -1 && tablero[5][3].color != -1) {
            if (tablero[5][5].color == 1) {
                cout << "la ficha del azul en la posicion 6, 3 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 6, 3 ta atascada pe" << endl;
            }
        }
    }
    if (tablero[1][5].color != -1) {
        if (tablero[3][5].color != -1 && tablero[1][3].color != -1) {
            if (tablero[1][5].color == 1) {
                cout << "la ficha del azul en la posicion 2, 3 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 2, 3 ta atascada pe" << endl;
            }
        }
    }
    //cuadrado pequeño 
    if (tablero[2][3].color != -1) {
        if (tablero[2][2].color != -1 && tablero[2][4].color != -1 && tablero[1][3].color != -1) {
            if (tablero[2][3].color == 1) {
                cout << "la ficha del azul en la posicion 3, 2 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 3, 2 ta atascada pe" << endl;
            }
        }
    }
    if (tablero[3][2].color != -1) {
        if (tablero[3][1].color != -1 && tablero[2][2].color != -1 && tablero[4][2].color != -1) {
            if (tablero[3][2].color == 1) {
                cout << "la ficha del azul en la posicion 4, 3 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 4, 3 ta atascada pe" << endl;
            }
        }
    }
    if (tablero[4][3].color != -1) {
        if (tablero[4][4].color != -1 && tablero[5][3].color != -1 && tablero[4][2].color != -1) {
            if (tablero[4][3].color == 1) {
                cout << "la ficha del azul en la posicion 5, 2 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 5, 2 ta atascada pe" << endl;
            }
        }
    }
    if (tablero[3][4].color != -1) {
        if (tablero[4][4].color != -1 && tablero[2][4].color != -1 && tablero[3][5].color != -1) {
            if (tablero[4][3].color == 1) {
                cout << "la ficha del azul en la posicion 4, 4 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 4, 4 ta atascada pe" << endl;
            }
        }
    }
    //esquinas
    if (tablero[2][2].color != -1) {
        if (tablero[3][2].color != -1 && tablero[2][3].color != -1) {
            if (tablero[2][2].color == 1) {
                cout << "la ficha del azul en la posicion 3, 1 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 3, 1 ta atascada pe" << endl;
            }
        }
    }
    if (tablero[2][4].color != -1) {
        if (tablero[3][4].color != -1 && tablero[2][3].color != -1) {
            if (tablero[2][4].color == 1) {
                cout << "la ficha del azul en la posicion 3, 3 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 3, 3 ta atascada pe" << endl;
            }
        }
    }
    if (tablero[4][2].color != -1) {
        if (tablero[3][2].color != -1 && tablero[4][3].color != -1) {
            if (tablero[4][2].color == 1) {
                cout << "la ficha del azul en la posicion 5, 1 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 5, 1 ta atascada pe" << endl;
            }
        }
    }
    if (tablero[4][4].color != -1) {
        if (tablero[3][4].color != -1 && tablero[4][3].color != -1) {
            if (tablero[4][4].color == 1) {
                cout << "la ficha del azul en la posicion 5, 3 ta atascada pe" << endl;
            }
            else {
                cout << "la ficha del rojo en la posicion 5, 3 ta atascada pe" << endl;
            }
        }
    }
    return 0;
}