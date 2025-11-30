#include "ControladorJugador.h"
#include "../sistemas/SistemaCombate.h"
#include "../interfaz/InterfazConsola.h"
#include <iostream>

using namespace std;

//constructor del ControladorJugador
ControladorJugador::ControladorJugador(Mapa* mapa, SistemaRecursos* recursos)
    : mapa(mapa), recursos(recursos), puntosAccion(2) {}

//función para limpiar buffer, aun verde
void limpiarBufferInput() {
    cin.clear();
}

//ejecutar turno completo del jugador
void ControladorJugador::ejecutarTurno(int turnoActual) {
    cout << "Tienes " << puntosAccion << " puntos de accion." << endl;

    int accionesRealizadas = 0;

    //bucle de acciones por turno
    while (puntosAccion > 0 && accionesRealizadas < 2) {
        cout << endl; //espacio antes del menú

        mostrarMenuAcciones();

        int opcion;
        cout << "Seleccione accion (" << puntosAccion << " puntos restantes): ";

        //leer opción de forma segura
        if (!(cin >> opcion)) {
            cout << "Error: Ingrese un numero valido." << endl;
            limpiarBufferInput();
            continue;
        }

        //procesar la opción seleccionada
        switch (opcion) {
            case 1:
                limpiarBufferInput();
                moverUnidad();
                break;
            case 2:
                limpiarBufferInput();
                construirEdificio();
                break;
            case 3:
                limpiarBufferInput();
                reclutarUnidad();
                break;
            case 4:
                limpiarBufferInput();
                atacarUnidad();
            case 5:
                limpiarBufferInput();
                usarHabilidad();
                break;
            case 6:
                limpiarBufferInput();
                verMapa();
                continue;  //continuar sin consumir puntos
            case 7:
                refreshPantalla(turnoActual);
                continue;  //continuar sin consumir puntos
            case 8:
                cout << "Turno finalizado." << endl;
                puntosAccion = 0; //terminar turno
                break;
            default:
                cout << "Opcion no valida." << endl;
                limpiarBufferInput();
                continue;
        }

        if (opcion >= 1 && opcion <= 5) {
            puntosAccion--;
            accionesRealizadas++;
        }

        //mostrar estado actual despues de cada accion que consume puntos
        if (opcion >= 1 && opcion <= 5) {
            cout << "\n--- ESTADO ACTUAL ---" << endl;
            recursos->mostrarEstado();
            cout << "Dominio: " << mapa->calcularDominioJugador() << "%" << endl;
        }
    }

    cout << "Fin de la fase del jugador." << endl;
    puntosAccion = 2; //resetear puntos para el próximo turno
}

//refresci completo de pantalla POR SI FALLA ALGO
void ControladorJugador::refreshPantalla(int turnoActual) {

    //obtener datos actualizados
    int dominioJugador = mapa->calcularDominioJugador();
    int dominioSistema = mapa->calcularDominioSistema();

    //mostrar EXACTAMENTE la misma pantalla que al inicio del turno
    cout << "==========================================" << endl;
    cout << "          RIVAL FRONTIERS 2 - TURNO " << turnoActual << endl;
    cout << "==========================================" << endl;
    cout << "OBJETIVO: Alcanzar 60% de dominio (Turno " << turnoActual << "/12)" << endl;
    cout << "RECURSOS: Comida=" << recursos->obtenerComida()
         << " | Metal=" << recursos->obtenerMetal()
         << " | Energia=" << recursos->obtenerEnergia() << endl;
    cout << "DOMINIO:  Jugador=" << dominioJugador << "% | Sistema=" << dominioSistema << "%" << endl;
    cout << "==========================================" << endl;

    //mostrar mapa
    InterfazConsola::mostrarMapa(*mapa);

    //mostrar fase del jugador
    cout << "--- Fase del Jugador ---" << endl;
    cout << "Tienes " << puntosAccion << " puntos de accion." << endl;
    cout << endl;

    // NO mostrar el menú aquí,  solo mostrar que el refresh fue exitoso
    cout << ">>> Pantalla actualizada correctamente <<<" << endl;
    cout << "Presione Enter para continuar...";

    //limpiar buffer y esperar Enter
    limpiarBufferInput();
    cin.get();
}

//mover una unidad por el mapa
void ControladorJugador::moverUnidad() {
    cout << "\n--- MOVER UNIDAD ---" << endl;

    int x, y, nuevoX, nuevoY;
    cout << "Ingrese coordenadas de la unidad a mover (x y): ";
    cin >> x >> y;

    //cerificar coordenadas válidas
    if (!mapa->esCoordenadaValida(x, y)) {
        cout << "Coordenadas invalidas!" << endl;
        return;
    }

    //cerificar que haya una unidad del jugador
    Celda& celda = mapa->obtenerCelda(x, y);
    if (celda.unidad == nullptr || celda.unidad->obtenerCodigo().substr(0, 2) != "J1") {
        cout << "No hay una unidad aliada en esas coordenadas!" << endl;
        return;
    }

    cout << "Ingrese coordenadas destino (x y): ";
    cin >> nuevoX >> nuevoY;

    //verificar coordenadas destino válidas
    if (!mapa->esCoordenadaValida(nuevoX, nuevoY)) {
        cout << "Coordenadas destino invalidas!" << endl;
        return;
    }

    //verificar que destino esté libre
    Celda& celdaDestino = mapa->obtenerCelda(nuevoX, nuevoY);
    if (celdaDestino.estaOcupada()) {
        cout << "Celda destino ocupada!" << endl;
        return;
    }

    //verificar que sea transitable
    if (!celdaDestino.esTransitable()) {
        cout << "Terreno no transitable!" << endl;
        return;
    }

    //mover unidad
    cout << "Moviendo " << celda.unidad->obtenerCodigo()
         << " de (" << x << "," << y << ") a (" << nuevoX << "," << nuevoY << ")" << endl;

    celdaDestino.unidad = celda.unidad;
    celda.unidad = nullptr;
    celdaDestino.control = "J1"; // Tomar control del territorio

    cout << "Movimiento exitoso!" << endl;
}

//construir un edificio
void ControladorJugador::construirEdificio() {
    cout << "\n--- CONSTRUIR EDIFICIO ---" << endl;

    //mostrar opciones de construcción
    cout << "1. Granja (Costo: 1 Metal, 1 Energia)" << endl;
    cout << "2. Torre (Costo: 2 Metal, 1 Energia)" << endl;
    cout << "3. Cuartel (Costo: 3 Metal, 1 Energia)" << endl;

    int opcion;
    cout << "Seleccione edificio: ";
    cin >> opcion;

    int x, y;
    cout << "Ingrese coordenadas para construir (x y): ";
    cin >> x >> y;

    //verificar coordenadas válidas y control del jugador
    if (!mapa->esCoordenadaValida(x, y)) {
        cout << "Coordenadas invalidas!" << endl;
        return;
    }

    Celda& celda = mapa->obtenerCelda(x, y);
    if (celda.control != "J1") {
        cout << "No controlas este territorio!" << endl;
        return;
    }

    if (celda.estaOcupada()) {
        cout << "Celda ocupada!" << endl;
        return;
    }

    //procesar construcción según opción
    Edificio* nuevoEdificio = nullptr;
    bool recursosSuficientes = false;

    switch (opcion) {
        case 1: // Granja
            if (recursos->consumirMetal(1) && recursos->consumirEnergia(1)) {
                nuevoEdificio = new Granja("J1");
                recursosSuficientes = true;
            }
            break;
        case 2: // Torre
            if (recursos->consumirMetal(2) && recursos->consumirEnergia(1)) {
                nuevoEdificio = new Torre("J1");
                recursosSuficientes = true;
            }
            break;
        case 3: // Cuartel
            if (recursos->consumirMetal(3) && recursos->consumirEnergia(1)) {
                nuevoEdificio = new Cuartel("J1");
                recursosSuficientes = true;
            }
            break;
        default:
            cout << "Opcion no valida!" << endl;
            return;
    }

    if (recursosSuficientes && nuevoEdificio != nullptr) {
        mapa->colocarEdificio(x, y, nuevoEdificio);
        cout << "Edificio construido exitosamente: " << nuevoEdificio->obtenerCodigo() << endl;
    } else {
        cout << "No se pudo construir el edificio." << endl;
        delete nuevoEdificio;
    }
}

//reclutar una nueva unidad
void ControladorJugador::reclutarUnidad() {
    cout << "\n--- RECLUTAR UNIDAD ---" << endl;

    // Verificar que hay un cuartel disponible
    bool tieneCuartel = false;
    for (int y = 0; y < mapa->obtenerAlto(); y++) {
        for (int x = 0; x < mapa->obtenerAncho(); x++) {
            Celda& celda = mapa->obtenerCelda(x, y);
            if (celda.edificio != nullptr && celda.edificio->obtenerCodigo() == "J1Cu") {
                tieneCuartel = true;
                break;
            }
        }
    }

    if (!tieneCuartel) {
        cout << "Necesitas un Cuartel (J1Cu) para reclutar unidades!" << endl;
        return;
    }

    // Mostrar opciones de reclutamiento
    cout << "1. Soldado (Costo: 1 Comida, 1 Metal)" << endl;
    cout << "2. Arquero (Costo: 1 Comida, 1 Metal)" << endl;
    cout << "3. Ingeniero (Costo: 1 Comida, 1 Metal)" << endl;
    cout << "4. Mago (Costo: 1 Comida, 1 Metal)" << endl;
    cout << "5. Caballero (Costo: 1 Comida, 1 Metal)" << endl;

    int opcion;
    cout << "Seleccione unidad: ";
    cin >> opcion;

    int x, y;
    cout << "Ingrese coordenadas para colocar unidad (x y): ";
    cin >> x >> y;

    //verificar coordenadas válidas y control del jugador
    if (!mapa->esCoordenadaValida(x, y)) {
        cout << "Coordenadas invalidas!" << endl;
        return;
    }

    Celda& celda = mapa->obtenerCelda(x, y);
    if (celda.control != "J1") {
        cout << "No controlas este territorio!" << endl;
        return;
    }

    if (celda.estaOcupada()) {
        cout << "Celda ocupada!" << endl;
        return;
    }

    //procesar reclutamiento
    Unidad* nuevaUnidad = nullptr;
    bool recursosSuficientes = false;

    if (recursos->consumirComida(1) && recursos->consumirMetal(1)) {
        recursosSuficientes = true;
        switch (opcion) {
            case 1: nuevaUnidad = new Soldado("J1"); break;
            case 2: nuevaUnidad = new Arquero("J1"); break;
            case 3: nuevaUnidad = new Ingeniero("J1"); break;
            case 4: nuevaUnidad = new Mago("J1"); break;
            case 5: nuevaUnidad = new Caballero("J1"); break;
            default:
                cout << "Opcion no valida!" << endl;
                recursosSuficientes = false;
                break;
        }
    }

    if (recursosSuficientes && nuevaUnidad != nullptr) {
        mapa->colocarUnidad(x, y, nuevaUnidad);
        cout << "Unidad reclutada exitosamente: " << nuevaUnidad->obtenerCodigo() << endl;
    } else {
        cout << "No se pudo reclutar la unidad." << endl;
        delete nuevaUnidad;
    }
}

//usar ataque de una unidad
void ControladorJugador::atacarUnidad() {
    cout << "\n--- ATACAR UNIDAD ---" << endl;

    int x, y;
    cout << "Ingrese coordenadas de su unidad atacante (x y): ";
    cin >> x >> y;

    // validar posicion del atacante
    if (!mapa->esCoordenadaValida(x, y)) {
        cout << "Coordenadas invalidas!" << endl;
        return;
    }

    Celda& celdaAtacante = mapa->obtenerCelda(x, y);

    // validar que haya unidad aliada
    if (celdaAtacante.unidad == nullptr ||
        celdaAtacante.unidad->obtenerCodigo().substr(0, 2) != "J1") {
        cout << "No hay una unidad aliada ahi!" << endl;
        return;
        }

    // pedir objetivo
    int tx, ty;
    cout << "Ingrese coordenadas del objetivo enemigo (x y): ";
    cin >> tx >> ty;

    // validar posicion del objetivo
    if (!mapa->esCoordenadaValida(tx, ty)) {
        cout << "Coordenadas destino invalidas!" << endl;
        return;
    }

    Celda& celdaObjetivo = mapa->obtenerCelda(tx, ty);

    // validar que haya unidad enemiga
    if (celdaObjetivo.unidad == nullptr ||
        celdaObjetivo.unidad->obtenerCodigo().substr(0, 2) == "J1") {
        cout << "No hay una unidad enemiga en ese lugar!" << endl;
        return;
        }

    // mostrar info
    cout << "Atacando "
         << celdaObjetivo.unidad->obtenerCodigo()
         << " desde (" << x << "," << y << ") hacia (" << tx << "," << ty << ")" << endl;

    // realizar ataque con el sistema de combate
    realizarAtaque(
        *celdaAtacante.unidad,
        *celdaObjetivo.unidad
    );

    // si la unidad enemiga murio se lo quita xd
    if (!celdaObjetivo.unidad->estaViva()) {
        cout << "Unidad enemiga eliminada. Removiendo del mapa..." << endl;
        delete celdaObjetivo.unidad;
        celdaObjetivo.unidad = nullptr;
    }

    cout << "Ataque finalizado." << endl;
}



//usar habilidad especial de una unidad
void ControladorJugador::usarHabilidad() {
    cout << "\n--- USAR HABILIDAD ESPECIAL ---" << endl;

    int x, y;
    cout << "Ingrese coordenadas de la unidad (x y): ";
    cin >> x >> y;

    //berificar coordenadas válidas
    if (!mapa->esCoordenadaValida(x, y)) {
        cout << "Coordenadas invalidas!" << endl;
        return;
    }

    //verificar que haya una unidad del jugador
    Celda& celda = mapa->obtenerCelda(x, y);
    if (celda.unidad == nullptr || celda.unidad->obtenerCodigo().substr(0, 2) != "J1") {
        cout << "No hay una unidad aliada en esas coordenadas!" << endl;
        return;
    }

    //verificar costo de energía
    if (!recursos->consumirEnergia(1)) {
        cout << "Energia insuficiente para usar habilidad!" << endl;
        return;
    }

    //usar habilidad
    cout << "Usando habilidad de " << celda.unidad->obtenerCodigo() << "..." << endl;
    celda.unidad->usarHabilidadEspecial();
    cout << "Habilidad usada exitosamente!" << endl;
}

// NUEVA FUNCIÓNnnnnnnnn ver mapa sin consumir acción
void ControladorJugador::verMapa() {
    cout << "\n--- VISUALIZAR MAPA ---" << endl;
    InterfazConsola::mostrarMapa(*mapa);
    cout << "\nPresione Enter para continuar...";
    limpiarBufferInput();
    cin.get();
}

//mostrar menú de acciones disponibles
void ControladorJugador::mostrarMenuAcciones() const {
    cout << "\n=== ACCIONES DISPONIBLES ===" << endl;
    cout << "1. Mover Unidad" << endl;
    cout << "2. Construir Edificio" << endl;
    cout << "3. Reclutar Unidad" << endl;
    cout << "4. Atacar Unidad" << endl;
    cout << "5. Usar Habilidad" << endl;
    cout << "6. Ver Mapa (No consume accion)" << endl;
    cout << "7. Refresh Pantalla (No consume accion)" << endl;
    cout << "8. Terminar Turno" << endl;
    cout << "============================" << endl;
}

//verificar si quedan acciones disponibles
bool ControladorJugador::tieneAccionesDisponibles() const {
    return puntosAccion > 0;
}