#ifndef CONTROLADORJUGADOR_H
#define CONTROLADORJUGADOR_H

#include "../modelos/Mapa.h"
#include "../sistemas/SistemaRecursos.h"
#include "../interfaz/InterfazConsola.h"

//controla todas las acciones del jugador que no es guardian
class ControladorJugador {
private:
    Mapa* mapa;                      // Puntero al mapa del juego
    SistemaRecursos* recursos;       // Puntero a los recursos
    int puntosAccion;                // Puntos de acción por turno (siempre 2)

public:
    //cnstructor
    ControladorJugador(Mapa* mapa, SistemaRecursos* recursos);

    //ejecuta el turno del jugador
    void ejecutarTurno(int turnoActual);

    //,étodos de acciones disponibles
    void moverUnidad();
    void construirEdificio();
    void reclutarUnidad();
    void atacarUnidad();
    void usarHabilidad();
    void verMapa();                  //nueva función para ver mapa
    void refreshPantalla(int turnoActual); //nueva función para refresh

    //mostrar menú de acciones
    void mostrarMenuAcciones() const;

    //verificar si hay acciones disponibles
    bool tieneAccionesDisponibles() const;

    //mostrar estado completo del juego
    void mostrarEstadoCompleto(int turnoActual) const;
};

#endif