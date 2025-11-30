#include "Persistencia.h"
#include <fstream>
#include <iostream>

using namespace std;
//ESTE Y EL HEADER SON PLACEHOLDERSSSSSSSSS
bool Persistencia::guardarPartida(const Juego& juego, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    
    if (!archivo.is_open()) {
        cout << "Error: No se pudo crear archivo de guardado." << endl;
        return false;
    }
    
    // Guardar datos básicos del juego
    archivo << "RIVAL_FRONTIERS_2_SAVE" << endl;
    archivo << juego.obtenerTurnoActual() << endl;
    
    //aquí se guardarían más datos del estado del juego
    
    archivo.close();
    cout << "Partida guardada en: " << nombreArchivo << endl;
    return true;
}

bool Persistencia::cargarPartida(Juego& juego, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir archivo de guardado." << endl;
        return false;
    }
    
    string linea;
    getline(archivo, linea);
    
    if (linea != "RIVAL_FRONTIERS_2_SAVE") {
        cout << "Error: Archivo de guardado no valido." << endl;
        archivo.close();
        return false;
    }
    
    // aquí se cargarían los datos del estado del juego
    
    archivo.close();
    cout << "Partida cargada desde: " << nombreArchivo << endl;
    return true;
}

// berificar si existe archivo de partida
bool Persistencia::existePartida(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    bool existe = archivo.is_open();
    archivo.close();
    return existe;
}