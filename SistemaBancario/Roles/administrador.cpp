#include "administrador.hpp"

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

Administrador::Administrador()
    : Persona(),
      usuario_(),
      fechaContratacion_(fechaActual()),
      departamento_("SISTEMAS") {}

Administrador::Administrador(std::string dui,
                             std::string nombre,
                             std::string apellido,
                             std::string email,
                             std::string telefono,
                             std::string direccion,
                             std::string usuario,
                             std::string departamento)
    : Persona(std::move(dui),
              std::move(nombre),
              std::move(apellido),
              std::move(email),
              std::move(telefono),
              std::move(direccion)),
      usuario_(std::move(usuario)),
      fechaContratacion_(fechaActual()),
      departamento_(std::move(departamento)) {}

const std::string& Administrador::getUsuario() const { return usuario_; }
const std::string& Administrador::getFechaContratacion() const { return fechaContratacion_; }
const std::string& Administrador::getDepartamento() const { return departamento_; }

void Administrador::setUsuario(const std::string& usuario) { usuario_ = usuario; }
void Administrador::setDepartamento(const std::string& departamento) { departamento_ = departamento; }

void Administrador::mostrarInfo() const {
    Persona::mostrarInfo();
    std::cout << "Usuario: " << usuario_
              << "\nDepartamento: " << departamento_
              << "\nFecha Contratación: " << fechaContratacion_ << std::endl;
}
