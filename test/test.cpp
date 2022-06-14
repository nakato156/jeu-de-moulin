#include "../modules/Tablero.cpp"
#include "../modules/Cache.cpp"

int main(){
    Tablero tablero = Tablero();
    CacheGame<Tablero> game;

    tablero.Show();

    for(int i = 0; i<5; i++){
        tablero[i][1].color = 1;
        game.add(tablero);
    }
    
    for(int i=0; i<5; i++){
        game.cache[i].Show();
        cout << endl << endl;
    }
}
/*#include <iostream>
#include<conio.h>
#include <string.h>
using namespace std;

void mostrarMenu()
{
    cout << "\tBienvenido al Juego del Molino" << endl;
    cout << "\t============================================================================================================" << endl;
    cout << "\t1) Reglas del juego: " << endl;
    cout << "\t2) Crear nuevo juego: " << endl;
    cout << "\t3) Fin." << endl;
}

void mostrarMenuModo()
{
    cout << "\tElija su modo de juego: " << endl;
    cout << "\t1) Juego online" << endl;
    cout << "\t2) Juego offline: " << endl;
}

void mostrarMenuOnline()
{
    cout << "\t1)Unirse a un juego en curso: " << endl;
    cout << "\t2)Crear un nuevo juego: " << endl;
}

void mostarMenuOffline()
{
    cout << "\tElige como quieres jugar: " << endl;
    cout << "\t1) Jugador contra bot." << endl;
    cout << "\t2) Dos jugadores. " << endl;
}

int leerOpcion()
{
    int opcion;
    do {
        cout << "\tIngrese su opcion (1-3): " << endl;
        cin >> opcion;
    } while (opcion < 1 || opcion > 3);
    return opcion;
}

int leerOpcionModoJuego(int opcion)
{
    int opcionModo;
    mostrarMenuModo();
    do {
        cout << "\tIngrese su eleccion (1-2): " << endl;
        cin >> opcionModo;
    } while (opcionModo < 1 || opcionModo > 2);
    return opcionModo;
}

int leerOpcionOnline(int opcionModo)
{
    int opcionOnline = 0;
    if (opcionModo == 1)
    {
        mostrarMenuOnline();
        do {
            cout << "\tIngrese su eleccion (1-2): " << endl;
            cin >> opcionOnline;
        } while (opcionOnline < 1 || opcionOnline > 2);
    }
    return opcionOnline;
}

string leerCodigoOnline(int opcionOnline)
{
    string codigoOnline;
    if (opcionOnline == 1) {
        do {
            cout << "Ingrese su codigo de 6 digitos: " << endl;
            cin >> codigoOnline;
            if (codigoOnline.size() != 6) {
                cout << "Ingrese un codigo correcto." << endl;
            }
        } while (codigoOnline.size() != 6);
    }
    cout << "aca va la parte online post codigo" << endl;
    return codigoOnline;
}

void nuevoOnline(int opcionOnline)
{
    if (opcionOnline == 2)
    {
        cout << "Creando nuevo juego..." << endl;
    }
}

int leerOpcionOffline(int opcionModo)
{
    int opcionOffline = 0;
    if (opcionModo == 2) {
        mostarMenuOffline();
        do {
            cout << "\tIngrese su eleccion (1-2): " << endl;
            cin >> opcionOffline;
        } while (opcionOffline < 1 || opcionOffline>2);
    }
    return opcionOffline;

}
void juegoOffline1Jugador(int opcionOffline)
{
    if (opcionOffline == 1)
    {
        cout << "aca va la parte de jugador vs bot" << endl;
    }
}

void juegoOffline_2Jugadores(int opcionOffline)
{
    string jugador1;
    string jugador2;
    if (opcionOffline == 2)
    {
        cout << "Ingrese su nombre jugador 1: " << endl;
        cin >> jugador1;
        cout << "Ingrese su nombre jugador 2: " << endl;
        cin >> jugador2;
    }
}

void procesoModoJuego(int opcion)
{
    int modoJuego = leerOpcionModoJuego(opcion);
    int opcionOnline = leerOpcionOnline(modoJuego);
    string codigoOnline = leerCodigoOnline(opcionOnline);
    nuevoOnline(opcionOnline);
    int opcionOffline = leerOpcionOffline(modoJuego);
    juegoOffline1Jugador(opcionOffline);
    juegoOffline_2Jugadores(opcionOffline);

}

void procesoReglas()
{
    cout << "\t============================================================================================================" << endl;
    cout << "\t-Este juego consiste en lograr hacer la mayor cantidad de 3 en raya que puedas con tus fichas." << endl;
    cout << "\t-Las reglas son las siguientes:" << endl;
    cout << "\t-El juego tiene 3 fases." << endl;
    cout << "\t-La primera fase es la colocacion: " << endl;
    cout << "\t-Cada jugador empezara con 9 fichas respectivamente." << endl;
    cout << "\t-Cada jugador se turnara para ir poniendo una pieza en cada punto del tablero." << endl;
    cout << "\t-Si un jugador logra hacer 3 en raya, podra elegir que ficha del rival desea eliminar." << endl;
    cout << "\t-Cuando todas las fichas disponibles esten colocadas, empieza la fase 2." << endl;
    cout << "\t-Esta fase consiste en mover tus fichas." << endl;
    cout << "\t-Podras moverlas a puntos adyacentes de tu ubicacion actual mientras no este ocupada por otra ficha." << endl;
    cout << "\t-Cuando a un jugador solo le queden 3 fichas, podra moverlas tanto horizontal como verticalmente como desee." << endl;
    cout << "\t-Es decir, puede ir de punta a punta mientras no haya una ficha en ese punto." << endl;
    cout << "\t-El juego acaba en 2 oportunidades: " << endl;
    cout << "\t-Si al rival solo le quedan dos fichas." << endl;
    cout << "\t-Si el rival no puede hacer ningun movimiento al estar encerrado." << endl;
}

int main()
{
    int opcion;
    do {
        mostrarMenu();
        opcion = leerOpcion();

        switch (opcion) {

        case 1: {

            cout << "\tReglas del juego: " << endl;
            procesoReglas();
        }break;

        case 2: {

            cout << "\tModos de juego: " << endl;
            cout << "\t============================================================================================================" << endl;
            procesoModoJuego(opcion);
        }break;

        }
        system("pause");

    } while (opcion != 3);

    return 0;
}/*
