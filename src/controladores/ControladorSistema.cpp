#include "ControladorSistema.h"
#include <iostream>


using namespace std;

//constructor del ControladorSistema
ControladorSistema::ControladorSistema(Mapa* mapa) : mapa(mapa) {
    srand(time(0)); //inicializar semilla aleatoria
}

//ejecutar rutinas automáticas del sistema
void ControladorSistema::ejecutarRutina() {
    cout << "Sistema ejecutando rutinas automaticas..." << endl;
    
    //ejecutar diferentes rutinas basadas en turno o condiciones
    rutinaDefensiva();
    rutinaOfensiva();
    rutinaExpansion();
    
    cout << "Rutinas del sistema completadas." << endl;
}

//rutina defensiva - proteger territorios y edificios
void ControladorSistema::rutinaDefensiva() {
    cout << "- Rutina defensiva: Fortaleciendo posiciones..." << endl;
    
    //mover unidades hacia posiciones defensivas
    for (int y = 0; y < mapa->obtenerAlto(); y++) {
        for (int x = 0; x < mapa->obtenerAncho(); x++) {
            Celda& celda = mapa->obtenerCelda(x, y);
            
            //si hay unidad del sistema, posiblemente moverla
            if (celda.unidad != nullptr && celda.unidad->obtenerCodigo().substr(0, 2) == "J2") {
                //50% de probabilidad de mover cada unidad
                if (rand() % 2 == 0) {
                    //intentar mover en dirección aleatoria
                    int direccion = rand() % 4;
                    int nuevoX = x, nuevoY = y;
                    
                    switch (direccion) {
                        case 0: nuevoY--; break; // Arriba
                        case 1: nuevoY++; break; // Abajo
                        case 2: nuevoX--; break; // Izquierda
                        case 3: nuevoX++; break; // Derecha
                    }
                    
                    // verificar movimiento válido
                    if (mapa->esCoordenadaValida(nuevoX, nuevoY)) {
                        Celda& celdaDestino = mapa->obtenerCelda(nuevoX, nuevoY);
                        if (!celdaDestino.estaOcupada() && celdaDestino.esTransitable()) {
                            // Mover unidad
                            cout << "  " << celda.unidad->obtenerCodigo() 
                                 << " se mueve a (" << nuevoX << "," << nuevoY << ")" << endl;
                            
                            celdaDestino.unidad = celda.unidad;
                            celda.unidad = nullptr;
                            celdaDestino.control = "J2";
                        }
                    }
                }
            }
        }
    }
}

//rutina ofensiva - atacar territorios del jugador
void ControladorSistema::rutinaOfensiva() {
    cout << "- Rutina ofensiva: Buscando objetivos..." << endl;
    
    //buscar unidades del jugador para atacar
    for (int y = 0; y < mapa->obtenerAlto(); y++) {
        for (int x = 0; x < mapa->obtenerAncho(); x++) {
            Celda& celda = mapa->obtenerCelda(x, y);
            
            // si hay unidad del sistema, buscar objetivos cercanos
            if (celda.unidad != nullptr && celda.unidad->obtenerCodigo().substr(0, 2) == "J2") {
                // buscar en celdas adyacentes por unidades del jugador
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        if (dx == 0 && dy == 0) continue; // Saltar celda actual
                        
                        int objetivoX = x + dx;
                        int objetivoY = y + dy;
                        
                        if (mapa->esCoordenadaValida(objetivoX, objetivoY)) {
                            Celda& celdaObjetivo = mapa->obtenerCelda(objetivoX, objetivoY);
                            
                            //si hay unidad del jugador, atacar
                            if (celdaObjetivo.unidad != nullptr && 
                                celdaObjetivo.unidad->obtenerCodigo().substr(0, 2) == "J1") {
                                
                                cout << "  " << celda.unidad->obtenerCodigo() 
                                     << " ataca a " << celdaObjetivo.unidad->obtenerCodigo() << endl;
                                
                                //simular ataque
                                celda.unidad->atacar(*celdaObjetivo.unidad);
                                
                                //si el defensor muere, liberar celda y pues elminarlo
                                if (!celdaObjetivo.unidad->estaViva()) {
                                    delete celdaObjetivo.unidad;
                                    celdaObjetivo.unidad = nullptr;
                                    //el control aun no cambia inmediatamente
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

//rutina de expansión, osea toma territorios neutrales
void ControladorSistema::rutinaExpansion() {
    cout << "- Rutina expansion: Tomando territorios..." << endl;
    
    //ocasionalmente crear nueva unidad (33% de probabilidad)
    if (rand() % 3 == 0) {
        int x, y;
        if (encontrarPosicionLibre(x, y)) {
            // Crear nueva unidad del sistema
            Unidad* nuevaUnidad = nullptr;
            int tipoUnidad = rand() % 3;
            
            switch (tipoUnidad) {
                case 0: nuevaUnidad = new Soldado("J2"); break;
                case 1: nuevaUnidad = new Arquero("J2"); break;
                case 2: nuevaUnidad = new Ingeniero("J2"); break;
            }
            
            if (nuevaUnidad != nullptr) {
                mapa->colocarUnidad(x, y, nuevaUnidad);
                mapa->obtenerCelda(x, y).control = "J2";
                cout << "  Sistema despliega " << nuevaUnidad->obtenerCodigo() 
                     << " en (" << x << "," << y << ")" << endl;
            }
        }
    }
}

//encontrar posición libre para colocar unidad
bool ControladorSistema::encontrarPosicionLibre(int& x, int& y) const {
    //buscar en territorio controlado por el sistema
    for (int intentos = 0; intentos < 10; intentos++) {
        x = rand() % mapa->obtenerAncho();
        y = rand() % mapa->obtenerAlto();
        
        Celda& celda = mapa->obtenerCelda(x, y);
        if (!celda.estaOcupada() && celda.control == "J2" && celda.esTransitable()) {
            return true;
        }
    }
    
    //si no encuentra en territorio propio, buscar cualquier posición libre
    for (int y = 0; y < mapa->obtenerAlto(); y++) {
        for (int x = 0; x < mapa->obtenerAncho(); x++) {
            Celda& celda = mapa->obtenerCelda(x, y);
            if (!celda.estaOcupada() && celda.esTransitable()) {
                return true;
            }
        }
    }
    
    return false; // bo hay posiciones libres
}