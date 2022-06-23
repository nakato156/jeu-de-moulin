#include <iostream>
#include "modules/Funciones.cpp"
#include "modules/Jugador.cpp"
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