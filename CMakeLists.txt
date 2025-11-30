cmake_minimum_required(VERSION 4.0)
project(RIVALFRONTIERS2)

set(CMAKE_CXX_STANDARD 20)

add_executable(RIVALFRONTIERS2 src/main.cpp
        src/juego/Juego.cpp
        src/juego/Juego.h
        src/modelos/Terreno.cpp
        src/modelos/Terreno.h
        src/modelos/Unidad.cpp
        src/modelos/Unidad.h
        src/modelos/Edificio.cpp
        src/modelos/Edificio.h
        src/modelos/Mapa.cpp
        src/modelos/Mapa.h
        src/sistemas/SistemaRecursos.cpp
        src/sistemas/SistemaRecursos.h
        src/sistemas/SistemaCombate.cpp
        src/sistemas/SistemaCombate.h
        src/utilidades/Utilidades.cpp
        src/utilidades/Utilidades.h
        src/utilidades/Persistencia.cpp
        src/utilidades/Persistencia.h
        src/interfaz/InterfazConsola.cpp
        src/interfaz/InterfazConsola.h
        src/interfaz/Reportes.cpp
        src/interfaz/Reportes.h
        src/controladores/ControladorJugador.cpp
        src/controladores/ControladorJugador.h
        src/controladores/ControladorSistema.cpp
        src/controladores/ControladorSistema.h)
