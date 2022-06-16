#include <iostream>
#include "modules/Tablero.cpp"
#include "modules/Menu.cpp"
#include "modules/Bot.cpp"
/*
0 para Rojos
1 para Azules
*/
using namespace std;
void PlayOff2Players() {
    Jugador player1 = RegistrarJugador();
    Jugador player2 = RegistrarJugador(0, player1.color);
    system("cls");

    Tablero tablero = Tablero();
    tablero.Show(1);

    Jugador player, oponente;
    int *puntos = nullptr;
    int pnt_para, eliminar_fila, eliminar_col;

    for(int i=0; i<18; i++){ 
        if(i%2 == 0){
            player = player1;
            oponente = player2;
        }else{
            player = player2;
            oponente = player1;
        }
        cout << "Turno de " << player.nombre << endl;
        tablero = ColocarFicha(tablero, player);
        if(i > 1) {
            if(puntos != nullptr){
                int *n_puntos = puntoenhori(tablero);
                // cout << "anteriores puntos: " << puntos[0] << ", " << puntos[1] << endl;
                // cout << "actuales puntos: " << n_puntos[0] << ", " << n_puntos[1] << endl;
                if(puntos[0] != n_puntos[0] || puntos[1] != n_puntos[1]){
                    pnt_para = puntos[0] != n_puntos[0] ? 1 : 0;
                    puntos = n_puntos;
                    cout << "molino para " << player.nombre << endl;
                    cout << "fila de la ficha a eliminar: ";
                    cin >> eliminar_fila;
                    cout << "columna de la ficha a eliminar: ";
                    cin >> eliminar_col;
                    tablero.eliminarFicha(eliminar_fila, eliminar_col, oponente);
                }
            }else puntos = puntoenhori(tablero);
        }
        tablero.Show(1);
    }
    cout << "movida de fichas" << endl;
    int i = 0, isMove, row, col;
    char direccion;
    while(1){
        if(player.fichas == 2) break;
        player =  i%2==0 ? player1 : player2;
        cout << "Turno de " << player.nombre << endl;
        player.leerFicha(row, col, "Ingrese la fila de la ficha a mover: ", "ingrese la columna de la ficha a mover: ");
        
        if(tablero[row][col].color != player.color ){
            cout << "esa ficha no le pertenece." << endl;
            continue;
        }
        if(player.fichas == 3) tablero.SetFicha(row, col, player.color);
        else {
            do
            {
                cout << "A donde lo deseas mover? (w/a/s/d): ";
                cin >> direccion;
                direccion = tolower(direccion);
                isMove = tablero.moveFicha(row, col, direccion, player.color);
            } while (isMove!=1);
        }
        tablero.Show(1);
        i++;
    }
    cout << "perdio: " << player.nombre << endl;
}

void PlayWithBot() {

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