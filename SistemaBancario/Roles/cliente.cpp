#include "cliente.hpp"

#include <iostream>
#include <utility>

#include "../core/util_fecha.hpp"

Cliente::Cliente()
    : Persona(), estado_("ACTIVO"), fechaRegistro_(util::fechaActual()), cuenta_(nullptr) {}

Cliente::Cliente(std::string dui,
                 std::string nombre,
                 std::string apellido,
                 std::string email,
                 std::string telefono,
                 std::string direccion,
                 std::string estado)
    : Persona(std::move(dui),
              std::move(nombre),
              std::move(apellido),
              std::move(email),
              std::move(telefono),
              std::move(direccion)),
      estado_(std::move(estado)),
      fechaRegistro_(util::fechaActual()),
      cuenta_(nullptr) {}

const std::string& Cliente::getEstado() const { return estado_; }
const std::string& Cliente::getFechaRegistro() const { return fechaRegistro_; }
std::shared_ptr<Cuenta> Cliente::getCuenta() const { return cuenta_; }

void Cliente::setEstado(const std::string& estado) { estado_ = estado; }
void Cliente::setFechaRegistro(const std::string& fechaRegistro) {
    fechaRegistro_ = fechaRegistro;
}
void Cliente::setCuenta(std::shared_ptr<Cuenta> cuenta) { cuenta_ = std::move(cuenta); }

void Cliente::mostrarInfo() const {
    Persona::mostrarInfo();
    std::cout << "Estado: " << estado_
              << "\nFecha Registro: " << fechaRegistro_ << std::endl;
    if (cuenta_) {
        std::cout << "--- Cuenta asociada ---" << std::endl;
        cuenta_->mostrarInfo();
    }
}

void Cliente::activar() { estado_ = "ACTIVO"; }
void Cliente::desactivar() { estado_ = "INACTIVO"; }
void Cliente::bloquear() { estado_ = "BLOQUEADO"; }

bool Cliente::estaActivo() const { return estado_ == "ACTIVO"; }

bool Cliente::depositar(double monto) {
    return cuenta_ != nullptr && cuenta_->depositar(monto);
}

bool Cliente::retirar(double monto) {
    return cuenta_ != nullptr && cuenta_->retirar(monto);
}

bool Cliente::transferir(Cliente& clienteDestino, double monto) {
    if (cuenta_ == nullptr || clienteDestino.getCuenta() == nullptr) {
        return false;
    }
    return cuenta_->transferir(*clienteDestino.getCuenta(), monto);
}

double Cliente::consultarSaldo() const {
    return cuenta_ != nullptr ? cuenta_->getSaldo() : 0.0;
}

bool Cliente::operator<(const Cliente& otro) const {
    return getDui() < otro.getDui();
}
