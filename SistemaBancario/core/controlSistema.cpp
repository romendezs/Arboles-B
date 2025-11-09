#include "controlSistema.hpp"

#include <cstdlib>
#include <iostream>
#include <limits>

ControlSistema::ControlSistema()
    : arbolClientes_(std::make_unique<ArbolB>()),
      sistemaActivo_(false),
      usuarioActual_(),
      esAdministrador_(false),
      reporte_() {}

void ControlSistema::IniciarSistema() {
    sistemaActivo_ = true;
    std::cout << "=== SISTEMA BANCARIO INICIADO ===" << std::endl;
    if (reporte_.cargarClientes(*arbolClientes_)) {
        std::cout << "Clientes cargados desde persistencia." << std::endl;
    } else {
        std::cout << "No se encontraron clientes almacenados." << std::endl;
    }
    std::cout << std::endl;
}

void ControlSistema::CerrarSistema() {
    sistemaActivo_ = false;
    std::cout << "=== SISTEMA BANCARIO CERRADO ===" << std::endl;
}

void ControlSistema::Ejecutar() {
    IniciarSistema();

    while (sistemaActivo_) {
        if (!hayUsuarioLogueado()) {
            if (!mostrarMenuPrincipal()) {
                continue;
            }
            if (!validarUsuario()) {
                continue;
            }
        }

        if (esAdministrador_) {
            menuAdmin();
        } else {
            menuCliente();
        }
    }

    CerrarSistema();
}

bool ControlSistema::validarUsuario() {
    std::string usuario;
    std::string password;

    std::cout << "=== INICIO DE SESION ===" << std::endl;
    std::cout << "Usuario: ";
    std::cin >> usuario;
    std::cout << "Password: ";
    std::cin >> password;

    if (reporte_.verificarAdmin(usuario, password)) {
        usuarioActual_ = usuario;
        esAdministrador_ = true;
        std::cout << "Bienvenido Administrador!" << std::endl;
    } else if (reporte_.verificarCliente(usuario, password)) {
        usuarioActual_ = usuario;
        esAdministrador_ = false;
        std::cout << "Bienvenido Cliente!" << std::endl;
    } else {
        std::cout << "Error: Credenciales incorrectas." << std::endl;
        pausarPantalla();
        return false;
    }

    pausarPantalla();
    return true;
}

void ControlSistema::menuCliente() {
    int opcion = 0;

    do {
        std::system("clear");
        std::cout << "=== MENU CLIENTE ===" << std::endl;
        std::cout << "Usuario: " << usuarioActual_ << std::endl;
        std::cout << "1. Consultar mis datos" << std::endl;
        std::cout << "2. Ver reporte de clientes" << std::endl;
        std::cout << "3. Cerrar sesion" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                Cliente cliente;
                if (arbolClientes_->buscar(usuarioActual_, cliente)) {
                    cliente.mostrarInfo();
                } else {
                    std::cout << "No se encontró información del cliente." << std::endl;
                }
                break;
            }
            case 2:
                if (reporte_.generarReporteClientes(*arbolClientes_)) {
                    std::cout << "Reporte generado correctamente." << std::endl;
                } else {
                    std::cout << "No fue posible generar el reporte." << std::endl;
                }
                break;
            case 3:
                cerrarSesion();
                break;
            default:
                std::cout << "Opción inválida." << std::endl;
                break;
        }

        if (opcion != 3) {
            pausarPantalla();
        }

    } while (hayUsuarioLogueado() && !esAdministrador_);
}

void ControlSistema::menuAdmin() {
    int opcion = 0;

    do {
        std::system("clear");
        std::cout << "=== MENU ADMINISTRADOR ===" << std::endl;
        std::cout << "Usuario: " << usuarioActual_ << std::endl;
        std::cout << "1. Gestionar Clientes" << std::endl;
        std::cout << "2. Buscar Cliente" << std::endl;
        std::cout << "3. Mostrar Reportes" << std::endl;
        std::cout << "4. Operaciones del Arbol" << std::endl;
        std::cout << "5. Guardar Clientes" << std::endl;
        std::cout << "6. Cerrar sesion" << std::endl;
        std::cout << "7. Salir del sistema" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                gestionarClientes();
                break;
            case 2:
                buscarCliente();
                break;
            case 3:
                mostrarReportes();
                break;
            case 4:
                operacionesArbol();
                break;
            case 5:
                if (reporte_.guardarClientes(*arbolClientes_)) {
                    std::cout << "Clientes guardados correctamente." << std::endl;
                } else {
                    std::cout << "No fue posible guardar los clientes." << std::endl;
                }
                pausarPantalla();
                break;
            case 6:
                cerrarSesion();
                break;
            case 7:
                CerrarSistema();
                break;
            default:
                std::cout << "Opción inválida." << std::endl;
                pausarPantalla();
                break;
        }

    } while (hayUsuarioLogueado() && esAdministrador_ && opcion != 6 && opcion != 7);
}

void ControlSistema::gestionarClientes() {
    int opcion = 0;

    do {
        std::system("clear");
        std::cout << "=== GESTION DE CLIENTES ===" << std::endl;
        std::cout << "1. Insertar cliente" << std::endl;
        std::cout << "2. Mostrar todos los clientes" << std::endl;
        std::cout << "3. Volver" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                std::string dui, nombre, apellido, email, telefono, direccion;
                std::cout << "DUI: ";
                std::cin >> dui;
                std::cout << "Nombre: ";
                std::cin >> nombre;
                std::cout << "Apellido: ";
                std::cin >> apellido;
                std::cout << "Email: ";
                std::cin >> email;
                std::cout << "Telefono: ";
                std::cin >> telefono;
                std::cout << "Direccion: ";
                std::cin >> direccion;

                Cliente cliente(dui, nombre, apellido, email, telefono, direccion);
                if (arbolClientes_->insertar(cliente)) {
                    std::cout << "Cliente insertado." << std::endl;
                } else {
                    std::cout << "Cliente actualizado." << std::endl;
                }
                break;
            }
            case 2:
                arbolClientes_->imprimir(std::cout);
                break;
            case 3:
                return;
            default:
                std::cout << "Opción inválida." << std::endl;
                break;
        }

        pausarPantalla();
    } while (opcion != 3);
}

void ControlSistema::buscarCliente() {
    std::string dui;
    std::cout << "=== BUSCAR CLIENTE ===" << std::endl;
    std::cout << "Ingrese el DUI del cliente: ";
    std::cin >> dui;

    Cliente cliente;
    if (arbolClientes_->buscar(dui, cliente)) {
        cliente.mostrarInfo();
    } else {
        std::cout << "Cliente no encontrado." << std::endl;
    }

    pausarPantalla();
}

void ControlSistema::mostrarReportes() {
    std::cout << "=== REPORTES DEL ARBOL B ===" << std::endl;
    std::cout << "Total clientes: " << arbolClientes_->obtenerCantidad() << std::endl;
    if (reporte_.generarReporteClientes(*arbolClientes_)) {
        std::cout << "Reporte de clientes generado en " << "data/reporte_sistema.txt" << std::endl;
    } else {
        std::cout << "No fue posible generar el reporte." << std::endl;
    }
    pausarPantalla();
}

void ControlSistema::operacionesArbol() {
    std::cout << "=== OPERACIONES DEL ARBOL B ===" << std::endl;
    arbolClientes_->imprimir(std::cout);
    pausarPantalla();
}

bool ControlSistema::mostrarMenuPrincipal() {
    std::system("clear");
    std::cout << "=== SISTEMA BANCARIO ===" << std::endl;
    std::cout << "1. Iniciar sesion" << std::endl;
    std::cout << "2. Crear usuario" << std::endl;
    std::cout << "3. Salir del sistema" << std::endl;
    std::cout << "Seleccione una opcion: ";

    int opcion = 0;
    std::cin >> opcion;

    switch (opcion) {
        case 1:
            return true;
        case 2:
            registrarNuevoCliente();
            return false;
        case 3:
            CerrarSistema();
            return false;
        default:
            std::cout << "Opción inválida." << std::endl;
            pausarPantalla();
            return false;
    }
}

bool ControlSistema::registrarNuevoCliente() {
    std::system("clear");
    std::cout << "=== CREAR NUEVO USUARIO ===" << std::endl;

    std::string dui;
    std::cout << "DUI: ";
    std::cin >> dui;

    Cliente existente;
    if (arbolClientes_->buscar(dui, existente)) {
        std::cout << "Ya existe un cliente registrado con ese DUI." << std::endl;
        pausarPantalla();
        return false;
    }

    if (reporte_.existeCredencialCliente(dui)) {
        std::cout << "Ya existen credenciales asociadas a ese DUI. Contacte al administrador." << std::endl;
        pausarPantalla();
        return false;
    }

    std::string nombre;
    std::string apellido;
    std::string email;
    std::string telefono;
    std::string direccion;
    std::string password;

    std::cout << "Nombre: ";
    std::cin >> nombre;
    std::cout << "Apellido: ";
    std::cin >> apellido;
    std::cout << "Email: ";
    std::cin >> email;
    std::cout << "Telefono: ";
    std::cin >> telefono;
    std::cout << "Direccion: ";
    std::cin >> direccion;
    std::cout << "Password: ";
    std::cin >> password;

    Cliente nuevoCliente(dui, nombre, apellido, email, telefono, direccion);
    const bool insertado = arbolClientes_->insertar(nuevoCliente);
    if (!insertado) {
        std::cout << "No se pudo registrar al nuevo cliente." << std::endl;
        pausarPantalla();
        return false;
    }

    const bool clientesGuardados = reporte_.guardarClientes(*arbolClientes_);
    const bool credencialesGuardadas = reporte_.guardarCredencialesCliente(dui, password);

    if (clientesGuardados && credencialesGuardadas) {
        std::cout << "Usuario creado correctamente. Ya puede iniciar sesion." << std::endl;
    } else {
        if (!clientesGuardados) {
            std::cout << "Advertencia: no se pudo actualizar el archivo de clientes." << std::endl;
        }
        if (!credencialesGuardadas) {
            std::cout << "Error: no se pudieron guardar las credenciales. Contacte al administrador." << std::endl;
        }
    }

    pausarPantalla();
    return clientesGuardados && credencialesGuardadas;
}

void ControlSistema::cerrarSesion() {
    std::cout << "Cerrando sesion de " << usuarioActual_ << "..." << std::endl;
    usuarioActual_.clear();
    esAdministrador_ = false;
    pausarPantalla();
}

bool ControlSistema::hayUsuarioLogueado() const {
    return !usuarioActual_.empty();
}

void ControlSistema::pausarPantalla() {
    std::cout << std::endl << "Presione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
