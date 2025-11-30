#ifndef INTERFAZCONSOLA_H
#define INTERFAZCONSOLA_H

#include <string>
#include "../modelos/Mapa.h"
#include "../sistemas/SistemaRecursos.h"

//maneja toda la visualización en consola
class InterfazConsola {
public:
    //mostrar el mapa en consola
    static void mostrarMapa(const Mapa& mapa);
    
    //mostrar panel superior con información de la partida
    static void mostrarPanelSuperior(int turno, const SistemaRecursos& recursos, 
                                   int dominioJugador, int dominioSistema);
    
    //mostrar mensajes al jugador
    static void mostrarMensaje(const std::string& mensaje);
    static void mostrarAlerta(const std::string& alerta);
    
    //lmpiar pantalla
    static void limpiarPantalla();
    
    // esperar entrada del usuario
    static void esperarEntrada();
};

#endif