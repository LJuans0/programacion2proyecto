#ifndef UNIDAD_H
#define UNIDAD_H

#include <string>

// clase base para todas las unidades del juego
class Unidad {
protected:
    std::string nombre;          // Nombre de la unidad
    std::string codigo;          // Código (J1S, J2A, etc.)
    int vida;                   // Puntos de vida actuales
    int vidaMaxima;             // Puntos de vida máximos
    int ataque;                 // Poder de ataque
    int defensa;                // Poder de defensa
    int rangoMovimiento;        // Casillas que puede moverse
    int costoComida;            // Costo de mantenimiento en comida

public:
    Unidad(const std::string& nombre, const std::string& codigo, int vida,
           int ataque, int defensa, int movimiento, int costoComida);

    virtual ~Unidad() {}

    virtual void atacar(Unidad& objetivo);
    virtual void usarHabilidadEspecial();

    void recibirDano(int dano);
    void curar(int curacion);

    // fetters
    std::string obtenerNombre() const;
    std::string obtenerCodigo() const;
    int obtenerVida() const;
    bool estaViva() const;

    // sobrecarga de operadores
    bool operator>(const Unidad& otra) const; // Comparar poder
};

//DERIVADASSS

class Soldado : public Unidad {
public:
    Soldado(const std::string& prefijo); // J1 o J2
    void usarHabilidadEspecial() override;
};

class Arquero : public Unidad {
public:
    Arquero(const std::string& prefijo); // J1 o J2
    void usarHabilidadEspecial() override;
};

class Caballero : public Unidad {
public:
    Caballero(const std::string& prefijo); // J1 o J2
    void usarHabilidadEspecial() override;
};

class Mago : public Unidad {
public:
    Mago(const std::string& prefijo); // J1 o J2
    void usarHabilidadEspecial() override;
};

class Ingeniero : public Unidad {
public:
    Ingeniero(const std::string& prefijo); // J1 o J2
    void usarHabilidadEspecial() override;
};

#endif