#ifndef CODIGO_TABLERO
#define CODIGO_TABLERO

#include "Jugador.cpp"
#include "Ficha.cpp"

void printEsp(int cant, int code){
    for(int i=0; i<cant; i++) cout << char(code);
}

int userXYToTableroXY(int row, int col){
    if (row < 0 && row > 7) return -1;
    if (row == 1 || row == 7) col = (col-1)*3;
    else if (row == 2 || row == 6) col = (col*2)-1;
    else if (row == 3 || row == 5) col++;
    else if (row == 4) col = col<4 ? col-1 : col;
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
        if (clear) system("cls");
        cout << char(201); printEsp(23, 205); cout << char(187) << endl;
        for(int i = 0; i<7; i++){
            printf("%c  ", 186);
            if (i==0 || i==6){
                tablero[i][0].imprimir();
                printEsp(8, 205); tablero[i][3].imprimir();
                printEsp(8, 205); tablero[i][6].imprimir();
            }else if (i==1 || i==5){
                printf("%c  ", 186); 
                tablero[i][1].imprimir();
                printEsp(5, 205); tablero[i][3].imprimir();
                printEsp(5, 205); tablero[i][5].imprimir();
                printf("  %c", 186);
            }else if (i==2 || i==4){
                printf("%c  %c  ", 186, 186); tablero[i][2].imprimir();
                printEsp(2, 205); tablero[i][3].imprimir();
                printEsp(2, 205); tablero[i][4].imprimir();
                printf("  %c  %c", 186, 186);
            }else if (i==3){
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
    void SetFicha(int row, int col, int color){
        col = userXYToTableroXY(row, col);
        row--;
        tablero[row][col].color = color;
    }
    bool eliminarFicha(int x, int y, Jugador player){
        x = userXYToTableroXY(x, y);
        if (x == -1) return false;
        y--;
        player.fichas--;
        tablero[x][y].color = -1;
        return true;
    }
    bool isEmptyCell (int x, int y){
        return tablero[x][y].color==-1;
    }
    int* IsValidDireccion(int row, int col, char dir){

    }
    int moveFicha(int row, int col, char dir, int color){
        int act_col = userXYToTableroXY(row, col);
        int act_row = row-1;

        if (tablero[act_row][act_col].color != color) return 0;

        if (dir == 'a') col--;
        else if (dir == 'd') col++;
        
        col = userXYToTableroXY(row, col);
        row --;

        int ws = 3, _row = row;
        if (dir == 'w' || dir == 's'){
            if (col>2) _row = 6 - col;
            _row = ws - col;
            row += dir == 'w' ? -_row : _row;
        }
        
        if (col < 0 || row < 0) return -1;

        if ( isEmptyCell(row, col) ){
            tablero[act_row][act_col].color = -1;
            tablero[row][col].color = color;
            return true;
        }
        // cout << "la casilla esta ocupada. Intente con otra posicion";
        return false;
    }
    Ficha *operator [] (unsigned int index){ return tablero[index]; }
};

Tablero ColocarFicha(Tablero tablero, Jugador player){
    int row, col;
    player.leerFicha(row, col, "ingrese la fila donde ira la ficha: ", "ingrese la columna donde ira la ficha: ");
    tablero.SetFicha(row, col, player.color);
    return tablero;
}

#endif