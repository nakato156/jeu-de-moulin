#ifndef CODIGO_MENU
#define CODIGO_MENU
#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <string.h>
#include <Windows.h>
using namespace std;

void mostrarReglas()
{
    ifstream archivo;
    archivo.open("C:/Users/bruno/OneDrive/Escritorio/UPC/1er semestre/programación 1/Trabajo final/reglas.txt");
    string linea;
    if(archivo.is_open()){
        while(getline(archivo, linea)) {
            cout << linea << endl;
        }
        archivo.close();
    } else exit(EXIT_FAILURE);
}

void dibujarLogo()
{
    int logo[25][45] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,2,2,2,0,0,0,0,0,0,0,0,0,2,2,2,0,0},
{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,2,3,3,3,2,0,2,2,2,2,2,0,2,3,3,3,2,0},
{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,2,3,3,3,2,2,0,0,0,0,0,2,2,3,3,3,2,0},
{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,2,3,3,2,0,0,0,0,0,0,0,0,0,2,3,3,2,0},
{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,2,3,2,0,0,0,0,0,0,0,0,0,0,0,2,3,2,0},
{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0},
{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,2,0,0,2,2,0,0,0,0,0,2,2,0,0,2,0,0},
{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,4,0,4,0,0,2,0,0,2,3,2,0,0,0,0,0,2,3,2,0,0,2,0},
{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,4,0,4,0,0,2,0,0,2,0,2,0,0,0,0,0,2,0,2,0,0,2,0},
{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,4,4,4,0,0,2,0,4,2,2,2,0,0,2,0,0,2,2,2,4,0,2,0},
{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,4,0,0,0,2,0,4,4,4,4,0,2,0,2,0,4,4,4,4,0,2,0},
{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,2,0,0},
{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,2,2,0,0,0},
{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,2,2,2,0,0,0,0,0,0,0,2,2,2,0,0,0},
{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,2,3,3,3,2,0,2,0,2,0,2,3,3,3,2,0,0},
{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,2,3,3,3,2,0,0,2,0,0,2,3,3,3,2,0,0},
{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,2,3,3,3,2,0,0,0,0,0,2,3,3,3,2,0,0},
{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,2,2,2,0,2,2,2,2,2,0,2,2,2,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 45; j++) {
            if (logo[i][j] == 0) {
                SetConsoleTextAttribute(hConsole, 15);
                cout << char(219);
            }
            else if (logo[i][j] == 1) {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 1); //azul
                cout << char(219);
            }
            else if (logo[i][j] == 2) {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 0); //negro
                cout << char(219);
            }
            else if (logo[i][j] == 3) {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 0); // negro
                cout << char(219);
            }
            else if (logo[i][j] == 4) {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 12); //rosado
                cout << char(219);
            }
            else if (logo[i][j] == 5) {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 2); //verde
                cout << char(219);
            }
        }
        cout << endl;
    }
}

int mostrarMenu()
{
    cout << "BIENVENIDO A NUESTRO JUEGO DEL MOLINO" << endl; cout << endl;
    dibujarLogo();
    cout << endl;
    cout << "EQUIPO LOS CARINIOSITOS DE C++" << endl;
    cout << endl;
    cout << "Integrantes del equipo: " << endl; cout << endl;
    cout << "Borasino Velasquez, Christian Aaron \tU202218075" << endl;
    cout << "Eguia Castillo,     Joaquin Mauricio \tU202213539" << endl;
    cout << "Medina Agnini,      Bruno Alessandro \tU202216661" << endl;
    cout << "Arteaga Bonilla,    Erick Germail \tU202217802" << endl;
    cout << endl;
    cout << "============================================================================================================" << endl;
    cout << endl;
    cout << "1) Reglas del juego. " << endl;
    cout << "2) Jugar. " << endl;
    cout << "3) Fin." << endl;
    int opcion;
    do {
        cout << "Ingrese su opcion (1-3): " << endl;
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
    return codigoOnline;
}

int MenuOnline()
{
    int opcionOnline;
    cout << "1)Unirse a un juego en curso: " << endl;
    cout << "2)Crear un nuevo juego: " << endl;
    do {
        cout << "Ingrese su eleccion (1-2): " << endl;
        cin >> opcionOnline;
    } while (opcionOnline < 1 || opcionOnline > 2);
    return opcionOnline;
}

void MenuOffline(void (*PlayWithBot)(), void (*PlayWithFriend)())
{
    cout << "Elige como quieres jugar: " << endl;
    cout << "1) Jugador contra bot." << endl;
    cout << "2) Dos jugadores. " << endl;
    int opcionOffline;
    do {
        cout << "Ingrese su eleccion (1-2): " << endl;
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
        cout << "Elija su modo de juego: " << endl;
        cout << "1) Juego online." << endl;
        cout << "2) Juego offline. " << endl;
        cout << "3) Salir. " << endl;
        cout << "Ingrese su opcion (1-3): " << endl;
        cin >> opcion;
    } while (opcion < 1 || opcion > 3);
    if(opcion == 3) exit(EXIT_SUCCESS);
    return opcion;
}

// Pantalla de fin
int generarNumWin() {
    int variableini;
    variableini = rand() % 2;
    return variableini;
}
int generarNumloss() {
    int loss;
    loss = rand() % 2;
    return loss;
}
#endif