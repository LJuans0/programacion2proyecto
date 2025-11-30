#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include <string>
#include "Terreno.h"
#include "Unidad.h"
#include "Edificio.h"

//representa una celda individual del mapa
struct Celda {
    Terreno* terreno;    // Puntero al terreno de esta celda
    Unidad* unidad;      // Puntero a unidad presente (nullptr si no hay)
    Edificio* edificio;  // Puntero a edificio presente (nullptr si no hay)
    std::string control; // "J1", "J2" o "NE" (neutral)
    
    Celda(Terreno* t = nullptr, Unidad* u = nullptr, Edificio* e = nullptr,
          const std::string& ctrl = "NE");
    
    bool estaOcupada() const;
    
    bool esTransitable() const;
    std::string obtenerRepresentacion() const;
};

// CLase que representa el mapa completo del juego
class Mapa {
private:
    int ancho;                      // Ancho del mapa
    int alto;                       // Alto del mapa  
    std::vector<std::vector<Celda>> celdas; // Matriz de celdas

public:
    // crear mapa con dimensiones específicas
    Mapa(int ancho, int alto);
    
    // liberar memoria
    ~Mapa();
    
    // getters
    Celda& obtenerCelda(int x, int y);
    const Celda& obtenerCelda(int x, int y) const;
    
    // scolocadores
    bool colocarUnidad(int x, int y, Unidad* unidad);
    bool colocarEdificio(int x, int y, Edificio* edificio);
    bool colocarTerreno(int x, int y, Terreno* terreno);
    
    //métodos para remover elementos
    bool removerUnidad(int x, int y);
    bool removerEdificio(int x, int y);
    
    // métodos de utilidad
    bool esCoordenadaValida(int x, int y) const;
    void mostrarMapa() const;
    int calcularDominioJugador() const;
    int calcularDominioSistema() const;
    
    //+getters
    int obtenerAncho() const;
    int obtenerAlto() const;
};

#endif