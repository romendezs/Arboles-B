#include "cuenta.hpp"
#include <iostream>
#include <ctime>

// Constructor por defecto
Cuenta::Cuenta() 
    : numeroCuenta(""), duiCliente(""), tipo("AHORRO"), saldo(0.0), 
      limiteSobregiro(0.0), fechaApertura(""), estado("ACTIVA") {}

// Constructor con parámetros
Cuenta::Cuenta(std::string numeroCuenta, std::string duiCliente, std::string tipo, 
               double saldoInicial, double limiteSobregiro)
    : numeroCuenta(numeroCuenta), duiCliente(duiCliente), tipo(tipo), 
      saldo(saldoInicial), limiteSobregiro(limiteSobregiro), estado("ACTIVA") {
    
    // Establecer fecha de apertura actual
    time_t ahora = time(nullptr);
    tm* tiempoLocal = localtime(&ahora);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", tiempoLocal);
    fechaApertura = buffer;
}

// Getters
std::string Cuenta::getNumeroCuenta() const { return numeroCuenta; }
std::string Cuenta::getDuiCliente() const { return duiCliente; }
std::string Cuenta::getTipo() const { return tipo; }
double Cuenta::getSaldo() const { return saldo; }
double Cuenta::getLimiteSobregiro() const { return limiteSobregiro; }
std::string Cuenta::getFechaApertura() const { return fechaApertura; }
std::string Cuenta::getEstado() const { return estado; }

// Setters
void Cuenta::setTipo(std::string tipo) { this->tipo = tipo; }
void Cuenta::setLimiteSobregiro(double limite) { this->limiteSobregiro = limite; }
void Cuenta::setEstado(std::string estado) { this->estado = estado; }

// Operaciones bancarias
bool Cuenta::depositar(double monto) {
    if (monto <= 0) return false;
    saldo += monto;
    return true;
}

bool Cuenta::retirar(double monto) {
    if (monto <= 0 || !tieneFondosSuficientes(monto) || !estaActiva()) {
        return false;
    }
    saldo -= monto;
    return true;
}

bool Cuenta::transferir(Cuenta& cuentaDestino, double monto) {
    if (!retirar(monto)) return false;
    return cuentaDestino.depositar(monto);
}

// Validaciones
bool Cuenta::tieneFondosSuficientes(double monto) const {
    return (saldo + limiteSobregiro) >= monto;
}

bool Cuenta::estaActiva() const {
    return estado == "ACTIVA";
}

// Mostrar información
void Cuenta::mostrarInfo() const {
    std::cout << "Número de Cuenta: " << numeroCuenta
              << "\nDUI Cliente: " << duiCliente
              << "\nTipo: " << tipo
              << "\nSaldo: $" << saldo
              << "\nLímite Sobregiro: $" << limiteSobregiro
              << "\nFecha Apertura: " << fechaApertura
              << "\nEstado: " << estado << std::endl;
}

// Operadores para árbol B
bool Cuenta::operator<(const Cuenta& otro) const {
    return numeroCuenta < otro.numeroCuenta;  // Ordenar por número de cuenta
}

bool Cuenta::operator==(const Cuenta& otro) const {
    return numeroCuenta == otro.numeroCuenta;  // Comparar por número de cuenta
}