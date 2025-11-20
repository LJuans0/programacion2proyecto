//
// Created by johns on 19/11/2025.
//

#ifndef PROGRAMACION2PROYECTO_CLASES_H
#define PROGRAMACION2PROYECTO_CLASES_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


class Coordenada
{
    public:
    int fila;
    int columna;
    Coordenada(int filai = 0, int columnai = 0) : fila(filai), columna(columnai) {}
};
class Recursos
{
    public:
    int comida = 0;
    int metal = 0;
    int energia = 0;
};
class Faccion
{
    public:
    string nombre;        // J1, J2, Ne
    Recursos recursos;    // propia economia
    int dominio = 0;      // porcentaje o contador

    Faccion(const string& n = "") : nombre(n) {}
};

class Evento
{
    public:
    string tipo;        // "clima", "refuerzo", "alerta", etc
    Coordenada pos;     // donde afecta
    int turno;          // turno en que ocurre

    Evento(const string& t = "", Coordenada p = {}, int k = 0): tipo(t), pos(p), turno(k) {}
};

class Edificio
{
    private:
    string prefijo; // J1, J2, Ne
    public:
    virtual void efecto_turno(Faccion& f) = 0;
    virtual void reaccion_evento(const Evento& e) = 0;
    virtual string codigo() const = 0;
    virtual ~Edificio() = default;
};

class Granja : public Edificio
{
    public:
    void efecto_turno(Faccion& f) override;
    void reaccion_evento(const Evento& e) override;
    string codigo() const override;
};

class Cuartel : public Edificio
{
    public:
    void efecto_turno(Faccion& f) override;
    void reaccion_evento(const Evento& e) override;
    string codigo() const override;
};

class Torre : public Edificio
{
    public:
    void efecto_turno(Faccion& f) override;
    void reaccion_evento(const Evento& e) override;
    string codigo() const override;
};

class Forja : public Edificio
{
    public:
    void efecto_turno(Faccion& f) override;
    void reaccion_evento(const Evento& e) override;
    string codigo() const override;
};


class Controlador
{
    public:
    virtual void resolver_fase(Contexto& ctx) = 0;
    virtual void aplicar_rutina(const Evento& e) = 0;
    virtual ~Controlador() = default;
};

class Tablero {
private:
    vector<vector<Celda>> mapa;
public:
    Tablero(int filas, int cols);
    Celda& at(int i, int j);
    void imprimir() const;
};

class Contexto
{
public:
    Tablero tablero;
    Faccion faccion_j1;
    Faccion faccion_j2;
    Controlador* jugador = nullptr;
    Controlador* sistema = nullptr;
    int turno = 1;

    Contexto(int filas, int cols)
        : tablero(filas, cols),
          faccion_j1("J1"),
          faccion_j2("J2") {}
};

class Jugador : public Controlador
{
    public:
    void resolver_fase(Contexto& ctx) override;
    void aplicar_rutina(const Evento& e) override;
};

class Sistema : public Controlador
{
    public:
    void resolver_fase(Contexto& ctx) override;
    void aplicar_rutina(const Evento& e) override;
};

class Neutral : public Controlador
{
    public:
    void resolver_fase(Contexto& ctx) override;
    void aplicar_rutina(const Evento& e) override;
};

class Unidad
{
    private:
    string prefijo; // J1, J2, Ne
    public:
    virtual bool mover(const Coordenada& destino, Contexto& ctx) = 0;
    virtual void atacar(Unidad& objetivo, Contexto& ctx) = 0;
    virtual void habilidad_especial(Contexto& ctx) = 0;
    virtual string codigo() const = 0;
    virtual ~Unidad() = default;
};

class Soldado : public Unidad
{
    public:
    bool mover(const Coordenada& d, Contexto& ctx) override;
    void atacar(Unidad& o, Contexto& ctx) override;
    void habilidad_especial(Contexto& ctx) override;
    string codigo() const override;
};

class Arquero : public Unidad
{
    public:
    bool mover(const Coordenada& d, Contexto& ctx) override;
    void atacar(Unidad& o, Contexto& ctx) override;
    void habilidad_especial(Contexto& ctx) override;
    string codigo() const override;
};

class Caballero : public Unidad
{
    public:
    bool mover(const Coordenada& d, Contexto& ctx) override;
    void atacar(Unidad& o, Contexto& ctx) override;
    void habilidad_especial(Contexto& ctx) override;
    string codigo() const override;
};

class Mago : public Unidad
{
    public:
    bool mover(const Coordenada& d, Contexto& ctx) override;
    void atacar(Unidad& o, Contexto& ctx) override;
    void habilidad_especial(Contexto& ctx) override;
    string codigo() const override;
};

class Ingeniero : public Unidad
{
    public:
    bool mover(const Coordenada& d, Contexto& ctx) override;
    void atacar(Unidad& o, Contexto& ctx) override;
    void habilidad_especial(Contexto& ctx) override;
    string codigo() const override;
};

class Terreno {
    public:
    virtual int costo_movimiento(const Unidad& u) const = 0;
    virtual int bono_defensa(const Unidad& u) const = 0;
    virtual string codigo() const = 0;
    virtual ~Terreno() = default;
};

class Llanura : public Terreno
{
    public:
    int costo_movimiento(const Unidad& u) const override;
    int bono_defensa(const Unidad& u) const override;
    string codigo() const override;
};

class Bosque : public Terreno
{
    public:
    int costo_movimiento(const Unidad& u) const override;
    int bono_defensa(const Unidad& u) const override;
    string codigo() const override;
};

class Montana : public Terreno
{
    public:
    int costo_movimiento(const Unidad& u) const override;
    int bono_defensa(const Unidad& u) const override;
    string codigo() const override;
};

class Agua : public Terreno
{
    public:
    int costo_movimiento(const Unidad& u) const override;
    int bono_defensa(const Unidad& u) const override;
    string codigo() const override;
};

class Celda
{
    public:
    Terreno* terreno = nullptr;
    Unidad* unidad = nullptr;
    Edificio* edificio = nullptr;
};


#endif //PROGRAMACION2PROYECTO_CLASES_H