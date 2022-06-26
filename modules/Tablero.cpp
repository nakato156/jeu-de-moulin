#ifndef CODIGO_TABLERO
#define CODIGO_TABLERO
#include "Ficha.cpp"

void printEsp(int cant, int code){
    for(int i=0; i<cant; i++) cout << char(code);
}

int userXYToTableroXY(int row, int col){
    if ( (row < 1 || row > 7) || ( col < 1 || col > 7) ) return -1;
    else if (row == 1 || row == 7) col = (col-1)*3;
    else if (row == 2 || row == 6) col = (col*2)-1;
    else if (row == 3 || row == 5) col++;
    else if (row == 4) col = col<4 ? col-1 : col;
    else return -1;
    col = col < 7 ? col : -1; 
    return col;
}

struct Tablero {
    Ficha **tablero;
    Tablero(){
        tablero = new Ficha*[7];
        for(int i = 0; i<7; i++) {
            tablero[i] = new Ficha[7];
            for(int c=0; c<7; c++){ Ficha ficha; tablero[i][c] = ficha; }
        }
    }
    ~Tablero(){
        for(int i = 0; i<7; i++) delete[] tablero[i];
        delete[] tablero;
        tablero = nullptr;
    }
    Tablero(const Tablero &) = delete;
    Tablero &operator =(const Tablero &) = delete;
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
    void SetFicha(int row, int col, int _color){
        tablero[row][col].setColor(_color);
    }
    bool Iam(int row, int col, int color){
        return tablero[row][col].getColor() == color;
    }
    bool isEmptyCell (int x, int y){
        return tablero[x][y].getColor() == -1;
    }
    int moveFicha(int act_row, int act_col, int row, int col, char dir, int color){
        if (dir == 'a') col--;
        else if (dir == 'd') col++;
        
        col = userXYToTableroXY(row, col);
        row --;
<<<<<<< HEAD
        int salto, ws = 3, _row = row;
        if (dir == 'w' || dir == 's') {
=======

        int salto, ws = 3, _row = row;
        if (dir == 'w' || dir == 's'){
>>>>>>> faaa7a8bf9b2c800f718abc90311fe4ca3ee4acc
            if (col == 0 || col == 6) {
                salto = 3;
            }
            else if (col == 1 || col == 5) {
                salto = 2;
            }
            else if (col == 2 || col == 3 || col == 4) {
                salto = 1;
            }
            if (dir == 'w') {
                row -= salto;
            }
            else if (dir == 's') {
                row += salto;
            }
        }
        
        if (col < 0 || row < 0) return -1;

        if ( isEmptyCell(row, col) ){
            tablero[act_row][act_col].reset();
            tablero[row][col].setColor(color);
            return true;
        }
        cout << "la casilla esta ocupada. Intente con otra posicion" << endl;
        cout << "info: " << endl << "row en tablero: " << row << endl << "col en tablero: " << col << endl;
        printf("color de la ficha en posicion %i;%i: %i", row, col, tablero[row][col].getColor());
        return false;
    }
    Ficha* getRow(int row){
        if(row < 0 || row > 6) return nullptr;
        Ficha *fila = new Ficha[3];
        if(row == 0 || row == 6) {
            fila[0] = tablero[row][0]; fila[1] = tablero[row][3]; fila[2] = tablero[row][6];
        }else if(row == 1 || row == 5){
            fila[0] = tablero[row][1]; fila[1] = tablero[row][3]; fila[2] = tablero[row][5];
        }else if(row == 2 || row == 4){
            fila[0] = tablero[row][2]; fila[1] = tablero[row][3]; fila[2] = tablero[row][4];
        }else {
            delete[] fila;
            fila = new Ficha[7];
            fila = tablero[row];
        }
        return fila;
    }
    Ficha* getCol(int col){
        Ficha *columna = new Ficha[3];
        if ( col == 0 || col == 6 ){
            columna[0] = tablero[0][col]; columna[1] = tablero[3][col]; columna[2] = tablero[6][col];
        }else if ( col == 1 || col == 5 ){
            columna[0] = tablero[1][col]; columna[1] = tablero[3][col]; columna[2] = tablero[5][col];
        }else if ( col == 2 || col == 4 ){
            columna[0] = tablero[2][col]; columna[1] = tablero[3][col]; columna[2] = tablero[4][col];
        }else{
            delete[] columna;
            columna = new Ficha[7];
            for(int i = 0; i < 7; i++) columna[i] = tablero[i][3];
        }
        return columna;
    }
    Ficha *operator [] (unsigned int index){ return tablero[index]; }
};

int* puntoenhori(Tablero &tablero) {
    int cont_az = 0;
    int cont_rj = 0;
    int color_verde = 0;

    //cuadrado grande
    //horizontales
    if (tablero[0][0].color !=-1 ) { //un o es azul y el otro O es rojo
        if (tablero[0][0].color == tablero[0][3].color && tablero[0][0].color == tablero[0][6].color) {
            if (tablero[0][0].color == 1) {
                cont_az++;
            }
            else if (tablero[0][0].color == 0) {
                cont_rj++;
            }
            else {color_verde++;}
        }

    }
    if (tablero[6][0].color != -1 ) {//un o es azul y el otro O es rojo
        if (tablero[6][0].color == tablero[6][3].color && tablero[6][0].color == tablero[6][6].color) {
            if (tablero[6][0].color == 1) {
                cont_az++;
            }
            else if (tablero[6][0].color == 0) {
                cont_rj++;
            }
            else {color_verde++;}
        }

    }
    //verticales
    if (tablero[0][0].color !=-1 ) {//un O azul y el otro O es rojo
        if (tablero[0][0].color == tablero[3][0].color && tablero[0][0].color == tablero[6][0].color) {
            if (tablero[0][0].color == 1) {
                cont_az++;
            }
            else if (tablero[0][0].color == 0) {
                cont_rj++;
            }
            else {color_verde++;}
        }
    }
    if (tablero[0][6].color !=-1 ) {//un O azul y el otro O es rojo
        if (tablero[0][6].color == tablero[3][6].color && tablero[0][6].color == tablero[6][6].color) {
            if (tablero[0][6].color == 1) {
                cont_az++;
            }
            else if (tablero[0][6].color == 0) {
                cont_rj++;
            }
            else {color_verde++;}
        }
    }
 
    //cuadrado de en medio
    //horizontales
    if (tablero[1][1].color !=-1 ) {//un o es azul y el otro O es rojo
        if (tablero[1][1].color == tablero[1][3].color && tablero[1][1].color == tablero[1][5].color) {
            if (tablero[1][1].color == 1) {
                cont_az++;
            }
            else if (tablero[1][1].color == 0) {
                cont_rj++;
            }
            else {color_verde++;}
        }

    }
    if (tablero[5][1].color !=-1 ) {//un o es azul y el otro O es rojo
        if (tablero[5][1].color == tablero[5][3].color && tablero[5][1].color == tablero[5][5].color) {
            if (tablero[5][1].color == 1) {
                cont_az++;
            }
            else if (tablero[5][1].color == 0) {
                cont_rj++;
            }
            else {color_verde++;}
        }

    }
    //verticales
    if (tablero[1][1].color !=-1 ) {//un O azul y el otro O es rojo
        if (tablero[1][1].color == tablero[3][1].color && tablero[1][1].color == tablero[5][1].color) {
            if (tablero[1][1].color == 1) {
                cont_az++;
            }
            else if (tablero[1][1].color == 0) {
                cont_rj++;
            }
            else {color_verde++;}
        }
    }
    if (tablero[1][5].color !=-1 ) {//un O azul y el otro O es rojo
        if (tablero[1][5].color == tablero[3][5].color && tablero[1][5].color == tablero[5][5].color) {
            if (tablero[1][5].color == 1) {
                cont_az++;
            }
            else if (tablero[1][5].color == 0) {
                cont_rj++;
            }
            else {color_verde++;}
        }
    }
 
    //cuadrado pequeño
    //horizontales
    if (tablero[2][2].color !=-1 ) {//un o es azul y el otro O es rojo
        if (tablero[2][2].color == tablero[2][3].color && tablero[2][2].color == tablero[2][4].color) {
            if (tablero[2][2].color == 1) {
                cont_az++;
            }
            else if (tablero[2][2].color == 0) {
                cont_rj++;
            }
            else {color_verde++;}
        }

    }
    if (tablero[4][2].color !=-1 ) {//un o es azul y el otro O es rojo
        if (tablero[4][2].color == tablero[4][3].color && tablero[4][2].color== tablero[4][4].color) {
            if (tablero[4][2].color == 1) {
                cont_az++;
            }
            else if (tablero[4][2].color == 0) {
                cont_rj++;
            }
            else {color_verde++;}
        }

    }
    //verticales
    if (tablero[2][2].color !=-1 ) {//un O azul y el otro O es rojo
        if (tablero[2][2].color == tablero[3][2].color && tablero[2][2].color == tablero[4][2].color) {
            if (tablero[2][2].color == 1) {
                cont_az++;
            }
            else if (tablero[2][2].color == 0) {
                cont_rj++;
            }
            else {color_verde++;}
        }
    }
    if (tablero[2][4].color !=-1 ) {//un O azul y el otro O es rojo
        if (tablero[2][4].color == tablero[3][4].color && tablero[2][4].color == tablero[4][4].color) {
            if (tablero[2][4].color == 1) {
                cont_az++;
            }
            else if (tablero[2][4].color == 0) {
                cont_rj++;
            }
            else {color_verde++;}
        }
    }

    //extras del tablero
    //horizontales
    if (tablero[3][0].color !=-1 ) {//un o es azul y el otro O es rojo
        if (tablero[3][0].color == tablero[3][1].color && tablero[3][0].color == tablero[3][2].color) {
            if (tablero[3][0].color == 1) {
                cont_az++;
            }
            else if (tablero[3][0].color == 0) {
                cont_rj++;
            }
            else {color_verde++;}
        }

    }
    if (tablero[3][4].color !=-1 ) {//un o es azul y el otro O es rojo
        if (tablero[3][4].color == tablero[3][5].color && tablero[3][4].color==tablero[3][6].color) {
            if (tablero[3][4].color == 1) {
                cont_az++;
            }
            else if (tablero[3][4].color == 0) {
                cont_rj++;
            }
            else {color_verde++;}
        }

    }
    //verticales
    if (tablero[0][3].color !=-1 ) {//un O azul y el otro O es rojo
        if (tablero[0][3].color == tablero[1][3].color && tablero[0][3].color == tablero[2][3].color) {
            if (tablero[0][3].color == 1) {
                cont_az++;
            }
            else if (tablero[0][3].color == 0) {
                cont_rj++;
            }
            else {color_verde++;}
        }
    }
    if (tablero[4][3].color !=-1 ) {//un O azul y el otro O es rojo
        if (tablero[4][3].color == tablero[5][3].color && tablero[4][3].color == tablero[6][3].color) {
            if (tablero[4][3].color == 1) {
                cont_az++;
            }
            else if (tablero[4][3].color == 0) {
                cont_rj++;
            }
            else {color_verde++;}
        }
    }
 
    int *xaviersini = new int[3];
    xaviersini[0] = cont_az; xaviersini[1] = cont_rj; xaviersini[2]=color_verde;
    return xaviersini;
}
#endif