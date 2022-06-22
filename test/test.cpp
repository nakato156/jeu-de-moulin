#include <iostream>
// #include "../modules/Tablero.cpp"
// #include "../modules/Bot.cpp"
// #include "../modules/Cache.cpp"
// #include "../modules/Menu.cpp"

using namespace std;
class Padre {
    public:
    int edad;
    string nombre;
    Padre() = default;
    Padre(string nombre, int edad){
        this->nombre = nombre;
        this->edad = edad; 
    }
    void Saludar(){
        cout << "Hola soy " << nombre;
    }
};


class Hijo : public Padre{
    public:
    Hijo(string nombre){
        this->nombre = nombre; 
    }
    void Crecer(){
        edad++;
    }
};


void testBot(){
    Padre padre = Padre("Padre joaquin", 16);
    padre.Saludar();

    cout << endl;

    Hijo bot = Hijo("joaquin");
    bot.Saludar();


    //getter -> obtiene un valor
    // setter -> establece un valor
}

// void animationTablero(){
//     Tablero tablero;
//     CacheGame game;

//     tablero.Show();

//     for(int i = 0; i<5; i++){
//         tablero[i][1].color = 1;
//         game.add(tablero);
//     }
    
//     for(int i=0; i<5; i++){
//         game.cache[i].Show();
//         cout << endl << endl;
//     }
// }

// void testMenu() {
//     mostrarReglas();
// }

// void testMoveFicha(){
//     Tablero tablero;

//     Jugador player1, player2;

//     player1.color = 0;
//     player1.nombre = "c";
//     player2.color = 1;
//     player2.nombre = "x";

//     tablero.SetFicha(2, 1, 0);
//     tablero.Show(1);
    
//     char direccion;
//     cout << "A donde lo desea mover?: ";
//     cin >> direccion;

//     tablero.moveFicha(2, 1, direccion, 0);
//     tablero.Show();
// }

int main(){
    testBot();
    // testMoveFicha();
    return 0;
}