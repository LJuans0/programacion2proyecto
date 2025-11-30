#include "Unidad.h"
#include <iostream>

using namespace std;

//UNIDAD!!!!!!!!!!!!

// constructor
Unidad::Unidad(const string& nombre, const string& codigo, int vida, 
               int ataque, int defensa, int movimiento, int costoComida)
    : nombre(nombre), codigo(codigo), vida(vida), vidaMaxima(vida),
      ataque(ataque), defensa(defensa), rangoMovimiento(movimiento), 
      costoComida(costoComida) {}

//método básico de ataque
void Unidad::atacar(Unidad& objetivo) {
    cout << codigo << " ataca a " << objetivo.codigo << endl;
    int dano = ataque - objetivo.defensa / 2;
    if (dano < 1) dano = 1; // Mínimo 1 de daño
    objetivo.recibirDano(dano);
}

// método base para habilidad especial
void Unidad::usarHabilidadEspecial() {
    cout << codigo << " usa habilidad especial: " << nombre << endl;
}

// recibir daño en combate
void Unidad::recibirDano(int dano) {
    vida -= dano;
    if (vida < 0) vida = 0;
    cout << codigo << " recibe " << dano << " de dano. Vida: " << vida << endl;
}

// curar unidad
void Unidad::curar(int curacion) {
    vida += curacion;
    if (vida > vidaMaxima) vida = vidaMaxima;
    cout << codigo << " curada. Vida: " << vida << endl;
}

//getters
string Unidad::obtenerNombre() const { return nombre; }
string Unidad::obtenerCodigo() const { return codigo; }
int Unidad::obtenerVida() const { return vida; }
bool Unidad::estaViva() const { return vida > 0; }

//sobrecarga del operador > para comparar poder
bool Unidad::operator>(const Unidad& otra) const {
    return (ataque + defensa) > (otra.ataque + otra.defensa);
}

// DERIVADAS

// soldado unidad básica de combate cuerpo a cuerpo
Soldado::Soldado(const string& prefijo)
    : Unidad("Soldado", prefijo + "S", 10, 6, 4, 2, 1) {}

void Soldado::usarHabilidadEspecial() {
    cout << codigo << " usa Ataque Doble! (aumenta el ataque)" << endl;
    ataque += 2; // Bono temporal
}

// arquero unidad de ataque a distancia
Arquero::Arquero(const string& prefijo)
    : Unidad("Arquero", prefijo + "A", 8, 7, 3, 2, 1) {}

void Arquero::usarHabilidadEspecial() {
    cout << codigo << " usa precision! (tiene mas rango de movimiento)" << endl;
    rangoMovimiento++; // Bono de movimiento
}

// caballero= unidad rápida y fuerte asi como como un tanque xd
Caballero::Caballero(const string& prefijo)
    : Unidad("Caballero", prefijo + "C", 12, 8, 5, 3, 2) {}

void Caballero::usarHabilidadEspecial() {
    cout << codigo << " usa super defensa! (aumenta MUCHISIMO su defensa)" << endl;
    defensa += 6; // Bono temporal
}

// mago= unidad con full vida
Mago::Mago(const string& prefijo)
    : Unidad("Mago", prefijo + "M", 6, 9, 2, 1, 2) {}

void Mago::usarHabilidadEspecial() {
    cout << codigo << " usa cura completa!" << endl;
    curar(15000);
}

// ingeniero - unidad de soporte
Ingeniero::Ingeniero(const string& prefijo)
    : Unidad("Ingeniero", prefijo + "I", 5, 3, 3, 2, 1) {}

void Ingeniero::usarHabilidadEspecial() {
    cout << codigo << " usa regeneracion (aumenta su vida maxima)!" << endl;
    vidaMaxima+=10;
}