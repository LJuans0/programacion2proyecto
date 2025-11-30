#ifndef SISTEMACOMBATE_H
#define SISTEMACOMBATE_H

#include "../modelos/Unidad.h"

//sistema que maneja todas las mecánicas de combate
//realizar un ataque entre dos unidades
bool realizarAtaque(Unidad& atacante, Unidad& defensor);

//calcular daño basado en estadísticas y terreno
int calcularDano(Unidad& atacante, Unidad& defensor, int bonoDefensa = 0);

//verificar si una unidad puede atacar a otra (rango, etc.)
bool puedeAtacar(const Unidad& atacante, const Unidad& defensor);

//procesar resultado del combate
void procesarResultadoCombate(Unidad& atacante, Unidad& defensor, bool exito);

#endif