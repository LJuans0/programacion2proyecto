#ifndef REPORTES_H
#define REPORTES_H

#include "../modelos/Mapa.h"
#include "../sistemas/SistemaRecursos.h"
//TODO ESTO ES UN PLACEHOLDERRRRRRRRR----------------
// Genera reportes detallados del estado del juego
class Reportes {
public:
    // Generar reporte de turno
    static void generarReporteTurno(int turno, const Mapa& mapa, const SistemaRecursos& recursos);
    
    // Generar reporte de batalla
    static void generarReporteBatalla();
    
    // Generar reporte de recursos
    static void generarReporteRecursos(const SistemaRecursos& recursos);
    
    // Generar reporte de dominio territorial
    static void generarReporteDominio(const Mapa& mapa);
};

#endif