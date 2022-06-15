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

    Jugador player;

    for(int i=0; i<18; i++){ 
        player =  i%2==0 ? player1 : player2;
        tablero = ColocarFicha(tablero, player);
        tablero.Show(1);
    }
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