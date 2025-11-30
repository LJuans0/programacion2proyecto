#include "InterfazConsola.h"
#include <iostream>

using namespace std;

//mostrar el mapa en LA consola
void InterfazConsola::mostrarMapa(const Mapa& mapa) {
    mapa.mostrarMapa();
}

//mostrar panel superior con información del juego
void InterfazConsola::mostrarPanelSuperior(int turno, const SistemaRecursos& recursos,
                                         int dominioJugador, int dominioSistema) {
    cout << "==========================================" << endl;
    cout << "          RIVAL FRONTIERS 2 - TURNO " << turno << endl;
    cout << "==========================================" << endl;
    cout << "OBJETIVO: Alcanzar 60% de dominio (Turno " << turno << "/12)" << endl;
    cout << "RECURSOS: Comida=" << recursos.obtenerComida()
         << " | Metal=" << recursos.obtenerMetal()
         << " | Energia=" << recursos.obtenerEnergia() << endl;
    cout << "DOMINIO:  Jugador=" << dominioJugador << "% | Sistema=" << dominioSistema << "%" << endl;

    //mostrar alertas basadas en el estado del juego
    if (recursos.obtenerComida() < 5) {
        cout << "ALERTA: Comida critica!" << endl;
    }
    if (recursos.obtenerMetal() < 3) {
        cout << "ALERTA: Metal insuficiente!" << endl;
    }
    if (dominioSistema > dominioJugador) {
        cout << "ALERTA: El sistema tiene mayor dominio!" << endl;
    }

    //mostrar progreso para ganar
    if (dominioJugador >= 60) {
        cout << "VICTORIA ALCANZADA!" << endl;
    } else if (dominioJugador >= 50) {
        cout << "¡Cerca de la victoria! (" << 60 - dominioJugador << "% restante)" << endl;
    } else if (dominioJugador >= 40) {
        cout << "Buen progreso (" << 60 - dominioJugador << "% restante)" << endl;
    }

    cout << "==========================================" << endl;
}

//mostrar mensaje normal al jugador
void InterfazConsola::mostrarMensaje(const string& mensaje) {
    cout << "> " << mensaje << endl;
}

//mostrar mensaje de alerta? aun en desarrollo
void InterfazConsola::mostrarAlerta(const string& alerta) {
    cout << "!!! " << alerta << " !!!" << endl;
}