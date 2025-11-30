#ifndef EDIFICIO_H
#define EDIFICIO_H

#include <string>

// clase base para todos los edificios del juego
class Edificio {
protected:
    std::string nombre;      // nombre del edificio
    std::string codigo;      // código J1Cu, J2Gr, etc......................
    int vida;               // puntos de vida actuales
    int vidaMaxima;         // puntos de vida máximos
    int costoMetal;         // costo en metal para construir
    int costoEnergia;       // costo en energía para construir

public:
    Edificio(const std::string& nombre, const std::string& codigo, int vida,
             int costoMetal, int costoEnergia);
    virtual ~Edificio() {}
    virtual void efectoPorTurno();
    virtual void reaccionarEvento(const std::string& evento);
    
    void recibirDano(int dano);
    void reparar(int reparacion);
    
    //getters
    std::string obtenerNombre() const;
    std::string obtenerCodigo() const;
    int obtenerVida() const;
    bool estaDestruido() const;
    
    //sobrecarga de operadores
    bool operator==(const Edificio& otro) const;
};

//clases derivadas para cada tipo específico de edificio
class Cuartel : public Edificio {
public:
    Cuartel(const std::string& prefijo);
    void efectoPorTurno() override;
};

class Granja : public Edificio {
public:
    Granja(const std::string& prefijo);
    void efectoPorTurno() override;
};

class Torre : public Edificio {
public:
    Torre(const std::string& prefijo);
    void efectoPorTurno() override;
};

class Forja : public Edificio {
public:
    Forja(const std::string& prefijo);
    void efectoPorTurno() override;
};

#endif