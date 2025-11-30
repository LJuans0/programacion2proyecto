#include <iostream>
#include <string>
#include "juego/Juego.h"
#include "interfaz/InterfazConsola.h"
#include "utilidades/Persistencia.h"

using namespace std;

//gunción para limpiar el buffer de entrada
void limpiarBuffer() {
    cin.clear();
}

// función para pausar y esperar Enter
void pausar() {
    cout << "Presione Enter para continuar...";
    limpiarBuffer();
    cin.get();
}

void mostrarMenuPrincipal() {
    cout << "==========================================" << endl;
    cout << "          RIVAL FRONTIERS 2" << endl;
    cout << "==========================================" << endl;
    cout << "1. Iniciar Juego" << endl;
    cout << "2. Cargar Partida" << endl;
    cout << "3. Creditos" << endl;
    cout << "4. Salir" << endl;
    cout << "==========================================" << endl;
    cout << "Seleccione una opcion: ";
}

// Función para mostrar los créditos COMPLETOS
void mostrarCreditos() {
    
    cout << "==========================================" << endl;
    cout << "              CREDITOS" << endl;
    cout << "==========================================" << endl;
    cout << "Desarrollado por:" << endl;
    cout << "- Campos Ticona, Jose Gabriel" << endl;
    cout << "- Estrella Camacho, Juan Martin" << endl;
    cout << "- Norena Paredes, Steven Daniel" << endl;
    cout << "- Briceno Villegas, Leonardo Fabian" << endl;
    cout << "==========================================" << endl;
    cout << "Released on 29/11/25" << endl;
    cout << "==========================================" << endl;
    pausar();
}

//gunción para iniciar nuevo juego
void iniciarNuevoJuego() {
    
    cout << "Iniciando nuevo juego..." << endl;
    cout << "Presione Enter para comenzar...";
    limpiarBuffer();
    cin.get();

    Juego juego;
    juego.iniciar();
}

//función para cargar partida existente AUN EN DESARROLLO
void cargarPartida() {
    
    string nombreArchivo = "partida_guardada.txt";

    if (!Persistencia::existePartida(nombreArchivo)) {
        cout << "No hay partidas guardadas." << endl;
        pausar();
        return;
    }

    cout << "Cargando partida..." << endl;
    Juego juego;
    if (Persistencia::cargarPartida(juego, nombreArchivo)) {
        juego.iniciar();
    } else {
        cout << "Error al cargar la partida." << endl;
        pausar();
    }
}

//función principal del programa
int main() {
    int opcion = 0;
    bool salir = false;

    //bcle principal del menú
    while (!salir) {
        
        mostrarMenuPrincipal();

        //leer opción
        cin >> opcion;

        //procesar la opción seleccionada
        switch (opcion) {
            case 1:
                iniciarNuevoJuego();
                break;

            case 2:
                cargarPartida();
                break;

            case 3:
                mostrarCreditos();
                break;

            case 4:
                cout << "\n¡Gracias por jugar Rival Frontiers 2!" << endl;
                salir = true;
                break;

            default:
                cout << "\nOpcion no valida. Intente nuevamente." << endl;
                pausar();
                break;
        }

        //limpiar buffer después de cada operación para evitar errores
        limpiarBuffer();
    }

    return 0;
}