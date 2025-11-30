#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
#include <vector>

//gunciones de utilidad general para el juego
namespace Utilidades {
    // dividir string por delimitador
    std::vector<std::string> dividirString(const std::string& texto, char delimitador);
    
    //convertir a mayúsculas
    std::string aMayusculas(const std::string& texto);
    
    //verificar si string es número
    bool esNumero(const std::string& texto);
    
    //generar número aleatorio en rango
    int aleatorioEnRango(int min, int max);
}

#endif