#include "Reportes.h"
#include <iostream>

using namespace std;
//TODO ESTO ES UN PLACEHOLDER------------------------------------------------
// generar reporte completo del turno
void Reportes::generarReporteTurno(int turno, const Mapa& mapa, const SistemaRecursos& recursos) {
    cout << "\n=== REPORTE TURNO " << turno << " ===" << endl;
    
    generarReporteRecursos(recursos);
    generarReporteDominio(mapa);
    
    cout << "=== FIN REPORTE ===" << endl;
}

//generar reporte de batalla (por ahora nada :'v)
void Reportes::generarReporteBatalla() {
    cout << "\n--- REPORTE DE BATALLA ---" << endl;
    cout << "Combates registrados este turno: 0" << endl;
    cout << "Unidades perdidas: 0" << endl;
    cout << "Unidades enemigas eliminadas: 0" << endl;
    cout << "---------------------------" << endl;
}

// generar reporte detallado de recursos
void Reportes::generarReporteRecursos(const SistemaRecursos& recursos) {
    cout << "\n--- RECURSOS ---" << endl;
    cout << "Comida:  " << recursos.obtenerComida() << endl;
    cout << "Metal:   " << recursos.obtenerMetal() << endl;
    cout << "Energia: " << recursos.obtenerEnergia() << endl;
    
    // análisis de recursos
    if (recursos.obtenerComida() < 3) {
        cout << "ALERTA: Nivel de comida critico!" << endl;
    }
    if (recursos.obtenerMetal() < 2) {
        cout << "ALERTA: Metal insuficiente para construcciones!" << endl;
    }
    if (recursos.obtenerEnergia() < 1) {
        cout << "ALERTA: Sin energia para habilidades!" << endl;
    }
}

//generar reporte de dominio territorial
void Reportes::generarReporteDominio(const Mapa& mapa) {
    int dominioJugador = mapa.calcularDominioJugador();
    int dominioSistema = mapa.calcularDominioSistema();
    int dominioNeutral = 100 - dominioJugador - dominioSistema;
    
    cout << "\n--- DOMINIO TERRITORIAL ---" << endl;
    cout << "Jugador:  " << dominioJugador << "%" << endl;
    cout << "Sistema:  " << dominioSistema << "%" << endl;
    cout << "Neutral:  " << dominioNeutral << "%" << endl;
    
    //análisis de dominio
    if (dominioJugador >= 60) {
        cout << "OBJETIVO CUMPLIDO: Dominio mayor al 60%!" << endl;
    } else if (dominioSistema >= 60) {
        cout << "ALERTA CRITICA: El sistema controla mas del 60%!" << endl;
    } else {
        cout << "Objetivo: Alcanzar 60% de dominio (" << 60 - dominioJugador << "% restante)" << endl;
    }
}