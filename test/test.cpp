#include "../modules/Tablero.cpp"
#include "../modules/Cache.cpp"

int main(){
    Tablero tablero = Tablero();
    CacheGame<Tablero> game;

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