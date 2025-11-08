#include <iostream>
#include <string>
#include <stdio.h>
#include "../Reporte/validacionUser.hpp"
#include "../Roles/cliente.hpp"

class ControlSistema {
private:
    ArbolB* arbolClientes;  
    bool sistemaActivo;
    std::string usuarioActual;
    bool esAdministrador;
    Transaccion* transaccionActual;  
    Cliente* clienteDestino;

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

    void verificarTransferencia();
    void verificarDeposito();
    void verificarRetiro();
private:
    // Métodos auxiliares
    void mostrarMenuPrincipal();
    void cerrarSesion();
    bool hayUsuarioLogueado();
    void pausarPantalla();
};