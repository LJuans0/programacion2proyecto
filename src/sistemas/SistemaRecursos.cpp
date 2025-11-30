#include "SistemaRecursos.h"
#include <iostream>

using namespace std;

SistemaRecursos::SistemaRecursos(int comidaInicial, int metalInicial, int energiaInicial)
    : comida(comidaInicial), metal(metalInicial), energia(energiaInicial) {}

//agregar recursos
void SistemaRecursos::agregarComida(int cantidad) {
    comida += cantidad;
    cout << "+" << cantidad << " comida. Total: " << comida << endl;
}

void SistemaRecursos::agregarMetal(int cantidad) {
    metal += cantidad;
    cout << "+" << cantidad << " metal. Total: " << metal << endl;
}

void SistemaRecursos::agregarEnergia(int cantidad) {
    energia += cantidad;
    cout << "+" << cantidad << " energia. Total: " << energia << endl;
}

//consumir recursos (retorna verdadero si fue exitoso)
bool SistemaRecursos::consumirComida(int cantidad) {
    if (comida >= cantidad) {
        comida -= cantidad;
        cout << "-" << cantidad << " comida. Restante: " << comida << endl;
        return true;
    }
    cout << "Comida insuficiente! Se necesitan: " << cantidad << endl;
    return false;
}

bool SistemaRecursos::consumirMetal(int cantidad) {
    if (metal >= cantidad) {
        metal -= cantidad;
        cout << "-" << cantidad << " metal. Restante: " << metal << endl;
        return true;
    }
    cout << "Metal insuficiente! Se necesitan: " << cantidad << endl;
    return false;
}

bool SistemaRecursos::consumirEnergia(int cantidad) {
    if (energia >= cantidad) {
        energia -= cantidad;
        cout << "-" << cantidad << " energia. Restante: " << energia << endl;
        return true;
    }
    cout << "Energia insuficiente! Se necesitan: " << cantidad << endl;
    return false;
}

//orocesar fin de turno (producción y mantenimiento)
void SistemaRecursos::procesarFinTurno() {
    cout << "\n--- PROCESANDO FIN DE TURNO ---" << endl;
    
    // producción base por turno
    agregarComida(2);  // Producción base de comida
    agregarMetal(1);   // Producción base de metal
    agregarEnergia(1); // Producción base de energía
    
    // costos de mantenimiento (simulado)
    int costoMantenimiento = 2; // Por unidades existentes
    if (!consumirComida(costoMantenimiento)) {
        cout << "ALERTA: No hay suficiente comida para mantenimiento!" << endl;
    }
    
    mostrarEstado();
}

//getters
int SistemaRecursos::obtenerComida() const { return comida; }
int SistemaRecursos::obtenerMetal() const { return metal; }
int SistemaRecursos::obtenerEnergia() const { return energia; }

//sobrecarga del operador += para sumar recursos
SistemaRecursos& SistemaRecursos::operator+=(const SistemaRecursos& otros) {
    comida += otros.comida;
    metal += otros.metal;
    energia += otros.energia;
    return *this;
}

//mostrar estado actual de recursos
void SistemaRecursos::mostrarEstado() const {
    cout << "\n=== RECURSOS ===" << endl;
    cout << "Comida:  " << comida << endl;
    cout << "Metal:   " << metal << endl;
    cout << "Energia: " << energia << endl;
    cout << "================" << endl;
}