#include <iostream>
#include <string>
#include <time.h>
#include "Bot.cpp"
#include "Menu.cpp"

using namespace std;

void piernitasCalientes(Tablero& tablero);
void piernini(Jugador winner, Jugador losser);

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

    if ( tablero.checkRow(row, color) ) return true;
    else return tablero.checkCol(col, color);
}

template <typename T>
bool eliminarFicha(Tablero &tablero, int row, int col, T &oponente){
    col = userXYToTableroXY(row, col);
    if (col == -1) return false;
    row--;
    if ( tablero[row][col].getColor() != oponente.color) {
        cout << "La ficha le pertenece " << oponente.color << " " << row << " " << col<< endl;
        return false;
    }
    if ( InMolino(tablero, row, col) ){
        cout << "La ficha forma un molino, no la puede eliminar" << endl; 
        return false;
    }
    oponente.fichas -= 1;
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
        tablero.Show(1);
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
        if (player.fichas == 2 || oponente.fichas == 2)
        {
            break;
        }
        cout << "fichas: " << player.fichas << endl;
        cout << "fichas oponente: " << oponente.fichas << endl;
        
        if(i == 17) {
            cout << "movida de fichas" << endl;
            active_move = true;
        }
        cout << "Turno de " << player.nombre << endl;
        piernitasCalientes(tablero);
        player.PlayGame(tablero, active_move);

        tablero.Show();

        if(i > 1) {
            if(puntos != nullptr){
                int *n_puntos = puntoenhori(tablero);
                if(puntos[0] < n_puntos[0] || puntos[1] < n_puntos[1] || puntos[2] < n_puntos[2]){
                    puntos = n_puntos;
                    cout << "molino para " << player.nombre << endl;
                    WhenMolino(tablero, oponente);
                    int *n_puntos = puntoenhori(tablero);
                    puntos[0] = n_puntos[0]; puntos[1] = n_puntos[1]; puntos[2] = n_puntos[2];
                }
                else {
                    puntos = puntoenhori(tablero);
                }
            }else puntos = puntoenhori(tablero);

            tablero.Show(1);
        }
    }
    if ( player.fichas == 2 ) piernini(oponente, player);
    else piernini(player, oponente);

}

void piernitasCalientes(Tablero& tablero) {
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
        }else tablero[4][4].block = false;
    }
}
void piernini(Jugador winner, Jugador losser) {
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
    cout << "numero de fichas: "<< winner.fichas<<endl;
    cout << "numeor de movimientos: "<<winner.movimientos<<endl;
    cout << "=============== PERDEDOR =============== " << endl;
    if (variableini == 0) {
        cout << losser.nombre << "mas suerte para la proxima :c" << endl;
    }
    else {
        cout << losser.nombre << "buen intento, pero no fue suficiente :(" << endl;
    }
    cout << "Estadisticas Perdedor---------------"<<endl;
    cout << "numero de fichas: " << losser.fichas<<endl;
    cout << "numeor de movimientos: " << losser.movimientos<<endl;
}