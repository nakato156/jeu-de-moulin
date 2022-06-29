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

void ahogamiento(Tablero& tablero);

struct Jugador {
    Jugador() = default;
    Jugador(int _color, string _nombre): color(_color), nombre(_nombre) {}//funciones miembro, utilizadas para asignar el valor de un parametro a un atributo
    //syntax:name_struct( args... ) : name_atr1( arg1 ), name_atr2( arg2 ) ... {}
    int turno;
    int color;
    string nombre;
    int fichas = 9;//numero de fichas al inicio
    int movimientos = 0;
    int ult_coordenada[2] = {-1, -1};
    void delFicha(){ fichas--; }//funcion para restarle 1 a 9
    //funciones dentro de una estructura es un metodo
    void PlayGame(Tablero &tablero, bool active_move){ //tablero se pasa por referencia para evitar que se cree otro tablero, active move es para definir si se puede mover o no
        int row = 0, col = 0; // fila y columna
        while(1) {//=while true
            if(active_move){//si active_move es verdad se ejecuta lo siguiente:
                ahogamiento(tablero);//true si la ficha esta ahogada y false si no lo esta 
                leerFicha(row, col, "ingrese la fila de la ficha a mover: ", "ingrese la columna de la ficha a mover: ");//esta abajo
                int act_col = userXYToTableroXY(row, col); //convierte lo que ingrese el usuario a una posicion en la matriz
                int act_row = row-1;//operacion general de la fila
                if( tablero[act_row][act_col].block){//si la ficha esta bloqueada
                    cout << "la ficha no puede ser movida" << endl;
                    continue;//vuelve al inicio
                }
                if( tablero[act_row][act_col].getColor() != color ) {//si el color de la ficha es distinto de nuestro color entonces:
                    cout << "La ficha no le corresponde" << endl;//se imprime esto 
                    continue;//vuelve al inicio
                }
                if ( fichas == 3 ) {//al contador de fichas, que tiene el jugador
                    leerFicha(row, col, "ingrese la fila de destino: ", "ingrese la columna de destino: ");//punto a otro punto, como queramos
                    col = userXYToTableroXY( row, col );//convierte las coordenadas para el codigo
                    if ( col == -1 ) continue;//cuando da error vuelve al inicio
                    tablero[act_row][act_col].reset();//resetea los valores de la ficha, cuando se deja la coordenada resetea a los valores por defecto
                    tablero.SetFicha( row-1, col, color);
                    movimientos++;//sumando la cantidad de movimientos
                    return;
                }
                char dir;//direccion en wasd
                cout << "a donde lo quiere mover? (w/a/s/d): ";
                cin >> dir;
                if( tablero.moveFicha(act_row, act_col, row, col, tolower(dir), color, ult_coordenada)) {//tolower convierte el caracter a minusculas
                    ult_coordenada[0] = row; ult_coordenada[1] = col;//se actualiza a las ultimas coordenadas
                    movimientos++;
                    return;
                }
            }else{
                leerFicha(row, col, "ingrese la fila donde ira la ficha: ", "ingrese la columna donde ira la ficha: ");//si las fichas no se mueven, solo le pedimos la posicion donde colocara la ficha
                col = userXYToTableroXY(row, col); row--;
                if( tablero.isEmptyCell(row, col) ) break;
            }
        }
        tablero.SetFicha(row, col, color);//establece la ficha 
    }
    void leerFicha(int &row, int &col, string promt_row, string prompt_col){//fila columnas por referencia para modificar directamente
        //promt_row mensaje que se muestra al pedir la fila, promt col lo mismo pero para la columna
        while(1){//while true XD
            cout << promt_row;//mensaje de la fila
            cin >> row;//leemos los datos de fila
            if (row>7 || row<0) continue;//continue: rompe el ciclo y vuelve al principio
            cout << prompt_col;//mostrar mensaje para pedir la columna
            cin >> col;//se lee columna
            if (row==4 && (col>0 && col<7)) break;//verifica si la fila es 4 y si es los valores de la columna deben de ser mayor que 0y<7
            else if (col>0 && col<4) break;
            cout << "valores incorrectos" << endl;
        }
    }
};

void ahogamiento(Tablero& tablero) {
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
        if (tablero[6][0].color != -1 && tablero[6][6].color != -1 && tablero[5][3].color != -1) {
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
}//verifica si la ficha se puede mover o esta atascada

Jugador RegistrarJugador(int ant_color = -2){
    int color;
    string nombre;

    cout << "Ingrese su nombre: ";
    cin >> nombre;

    do {//para que el color de los jugadores no se repitan
        menu();
        char opc = leerOpcion();
        color = convertirColor(opc);
    } while( ant_color == color);

    return Jugador( color, nombre );//retorna una estructura
}
#endif