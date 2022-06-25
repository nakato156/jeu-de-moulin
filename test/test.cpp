// #include "../modules/Jugador.cpp"
// #include "../modules/Bot.cpp"
// #include "../modules/Cache.cpp"
#include "../modules/Menu.cpp"
#include "../modules/Funciones.cpp"

using namespace std;

void testGets(){
    Tablero tablero;

    tablero.SetFicha(0, 0, 1);
    tablero.SetFicha(0, 3, 0);
    tablero.SetFicha(1, 1, 1);
    tablero.SetFicha(2, 2, 0);
    tablero.Show(1);

    tablero.moveFicha(1, 2, 2, 1, 'd', 1);
    tablero.Show(0);
}

void testMoveFicha(){
    Tablero tablero;

    Jugador player1, player2;

    player1.color = 0;
    player1.nombre = "c";
    player2.color = 1;
    player2.nombre = "x";

    tablero.SetFicha(2, 1, 0);
    tablero.Show(1);
    
    char direccion;
    cout << "A donde lo desea mover?: ";
    cin >> direccion;

    // tablero.moveFicha(2, 1, 2, 1, direccion, 0);
    tablero.Show();
}

void testPlayWithBot(){
    Jugador player = RegistrarJugador();
    Bot bot = Bot(player.color);
    Game(bot, player);
}

int main(){
    testGets();
    return 0;
}