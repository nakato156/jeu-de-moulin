#include <iostream>
#include "modules/Funciones.cpp"
#include "modules/Jugador.cpp"

using namespace std;

void PlayOff2Players() {
    Jugador player1 = RegistrarJugador();
    Jugador player2 = RegistrarJugador(player1.color);
    Game(player1, player2);
}

void PlayWithBot() {
    Jugador player = RegistrarJugador();
    Bot bot = Bot(player.color);//para que el bot eliga un color diferente al del jugador
    cout << "El Bot esta en etapa de desarrollo" << endl;
    system("pause");
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