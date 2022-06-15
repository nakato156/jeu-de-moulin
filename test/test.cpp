#include "../modules/Tablero.cpp"
#include "../modules/Cache.cpp"
#include "../modules/Menu.cpp"

void testMenu() {
    mostrarReglas();
}

int main(){
    testMenu();
    return 0;
    Tablero tablero = Tablero();
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