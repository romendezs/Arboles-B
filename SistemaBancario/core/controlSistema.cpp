#include "controlSistema.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

// Constructor
ControlSistema::ControlSistema() {
    arbolClientes = new ArbolB();  // Solo inicializamos el árbol de clientes
    sistemaActivo = false;
    usuarioActual = "";
    esAdministrador = false;
}

// Iniciar el sistema
void ControlSistema::IniciarSistema() {
    sistemaActivo = true;
    cout << "=== SISTEMA BANCARIO INICIADO ===" << endl;
    cout << "Arbol B de Clientes cargado" << endl << endl;
}

// Cerrar el sistema
void ControlSistema::CerrarSistema() {
    sistemaActivo = false;
    cout << "=== SISTEMA BANCARIO CERRADO ===" << endl;
}

// Método principal de ejecución
void ControlSistema::Ejecutar() {
    IniciarSistema();
    
    while (sistemaActivo) {
        if (!hayUsuarioLogueado()) {
            mostrarMenuPrincipal();
            if (!validarUsuario()) {
                continue;
            }
        }
        
        // Usuario válido - mostrar menu según tipo
        if (esAdministrador) {
            menuAdmin();
        } else {
            menuCliente();
        }
    }
    
    CerrarSistema();
}

// Validar usuario 
bool ControlSistema::validarUsuario() {
    string usuario, password;
    
    cout << "=== INICIO DE SESION ===" << endl;
    cout << "Usuario: ";
    cin >> usuario;
    cout << "Password: ";
    cin >> password;
    
    // Validación simple - puedes conectar esto con el árbol después
    if (usuario == "admin" && password == "admin") {
        usuarioActual = usuario;
        esAdministrador = true;
        cout << "Bienvenido Administrador!" << endl;
    } else if (usuario == "cliente" && password == "cliente") {
        usuarioActual = usuario;
        esAdministrador = false;
        cout << "Bienvenido Cliente!" << endl;
    } else {
        // Podrías buscar en el árbol de clientes aquí
        cout << "Error: Credenciales incorrectas." << endl;
        pausarPantalla();
        return false;
    }
    
    pausarPantalla();
    return true;
}

// Menú para clientes (operaciones básicas)
void ControlSistema::menuCliente() {
    int opcion;
    
    do {
        system("cls");
        cout << "=== MENU CLIENTE ===" << endl;
        cout << "Usuario: " << usuarioActual << endl;
        cout << "1. Consultar mis datos" << endl;
        cout << "2. Realizar transaccion" << endl;
        cout << "3. Ver historial" << endl;
        cout << "4. Cerrar sesion" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                cout << "Consultando datos del cliente..." << endl;
                // arbolClientes->buscar(usuarioActual);
                break;
            case 2:
                cout << "Realizando transaccion..." << endl;
                break;
            case 3:
                cout << "Mostrando historial..." << endl;
                break;
            case 4:
                cerrarSesion();
                break;
            default:
                cout << "Opcion invalida." << endl;
        }
        
        if (opcion != 4) {
            pausarPantalla();
        }
        
    } while (hayUsuarioLogueado() && !esAdministrador);
}

// Menú para administradores (gestión del árbol B)
void ControlSistema::menuAdmin() {
    int opcion;
    
    do {
        system("cls");
        cout << "=== MENU ADMINISTRADOR ===" << endl;
        cout << "Usuario: " << usuarioActual << endl;
        cout << "1. Gestionar Clientes (Arbol B)" << endl;
        cout << "2. Buscar Cliente" << endl;
        cout << "3. Mostrar Reportes" << endl;
        cout << "4. Operaciones del Arbol" << endl;
        cout << "5. Cerrar sesion" << endl;
        cout << "6. Salir del sistema" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        
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
                cerrarSesion();
                break;
            case 6:
                CerrarSistema();
                break;
            default:
                cout << "Opcion invalida." << endl;
        }
        
    } while (hayUsuarioLogueado() && esAdministrador && opcion != 5 && opcion != 6);
}

// Gestión de clientes usando el árbol B
void ControlSistema::gestionarClientes() {
    int opcion;
    
    do {
        system("cls");
        cout << "=== GESTION DE CLIENTES ===" << endl;
        cout << "1. Insertar cliente" << endl;
        cout << "2. Eliminar cliente" << endl;
        cout << "3. Mostrar todos los clientes" << endl;
        cout << "4. Volver al menu anterior" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                cout << "Insertando cliente en el arbol B..." << endl;
                // arbolClientes->insertar(nuevoCliente);
                break;
            case 2:
                cout << "Eliminando cliente del arbol B..." << endl;
                // arbolClientes->eliminar(clienteId);
                break;
            case 3:
                cout << "Mostrando clientes del arbol B..." << endl;
                // arbolClientes->recorrer();
                break;
            case 4:
                return;
            default:
                cout << "Opcion invalida." << endl;
        }
        
        pausarPantalla();
    } while (opcion != 4);
}

// Buscar cliente en el árbol B
void ControlSistema::buscarCliente() {
    string criterio;
    cout << "=== BUSCAR CLIENTE ===" << endl;
    cout << "Ingrese ID o nombre del cliente: ";
    cin >> criterio;
    
    cout << "Buscando cliente en el arbol B..." << endl;
    // bool encontrado = arbolClientes->buscar(criterio);
    // if (encontrado) { ... } else { ... }
    
    pausarPantalla();
}

// Mostrar reportes del árbol
void ControlSistema::mostrarReportes() {
    cout << "=== REPORTES DEL ARBOL B ===" << endl;
    // cout << "Total clientes: " << arbolClientes->contarNodos() << endl;
    // cout << "Altura del arbol: " << arbolClientes->obtenerAltura() << endl;
    // arbolClientes->mostrarEstadisticas();
    
    pausarPantalla();
}

// Operaciones específicas del árbol B
void ControlSistema::operacionesArbol() {
    cout << "=== OPERACIONES DEL ARBOL B ===" << endl;
    cout << "Mostrando estructura del arbol de clientes..." << endl;
    // arbolClientes->mostrarEstructura();
    
    pausarPantalla();
}

// Métodos auxiliares (se mantienen igual)
void ControlSistema::mostrarMenuPrincipal() {
    system("cls");
    cout << "=== SISTEMA BANCARIO ===" << endl;
    cout << "1. Iniciar sesion" << endl;
    cout << "2. Salir del sistema" << endl;
    cout << "Seleccione una opcion: ";
    
    int opcion;
    cin >> opcion;
    
    if (opcion == 2) {
        CerrarSistema();
    }
}

void ControlSistema::cerrarSesion() {
    cout << "Cerrando sesion de " << usuarioActual << "..." << endl;
    usuarioActual = "";
    esAdministrador = false;
    pausarPantalla();
}

bool ControlSistema::hayUsuarioLogueado() {
    return !usuarioActual.empty();
}

void ControlSistema::pausarPantalla() {
    cout << endl << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}