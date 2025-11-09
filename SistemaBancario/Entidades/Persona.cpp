#include "Persona.hpp"

#include <iostream>
#include <utility>

Persona::Persona()
    : dui_(), nombre_(), apellido_(), email_(), telefono_(), direccion_() {}

Persona::Persona(std::string dui,
                 std::string nombre,
                 std::string apellido,
                 std::string email,
                 std::string telefono,
                 std::string direccion)
    : dui_(std::move(dui)),
      nombre_(std::move(nombre)),
      apellido_(std::move(apellido)),
      email_(std::move(email)),
      telefono_(std::move(telefono)),
      direccion_(std::move(direccion)) {}

const std::string& Persona::getDui() const { return dui_; }
const std::string& Persona::getNombre() const { return nombre_; }
const std::string& Persona::getApellido() const { return apellido_; }
const std::string& Persona::getEmail() const { return email_; }
const std::string& Persona::getTelefono() const { return telefono_; }
const std::string& Persona::getDireccion() const { return direccion_; }

void Persona::setDui(const std::string& dui) { dui_ = dui; }
void Persona::setNombre(const std::string& nombre) { nombre_ = nombre; }
void Persona::setApellido(const std::string& apellido) { apellido_ = apellido; }
void Persona::setEmail(const std::string& email) { email_ = email; }
void Persona::setTelefono(const std::string& telefono) { telefono_ = telefono; }
void Persona::setDireccion(const std::string& direccion) { direccion_ = direccion; }

void Persona::mostrarInfo() const {
    std::cout << "DUI: " << dui_
              << "\nNombre: " << nombre_ << " " << apellido_
              << "\nEmail: " << email_
              << "\nTeléfono: " << telefono_
              << "\nDirección: " << direccion_ << std::endl;
}
