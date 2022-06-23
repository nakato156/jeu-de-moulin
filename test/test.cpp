// #include "../modules/Jugador.cpp"
// #include "../modules/Bot.cpp"
#include "../modules/Cache.cpp"
#include "../modules/Menu.cpp"
#include "../modules/Funciones.cpp"

using namespace std;

void animationTablero(){
    Tablero tablero;
    CacheGame game;

    tablero.Show();

    for(int i = 0; i<5; i++){
        tablero[i][1].color = 1;
        game.add(tablero);
    }
    
    for(int i=0; i<5; i++){
        game.cache[i].Show();
        cout << endl << endl;
    }
}

void testMenu() {
    mostrarReglas();
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
    testPlayWithBot();
    return 0;
}