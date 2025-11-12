#include "controlSistema.hpp"

#include <algorithm>
#include <chrono>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <sstream>
#include <string>

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
            mostrarMenuPrincipal();
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
        std::cout << "2. Depositar fondos" << std::endl;
        std::cout << "3. Retirar fondos" << std::endl;
        std::cout << "4. Transferir fondos" << std::endl;
        std::cout << "5. Ver reporte de clientes" << std::endl;
        std::cout << "6. Cerrar sesion" << std::endl;
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
                realizarDeposito();
                break;
            case 3:
                realizarRetiro();
                break;
            case 4:
                realizarTransferencia();
                break;
            case 5:
                if (reporte_.generarReporteClientes(*arbolClientes_)) {
                    std::cout << "Reporte generado correctamente." << std::endl;
                } else {
                    std::cout << "No fue posible generar el reporte." << std::endl;
                }
                break;
            case 6:
                cerrarSesion();
                break;
            default:
                std::cout << "Opción inválida." << std::endl;
                break;
        }

        if (opcion != 6) {
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
        std::cout << "2. Eliminar cliente" << std::endl;
        std::cout << "3. Mostrar todos los clientes" << std::endl;
        std::cout << "4. Volver" << std::endl;
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

                    std::string password = nombre;
                    std::transform(password.begin(), password.end(), password.begin(),
                                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                    password += "123";

                    reporte_.eliminarCredencialesCliente(dui);
                    if (reporte_.guardarCredencialesCliente(dui, password)) {
                        std::cout << "Credenciales generadas. Usuario: " << dui
                                  << " Password: " << password << std::endl;
                    } else {
                        std::cout << "No fue posible generar las credenciales del cliente." << std::endl;
                    }
                } else {
                    std::cout << "Cliente actualizado." << std::endl;
                }
                break;
            }
            case 2: {
                std::string dui;
                std::cout << "Ingrese el DUI del cliente a eliminar: ";
                std::cin >> dui;

                if (arbolClientes_->eliminar(dui)) {
                    std::cout << "Cliente eliminado del sistema." << std::endl;
                    if (reporte_.eliminarCredencialesCliente(dui)) {
                        std::cout << "Credenciales del cliente eliminadas." << std::endl;
                    }
                } else {
                    std::cout << "No se encontró un cliente con el DUI proporcionado." << std::endl;
                }
                break;
            }
            case 3:
                arbolClientes_->imprimir(std::cout);
                break;
            case 4:
                return;
            default:
                std::cout << "Opción inválida." << std::endl;
                break;
        }

        pausarPantalla();
    } while (opcion != 4);
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
        std::cout << "Reporte de clientes generado en "
                  << reporte_.obtenerRutaReporte() << std::endl;
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

Cliente* ControlSistema::obtenerClienteEnSesion() {
    if (!hayUsuarioLogueado()) {
        return nullptr;
    }
    return arbolClientes_->obtenerCliente(usuarioActual_);
}

bool ControlSistema::asegurarCuentaActiva(Cliente& cliente) {
    auto cuenta = cliente.getCuenta();
    if (!cuenta) {
        std::ostringstream numeroCuenta;
        numeroCuenta << "CTA-" << cliente.getDui();
        cuenta = std::make_shared<Cuenta>(numeroCuenta.str(), cliente.getDui(), "AHORRO");
        cliente.setCuenta(cuenta);
        std::cout << "Se ha asignado una cuenta predeterminada con número "
                  << cuenta->getNumeroCuenta() << '.' << std::endl;
    }

    if (!cuenta->estaActiva()) {
        std::cout << "La cuenta asociada no se encuentra activa." << std::endl;
        return false;
    }

    return true;
}

void ControlSistema::realizarDeposito() {
    Cliente* cliente = obtenerClienteEnSesion();
    if (!cliente) {
        std::cout << "No se pudo localizar la información del cliente." << std::endl;
        return;
    }

    if (!asegurarCuentaActiva(*cliente)) {
        return;
    }

    double monto = 0.0;
    std::cout << "Ingrese el monto a depositar: ";
    while (!(std::cin >> monto)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida. Ingrese el monto a depositar: ";
    }

    if (monto <= 0.0) {
        std::cout << "El monto debe ser mayor a cero." << std::endl;
        return;
    }

    const std::string numeroCuenta = cliente->getCuenta()->getNumeroCuenta();

    if (cliente->depositar(monto)) {
        registrarTransaccion(cliente->getDui(), numeroCuenta, "Deposito", monto, "Completada");
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(2) << cliente->consultarSaldo();
        std::cout << "Depósito realizado correctamente. Saldo actual: $" << ss.str()
                  << std::endl;
    } else {
        registrarTransaccion(cliente->getDui(), numeroCuenta, "Deposito", monto, "Fallida");
        std::cout << "No fue posible realizar el depósito." << std::endl;
    }
}

void ControlSistema::realizarRetiro() {
    Cliente* cliente = obtenerClienteEnSesion();
    if (!cliente) {
        std::cout << "No se pudo localizar la información del cliente." << std::endl;
        return;
    }

    if (!asegurarCuentaActiva(*cliente)) {
        return;
    }

    double monto = 0.0;
    std::cout << "Ingrese el monto a retirar: ";
    while (!(std::cin >> monto)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida. Ingrese el monto a retirar: ";
    }

    if (monto <= 0.0) {
        std::cout << "El monto debe ser mayor a cero." << std::endl;
        return;
    }

    const std::string numeroCuenta = cliente->getCuenta()->getNumeroCuenta();

    if (cliente->retirar(monto)) {
        registrarTransaccion(cliente->getDui(), numeroCuenta, "Retiro", monto, "Completada");
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(2) << cliente->consultarSaldo();
        std::cout << "Retiro realizado correctamente. Saldo actual: $" << ss.str()
                  << std::endl;
    } else {
        registrarTransaccion(cliente->getDui(), numeroCuenta, "Retiro", monto, "Fallida");
        std::cout << "No fue posible realizar el retiro. Verifique su saldo disponible."
                  << std::endl;
    }
}

void ControlSistema::realizarTransferencia() {
    Cliente* clienteOrigen = obtenerClienteEnSesion();
    if (!clienteOrigen) {
        std::cout << "No se pudo localizar la información del cliente." << std::endl;
        return;
    }

    std::string duiDestino;
    std::cout << "Ingrese el DUI del cliente destino: ";
    std::cin >> duiDestino;

    if (duiDestino == usuarioActual_) {
        std::cout << "No es posible transferir a la misma cuenta." << std::endl;
        return;
    }

    Cliente* clienteDestino = arbolClientes_->obtenerCliente(duiDestino);
    if (!clienteDestino) {
        std::cout << "El cliente destino no existe en el sistema." << std::endl;
        return;
    }

    if (!asegurarCuentaActiva(*clienteOrigen)) {
        return;
    }

    if (!asegurarCuentaActiva(*clienteDestino)) {
        return;
    }

    double monto = 0.0;
    std::cout << "Ingrese el monto a transferir: ";
    while (!(std::cin >> monto)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida. Ingrese el monto a transferir: ";
    }

    if (monto <= 0.0) {
        std::cout << "El monto debe ser mayor a cero." << std::endl;
        return;
    }

    const std::string cuentaOrigen = clienteOrigen->getCuenta()->getNumeroCuenta();
    const std::string cuentaDestino = clienteDestino->getCuenta()->getNumeroCuenta();

    if (clienteOrigen->transferir(*clienteDestino, monto)) {
        registrarTransaccion(clienteOrigen->getDui(),
                             cuentaOrigen,
                             "Transferencia Enviada",
                             monto,
                             "Completada");
        registrarTransaccion(clienteDestino->getDui(),
                             cuentaDestino,
                             "Transferencia Recibida",
                             monto,
                             "Completada");
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(2) << clienteOrigen->consultarSaldo();
        std::cout << "Transferencia realizada correctamente. Saldo actual: $" << ss.str()
                  << std::endl;
    } else {
        registrarTransaccion(clienteOrigen->getDui(),
                             cuentaOrigen,
                             "Transferencia Enviada",
                             monto,
                             "Fallida");
        std::cout << "No fue posible completar la transferencia. Verifique sus fondos disponibles."
                  << std::endl;
    }
}

void ControlSistema::registrarTransaccion(const std::string& dui,
                                          const std::string& numeroCuenta,
                                          const std::string& tipo,
                                          double monto,
                                          const std::string& estado) {
    Transaccion transaccion(
        generarIdTransaccion(), dui, numeroCuenta, tipo, monto, obtenerFechaHoraActual(), estado);

    if (!reporte_.guardarTransaccion(transaccion)) {
        std::cout << "Advertencia: no fue posible almacenar la transacción." << std::endl;
    }
}

std::string ControlSistema::generarIdTransaccion() const {
    static std::mt19937 generador(
        static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
    static std::uniform_int_distribution<int> distribucion(0, 999999);

    const auto ahora = std::chrono::system_clock::now();
    const auto marcaTiempo =
        std::chrono::duration_cast<std::chrono::milliseconds>(ahora.time_since_epoch()).count();

    std::ostringstream ss;
    ss << "TX-" << marcaTiempo << '-' << std::setw(6) << std::setfill('0') << distribucion(generador);
    return ss.str();
}

std::string ControlSistema::obtenerFechaHoraActual() const {
    const auto ahora = std::chrono::system_clock::now();
    const std::time_t tiempo = std::chrono::system_clock::to_time_t(ahora);
    std::tm tiempoLocal{};

    if (std::tm* ptr = std::localtime(&tiempo)) {
        tiempoLocal = *ptr;
    }

    std::ostringstream ss;
    ss << std::put_time(&tiempoLocal, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void ControlSistema::mostrarMenuPrincipal() {
    std::system("clear");
    std::cout << "=== SISTEMA BANCARIO ===" << std::endl;
    std::cout << "1. Iniciar sesion" << std::endl;
    std::cout << "2. Salir del sistema" << std::endl;
    std::cout << "Seleccione una opcion: ";

    int opcion = 0;
    std::cin >> opcion;

    if (opcion == 2) {
        CerrarSistema();
    }
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
