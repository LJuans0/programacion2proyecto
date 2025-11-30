#ifndef SISTEMARECURSOS_H
#define SISTEMARECURSOS_H

// sstema que maneja todos los recursos del jugador y basicamente del juego
class SistemaRecursos {
private:
    int comida;     // recurso comida
    int metal;      // recurso metal
    int energia;    // recurso energía
    
public:
    // constructor con valores iniciales
    SistemaRecursos(int comidaInicial, int metalInicial, int energiaInicial);
    
    // métodos para modificar recursos
    void agregarComida(int cantidad);
    void agregarMetal(int cantidad);
    void agregarEnergia(int cantidad);
    
    // métodos para consumir recursos (retornan éxito o fracaso)
    bool consumirComida(int cantidad);
    bool consumirMetal(int cantidad);
    bool consumirEnergia(int cantidad);
    
    // procesar fin de turno (producción y mantenimiento)
    void procesarFinTurno();
    
    // getters
    int obtenerComida() const;
    int obtenerMetal() const;
    int obtenerEnergia() const;
    
    //sobrecarga del operador += para agregar recursos
    SistemaRecursos& operator+=(const SistemaRecursos& otros);
    
    // mostrar estado de recursos
    void mostrarEstado() const;
};

#endif