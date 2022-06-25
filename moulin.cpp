#include <iostream>
#include "modules/Funciones.cpp"
#include "modules/Jugador.cpp"

using namespace std;

void PlayOff2Players() {
    Jugador player1 = RegistrarJugador();
    Jugador player2 = RegistrarJugador(player1.colorj);
    Game(player1, player2);
}

void PlayWithBot() {
    Jugador player = RegistrarJugador();
    Bot bot = Bot(player.colorj);
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
        cout << "coming soon" << endl;
        break;
    case 2:
        MenuOffline(PlayWithBot, PlayOff2Players);
        break;
    }
    return 0;
}