#include <iostream>

#ifndef SISTEMA_BANCARIO_NO_COMPILACION_UNICA
#include "compilacion_unica.hpp"
#endif
#include "controlSistema.hpp"

int main() {
    ControlSistema sistema;
    sistema.Ejecutar();
    return 0;
}
