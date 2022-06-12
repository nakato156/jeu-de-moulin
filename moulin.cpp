#include <iostream>
#include "modules/Tablero.cpp"
/*
0 para Rojos
1 para Azules
*/
using namespace std;

void PantallaInicio(){
    cout << "";
}

void initGame(Jugador player1, Jugador player2){
    Tablero tablero = Tablero();
    tablero.Show(1);

    Jugador player;

    for(int i=0; i<18; i++){ 
        player =  i%2==0 ? player1 : player2;
        tablero = ColocarFicha(tablero, player);
        tablero.Show(1);
    }
}

int main(){
    Jugador player1 = RegistrarJugador();
    Jugador player2 = RegistrarJugador(0, player1.color);
    system("cls");
    initGame(player1, player2);
    return 0;
}

