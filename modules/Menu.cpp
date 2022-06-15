#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <string.h>

using namespace std;

void mostrarReglas()
{
    ifstream archivo;
    archivo.open("reglas.txt");
    string linea;
    if(archivo.is_open()){
        while(getline(archivo, linea)) {
            cout << linea << endl;
        }
        archivo.close();
    } else exit(EXIT_FAILURE);
}

int mostrarMenu()
{
    cout << "\tBienvenido al Juego del Molino" << endl;
    cout << "\t============================================================================================================" << endl;
    cout << "\t1) Reglas del juego. " << endl;
    cout << "\t2) Jugar. " << endl;
    cout << "\t3) Fin." << endl;
    int opcion;
    do {
        cout << "\tIngrese su opcion (1-3): " << endl;
        cin >> opcion;
    } while (opcion < 1 || opcion > 3);
    if(opcion == 3) exit(EXIT_SUCCESS);
    return opcion;
}

string leerCodigoOnline()
{
    string codigoOnline;
    do {
        cout << "Ingrese su codigo de 6 digitos: " << endl;
        cin >> codigoOnline;
        if (codigoOnline.size() != 6) {
            cout << "Ingrese un codigo correcto." << endl;
        }
    } while (codigoOnline.size() != 6);
    // cout << "aca va la parte online post codigo" << endl;
    return codigoOnline;
}

int MenuOnline()
{
    int opcionOnline;
    cout << "\t1)Unirse a un juego en curso: " << endl;
    cout << "\t2)Crear un nuevo juego: " << endl;
    do {
        cout << "\tIngrese su eleccion (1-2): " << endl;
        cin >> opcionOnline;
    } while (opcionOnline < 1 || opcionOnline > 2);
    return opcionOnline;
}

void MenuOffline(void (*PlayWithBot)(), void (*PlayWithFriend)())
{
    cout << "\tElige como quieres jugar: " << endl;
    cout << "\t1) Jugador contra bot." << endl;
    cout << "\t2) Dos jugadores. " << endl;
    int opcionOffline;
    do {
        cout << "\tIngrese su eleccion (1-2): " << endl;
        cin >> opcionOffline;
    } while (opcionOffline < 1 || opcionOffline > 2);
    if(opcionOffline == 1){
        PlayWithBot();
    }else {
        PlayWithFriend();
    }
}

int MenuModo()
{
    int opcion;
    do {
        cout << "\tElija su modo de juego: " << endl;
        cout << "\t1) Juego online." << endl;
        cout << "\t2) Juego offline. " << endl;
        cout << "\t3) Salir. " << endl;
        cout << "\tIngrese su opcion (1-3): " << endl;
        cin >> opcion;
    } while (opcion < 1 || opcion > 3);
    if(opcion == 3) exit(EXIT_SUCCESS);
    return opcion;
}
