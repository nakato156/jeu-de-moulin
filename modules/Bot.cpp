#ifndef CODIGO_BOT
#define CODIGO_BOT
#include <time.h>
#include "Jugador.cpp"

struct Bot : public Jugador {
    public:
    bool first = true;
    int fichas = 9, size = 0;
    int color;
    string nombre = "El cariñoso";
    Ficha *posFichas;
    Bot() = default;
    Bot(int _color){
        color = _color == 1 ? 0 : 1;
        posFichas = new Ficha[1];
    }
    ~Bot(){
        delete[] posFichas;
    }

    void PlayGame(Tablero &tablero, bool active_move) {
        if( first ){
            srand(time(NULL));
            int col_random, row_random;
            while(1){
                row_random = 1 + rand() % 7;
                col_random = userXYToTableroXY(row_random, 1 + rand() % 7);
                if(col_random != -1) break;
            }
            row_random--;
            tablero[row_random][col_random].color = this->color;
            addFicha(row_random, col_random);
            first = false;
            return;
        } else if ( active_move ){
            MyDijkstra(tablero);
        } else pensar(tablero);
    }
    void addFicha(int row, int col){
        Ficha ficha;
        ficha.setCoordenate(row, col);
        if(size == 0) posFichas[size] = ficha;
        else{
            Ficha *new_arr = new Ficha[size];
            for(int i = 0; i < size; i++){
                new_arr[i] = posFichas[i];
            }
            delete[] posFichas;
            posFichas = new_arr;
            posFichas[size] = ficha;
        }
        size++;
    }
    void pensar(Tablero &tablero){
        for(int row = 1; row<8; row++){
            bool maybeWin = false;
            int contFichas = 0;
            for(int col = 1; col<8; col++){
                int _col = userXYToTableroXY(row, col);
                if ( _col == -1 && !(tablero.isEmptyCell(row-1, _col)) ) continue;
                int _row = row-1;
                int colorFicha = tablero[_row][_col].getColor();
                if (colorFicha != this->color) contFichas++;
                maybeWin = contFichas == 2;
                if (maybeWin && colorFicha == -1 ) {
                    tablero[_row][_col].color = this->color;
                    return;
                }
            }
        }
        cout << "no se me ocurrio nada :(" << endl;
    }

    void Molino(Tablero &tablero, Jugador &oponente){
        while(1) {
            int row = rand() % 7;
            int col = rand() % 7;

            col = userXYToTableroXY(row, col); row--;
            if ( col != -1 && tablero[row][col].getColor() != -1 && tablero[row][col].getColor() != color){
                tablero[row][col].reset();
                oponente.fichas--;
                break;
            }
        }
    }

    void MyDijkstra(Tablero &tablero){
        for(int i = 1; i< 8; i++){
            for ( int j = 1; j<8; j++){
                int col = userXYToTableroXY(i, j);
                if( col == -1 ) continue;
                else if ( tablero[i-1][col].getColor() == color && !(tablero[i-1][col].block) ){
                    int dir = 0;
                    while(1){
                        char dirs[4] = {'w', 'a', 's', 'd'};
                        int ult_coordenada[2] = {-1, -1};
                        if( tablero.moveFicha(i-1, col, i, j,  dirs[dir], color, ult_coordenada) ) break;
                        if( i != 3) i++;
                        else break;
                    }
                }
            }
        }
    }

};
#endif