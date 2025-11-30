#include "Juego.h"
#include "../interfaz/InterfazConsola.h"
#include <iostream>

using namespace std;

// Constructor - inicializa todos los componentes del juego
Juego::Juego() {
    cout << "Inicializando Rival Frontiers 2..." << endl;

    // Crear dinámicamente los componentes del juego
    mapa = new Mapa(6, 6); // Mapa de 6x6
    recursosJugador = new SistemaRecursos(18, 12, 7); // Comida, Metal, Energía inicial
    controladorJugador = new ControladorJugador(mapa, recursosJugador);
    controladorSistema = new ControladorSistema(mapa);

    turnoActual = 1;
    juegoActivo = true;

    cout << "Juego inicializado correctamente!" << endl;
}

// Destructor - libera toda la memoria asignada
Juego::~Juego() {
    // Liberar memoria de todos los componentes
    delete mapa;
    delete recursosJugador;
    delete controladorJugador;
    delete controladorSistema;

    cout << "Juego finalizado. Memoria liberada." << endl;
}

// Bucle principal del juego
void Juego::iniciar() {
    cout << "=== COMIENZA RIVAL FRONTIERS 2 ===" << endl;
    cout << "OBJETIVO: Alcanzar 60% de dominio en 12 turnos" << endl;

    // Bucle principal del juego - SOLO 12 TURNOS
    while (juegoActivo && turnoActual <= 12) {
        cout << "\n=== TURNO " << turnoActual << " ===" << endl;

        // MOSTRAR ESTADO ACTUAL DEL JUEGO
        int dominioJugador = mapa->calcularDominioJugador();
        int dominioSistema = mapa->calcularDominioSistema();

        // Mostrar panel superior con información
        InterfazConsola::mostrarPanelSuperior(turnoActual, *recursosJugador,
                                            dominioJugador, dominioSistema);

        // Mostrar el mapa
        InterfazConsola::mostrarMapa(*mapa);

        // Procesar el turno actual
        procesarTurno();

        // Verificar si el juego debe terminar
        if (verificarCondicionesVictoria()) {
            juegoActivo = false;
        } else {
            turnoActual++; // Pasar al siguiente turno
        }

        // Pausa entre turnos
        if (juegoActivo && turnoActual <= 12) {
            cout << "\nPresione Enter para continuar al siguiente turno...";
            cin.ignore();
            cin.get();
        }
    }

    // Mostrar mensaje final
    if (turnoActual > 12) {
        cout << "\n¡DERROTA POR TIEMPO! No alcanzaste el 60% de dominio en 12 turnos." << endl;
        cout << "Dominio final: " << mapa->calcularDominioJugador() << "%" << endl;
    } else {
        cout << "¡Fin del juego!" << endl;
    }
}

// Procesa un turno completo (jugador + sistema)
void Juego::procesarTurno() {
    // Fase del jugador - 2 puntos de acción
    cout << "--- Fase del Jugador ---" << endl;
    controladorJugador->ejecutarTurno(turnoActual); // Pasar turnoActual como parámetro

    // Fase del sistema (guardianes automáticos)
    cout << "--- Fase del Sistema ---" << endl;
    controladorSistema->ejecutarRutina();

    // Actualizar recursos y mantenimiento
    recursosJugador->procesarFinTurno();
}

// Verifica si se cumplen condiciones de victoria/derrota
bool Juego::verificarCondicionesVictoria() {
    int dominioJugador = mapa->calcularDominioJugador();
    int dominioSistema = mapa->calcularDominioSistema();

    // VICTORIA por dominio territorial
    if (dominioJugador >= 60) {
        cout << "\n¡VICTORIA! Has alcanzado el " << dominioJugador << "% de dominio." << endl;
        return true;
    }

    // DERROTA por dominio del sistema
    if (dominioSistema >= 60) {
        cout << "\n¡DERROTA! El sistema controla el " << dominioSistema << "% del territorio." << endl;
        return true;
    }

    // DERROTA por falta de recursos críticos
    if (recursosJugador->obtenerComida() <= 0 && recursosJugador->obtenerMetal() <= 0) {
        cout << "\n¡DERROTA! Te has quedado sin recursos." << endl;
        return true;
    }

    return false;
}

// Obtiene el turno actual
int Juego::obtenerTurnoActual() const {
    return turnoActual;
}