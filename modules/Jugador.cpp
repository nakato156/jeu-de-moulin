#ifndef CODIGO_Jugador
#define CODIGO_Jugador
#include <iostream>
#include "Tablero.cpp"

using namespace std;

void menu()
{
    cout << "Bienvenido a la eleccion del color de sus fichas: " << endl;
    cout << "Estos son sus opciones: " << endl;
    cout << "R) Rojo " << endl;
    cout << "A) Azul " << endl;
    cout << "V) Verde " << endl;
}

char leerOpcion()
{
    char color_jug;
    do {
        cout << "Elija su color por favor: " << endl;
        cin >> color_jug;
        color_jug = toupper(color_jug);
    } while (color_jug != 'R' && color_jug != 'A' && color_jug != 'V');
    return color_jug;
}

int convertirColor(char color_jug)
{
    int nuevo_color = 0;
    if (color_jug == 'R') {
        nuevo_color = 0;
    }
    else if (color_jug == 'A') {
        nuevo_color = 1;
    }
    else if (color_jug == 'V') {
        nuevo_color = 2;
    }
    return nuevo_color;
}

void piernitasCalientes(Tablero& tablero);

struct Jugador {
    Jugador() = default;
    Jugador(int _color, string _nombre): color(_color), nombre(_nombre) {}
    int turno;
    int color;
    string nombre;
    int fichas = 9;
    int movimientos = 0;
    void delFicha(){ fichas--; }
    void PlayGame(Tablero &tablero, bool active_move){
        int row = 0, col = 0;
        while(1){
            if(active_move){
                piernitasCalientes(tablero);
                leerFicha(row, col, "ingrese la fila de la ficha a mover: ", "ingrese la columna de la ficha a mover: ");
                int act_col = userXYToTableroXY(row, col); 
                int act_row = row-1;
                if( tablero[act_row][act_col].block){
                    cout << "la ficha no puede ser movida" << endl;
                    continue;
                }
                if( tablero[act_row][act_col].getColor() != color ) {
                    cout << "La ficha no le corresponde" << endl;
                    continue;
                }
                if ( fichas == 3 ) {
                    leerFicha(row, col, "ingrese la fila de destino: ", "ingrese la columna de destino: ");
                    col = userXYToTableroXY( row, col );
                    if ( col == -1 ) continue;
                    tablero.SetFicha( row-1, col, color);
                    return;
                }
                char dir;
                cout << "a donde lo quiere mover? (w/a/s/d): ";
                cin >> dir;
                if( tablero.moveFicha(act_row, act_col, row, col, tolower(dir), color)) {
                    return;
                }else {
                    cout << "ha ocurrido un error al mover la ficha info: " << endl;
                    cout << "posicion inicial segun el jugador: " << row << ";" << col << endl;
                    cout << "posicion inicial en el tablero: " << act_row << ";" << act_col << endl;
                    cout << "direccion: " << dir << endl << "color de la ficha: " << color << endl;
                }
            }else{
                leerFicha(row, col, "ingrese la fila donde ira la ficha: ", "ingrese la columna donde ira la ficha: ");
                col = userXYToTableroXY(row, col); row--;
                if( tablero.isEmptyCell(row, col) ) break;
            }
        }
        tablero.SetFicha(row, col, color);
    }
    void leerFicha(int &row, int &col, string promt_row, string prompt_col){
        while(1){
            cout << promt_row;
            cin >> row;
            if (row>7 || row<0) continue;
            cout << prompt_col;
            cin >> col;
            if (row==4 && (col>0 && col<7)) break;
            else if (col>0 && col<4) break;
            cout << "valores incorrectos" << endl;
        }
    }
};

void piernitasCalientes(Tablero& tablero) {
    //validaciones del cuadrado mas grande, incluyendo lineas de en medio
    if (tablero[0][3].color != -1) {
        if (tablero[0][0].color !=-1 && tablero[0][6].color!=-1 && tablero[1][3].color !=-1) {
            tablero[0][3].block = true;
        }else tablero[0][3].block = false;
    }
    if (tablero[3][0].color != -1) {
        if (tablero[0][0].color != -1 && tablero[6][0].color != -1 && tablero[3][1].color != -1) {
            tablero[3][0].block = true;
        } else tablero[3][0].block = false;
    }
    if (tablero[6][3].color != -1) {
        if (tablero[6][0].color != -1 && tablero[6][6].color != -1 && tablero[1][3].color != -1) {
            tablero[6][3].block = true;
        }else tablero[6][3].block = false;
    }
    if (tablero[3][6].color != -1) {
        if (tablero[0][6].color != -1 && tablero[6][6].color != -1 && tablero[3][5].color != -1) {
            tablero[3][6].block = true;
        } else tablero[3][6].block = false;
    }
    //esquinas del cuadrado grande
    if (tablero[0][0].color != -1) {
        if (tablero[0][3].color != -1 && tablero[3][0].color != -1) {
            tablero[0][0].block = true;
        }else tablero[0][0].block = false;
    }
    if (tablero[6][0].color != -1) {
        if (tablero[6][3].color != -1 && tablero[3][0].color != -1) {
            tablero[6][0].block = true;
        }else tablero[6][0].block = false;
    }
    if (tablero[6][6].color != -1) {
        if (tablero[6][3].color != -1 && tablero[3][6].color != -1) {
            tablero[6][6].block = true;
        }else tablero[6][6].block = false;
    }
    if (tablero[0][6].color != -1) {
        if (tablero[0][3].color != -1 && tablero[3][6].color != -1) {
            tablero[0][6].block = true;
        }else tablero[0][6].block = false;
    }
 
    //cuadrado de en medio pe
    if (tablero[1][3].color != -1) {
        if (tablero[1][1].color != -1 && tablero[1][5].color != -1 && tablero[2][3].color != -1 && tablero[0][3].color != -1) {
            tablero[1][3].block = true;
        }else tablero[1][3].block = false;
    }
    if (tablero[3][1].color != -1) {
        if (tablero[1][1].color != -1 && tablero[5][1].color != -1 && tablero[3][0].color != -1 && tablero[3][2].color != -1) {
            tablero[3][1].block = true;
        }else tablero[3][1].block = false;
    }
    if (tablero[5][3].color != -1) {
        if (tablero[5][1].color != -1 && tablero[5][5].color != -1 && tablero[4][3].color != -1 && tablero[6][3].color != -1) {
            tablero[5][3].block = true;
        }else tablero[5][3].block = false;
    }
    if (tablero[3][5].color != -1) {
        if (tablero[1][5].color != -1 && tablero[5][5].color != -1 && tablero[3][4].color != -1 && tablero[3][6].color != -1) {
            tablero[3][5].block = true;
        }else tablero[3][5].block = false;
    }
    //esquinas del cuadrado mediano pe
    if (tablero[1][1].color != -1) {
        if (tablero[1][3].color != -1 && tablero[3][1].color != -1) {
            tablero[1][1].block = true;
        }else tablero[1][1].block = false;
    }
    if (tablero[5][1].color != -1) {
        if (tablero[3][1].color != -1 && tablero[5][3].color != -1) {
            tablero[5][1].block = true;
        }else tablero[5][1].block = false;
    }
    if (tablero[5][5].color != -1) {
        if (tablero[3][5].color != -1 && tablero[5][3].color != -1) {
            tablero[5][5].block = true;
        }else tablero[5][5].block = false;
    }
    if (tablero[1][5].color != -1) {
        if (tablero[3][5].color != -1 && tablero[1][3].color != -1) {
            tablero[1][5].block = true;
        }else tablero[1][5].block = false;
    }
    //cuadrado pequeño 
    if (tablero[2][3].color != -1) {
        if (tablero[2][2].color != -1 && tablero[2][4].color != -1 && tablero[1][3].color != -1) {
            tablero[2][3].block = true;
        }else tablero[2][3].block = false;
    }
    if (tablero[3][2].color != -1) {
        if (tablero[3][1].color != -1 && tablero[2][2].color != -1 && tablero[4][2].color != -1) {
            tablero[3][2].block = true;
        }else tablero[3][2].block = false;
    }
    if (tablero[4][3].color != -1) {
        if (tablero[4][4].color != -1 && tablero[5][3].color != -1 && tablero[4][2].color != -1) {
            tablero[4][3].block = true;
        }else tablero[4][3].block = false;
    }
    if (tablero[3][4].color != -1) {
        if (tablero[4][4].color != -1 && tablero[2][4].color != -1 && tablero[3][5].color != -1) {
            tablero[3][4].block = true;
        }else tablero[3][4].block = false;
    }
    //esquinas
    if (tablero[2][2].color != -1) {
        if (tablero[3][2].color != -1 && tablero[2][3].color != -1) {
            tablero[2][2].block = true;
        }else tablero[2][2].block = false;
    }
    if (tablero[2][4].color != -1) {
        if (tablero[3][4].color != -1 && tablero[2][3].color != -1) {
            tablero[2][4].block = true;
        }else tablero[2][4].block = false;
    }
    if (tablero[4][2].color != -1) {
        if (tablero[3][2].color != -1 && tablero[4][3].color != -1) {
            tablero[4][2].block = true;
        }else tablero[4][2].block = false;
    }
    if (tablero[4][4].color != -1) {
        if (tablero[3][4].color != -1 && tablero[4][3].color != -1) {
            tablero[4][4].block = true;
        }else tablero[4][4].block = false;
    }
}

Jugador RegistrarJugador(int ant_color = -2){
    int color;
    string nombre;

    cout << "ingrese su nombre: ";
    cin >> nombre;

    do {
        menu();
        char opc = leerOpcion();
        color = convertirColor(opc);
    } while( ant_color == color );

    return Jugador( color, nombre );
}
#endif