#ifndef CODIGO_TABLERO
#define CODIGO_TABLERO

#include "Jugador.cpp"
#include "Ficha.cpp"

void printEsp(int cant, int code){
    for(int i=0; i<cant; i++) cout << char(code);
}

int userXYToTableroXY(int row, int col){
    if(row < 0 && row > 7) return -1;
    if(row == 1 || row == 7) col = (col-1)*3;
    else if(row == 2 || row == 6) col = (col*2)-1;
    else if(row == 3 || row == 5) col++;
    else if(row == 4) col = col<4 ? col-1 : col;
    else return -1;
    return col;
}

struct Tablero {
    Ficha **tablero;
    public:
    Tablero(){
        tablero = new Ficha*[7];
        for(int i =0; i<7; i++) {
            tablero[i] = new Ficha[7];
            for(int c=0; c<7; c++) tablero[i][c]=Ficha(-1, "O");
        }
    }
    void Show(int clear=0){
        if(clear) system("cls");
        cout << char(201); printEsp(23, 205); cout << char(187) << endl;
        for(int i = 0; i<7; i++){
            printf("%c  ", 186);
            if(i==0 || i==6){
                tablero[i][0].imprimir();
                printEsp(8, 205); tablero[i][3].imprimir();
                printEsp(8, 205); tablero[i][6].imprimir();
            }else if(i==1 || i==5){
                printf("%c  ", 186); 
                tablero[i][1].imprimir();
                printEsp(5, 205); tablero[i][3].imprimir();
                printEsp(5, 205); tablero[i][5].imprimir();
                printf("  %c", 186);
            }else if(i==2 || i==4){
                printf("%c  %c  ", 186, 186); tablero[i][2].imprimir();
                printEsp(2, 205); tablero[i][3].imprimir();
                printEsp(2, 205); tablero[i][4].imprimir();
                printf("  %c  %c", 186, 186);
            }else if(i==3){
                tablero[i][0].imprimir();
                printEsp(2, 205); tablero[i][1].imprimir();
                printEsp(2, 205); tablero[i][2].imprimir();
                printf("%c%c %c%c", 205, 205, 205, 205);
                tablero[i][4].imprimir();
                printEsp(2, 205); tablero[i][5].imprimir();
                printEsp(2, 205); tablero[i][6].imprimir();
            }
            printf("  %c\n", 186);
        }
        cout << char(200); printEsp(23, 205); cout << char(188) << endl;
    }
    void SetFicha(int x, int y, int color){
        x = userXYToTableroXY(x, y);
        y--;
        tablero[x][y].color = color;
    }
    bool eliminarFicha(int x, int y, Jugador player){
        x = userXYToTableroXY(x, y);
        if(x == -1) return false;
        y--;
        player.fichas--;
        tablero[x][y].color = -1;
        return true;
    }
    bool isEmptyCell (int x, int y){
        return tablero[x][y].color==-1;
    }
    bool moveFicha(int x_act, int y_act, int new_x, int new_y, int color){
        if( isEmptyCell(new_x, new_y) ){
            tablero[x_act][y_act].color = -1;
            tablero[new_x][new_y].color = color;
            return true;
        }
        cout << "la casilla esta ocupada. Intente con otra posicion";
    }
    Ficha *operator [] (unsigned int index){ return tablero[index]; }
};

Tablero ColocarFicha(Tablero tablero, Jugador player){
    int row, col;
    while(1){
        cout << "ingrese la fila donde ira la ficha: ";
        cin >> row;
        if(row>7 || row<0) continue;

        cout << "ingrese la columna donde ira la ficha: ";
        cin >> col;
        if(row==4 && (col>0 && col<7)) break;
        else if(col>0 && col<4) break;
        cout << "valores incorrectos" << endl;
    }

    tablero.SetFicha(row, col, player.color);
    return tablero;
}

#endif