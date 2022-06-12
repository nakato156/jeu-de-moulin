#include "Jugador.cpp"
#include "Ficha.cpp"

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
    void Show(){
        system("cls");
        cout << "_________________________" << endl;
        for(int i = 0; i<7; i++){
            if(i==0 || i==6){
                cout << "|--"; tablero[i][0].imprimir();
                cout << "--------"; tablero[i][3].imprimir();
                cout << "--------"; tablero[i][6].imprimir();
                cout << "--|" << endl;
            }else if(i==1 || i==5){
                cout << "|--|--"; tablero[i][1].imprimir();
                cout << "-----"; tablero[i][3].imprimir();
                cout << "-----"; tablero[i][5].imprimir();
                cout << "-----|" << endl;
            }else if(i==2 || i==4){
                cout << "|--|--|--"; tablero[i][2].imprimir();
                cout << "--"; tablero[i][3].imprimir();
                cout << "--"; tablero[i][4].imprimir();
                cout << "--|--|--|" << endl;
            }else if(i==3){
                cout << "|--"; tablero[i][0].imprimir();
                cout << "--"; tablero[i][1].imprimir(); 
                cout << "--"; tablero[i][2].imprimir();
                cout << "-- --"; tablero[i][4].imprimir();
                cout << "--"; tablero[i][5].imprimir();
                cout << "--"; tablero[i][6].imprimir();
                cout << "--|" << endl;
            }
        }
        cout << "-------------------------" << endl;
    }
    void SetFicha(int x, int y, int color){
        tablero[x][y].color = color;
    }
    void eliminarFicha(int x, int y, Jugador player){
        player.fichas--;
        tablero[x][y] = Ficha(-1, "*");
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

    if(row == 1 || row == 7) col = (col-1)*3;
    else if(row == 2 || row == 6) col = (col*2)-1;
    else if(row == 3 || row == 5) col++;
    else if(row == 4) col = col<4 ? col-1 : col;
    row--;

    tablero.SetFicha(row, col, player.color);
    return tablero;
}
