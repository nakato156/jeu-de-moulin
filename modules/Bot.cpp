#include "Jugador.cpp"

struct Bot : public Jugador {
    public:
    bool first = true;
    int fichas = 9, size = 0;
    int color;
    Ficha *posFichas = new Ficha[9];
    Bot() = default;
    Bot(int color){
        this->color = color == 1 ? 0 : 1;
        this->nombre = "BOTcito"
    }
    ~Bot(){
        delete[] posFichas;
    }

    void PlayGame(Tablero &tablero, bool active_move, Bot exc) {
        if( first ){
            int row_random = rand() % 7;
            int col_random;
            while(1){
                col_random = userXYToTableroXY(row_random, 1 + rand() % 9);
                if(col_random != -1) break;
            }
            Ficha pos_ficha = tablero[row_random][col_random];
            pos_ficha.color = this->color;
            pos_ficha.setCoordenate(row_random, col_random);
            posFichas[size];
            size++;
            first = false;
            return;
        }else if( active_move ){

        }
        pensar(tablero);
    }

    void pensar(Tablero &tablero){
        int stop = 0;
        for(int row = 0; row<7; row++){
            bool maybeWin = false;
            int contFichas = 0;
            for(int col = 0; col<7; col++){
                int colorFicha = tablero[row][col].color;
                if(colorFicha != this->color) contFichas++;
                else if(maybeWin && colorFicha == -1 ) {
                    tablero[row][col].color = this->color;
                    stop = 1;
                    break;
                }else contFichas = 0;
                maybeWin = contFichas == 2;
            }
            if(stop) break;
        }
    }

    void Dijkstra(Tablero const tablero){

    }

};

