#ifndef CODIGO_BOT
#define CODIGO_BOT
#include <time.h>
#include "Jugador.cpp"

struct Bot {
    public:
    bool first = true;
    int fichas = 9, size = 0;
    int color;
    string nombre = "BOTcito";
    Ficha *posFichas = new Ficha[9];
    Bot() = default;
    Bot(int color){
        this->color = color == 1 ? 0 : 1;
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
            // pos_ficha.setCoordenate(row_random, col_random);
            // posFichas[size];
            size++;
            first = false;
            return;
        }else if( active_move ){

        }
        pensar(tablero);
    }

    void pensar(Tablero &tablero){
        for(int row = 1; row<8; row++){
            bool maybeWin = false;
            int contFichas = 0;
            for(int col = 1; col<8; col++){
                int _col = userXYToTableroXY(row, col);
                if( _col == -1 ) continue;
                int _row = row-1;
                int colorFicha = tablero[_row][_col].getColor();
                if(colorFicha != this->color) contFichas++;
                maybeWin = contFichas == 2;
                if(maybeWin && colorFicha == -1 ) {
                    tablero[_row][_col].color = this->color;
                    cout << _row << "," << _col << endl;
                    return;
                }
            }
        }
        cout << "no se me ocurrio nada :(" << endl;
    }

    void Molino(Tablero const &tablero){

    }

    void Dijkstra(Tablero const &tablero){

    }

};
#endif