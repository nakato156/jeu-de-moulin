#ifndef CODIGO_BOT
#define CODIGO_BOT
#include <time.h>
#include "Jugador.cpp"

struct Bot : public Jugador {//herencia de jugador, para que el parametro de nuestras funcinoes sean compatibles
    bool first = true;//realiza el primer movimiento?
    int fichas = 9, size = 0;
    int color;
    string nombre = "El carinioso";
    Ficha *posFichas;
    Bot() = default;//constructor, compilador arma el constructor por defecto
    Bot(int _color){//constructor, pasar el color para que se le atribye a color
        //sintaxis: condicion ? valor_verdadero : valor_falso
        color = _color == 1 ? 0 : 1;
        posFichas = new Ficha[1];
    }
    ~Bot(){//destructor
        delete[] posFichas;
    }

    void PlayGame(Tablero &tablero, bool active_move) {
        if( first ){//si es true, para que el bot ponga una ficha en una posicion random
            srand(time(NULL));
            int col_random, row_random;
            while(1){
                row_random = 1 + rand() % 7;
                col_random = userXYToTableroXY(row_random, 1 + rand() % 7);
                if(col_random != -1) break;
            }
            row_random--;//le resta uno a row
            tablero[row_random][col_random].color = this->color;//colocamos el color del bot en la fila y columna donde salio, this: para este struct
            addFicha(row_random, col_random);
            first = false;//first hace referencia a la variable de la linea 7
            return;
        } else if ( active_move ){//si estamos moviendo la ficha
            MyDijkstra(tablero);
        } else pensar(tablero);//poner una ficha
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
    void pensar(Tablero &tablero){//en donde poner la ficha
        for(int row = 1; row<8; row++){//recorremos las filas
            bool maybeWin = false;
            int contFichas = 0;//contador de fichas
            for(int col = 1; col<8; col++){//recorremos las columnas
                int _col = userXYToTableroXY(row, col);
                if ( _col == -1 && !(tablero.isEmptyCell(row-1, _col)) ) continue;
                int _row = row-1;
                int colorFicha = tablero[_row][_col].getColor();
                if (colorFicha != this->color) contFichas++;//si el color de la ficha es diferente a nuestro color se suma 1 a cont fichas
                maybeWin = contFichas == 2;//si contfichas ==2, maybewin sera true
                if (maybeWin && colorFicha == -1 ) {//si maybewin = true y si el color de la ficha es -1
                    tablero[_row][_col].color = this->color;//si esa condicion se cumple el bot pondra su ficha ahi 
                    return;
                }
            }
        }
        cout << "no se me ocurrio nada :(" << endl;//si no se cumple ninguna condicion el bot escribe esto
    }

    void Molino(Tablero &tablero, Jugador &oponente){//borra una ficha aleatoria
        while(1) {
            int row = rand() % 7;
            int col = rand() % 7;

            col = userXYToTableroXY(row, col); row--;
            if ( col != -1 && tablero[row][col].getColor() != -1 && tablero[row][col].getColor() != color){//valida si la ficha se puede borrar
                tablero[row][col].reset();//poner la ficha en blanco
                oponente.fichas--;//restar uno al contador de fichas
                break;
            }
        }
    }

    void MyDijkstra(Tablero &tablero){
        for(int i = 1; i< 8; i++){//recorre todo el tablero
            for ( int j = 1; j<8; j++){//columnas
                int col = userXYToTableroXY(i, j);//posicion que estamos sugiriendo es valida
                if( col == -1 ) continue;//regresa al principio del ciclo
                else if ( tablero[i-1][col].getColor() == color && !(tablero[i-1][col].block) ){//verificar si este color es igual al nuestro y tambien se verifica si esa ficha esta bloqueada
                    int dir = 0;
                    while(1){
                        char dirs[4] = {'w', 'a', 's', 'd'};
                        int ult_coordenada[2] = {-1, -1};
                        if( tablero.moveFicha(i-1, col, i, j,  dirs[dir], color, ult_coordenada) ) break;//comprueba si se puede mover hacia arriba en caso contrario
                        if( dir != 3) dir++;//se le aumenta uno a dir accediendo al arreglo en la posicion siguiente 
                        else break;
                    }
                }
            }
        }
    }

};
#endif