#pragma once

// Este encabezado permite compilar el sistema completo ejecutando
// unicamente "g++ core/main.cpp". Incluirá las implementaciones de
// todas las clases siempre que no se defina el macro
// SISTEMA_BANCARIO_NO_COMPILACION_UNICA. De esta forma se mantiene la
// compatibilidad con compilaciones tradicionales que compilan cada
// unidad de traducción por separado.

#ifndef SISTEMA_BANCARIO_NO_COMPILACION_UNICA

#include "../Entidades/Persona.cpp"
#include "../Entidades/cuenta.cpp"
#include "../Entidades/transaccion.cpp"

#include "../Estructura/arbolB.cpp"

#include "../Roles/cliente.cpp"
#include "../Roles/administrador.cpp"

#include "../Reporte/reporte.cpp"

#include "controlSistema.cpp"

#endif  // SISTEMA_BANCARIO_NO_COMPILACION_UNICA

