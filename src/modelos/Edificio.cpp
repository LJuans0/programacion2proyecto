#include "Edificio.h"
#include <iostream>

using namespace std;

//CLASE EDIFICIO

// Constructor
Edificio::Edificio(const string& nombre, const string& codigo, int vida, 
                   int costoMetal, int costoEnergia)
    : nombre(nombre), codigo(codigo), vida(vida), vidaMaxima(vida),
      costoMetal(costoMetal), costoEnergia(costoEnergia) {}

//efecto que se aplica cada turno
void Edificio::efectoPorTurno() {
    cout << codigo << " produce recursos o efectos..." << endl;
}

// reaccionar a eventos del juego
void Edificio::reaccionarEvento(const string& evento) {
    cout << codigo << " reacciona al evento: " << evento << endl;
}

// recibir daño por ataques
void Edificio::recibirDano(int dano) {
    vida -= dano;
    if (vida < 0) vida = 0;
    cout << codigo << " recibe " << dano << " de dano. Vida: " << vida << endl;
}

// reparar edificio
void Edificio::reparar(int reparacion) {
    vida += reparacion;
    if (vida > vidaMaxima) vida = vidaMaxima;
    cout << codigo << " reparado. Vida: " << vida << endl;
}

// getters
string Edificio::obtenerNombre() const { return nombre; }
string Edificio::obtenerCodigo() const { return codigo; }
int Edificio::obtenerVida() const { return vida; }
bool Edificio::estaDestruido() const { return vida <= 0; }

// sobrecarga del operador ==
bool Edificio::operator==(const Edificio& otro) const {
    return codigo == otro.codigo;
}

//DERIVADASSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS

// CUARTEL
Cuartel::Cuartel(const string& prefijo)
    : Edificio("Cuartel", prefijo + "Cu", 20, 3, 1) {}

void Cuartel::efectoPorTurno() {
    cout << codigo << " permite reclutar unidades este turno" << endl;
}

// granja que produce comida cada turno
Granja::Granja(const string& prefijo)
    : Edificio("Granja", prefijo + "Gr", 15, 1, 1) {}

void Granja::efectoPorTurno() {
    cout << codigo << " produce +2 de comida" << endl;
}

// torre - proporciona defensa y visión
Torre::Torre(const string& prefijo)
    : Edificio("Torre", prefijo + "To", 25, 2, 1) {}

void Torre::efectoPorTurno() {
    cout << codigo << " proporciona +1 de energia y vision extendida" << endl;
}

// forja - produce metal y mejoras
Forja::Forja(const string& prefijo)
    : Edificio("Forja", prefijo + "Fo", 18, 2, 2) {}

void Forja::efectoPorTurno() {
    cout << codigo << " produce +1 de metal y permite mejoras" << endl;
}