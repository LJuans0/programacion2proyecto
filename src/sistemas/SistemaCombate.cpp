#include "SistemaCombate.h"
#include <iostream>

using namespace std;
//ESTAs funciones NOMAS LA USAN LAS UNIDADES AMIGAS, YA SE CODEO LODE LOS ENEMIGOSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
//inicializar generador de números aleatorios
bool inicializado = false;

//realizar un ataque entre dos unidades
bool realizarAtaque(Unidad& atacante, Unidad& defensor) {
    if (!inicializado) {
        srand(time(0));
        inicializado = true;
    }
    
    cout << "\n=== COMBATE ===" << endl;
    cout << atacante.obtenerCodigo() << " vs " << defensor.obtenerCodigo() << endl;
    
    //verificar si puede atacar
    if (!puedeAtacar(atacante, defensor)) {
        cout << "No se puede realizar el ataque!" << endl;
        return false;
    }
    
    //calcular probabilidad de éxito
    int probabilidadExito = 80;
    int roll = rand() % 100;
    
    bool exito = roll < probabilidadExito;
    
    if (exito) {
        int dano = calcularDano(atacante, defensor);
        defensor.recibirDano(dano);
        cout << "Ataque exitoso! " << dano << " de dano." << endl;
    } else {
        cout << "Ataque fallado!" << endl;
    }
    
    procesarResultadoCombate(atacante, defensor, exito);
    return exito;
}

// calcular daño del ataque
int calcularDano(Unidad& atacante, Unidad& defensor, int bonoDefensa) {
    int ataqueBase = atacante.obtenerVida();
    int defensaBase = defensor.obtenerVida();
    
    int dano = ataqueBase - (defensaBase / 2) - bonoDefensa;
    
    //Asegurar daño mínimo y máximo
    if (dano < 1) dano = 1;
    if (dano > 10) dano = 10;
    
    //Bariación aleatoria +/- 1
    dano += (rand() % 3) - 1;
    if (dano < 1) dano = 1;
    
    return dano;
}

//berificar condiciones para atacar
bool puedeAtacar(const Unidad& atacante, const Unidad& defensor) {
    //verificar que ambas unidades estén vivas
    if (!atacante.estaViva() || !defensor.estaViva()) {
        cout << "Una de las unidades no esta viva!" << endl;
        return false;
    }
    
    //verificar que no sean del mismo bando
    string codigoAtacante = atacante.obtenerCodigo();
    string codigoDefensor = defensor.obtenerCodigo();
    
    if (codigoAtacante.substr(0, 2) == codigoDefensor.substr(0, 2)) {
        cout << "No se puede atacar a unidades aliadas!" << endl;
        return false;
    }
    
    return true;
}

void procesarResultadoCombate(Unidad& atacante, Unidad& defensor, bool exito) {
    if (exito) {
        // atacante gana experiencia o recursos
        cout << atacante.obtenerCodigo() << " gana experiencia del combate." << endl;
        
        // berificar si defensor fue eliminado
        if (!defensor.estaViva()) {
            cout << defensor.obtenerCodigo() << " ha sido eliminado!" << endl;
        }
    } else {
        // defensor puede contraatacar (simplificado)
        cout << defensor.obtenerCodigo() << " resiste el ataque." << endl;
    }
    
    cout << "=== FIN COMBATE ===" << endl;
}