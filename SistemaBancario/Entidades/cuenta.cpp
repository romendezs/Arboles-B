#include "cuenta.hpp"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>

namespace {
std::string fechaActual() {
    std::time_t ahora = std::time(nullptr);
    std::tm* tiempoLocal = std::localtime(&ahora);
    std::ostringstream ss;
    ss << std::put_time(tiempoLocal, "%Y-%m-%d");
    return ss.str();
}
}  // namespace

Cuenta::Cuenta()
    : numeroCuenta_(),
      duiCliente_(),
      tipo_("AHORRO"),
      saldo_(0.0),
      limiteSobregiro_(0.0),
      fechaApertura_(fechaActual()),
      estado_("ACTIVA") {}

Cuenta::Cuenta(std::string numeroCuenta,
               std::string duiCliente,
               std::string tipo,
               double saldoInicial,
               double limiteSobregiro)
    : numeroCuenta_(std::move(numeroCuenta)),
      duiCliente_(std::move(duiCliente)),
      tipo_(std::move(tipo)),
      saldo_(saldoInicial),
      limiteSobregiro_(limiteSobregiro),
      fechaApertura_(fechaActual()),
      estado_("ACTIVA") {}

const std::string& Cuenta::getNumeroCuenta() const { return numeroCuenta_; }
const std::string& Cuenta::getDuiCliente() const { return duiCliente_; }
const std::string& Cuenta::getTipo() const { return tipo_; }
double Cuenta::getSaldo() const { return saldo_; }
double Cuenta::getLimiteSobregiro() const { return limiteSobregiro_; }
const std::string& Cuenta::getFechaApertura() const { return fechaApertura_; }
const std::string& Cuenta::getEstado() const { return estado_; }

void Cuenta::setTipo(const std::string& tipo) { tipo_ = tipo; }
void Cuenta::setLimiteSobregiro(double limite) { limiteSobregiro_ = limite; }
void Cuenta::setEstado(const std::string& estado) { estado_ = estado; }

bool Cuenta::depositar(double monto) {
    if (monto <= 0.0 || !estaActiva()) {
        return false;
    }
    saldo_ += monto;
    return true;
}

bool Cuenta::retirar(double monto) {
    if (monto <= 0.0 || !estaActiva() || !tieneFondosSuficientes(monto)) {
        return false;
    }
    saldo_ -= monto;
    return true;
}

bool Cuenta::transferir(Cuenta& cuentaDestino, double monto) {
    if (!retirar(monto)) {
        return false;
    }
    return cuentaDestino.depositar(monto);
}

bool Cuenta::tieneFondosSuficientes(double monto) const {
    return (saldo_ + limiteSobregiro_) >= monto;
}

bool Cuenta::estaActiva() const {
    return estado_ == "ACTIVA";
}

void Cuenta::mostrarInfo() const {
    std::cout << "Número de Cuenta: " << numeroCuenta_
              << "\nDUI Cliente: " << duiCliente_
              << "\nTipo: " << tipo_
              << "\nSaldo: $" << saldo_
              << "\nLímite Sobregiro: $" << limiteSobregiro_
              << "\nFecha Apertura: " << fechaApertura_
              << "\nEstado: " << estado_ << std::endl;
}
