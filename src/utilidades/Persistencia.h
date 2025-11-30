#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include <string>
#include "../juego/Juego.h"
//ESTE Y EL .cpp  SON PLACEHOLDERSSSSSSSSS

// sistema para guardar y cargar partidas
class Persistencia {
public:
    static bool guardarPartida(const Juego& juego, const std::string& nombreArchivo);
    
    static bool cargarPartida(Juego& juego, const std::string& nombreArchivo);
    
    static bool existePartida(const std::string& nombreArchivo);
};

#endif