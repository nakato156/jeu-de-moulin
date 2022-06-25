#include <iostream>
#include <string>
#include <time.h>
#include "Bot.cpp"
#include "Menu.cpp"

using namespace std;

int piernitasCalientes(Tablero& tablero);

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
    col = userXYToTableroXY(row, col); row--;
    Ficha *arr = tablero.getRow(row);
    int color = tablero[row][col].getColor();
    bool molino = arr[0].getColor() == color;
    int max;
    if( molino ){
        max = row != 4 ? 3 : 7;
        for(int i = 1; i < max; i++){
            if(i == 3) continue;
            if(molino && arr[i].getColor() == color) molino = true;
            else molino = false;
        }
        if( molino ) return true;
    }

    delete[] arr;
    arr = tablero.getCol(col);
    molino = arr[0].getColor() == color;

    if( !molino ) return false;
    for(int i = 1; i < 7; i++){
        if(i == 3) continue;
        int act_color = arr[i].getColor();
        if( act_color < -1 || act_color > 1 ) continue;
        else if(act_color != color) return false;
    }
    return true;
}

template <typename T>
bool eliminarFicha(Tablero &tablero, int row, int col, T oponente){
    col = userXYToTableroXY(row, col);
    if (col == -1) return false;
    row--;
    if ( !(tablero.Iam(row, col, oponente.color)) ){
        cout << "La ficha no le pertenece " << oponente.color << " " << row << " " << col<< endl;
        return false;
    }
    if ( InMolino(tablero, row+1, col) ){
        cout << "La ficha forma un molino, no la puede eliminar" << endl; 
        return false;
    }
    oponente.fichas--;
    tablero.SetFicha(row, col, -1);
    return true;
}

template <typename T>
void WhenMolino (Tablero &tablero, T oponente){
    while(1){
        int eliminar_fila, eliminar_col;
        cout << "fila de la ficha a eliminar: ";
        cin >> eliminar_fila;
        cout << "columna de la ficha a eliminar: ";
        cin >> eliminar_col;
        bool eliminado = eliminarFicha(tablero, eliminar_fila, eliminar_col, oponente);
        // cout << "exito" << endl;
        if(eliminado) return;
        cout << "Vuelva a intentarlo." << endl;
    }
}

void Game(Bot player1, Jugador player2){
    Tablero tablero;

    int isMove, row, col, *puntos = nullptr;
    char direccion;
    bool active_move = false;

    tablero.Show(1);

    for(int i = 0; ; i++){
        if(i == 17) {
            cout << "movida de fichas" << endl;
            active_move = true;
        }

        if(i%2 == 0){
            cout << "Turno de " << player1.nombre << endl;
            player1.PlayGame(tablero, active_move);
        }else{
            cout << "Turno de " << player2.nombre << endl;
            player2.PlayGame(tablero, active_move);
        }

        if(i > 1) {
            if(puntos != nullptr){
                int *n_puntos = puntoenhori(tablero);
                if(puntos[0] != n_puntos[0] || puntos[1] != n_puntos[1]){
                    puntos = n_puntos;
                    string nombre_player = i % 2 ? player2.nombre : player1.nombre;
                    cout << "molino para " << nombre_player << endl;
                    if ( i % 2 ) { 
                        WhenMolino(tablero, player1);
                    }
                    else player1.Molino(tablero);
                }
            }else puntos = puntoenhori(tablero);
            piernitasCalientes(tablero);
        }
        tablero.Show(0);
    }
}

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
        if( player.fichas == 2 || oponente.fichas == 2) break;
        
        if(i == 17) {
            cout << "movida de fichas" << endl;
            active_move = true;
        }
        cout << "Turno de " << player.nombre << endl;
        player.PlayGame(tablero, active_move);

        if(i > 1) {
            if(puntos != nullptr){
                int *n_puntos = puntoenhori(tablero);
                if(puntos[0] != n_puntos[0] || puntos[1] != n_puntos[1]){
                    puntos = n_puntos;
                    cout << "molino para " << player.nombre << endl;
                    WhenMolino(tablero, oponente);
                    int *n_puntos = puntoenhori(tablero);
                    puntos[0] = n_puntos[0]; puntos[1] = n_puntos[1];
                }
            }else puntos = puntoenhori(tablero);
            piernitasCalientes(tablero);
        }
        tablero.Show(1);
    }
    if ( player.fichas == 2 ) piernini(oponente, player);
    else piernini(player, oponente);

}

int piernitasCalientes(Tablero& tablero) {
    bool *results = new bool[24];
    //validaciones del cuadrado mas grande, incluyendo lineas de en medio
    if (tablero[0][3].color != -1) {
        if (tablero[0][0].color !=-1 && tablero[0][6].color!=-1 && tablero[1][3].color !=-1) {
            tablero[0][3].block = true;
        }else tablero[0][3].block = false;
    }
    if (tablero[3][0].color != -1) {
        if (tablero[0][0].color != -1 && tablero[6][0].color != -1 && tablero[3][1].color != -1) {
            tablero[3][0].block = true;
        } else tablero[3][0].block = false;
    }
    if (tablero[6][3].color != -1) {
        if (tablero[6][0].color != -1 && tablero[6][6].color != -1 && tablero[1][3].color != -1) {
            tablero[6][3].block = true;
        }else tablero[6][3].block = false;
    }
    if (tablero[3][6].color != -1) {
        if (tablero[0][6].color != -1 && tablero[6][6].color != -1 && tablero[3][5].color != -1) {
            tablero[3][6].block = true;
        } else tablero[3][6].block = false;
    }
    //esquinas del cuadrado grande
    if (tablero[0][0].color != -1) {
        if (tablero[0][3].color != -1 && tablero[3][0].color != -1) {
            tablero[0][0].block = true;
        }else tablero[0][0].block = false;
    }
    if (tablero[6][0].color != -1) {
        if (tablero[6][3].color != -1 && tablero[3][0].color != -1) {
            tablero[6][0].block = true;
        }else tablero[6][0].block = false;
    }
    if (tablero[6][6].color != -1) {
        if (tablero[6][3].color != -1 && tablero[3][6].color != -1) {
            tablero[6][6].block = true;
        }else tablero[6][6].block = false;
    }
    if (tablero[0][6].color != -1) {
        if (tablero[0][3].color != -1 && tablero[3][6].color != -1) {
            tablero[0][6].block = true;
        }else tablero[0][6].block = false;
    }
 
    //cuadrado de en medio pe
    if (tablero[1][3].color != -1) {
        if (tablero[1][1].color != -1 && tablero[1][5].color != -1 && tablero[2][3].color != -1 && tablero[0][3].color != -1) {
            tablero[1][3].block = true;
        }else tablero[1][3].block = false;
    }
    if (tablero[3][1].color != -1) {
        if (tablero[1][1].color != -1 && tablero[5][1].color != -1 && tablero[3][0].color != -1 && tablero[3][2].color != -1) {
            tablero[3][1].block = true;
        }else tablero[3][1].block = false;
    }
    if (tablero[5][3].color != -1) {
        if (tablero[5][1].color != -1 && tablero[5][5].color != -1 && tablero[4][3].color != -1 && tablero[6][3].color != -1) {
            tablero[5][3].block = true;
        }else tablero[5][3].block = false;
    }
    if (tablero[3][5].color != -1) {
        if (tablero[1][5].color != -1 && tablero[5][5].color != -1 && tablero[3][4].color != -1 && tablero[3][6].color != -1) {
            tablero[3][5].block = true;
        }else tablero[3][5].block = false;
    }
    //esquinas del cuadrado mediano pe
    if (tablero[1][1].color != -1) {
        if (tablero[1][3].color != -1 && tablero[3][1].color != -1) {
            tablero[1][1].block = true;
        }else tablero[1][1].block = false;
    }
    if (tablero[5][1].color != -1) {
        if (tablero[3][1].color != -1 && tablero[5][3].color != -1) {
            tablero[5][1].block = true;
        }else tablero[5][1].block = false;
    }
    if (tablero[5][5].color != -1) {
        if (tablero[3][5].color != -1 && tablero[5][3].color != -1) {
            tablero[5][5].block = true;
        }else tablero[5][5].block = false;
    }
    if (tablero[1][5].color != -1) {
        if (tablero[3][5].color != -1 && tablero[1][3].color != -1) {
            tablero[1][5].block = true;
        }else tablero[1][5].block = false;
    }
    //cuadrado pequeño 
    if (tablero[2][3].color != -1) {
        if (tablero[2][2].color != -1 && tablero[2][4].color != -1 && tablero[1][3].color != -1) {
            tablero[2][3].block = true;
        }else tablero[2][3].block = false;
    }
    if (tablero[3][2].color != -1) {
        if (tablero[3][1].color != -1 && tablero[2][2].color != -1 && tablero[4][2].color != -1) {
            tablero[3][2].block = true;
        }else tablero[3][2].block = false;
    }
    if (tablero[4][3].color != -1) {
        if (tablero[4][4].color != -1 && tablero[5][3].color != -1 && tablero[4][2].color != -1) {
            tablero[4][3].block = true;
        }else tablero[4][3].block = false;
    }
    if (tablero[3][4].color != -1) {
        if (tablero[4][4].color != -1 && tablero[2][4].color != -1 && tablero[3][5].color != -1) {
            tablero[3][4].block = true;
        }else tablero[3][4].block = false;
    }
    //esquinas
    if (tablero[2][2].color != -1) {
        if (tablero[3][2].color != -1 && tablero[2][3].color != -1) {
            tablero[2][2].block = true;
        }else tablero[2][2].block = false;
    }
    if (tablero[2][4].color != -1) {
        if (tablero[3][4].color != -1 && tablero[2][3].color != -1) {
            tablero[2][4].block = true;
        }else tablero[2][4].block = false;
    }
    if (tablero[4][2].color != -1) {
        if (tablero[3][2].color != -1 && tablero[4][3].color != -1) {
            tablero[4][2].block = true;
        }else tablero[4][2].block = false;
    }
    if (tablero[4][4].color != -1) {
        if (tablero[3][4].color != -1 && tablero[4][3].color != -1) {
            tablero[4][4].block = true;
        }else tablero[4][2].block = false;
    }
    return 0;
}