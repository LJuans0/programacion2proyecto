#include "Utilidades.h"
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;
//ESTAS SON HERRAMIENTAS NOMAS
// inicializar generador de números aleatorios
bool aleatorioInicializado = false;

//dividir string en partes usando delimitador
vector<string> Utilidades::dividirString(const string& texto, char delimitador) {
    vector<string> partes;
    stringstream ss(texto);
    string parte;
    
    while (getline(ss, parte, delimitador)) {
        partes.push_back(parte);
    }
    
    return partes;
}

//convertir string a mayúsculas
string Utilidades::aMayusculas(const string& texto) {
    string resultado = texto;
    for (char& c : resultado) {
        c = toupper(c);
    }
    return resultado;
}

//berificar si string representa un número
bool Utilidades::esNumero(const string& texto) {
    if (texto.empty()) return false;
    
    for (char c : texto) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// generar número aleatorio en rango [min, max]
int Utilidades::aleatorioEnRango(int min, int max) {
    if (!aleatorioInicializado) {
        srand(time(0));
        aleatorioInicializado = true;
    }
    
    if (min > max) {
        int temp = min;
        min = max;
        max = temp;
    }
    
    return min + (rand() % (max - min + 1));
}