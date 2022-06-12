#include <iostream>
#include <windows.h>

/*
0 para Negras
1 para Blancas
*/

using namespace std;

struct Ficha {
    Ficha() = default;
    Ficha(int color, string repr): color(color), repr(repr) {}
    int color;
    string repr;
    public:
    void imprimir(){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if(color == -1){
            cout << "*";
            return;
        }
        int color_letra =  !color ? FOREGROUND_RED : FOREGROUND_BLUE;
        SetConsoleTextAttribute(hConsole, color_letra);
        cout << repr;
        SetConsoleTextAttribute(hConsole, 7);
    }
};

struct Jugador {
    Jugador() = default;
    Jugador(int color, string nombre, int fichas = 9, int movimientos = 0): 
    color(color), nombre(nombre), fichas(fichas), movimientos(movimientos) {}
    int turno;
    int color;
    string nombre;
    int fichas = 9;
    int movimientos = 0;
};

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
                cout << "|--";
                tablero[i][0].imprimir();
                cout << "--------";
                tablero[i][3].imprimir();
                cout << "--------";
                tablero[i][6].imprimir();
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
    void ColocarFicha(int x, int y, Ficha ficha){
        tablero[x][y] = ficha;
    }
    void eliminarFicha(int x, int y){
        tablero[x][y] = Ficha(-1, "*");
    }
};

Ficha **generarTablero();
void mostrarTablero(Ficha **tablero);

Jugador RegistrarJugador(int enable_color = 1, int ant_color = 0){
    int fichas, movimientos, color;
    string nombre;
    char _color;

    cout << "Ingrese su nombre: ";
    cin >> nombre;
    if(enable_color){
        cout << "color de ficha (R/A): ";
        cin >> _color;
        color = _color=='A';
    }else color = !ant_color;

    return Jugador( color, nombre );
}

Tablero ColocarFicha(Tablero tablero, Jugador player);

void initGame(Jugador player1, Jugador player2);

int main(){
    Jugador player1 = RegistrarJugador();
    Jugador player2 = RegistrarJugador(0, player1.color);
    system("cls");
    initGame(player1, player2);
    return 0;
}

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

    tablero.tablero[row][col].color = player.color;
    // cout << ficha.imprimir() << endl;
    return tablero;
}

void initGame(Jugador player1, Jugador player2){
    Tablero tablero = Tablero();
    tablero.Show();

    Jugador player;

    for(int i=0; i<18; i++){ 
        player =  i%2==0 ? player1 : player2;
        tablero = ColocarFicha(tablero, player);
        tablero.Show();
    }
}

