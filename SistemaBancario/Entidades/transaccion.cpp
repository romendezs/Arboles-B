#include "Transaccion.hpp"
#include <iostream>
#include <ctime>
#include <random>

// Constructor por defecto
Transaccion::Transaccion() 
    : id(""), duiCliente(""), numeroCuenta(""), tipo(""), monto(0.0), 
      fecha(""), estado("PENDIENTE") {}

// Constructor con parámetros
Transaccion::Transaccion(std::string id, std::string duiCliente, std::string numeroCuenta,
                         std::string tipo, double monto)
    : id(id), duiCliente(duiCliente), numeroCuenta(numeroCuenta), 
      tipo(tipo), monto(monto), estado("EXITOSA") {
    
    // Establecer fecha actual
    fecha = obtenerFechaActual();
}

// Getters (si los necesitas en el .cpp)
std::string Transaccion::getId() const { return id; }
std::string Transaccion::getDuiCliente() const { return duiCliente; }
std::string Transaccion::getNumeroCuenta() const { return numeroCuenta; }
std::string Transaccion::getTipo() const { return tipo; }
double Transaccion::getMonto() const { return monto; }
std::string Transaccion::getFecha() const { return fecha; }
std::string Transaccion::getEstado() const { return estado; }

// Setters
void Transaccion::setEstado(std::string estado) {
    this->estado = estado;
}

// Generar ID único para transacción
std::string Transaccion::generarId() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 9999);
    
    return "T" + std::to_string(dis(gen));
}

// Obtener fecha actual
std::string Transaccion::obtenerFechaActual() {
    time_t ahora = time(nullptr);
    tm* tiempoLocal = localtime(&ahora);
    
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tiempoLocal);
    return std::string(buffer);
}

// Mostrar información de la transacción
void Transaccion::mostrarInfo() const {
    std::cout << "ID: " << id
              << "\nDUI Cliente: " << duiCliente
              << "\nCuenta: " << numeroCuenta
              << "\nTipo: " << tipo
              << "\nMonto: $" << monto
              << "\nFecha: " << fecha
              << "\nEstado: " << estado << std::endl;
}
