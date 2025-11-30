#ifndef TERRENO_H
#define TERRENO_H

#include <string>

// clase base para todos los tipos de terreno
class Terreno {
protected:
    std::string nombre;      // Nombre del terreno
    std::string codigo;      // Código abreviado (LL, BO, MO, etc.)
    int costoMovimientoBase; // Costo base de movimiento

public:
    Terreno(const std::string& nombre, const std::string& codigo, int costo);
    
    virtual ~Terreno() {}
    
    virtual int calcularCostoMovimiento() const;
    virtual int calcularBonoDefensa() const;
    
    //getters
    std::string obtenerNombre() const;
    std::string obtenerCodigo() const;
    
    //sobrecarga del operador << para imprimir terreno
    friend std::ostream& operator<<(std::ostream& os, const Terreno& terreno);
};

// clases derivadas para cada tipo específico de terreno
class Llanura : public Terreno {
public:
    Llanura();
    int calcularBonoDefensa() const override;
};

class Bosque : public Terreno {
public:
    Bosque();
    int calcularBonoDefensa() const override;
};

class Montana : public Terreno {
public:
    Montana();
    int calcularCostoMovimiento() const override;
    int calcularBonoDefensa() const override;
};

class Agua : public Terreno {
public:
    Agua();
    int calcularCostoMovimiento() const override;
    int calcularBonoDefensa() const override;
};

class Pantano : public Terreno {
public:
    Pantano();
    int calcularCostoMovimiento() const override;
    int calcularBonoDefensa() const override;
};

#endif