#include <iostream>
#include "modules/Jugador.cpp"
#include "modules/Menu.cpp"
#include "modules/Bot.cpp"
/*
0 para Rojos
1 para Azules
*/
using namespace std;

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

void Game(Jugador player1, Jugador player2){
    Tablero tablero;
    Jugador player, oponente;

    int isMove, row, col, *puntos = nullptr;
    char direccion;
    bool active_move = false;

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
        player.PlayGame(tablero, active_move);

        if(i > 1) {
            if(puntos != nullptr){
                int *n_puntos = puntoenhori(tablero);
                if(puntos[0] != n_puntos[0] || puntos[1] != n_puntos[1]){
                    // delete puntos;
                    puntos = n_puntos;
                    cout << "molino para " << player.nombre << endl;
                    WhenMolino(tablero, oponente);
                }
            }else puntos = puntoenhori(tablero);
        }
        tablero.Show(1);
    }
}

void PlayOff2Players() {
    Jugador player1 = RegistrarJugador();
    Jugador player2 = RegistrarJugador(0, player1.color);
    Game(player1, player2);
}

void PlayWithBot() {
    Jugador player = RegistrarJugador();
    Bot bot = Bot(player.color);
    Game(bot, player);
}

int main(){
    char jugar;
    int opcion = mostrarMenu();
    if(opcion == 1) {
        mostrarReglas();
        cout << "Desea Jugar? (S/N): ";
        cin >> jugar;
        jugar = toupper(jugar);
        if(jugar != 'S') exit(EXIT_SUCCESS);
    }
    int modo_juego = MenuModo();
    switch (modo_juego)
    {
    case 1:
        /* code Online game*/
        break;
    case 2:
        MenuOffline(PlayWithBot, PlayOff2Players);
        break;
    }
    return 0;
}