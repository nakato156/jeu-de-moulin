#ifndef CODIGO_TABLERO
#define CODIGO_TABLERO
#include "Ficha.cpp"

void printEsp(int cant, int code){//imprimir especial, cant= cantidad de veces que se imprime, code representacion de un caracter en numeros 
    for(int i=0; i<cant; i++) cout << char(code);//transforma un numero a un caracter
}

int userXYToTableroXY(int row, int col){ 
    if ( (row < 1 || row > 7) || ( col < 1 || col > 7) ) return -1;//comprueba que los valores esten dentro del rango
    else if ( (row == 1 || row == 7) && col < 4) col = (col-1)*3; //verifica si la fila es igual a uno o igual a 7 y que las columnas sean < 4 
    //entonces se realiza la operacion
    else if ( (row == 2 || row == 6) && col < 4) col = (col*2)-1;
    else if ( (row == 3 || row == 5) && col < 4) col++;
    else if ( row == 4 ) col = col<4 ? col-1 : col;//sintaxis operador terneario: condicion ? valor_verdadero : valor_falso 
    else return -1;//seguramente hubo un error
    col = col < 7 ? col : -1; //si col <7 su valor no cambia de lo contrario es -1, si es mayor a ocurrido error
    return col;
}

struct Tablero {
    Ficha **tablero;//arreglo bidimensional de fichas
    Tablero(){//constructor
        tablero = new Ficha*[7];//reservamos espacio para un arreglo de 7 fichas
        for(int i = 0; i<7; i++) {//se recorre el tablero
            tablero[i] = new Ficha[7];//reservamos memoria para 7 fichas
            for(int c=0; c<7; c++){ 
                Ficha ficha; //se crea una nueva ficha
                tablero[i][c] = ficha;//asignamos la ficha a una posicion en el tablero
            }
        }
    }
    ~Tablero(){//destructor: se ejecuta cuando se termina de llamar a la funcion
        for(int i = 0; i<7; i++) delete[] tablero[i];//se recorre el tablero y liberamos la memoria de filas
        delete[] tablero;//se libera memoria de la matriz tablero
        tablero = nullptr;//es recomendado asignar el valor nullptr a la memoria que ya no se utiliza
    }
    Tablero(const Tablero &) = delete;//sobrecarga de operadores & (le decimos al compilador para que elimine esta funcion)
    //se ejecuta al momento la estructura  a una variable
    void Show(int clear=0){//imprime el tablero
        if (clear) system("cls");
        cout << char(201); printEsp(23, 205); cout << char(187) << endl;
        for(int i = 0; i<7; i++){
            printf("%c  ", 186);//printf funcion de C, si le pasas "%c" es para imprimir un caracter
            if (i==0 || i==6){                                      
                tablero[i][0].imprimir();
                printEsp(8, 205); tablero[i][3].imprimir();//tablero[i][3].imprimir-imprime manualmente cada ficha
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
    void SetFicha(int row, int col, int _color){//accede a esa posicion y a esa ficha que esta en esa posicion se le establece el color
        tablero[row][col].setColor(_color);
    }
    bool Iam(int row, int col, int color){//comprueba que la ficha es de un color determinado
        return tablero[row][col].getColor() == color;
    }
    bool isEmptyCell (int x, int y){//comprueba si la casilla esta vacia
        return tablero[x][y].getColor() == -1;
    }
    int moveFicha(int act_row, int act_col, int row, int col, char dir, int color, int ult_coordenadas[2]){
        if (dir == 'a') col--;
        else if (dir == 'd') col++;
        
        col = userXYToTableroXY(row, col);
        row --;

        int salto, ws = 3, _row = row;
        if (dir == 'w' || dir == 's'){
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
        if ( ult_coordenadas[0] == row && ult_coordenadas[1] == col ){//compara si la posicion es igual a la ultima posicion movida
            cout << "no puede repetir la jugada" << endl; return false;
        }
        else if (col < 0 || row < 0 || col>7 || row>7) {//si sale del tablero no se puede mover
            cout << "la ficha no se puede mover en esa direccion " << endl;
            return false;
        }

        if ( isEmptyCell(row, col) ){//si la casilla esta vacia se mueve la ficha
            tablero[act_row][act_col].reset();
            tablero[row][col].setColor(color);
            return true;
        }
        return false;
    }
    bool checkRow(int row, int col, int _color){
        if(row < 0 || row > 6) return false;
        if(row == 0 || row == 6) {
            return ( tablero[row][0].getColor() == _color && tablero[row][3].getColor() == _color && tablero[row][6].getColor() == _color );
        }else if(row == 1 || row == 5){
            return ( tablero[row][1].getColor() == _color && tablero[row][3].getColor() == _color && tablero[row][5].getColor() == _color );
        }else if(row == 2 || row == 4){
            return ( tablero[row][2].getColor() == _color && tablero[row][3].getColor() == _color && tablero[row][4].getColor() == _color );
        }else if( col < 3 ){
            return ( tablero[row][0].getColor() == _color && tablero[row][1].getColor() == _color && tablero[row][2].getColor() == _color );
        } else if( col >= 4 ) {
            return ( tablero[row][4].getColor() == _color && tablero[row][5].getColor() == _color && tablero[row][6].getColor() == _color );
        }
    }
    bool checkCol(int row, int col, int _color){
        if ( col == 0 || col == 6 ) {
            return ( tablero[0][col].getColor() == _color && tablero[3][col].getColor() == _color && tablero[6][col].getColor() == _color );
        }else if ( col == 1 || col == 5 ) {
            return ( tablero[1][col].getColor() == _color && tablero[3][col].getColor() == _color && tablero[5][col].getColor() == _color );
        }else if ( col == 2 || col == 4 ) {
            return ( tablero[2][col].getColor() == _color && tablero[3][col].getColor() == _color && tablero[4][col].getColor() == _color );
        }else if ( row < 3 ) {
            return ( tablero[0][3].getColor() == _color && tablero[1][3].getColor() == _color && tablero[2][3].getColor() == _color ); 
        }else if ( row >= 4 ) {
            return ( tablero[4][3].getColor() == _color && tablero[5][3].getColor() == _color && tablero[6][3].getColor() == _color );
        }
    }
    bool checkDiag ( int row, int col, int _color ) {
        if( col < 3 ) {
            if ( row < 3 ){
                return ( tablero[0][0].getColor() == _color && tablero[1][1].getColor() == _color && tablero  && tablero[2][2].getColor() == _color );
            }
            return ( tablero[6][0].getColor() == _color && tablero[5][1].getColor() == _color && tablero  && tablero[4][2].getColor() == _color );
        }else {
            if ( row < 3 ){
                return ( tablero[0][6].getColor() == _color && tablero[1][5].getColor() == _color && tablero  && tablero[2][4].getColor() == _color );
            }
            return ( tablero[6][6].getColor() == _color && tablero[5][5].getColor() == _color && tablero  && tablero[4][4].getColor() == _color );
        }
    }
    Ficha *operator [] (unsigned int index){ return tablero[index]; }
};
int* generarCeros( int num) {
    int* ceros = new int[num];
    for (int i = 0; i < num; i++)
    {
        ceros[i] = 0;
    }
    return ceros;
}
int** puntoenhori(Tablero& tablero) {
    int* filas = generarCeros(8);
    int* columnas = generarCeros(8);
    int* diagonales = generarCeros(4);
    //cuadrado grande
    //horizontales
    if (tablero[0][0].color !=-1 ) { //un o es azul y el otro O es rojo
        if (tablero[0][0].color == tablero[0][3].color && tablero[0][0].color == tablero[0][6].color) {//0 vacio y 1 ocupado / molinop en esa fila
            filas[0] = 1;
        }
        else
        {
            filas[0]=0;
        }
    }
    if (tablero[6][0].color !=-1 ) {//un o es azul y el otro O es rojo
        if (tablero[6][0].color == tablero[6][3].color && tablero[6][0].color == tablero[6][6].color) {
            filas[7] = 1;
        }
        else
        {
            filas[7] = 0;
        }
    }
    //verticales
    if (tablero[0][0].color !=-1 ) {//un O azul y el otro O es rojo
        if (tablero[0][0].color == tablero[3][0].color && tablero[0][0].color == tablero[6][0].color) {
            columnas[0] = 1;
        }
        else
        {
            columnas[0] = 0;
        }
    }
    if (tablero[0][6].color !=-1 ) {//un O azul y el otro O es rojo
        if (tablero[0][6].color == tablero[3][6].color && tablero[0][6].color == tablero[6][6].color) {
            columnas[7] = 1;
        }
        else
        {
            columnas[7] = 0;
        }
    }
 
    //cuadrado de en medio
    //horizontales
    if (tablero[1][1].color !=-1 ) {//un o es azul y el otro O es rojo
        if (tablero[1][1].color == tablero[1][3].color && tablero[1][1].color == tablero[1][5].color) {
            filas[1] = 1;
        }
        else {
            filas[1] = 0;
        }

    }
    if (tablero[5][1].color !=-1 ) {//un o es azul y el otro O es rojo
        if (tablero[5][1].color == tablero[5][3].color && tablero[5][1].color == tablero[5][5].color) {
            filas[6] = 1;
        }
        else {
            filas[6] = 0;
        }

    }
    //verticales
    if (tablero[1][1].color !=-1 ) {//un O azul y el otro O es rojo
        if (tablero[1][1].color == tablero[3][1].color && tablero[1][1].color == tablero[5][1].color) {
            columnas[1] = 1;
        }
        else {
            columnas[1] = 0;
        }
    }
    if (tablero[1][5].color !=-1 ) {//un O azul y el otro O es rojo
        if (tablero[1][5].color == tablero[3][5].color && tablero[1][5].color == tablero[5][5].color) {
            columnas[6] = 1;
        }
        else
        {
            columnas[6] = 0;
        }
    }
 
    //cuadrado peque??o
    //horizontales
    if (tablero[2][2].color !=-1 ) {//un o es azul y el otro O es rojo
        if (tablero[2][2].color == tablero[2][3].color && tablero[2][2].color == tablero[2][4].color) {
            filas[2] = 1;
        }
        else
        {
            filas[2] = 0;
        }
    }
    if (tablero[4][2].color !=-1 ) {//un o es azul y el otro O es rojo
        if (tablero[4][2].color == tablero[4][3].color && tablero[4][2].color== tablero[4][4].color) {
            filas[5] = 1;
        }
        else {
            filas[5] = 0;
        }
    }
    //verticales
    if (tablero[2][2].color !=-1 ) {//un O azul y el otro O es rojo
        if (tablero[2][2].color == tablero[3][2].color && tablero[2][2].color == tablero[4][2].color) {
            columnas[2] = 1;
        }
        else {
            columnas[2] = 0;
        }
        
    }
    if (tablero[2][4].color !=-1 ) {//un O azul y el otro O es rojo
        if (tablero[2][4].color == tablero[3][4].color && tablero[2][4].color == tablero[4][4].color) {
            columnas[5] = 1;
        }
        else {
            columnas[5] = 0;
        }
    }

    //extras del tablero
    //horizontales
    if (tablero[3][0].color !=-1 ) {//un o es azul y el otro O es rojo
        if (tablero[3][0].color == tablero[3][1].color && tablero[3][0].color == tablero[3][2].color) {
            filas[3] = 1;
        }
        else
        {
            filas[3]=0;
        }

    }
    if (tablero[3][4].color !=-1 ) {//un o es azul y el otro O es rojo
        if (tablero[3][4].color == tablero[3][5].color && tablero[3][4].color==tablero[3][6].color) {
            filas[4] = 1;
        }
        else {
            filas[4] = 0;
        }
    }
    //verticales
    if (tablero[0][3].color !=-1 ) {//un O azul y el otro O es rojo
        if (tablero[0][3].color == tablero[1][3].color && tablero[0][3].color == tablero[2][3].color) {
            columnas[3] = 1;
        }
        else {
            columnas[3] = 0;
        }
    }
    if (tablero[4][3].color !=-1 ) {//un O azul y el otro O es rojo
        if (tablero[4][3].color == tablero[5][3].color && tablero[4][3].color == tablero[6][3].color) {
            columnas[4] = 1;
        }
        else
        {
            columnas[4] = 0;
        }
    }
    //diagonales aaribas
    if (tablero[0][0].color != -1) {//un O azul y el otro O es rojo
        if (tablero[1][1].color == tablero[0][0].color && tablero[0][0].color == tablero[2][2].color) {
            diagonales[0] = 1;
        }
        else
        {
            diagonales[0] = 0;
        }
    }
    if (tablero[0][6].color != -1) {//un O azul y el otro O es rojo
        if (tablero[1][5].color == tablero[0][6].color && tablero[0][6].color == tablero[2][4].color) {
            diagonales[1] = 1;
        }
        else
        {
            diagonales[1] = 0;
        }
    }
    //diagonales abajos
    if (tablero[6][0].color != -1) {//un O azul y el otro O es rojo
        if (tablero[5][1].color == tablero[6][0].color && tablero[6][0].color == tablero[4][2].color) {
            diagonales[2] = 1;
        }
        else
        {
            diagonales[2] = 0;
        }
    }
    if (tablero[6][6].color != -1) {//un O azul y el otro O es rojo
        if (tablero[5][5].color == tablero[6][6].color && tablero[6][6].color == tablero[4][4].color) {
            diagonales[3] = 1;
        }
        else
        {
            diagonales[3] = 0;
        }
    }

    int **xaviersini = new int*[3];
    xaviersini[0] = new int[8];
    xaviersini[0] = filas;
    xaviersini [1]= new int[8];
    xaviersini[1] = columnas;
    xaviersini[2] = new int[4];
    xaviersini[2] = diagonales;
    return xaviersini;
}
#endif