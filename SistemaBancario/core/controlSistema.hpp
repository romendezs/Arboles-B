#pragma once
#include <iostream>
#include <string>
#include "ArbolB.hpp"      
#include "Validaciones.hpp" 

class ControlSistema {
private:
    ArbolB* arbolClientes;  
    bool sistemaActivo;
    std::string usuarioActual;
    bool esAdministrador;

public:
    // Constructor
    ControlSistema();
    

    // Métodos principales del sistema
    void IniciarSistema();
    void CerrarSistema();
    void Ejecutar();
    bool validarUsuario();
    void menuCliente();
    void menuAdmin();

    // Métodos específicos para gestión de clientes
    void gestionarClientes();
    void buscarCliente();
    void mostrarReportes();
    void operacionesArbol();

private:
    // Métodos auxiliares
    void mostrarMenuPrincipal();
    void cerrarSesion();
    bool hayUsuarioLogueado();
    void pausarPantalla();
};