/*
 ====================================================================
 Materia: Laboratorio de Programacion (LPR) — 5 Ano
 Institucion: E.E.S.T. N 100 "Toy Story" — Vicente Lopez
 Archivo: src/main.cpp
 Actividad 7: Mini Juego Piedra, Papel o Tijera + Persistencia en Disco
 Profesor: Prof. Mansilla Muñoz York Elías
 Estudiante: Aramis Demaria
 ====================================================================
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Partida {
    int idPartida;
    string jugador;
    string eleccionJugador;
    string eleccionIA;
    string resultado;
};

void jugarPartida(int& contadorID);
void guardarEnDisco(const Partida& p);
void leerHistorialDisco();

int main() {
    srand(time(0));
    int contadorID = 1;
    int opcion = 0;
    cout << "=====================================================" << endl;
    cout << " LPR 2026 - ACTIVIDAD 7: PIEDRA, PAPEL O TIJERA " << endl;
    cout << " Estudiante / Grupo: Aramis Demaria " << endl;
    cout << "=====================================================" << endl;
    do {
        cout << "\n--- MENU PRINCIPAL DE JUEGO Y PERSISTENCIA ---" << endl;
        cout << "1. Jugar Partida (Piedra, Papel o Tijera)" << endl;
        cout << "2. Ver Historial de Partidas Guardadas en Disco (.txt)" << endl;
        cout << "3. Salir del Sistema" << endl;
        cout << "Ingrese una opcion (1-3): ";
        cin >> opcion;
        if (opcion == 1) jugarPartida(contadorID);
        else if (opcion == 2) leerHistorialDisco();
        else if (opcion == 3) cout << "\n[SISTEMA] Saliendo del programa... Datos resguardados en disco." << endl;
        else cout << "\n[ERROR] Opcion invalida. Reintente." << endl;
    } while (opcion != 3);
    return 0;
}

void jugarPartida(int& contadorID) {
    Partida p;
    p.idPartida = contadorID++;
    cout << "\n--- NUEVA PARTIDA #" << p.idPartida << " ---" << endl;
    cout << "Ingrese su Nombre / Nickname: ";
    cin.ignore();
    getline(cin, p.jugador);
    int opcJugador = 0;
    cout << "\nElija su jugada:\n1. Piedra\n2. Papel\n3. Tijera\nOpcion (1-3): ";
    cin >> opcJugador;
    if (opcJugador == 1) p.eleccionJugador = "Piedra";
    else if (opcJugador == 2) p.eleccionJugador = "Papel";
    else p.eleccionJugador = "Tijera";
    int opcIA = (rand() % 3) + 1;
    if (opcIA == 1) p.eleccionIA = "Piedra";
    else if (opcIA == 2) p.eleccionIA = "Papel";
    else p.eleccionIA = "Tijera";
    cout << "\n[JUGADA] " << p.jugador << " eligio: " << p.eleccionJugador << endl;
    cout << "[JUGADA] La IA eligio: " << p.eleccionIA << endl;
    if (p.eleccionJugador == p.eleccionIA) p.resultado = "Empate";
    else if ((p.eleccionJugador == "Piedra" && p.eleccionIA == "Tijera") ||
             (p.eleccionJugador == "Papel" && p.eleccionIA == "Piedra") ||
             (p.eleccionJugador == "Tijera" && p.eleccionIA == "Papel")) p.resultado = "Victoria";
    else p.resultado = "Derrota";
    cout << "=> RESULTADO: " << p.resultado << "!" << endl;
    guardarEnDisco(p);
}

void guardarEnDisco(const Partida& p) {
    ofstream archivo("src/historial_partidas.txt", ios::app);
    if (!archivo.is_open()) {
        cerr << "[ERROR] No se pudo abrir el archivo para guardar la partida." << endl;
        return;
    }
    archivo << p.idPartida << "," << p.jugador << "," << p.eleccionJugador << "," << p.eleccionIA << "," << p.resultado << endl;
    archivo.close();
    cout << "[DISCO] Partida resguardada con exito en 'historial_partidas.txt'." << endl;
}

void leerHistorialDisco() {
    ifstream archivo("src/historial_partidas.txt");
    if (!archivo.is_open()) {
        cout << "\n[AVISO] Aun no existen partidas guardadas en disco." << endl;
        return;
    }
    cout << "\n=====================================================" << endl;
    cout << " HISTORIAL DE PARTIDAS RECUPERADO DESDE DISCO " << endl;
    cout << "=====================================================" << endl;
    string idStr, jugador, elJug, elIA, resultado;
    int total = 0;
    while (getline(archivo, idStr, ',') && getline(archivo, jugador, ',') && getline(archivo, elJug, ',') && getline(archivo, elIA, ',') && getline(archivo, resultado)) {
        total++;
        cout << "Partida #" << idStr << " | Jugador: " << jugador << " | " << elJug << " vs " << elIA << " | Resultado: " << resultado << endl;
    }
    archivo.close();
    if (total == 0) cout << "[AVISO] El archivo de historial esta vacio." << endl;
    else cout << "\n[SISTEMA] Total de registros leidos desde disco: " << total << endl;
    cout << "=====================================================" << endl;
}
