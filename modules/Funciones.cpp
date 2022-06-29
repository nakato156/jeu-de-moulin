#include <iostream>
#include <string>
#include <time.h>
#include "Bot.cpp"
#include "Menu.cpp"
#include "Tablero.cpp"

using namespace std;

void pantallaFinal(Jugador winner, Jugador losser);

string generarCodigoStr()//codigo de 6 digitos para el codigo online
{
    srand(time(NULL));
    string codigo;
    for (int i = 0; i < 6; i++) {

        int digitoUni = rand() % 2;//random de 0 a 1

        if (digitoUni == 0) {

            char digitoC = 'A' + rand() % 28;
            codigo.push_back(digitoC);//char a un string
        }
        else {

            int digito = rand() % 10;//random de 0 a 1
            codigo.push_back(digito + '0');//para transformarlo a un string
        }
    }
    return codigo;
}

bool InMolino(Tablero &tablero, int row, int col){//devuelve verdader si la posicion de la ficha a verificar forma un molino
    int color = tablero[row][col].getColor();

    if ( tablero.checkDiag(row, col, color) ) return true;
    else if ( tablero.checkRow(row, col, color) ) return true;
    else return tablero.checkCol(row, col, color);
}

bool CheckAllMolinos(Tablero& tablero) {//verifica todos los molinos
    for (int i = 1; i < 8; i++) {//recorre todo el tablero
        for (int j = 1; j < 8; j++) {//recorre el tablero
            int _j = userXYToTableroXY(i - 1, j);//para convertir a las posiciones reales del tablero
            if (_j == -1) continue;
            if (!(InMolino(tablero, i - 1, _j))) return false;//si la ficha no forma un molino retorna falso
        }
    }
    return true;
}

template <typename T>//plantillas: como tener un nuevo tipo de dato, ese t es un nuevo tipo de dato
bool eliminarFicha(Tablero &tablero, int row, int col, T &oponente){//oponente puede ser cualquier tipo de dato, esta funcion se usa para el jugador y para el bot
    //y para no esta copiando pues se le pone la plantilla
    col = userXYToTableroXY(row, col);//posiciones del tablero
    if (col == -1) return false;//error
    row--;//posiciones en tablero de fila
    if ( tablero[row][col].getColor() != oponente->color) {//color de la ficha diferente al del oponente
        cout << "La ficha le pertenece " << endl;//no se puede eliminar una ficha de nosotros
        return false;
    }
    if (CheckAllMolinos(tablero)) {//verifica si todos son molinos
        tablero[row][col].reset();//entonces reseteamos los valores de la ficha
        return true;
    }
    else if ( InMolino(tablero, row, col) ){//si l aficha forma algun molino
        cout << "La ficha forma un molino, no la puede eliminar" << endl; 
        return false;
    }
    tablero[row][col].reset();//sino se cumple ninguno se resetea la ficha 
    return true;
}
template <typename T>
void WhenMolino (Tablero &tablero, T &oponente){//pedimos la ficha a eliminar
    while(1){
        int eliminar_fila, eliminar_col;
        cout << "fila de la ficha a eliminar: ";
        cin >> eliminar_fila;
        cout << "columna de la ficha a eliminar: ";
        cin >> eliminar_col;
        bool eliminado = eliminarFicha(tablero, eliminar_fila, eliminar_col, oponente);//si devuelve true se acaba
        if(eliminado) return;//y si es false se dice que lo vuelva a intentar
        cout << "Vuelva a intentarlo." << endl;
    }
}

void Game(Bot player1, Jugador player2){
    Tablero tablero;

    int isMove, row, col, **puntos = nullptr;
    char direccion;//direccion en la que se movera
    bool active_move = false;//para ver si nos toca una ficha

    tablero.Show(1);

    for(int i = 0; ; i++){//no tiene tope ya que no sabemos cuando terminara el juego
        if(i == 18) {
            cout << "movida de fichas" << endl;
            active_move = true;
        }
        //player1 es el bot y el 2 es el jugador
        if ( player1.fichas == 2 || player2.fichas == 2) break;//cantidad de fichas que tiene cada uno

        ahogamiento(tablero);

        if(i%2 == 0){//saber a quien le toca
            cout << "Turno de " << player1.nombre << endl;//turno de bot
            player1.PlayGame(tablero, active_move);
        }else{//turno del jugador
            cout << "Turno de " << player2.nombre << endl;
            player2.PlayGame(tablero, active_move);
        }

        if(i > 1) {//cuando sea la tercera vez que se repita el for significa que ya puede haber molinos
            if(puntos != nullptr){
                int **n_puntos = puntoenhori(tablero);
                bool haymolino=false;
                //filas
                for (int i = 0; i < 8; i++)
                {
                    if (puntos[0][i] != n_puntos[0][i]) {
                        if (n_puntos[0][i] == 1) {
                            haymolino = true;
                            break;
                        }
                    }
                }
                //columnas
                for (int i = 0; i < 8; i++)
                {
                    if (puntos[1][i] != n_puntos[1][i]) {
                        if (n_puntos[1][i] == 1) {
                            haymolino = true;
                            break;
                        }
                    }
                }
                //diagonales
                for (int i = 0; i < 4; i++)
                {
                    if (puntos[2][i] != n_puntos[2][i]) {
                        if (n_puntos[2][i] == 1) {
                            haymolino = true;
                            break;
                        }
                    }
                }
                if(haymolino){
                    puntos = n_puntos;
                    string nombre_player = i % 2 ? player2.nombre : player1.nombre;
                    cout << "molino para " << nombre_player << endl;
                    if ( i % 2 ) { 
                        Bot *player = &player1;
                        WhenMolino(tablero, player);
                        player1.fichas--;
                    }
                    else player1.Molino(tablero, player2);
                    puntos = puntoenhori(tablero);
                }
            }else puntos = puntoenhori(tablero);
        }
        tablero.Show(1);
    }
    if ( player1.fichas == 2 ) pantallaFinal(player2, player1);//se hace llamado a la pantalla final porque el for se rompera
    else pantallaFinal(player1, player2);
}

void Game(Jugador player1, Jugador player2){
    Tablero tablero;
    Jugador *player, *oponente;

    int isMove, row, col, **puntos = nullptr;
    char direccion;
    bool active_move = false;

    tablero.Show(1);

    for(int i = 0; ; i++){
        if(i%2 == 0){//si es 0 el player sera el player1 y el oponente sera el player 2
            player = &player1;
            oponente = &player2;
        }else{
            player = &player2;
            oponente = &player1;
        }
        if ( (*player).fichas == 2 || (*oponente).fichas == 2)//se accede al espacio de memoria, se pone parentesis porque queremos especificar quien es el puntero
        {
            break;//se rompe porque se termina el juego
        }
        cout << "fichas: " << (*player).fichas << endl;//escribimos las fichas
        cout << "fichas oponente: " << (*oponente).fichas << endl;//fichas del oponente
        
        if(i == 18) {//cuando haya 18 fichas en el tablero 
            cout << "movida de fichas" << endl;
            active_move = true;
        }
        cout << "Turno de " << (*player).nombre << endl;
        (*player).PlayGame(tablero, active_move);

        tablero.Show(1);

        if(i > 1) {//para que en los 3 primeros turnos no haga la verificacion del molino
            if(puntos != nullptr){//nullptr =nullpointer, manera recomendada de iniciar un puntero
                int **n_puntos = puntoenhori(tablero);
                bool haymolino=false;
                //filas
                for (int i = 0; i < 8; i++)
                {
                    if (puntos[0][i] != n_puntos[0][i]) {
                        if (n_puntos[0][i] == 1) {
                            haymolino = true;
                            break;
                        }
                    }
                }
                //columnas
                for (int i = 0; i < 8; i++)
                {
                    if (puntos[1][i] != n_puntos[1][i]) {
                        if (n_puntos[1][i] == 1) {
                            haymolino = true;
                            break;
                        }
                    }
                }
                //diagonales
                for (int i = 0; i < 4; i++)
                {
                    if (puntos[2][i] != n_puntos[2][i]) {
                        if (n_puntos[2][i] == 1) {
                            haymolino = true;
                            break;
                        }
                    }
                }
                if(haymolino){
                    cout << "molino para " << (*player).nombre << endl;
                    WhenMolino(tablero, oponente);
                    (*oponente).delFicha();
                    int **n_puntos = puntoenhori(tablero);
                    delete puntos;
                    puntos = n_puntos;
                }
                else {
                    puntos = puntoenhori(tablero);
                }
            }else puntos = puntoenhori(tablero);
            tablero.Show(1);
        }
    }
    if ( (*player).fichas == 2 ) pantallaFinal((*oponente), (*player));
    else pantallaFinal(*player, *oponente);

}

void pantallaFinal(Jugador winner, Jugador losser) {
    int variableini = generarNumWin();
    int loss = generarNumloss();
    cout<<"===============FELICIDADES GANASTE=============== " << endl;
    if (variableini==0)
    {
        cout << winner.nombre <<" " << "bien jugado" << endl;
    }
    else {
        cout << winner.nombre <<" "<< "enhorabuena" << endl;
    }
    cout << "Estadisticas Ganador---------------"<<endl;
    cout << "Numero de fichas: "<< winner.fichas<<endl;
    cout << "Numero de movimientos: "<<winner.movimientos<<endl;
    cout << "=============== PERDEDOR =============== " << endl;
    if (loss == 0) {
        cout << losser.nombre << " " << "mas suerte para la proxima :c" << endl;
    }
    else {
        cout << losser.nombre << " " << "buen intento, pero no fue suficiente :(" << endl;
    }
    cout << "Estadisticas Perdedor---------------"<<endl;
    cout << "Numero de fichas: " << losser.fichas<<endl;
    cout << "Numero de movimientos: " << losser.movimientos<<endl;
}