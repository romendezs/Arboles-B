#pragma once

#include <memory>
#include <string>

#include "../Estructura/arbolB.hpp"
#include "../Entidades/transaccion.hpp"
#include "../Roles/cliente.hpp"
#include "../Reporte/reporte.hpp"

class ControlSistema {
private:
    std::unique_ptr<ArbolB> arbolClientes_;
    bool sistemaActivo_;
    std::string usuarioActual_;
    bool esAdministrador_;

    Reporte reporte_;

public:
    ControlSistema();

    void IniciarSistema();
    void CerrarSistema();
    void Ejecutar();

    bool validarUsuario();
    void menuCliente();
    void menuAdmin();

    void gestionarClientes();
    void buscarCliente();
    void mostrarReportes();
    void operacionesArbol();

private:
    void mostrarMenuPrincipal();
    void cerrarSesion();
    bool hayUsuarioLogueado() const;
    void pausarPantalla();
    void realizarDeposito();
    void realizarRetiro();
    void realizarTransferencia();
    Cliente* obtenerClienteEnSesion();
    bool asegurarCuentaActiva(Cliente& cliente);
    void registrarTransaccion(const std::string& dui,
                              const std::string& numeroCuenta,
                              const std::string& tipo,
                              double monto,
                              const std::string& estado);
    std::string generarIdTransaccion() const;
    std::string obtenerFechaHoraActual() const;
};
