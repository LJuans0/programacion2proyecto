#include "Terreno.h"
#include <iostream>

using namespace std;

//tERRENO------------------------

//constructor
Terreno::Terreno(const string& nombre, const string& codigo, int costo) 
    : nombre(nombre), codigo(codigo), costoMovimientoBase(costo) {}

//calcula costo de movimiento
int Terreno::calcularCostoMovimiento() const {
    return costoMovimientoBase;
}

//calcula bono de defensa
int Terreno::calcularBonoDefensa() const {
    return 0; // Por defecto no hay bono
}

//getters!!!!!!!!
string Terreno::obtenerNombre() const { return nombre; }
string Terreno::obtenerCodigo() const { return codigo; }

//sobrecarga del operador << para imprimir terreno
ostream& operator<<(ostream& os, const Terreno& terreno) {
    os << terreno.codigo;
    return os;
}

//DERIVADAS INSANAAAAAAAAAS

// ;lanura terreno básico sin modificadores
Llanura::Llanura() : Terreno("Llanura", "LL", 1) {}
int Llanura::calcularBonoDefensa() const { return 0; }

// bosqueproporciona bono defensivo
Bosque::Bosque() : Terreno("Bosque", "BO", 2) {}
int Bosque::calcularBonoDefensa() const { return 2; }

// montañ= alto costo de movimiento pero gran defensa
Montana::Montana() : Terreno("Montaña", "MO", 3) {}
int Montana::calcularCostoMovimiento() const { return 3; }
int Montana::calcularBonoDefensa() const { return 5; }

//agua= movimiento restringido
Agua::Agua() : Terreno("Agua", "AG", 4) {}
int Agua::calcularCostoMovimiento() const { return 4; }
int Agua::calcularBonoDefensa() const { return 1; }

// pantano= movimiento lento, defensa reducida
Pantano::Pantano() : Terreno("Pantano", "PA", 3) {}
int Pantano::calcularCostoMovimiento() const { return 3; }
int Pantano::calcularBonoDefensa() const { return -1; }