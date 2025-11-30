#ifndef CONTROLADORSISTEMA_H
#define CONTROLADORSISTEMA_H

#include "../modelos/Mapa.h"

//controla las acciones automáticas de los guardianes
class ControladorSistema {
private:
    Mapa* mapa; //puntero al mapa del juego

public:
    //constructor
    ControladorSistema(Mapa* mapa);
    
    //ejecuta las rutinas automáticas del sistema
    void ejecutarRutina();
    
    //métodos de rutinas específicas
    void rutinaDefensiva();
    void rutinaOfensiva();
    void rutinaExpansion();
    
    // encontrar posición para nueva unidad
    bool encontrarPosicionLibre(int& x, int& y) const;
};

#endif