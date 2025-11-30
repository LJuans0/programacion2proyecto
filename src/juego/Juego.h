#ifndef JUEGO_H
#define JUEGO_H

#include <string>
#include <vector>
#include "../modelos/Mapa.h"
#include "../sistemas/SistemaRecursos.h"
#include "../controladores/ControladorJugador.h"
#include "../controladores/ControladorSistema.h"

//Clase principal que controla CASI todo el juego
class Juego {
private:
    Mapa* mapa;                          // puntero al mapa del juego
    SistemaRecursos* recursosJugador;    // puntero a recursos del jugador
    ControladorJugador* controladorJugador; // puntero al controlador del jugador
    ControladorSistema* controladorSistema; //puntero al controlador del sistema
    int turnoActual;                     //trno actual del juego
    bool juegoActivo;                    // estado del juego (activo/inactivo), cosas de menus

public:
    Juego();
    ~Juego();
    void iniciar();
    void procesarTurno();
    bool verificarCondicionesVictoria();
    int obtenerTurnoActual() const;
};

#endif