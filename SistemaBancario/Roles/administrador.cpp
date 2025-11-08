#include "administrador.hpp"
#include <iostream>
#include <ctime>

Administrador::Administrador() 
    : Persona(), usuario(""), fechaContratacion(""), departamento("SISTEMAS") {
}

Administrador::Administrador(std::string dni, std::string nombre, std::string apellido, 
                           std::string email, std::string telefono, std::string direccion,
                           std::string usuario, std::string departamento)
    : Persona(dni, nombre, apellido, email, telefono, direccion),
      usuario(usuario), departamento(departamento) {
    
    // Establecer fecha de contratación actual
    time_t ahora = time(nullptr);
    tm* tiempoLocal = localtime(&ahora);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", tiempoLocal);
    fechaContratacion = buffer;
}

// Getters
std::string Administrador::getUsuario() const {
    return usuario;
}

std::string Administrador::getFechaContratacion() const {
    return fechaContratacion;
}

std::string Administrador::getDepartamento() const {
    return departamento;
}

// Setters
void Administrador::setUsuario(std::string usuario) {
    this->usuario = usuario;
}

void Administrador::setDepartamento(std::string departamento) {
    this->departamento = departamento;
}

void Administrador::mostrarInfo() const {
    Persona::mostrarInfo();
    std::cout << "Usuario: " << usuario
              << "\nDepartamento: " << departamento
              << "\nFecha Contratación: " << fechaContratacion << std::endl;
}
