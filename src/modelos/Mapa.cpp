#include "Mapa.h"
#include <iostream>

using namespace std;

//IMPLEMENTACIÓN ZELDa xd

//constructor de Celda
Celda::Celda(Terreno* t, Unidad* u, Edificio* e, const string& ctrl)
    : terreno(t), unidad(u), edificio(e), control(ctrl) {}

// verificar si la celda está ocupada por unidad o edificio
bool Celda::estaOcupada() const {
    return unidad != nullptr || edificio != nullptr;
}

//verificar si la celda es transitable para unidades
bool Celda::esTransitable() const {
    if (terreno == nullptr) return false;
    // Agua no es transitable para la mayoría de unidades
    return terreno->obtenerCodigo() != "AG";
}

//obtener representación visual de la celda
string Celda::obtenerRepresentacion() const {
    string representacion = "[";

    if (unidad != nullptr) {
        representacion += unidad->obtenerCodigo();
    } else if (edificio != nullptr) {
        representacion += edificio->obtenerCodigo();
    } else {
        representacion += "...";
    }

    representacion += "/";

    if (terreno != nullptr) {
        representacion += terreno->obtenerCodigo();
    } else {
        representacion += "??";
    }

    representacion += "]";
    return representacion;
}

// MAPA

//constructor del mapa maposo
Mapa::Mapa(int ancho, int alto) : ancho(ancho), alto(alto) {
    //inicializar generador de números aleatorios
    srand(time(0));

    //redimensionar la matriz de celdas
    celdas.resize(alto, vector<Celda>(ancho));

    //inicializar el mapa con terrenos aleatorios
    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            // Crear terreno aleatorio
            int tipoTerreno = rand() % 5;
            Terreno* terreno = nullptr;

            switch (tipoTerreno) {
                case 0: terreno = new Llanura(); break;
                case 1: terreno = new Bosque(); break;
                case 2: terreno = new Montana(); break;
                case 3: terreno = new Agua(); break;
                case 4: terreno = new Pantano(); break;
            }

            celdas[y][x] = Celda(terreno, nullptr, nullptr, "NE");
        }
    }

    // colocar posiciones iniciales del jugador y sistema
    // jugador empieza en esquina superior izquierda
    colocarEdificio(0, 0, new Cuartel("J1"));
    colocarUnidad(1, 1, new Soldado("J1"));
    celdas[0][0].control = "J1";
    celdas[1][1].control = "J1";

    // sistema mpieza en esquina inferior derecha
    colocarEdificio(ancho-1, alto-1, new Cuartel("J2"));
    colocarUnidad(ancho-2, alto-2, new Soldado("J2"));
    celdas[alto-1][ancho-1].control = "J2";
    celdas[alto-2][ancho-2].control = "J2";

    // colocar un edificios neutral
    if (ancho >= 3 && alto >= 3) {
        colocarEdificio(2, 2, new Cuartel("Ne"));
        celdas[2][2].control = "NE";
    }

    cout << "Mapa de " << ancho << "x" << alto << " inicializado." << endl;
}

// Destructor del Mapa para liberar toda la memoria
Mapa::~Mapa() {
    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            delete celdas[y][x].terreno;
            delete celdas[y][x].unidad;
            delete celdas[y][x].edificio;
        }
    }
    cout << "Memoria del mapa liberada." << endl;
}

//obtener referencia a zelda
Celda& Mapa::obtenerCelda(int x, int y) {
    if (!esCoordenadaValida(x, y)) {
        throw out_of_range("Coordenadas fuera del mapa");
    }
    return celdas[y][x];
}

// obtener referencia a zelda
const Celda& Mapa::obtenerCelda(int x, int y) const {
    if (!esCoordenadaValida(x, y)) {
        throw out_of_range("Coordenadas fuera del mapa");
    }
    return celdas[y][x];
}

//colocar unidad en coordenadas específicas
bool Mapa::colocarUnidad(int x, int y, Unidad* unidad) {
    if (!esCoordenadaValida(x, y) || celdas[y][x].unidad != nullptr) {
        delete unidad; //liberar memoria si no se puede colocar
        return false;
    }
    celdas[y][x].unidad = unidad;
    return true;
}

//colocar edificio en coordenadas específicas
bool Mapa::colocarEdificio(int x, int y, Edificio* edificio) {
    if (!esCoordenadaValida(x, y) || celdas[y][x].edificio != nullptr) {
        delete edificio; //liberar memoria si no se puede colocar
        return false;
    }
    celdas[y][x].edificio = edificio;
    celdas[y][x].control = edificio->obtenerCodigo().substr(0, 2); // J1 o J2
    return true;
}

//colocar terreno en coordenadas específicas
bool Mapa::colocarTerreno(int x, int y, Terreno* terreno) {
    if (!esCoordenadaValida(x, y)) {
        delete terreno;
        return false;
    }
    delete celdas[y][x].terreno; //liberar terreno anterior
    celdas[y][x].terreno = terreno;
    return true;
}

//remover unidad de coordenadas específicas
bool Mapa::removerUnidad(int x, int y) {
    if (!esCoordenadaValida(x, y) || celdas[y][x].unidad == nullptr) {
        return false;
    }
    delete celdas[y][x].unidad;
    celdas[y][x].unidad = nullptr;
    return true;
}

//remover edificio de coordenadas específicas
bool Mapa::removerEdificio(int x, int y) {
    if (!esCoordenadaValida(x, y) || celdas[y][x].edificio == nullptr) {
        return false;
    }
    delete celdas[y][x].edificio;
    celdas[y][x].edificio = nullptr;
    //no cambiar control inmediatamente, podría haber otras unidades
    return true;
}

//verificar si coordenadas están dentro del mapa
bool Mapa::esCoordenadaValida(int x, int y) const {
    return x >= 0 && x < ancho && y >= 0 && y < alto;
}

//mostrar el mapa en consola
void Mapa::mostrarMapa() const {
    cout << "\n=== MAPA ACTUAL ===" << endl;

    //mostrar números de columnas
    cout << "    ";
    for (int x = 0; x < ancho; x++) {
        cout << "  " << x << "   ";
    }
    cout << endl;

    //mstrar filas con números
    for (int y = 0; y < alto; y++) {
        cout << y << "  ";
        for (int x = 0; x < ancho; x++) {
            cout << celdas[y][x].obtenerRepresentacion() << " ";
        }
        cout << endl;
    }

    //mstrar leyenda
    cout << "\n--- LEYENDA ---" << endl;
    cout << "J1S: Soldado Jugador | J2S: Soldado Sistema" << endl;
    cout << "J1A: Arquero Jugador | J2A: Arquero Sistema" << endl;
    cout << "J1I: Ingeniero Jugador | J2I: Ingeniero Sistema" << endl;
    cout << "J1M: Mago Jugador | J2I: Mago Sistema" << endl;
    cout << "J1C: Caballero Jugador | J2I: Caballero Sistema" << endl;

    cout << "J1Cu: Cuartel Jugador | J2Cu: Cuartel Sistema" << endl;
    cout << "J1Gr: Granja Jugador | J2Gr: Granja Sistema" << endl;
    cout << "J1To: Torre Jugador | J2To: Torre Sistema" << endl;
    cout << "LL: Llanura | BO: Bosque | MO: Montana | AG: Agua | PA: Pantano" << endl;
}

//calcular porcentaje de dominio del jugador
int Mapa::calcularDominioJugador() const {
    int celdasJugador = 0;
    int totalCeldas = ancho * alto;

    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            if (celdas[y][x].control == "J1") {
                celdasJugador++;
            }
        }
    }

    return (celdasJugador * 100) / totalCeldas;
}

//calcular porcentaje de dominio del sistema
int Mapa::calcularDominioSistema() const {
    int celdasSistema = 0;
    int totalCeldas = ancho * alto;

    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            if (celdas[y][x].control == "J2") {
                celdasSistema++;
            }
        }
    }

    return (celdasSistema * 100) / totalCeldas;
}

// Getters
int Mapa::obtenerAncho() const { return ancho; }
int Mapa::obtenerAlto() const { return alto; }