#include "Persona.hpp"
#include <iostream>

// Constructores
Persona::Persona() 
    : dui(""), nombre(""), apellido(""), email(""), telefono(""), direccion("") {}

Persona::Persona(std::string dui, std::string nombre, std::string apellido, 
                 std::string email, std::string telefono, std::string direccion)
    : dui(dui), nombre(nombre), apellido(apellido), email(email), 
      telefono(telefono), direccion(direccion) {}

// Getters
std::string Persona::getDui() const { return dui; }
std::string Persona::getNombre() const { return nombre; }
std::string Persona::getApellido() const { return apellido; }
std::string Persona::getEmail() const { return email; }
std::string Persona::getTelefono() const { return telefono; }
std::string Persona::getDireccion() const { return direccion; }

// Setters
void Persona::setDui(std::string dui) { this->dui = dui; }
void Persona::setNombre(std::string nombre) { this->nombre = nombre; }
void Persona::setApellido(std::string apellido) { this->apellido = apellido; }
void Persona::setEmail(std::string email) { this->email = email; }
void Persona::setTelefono(std::string telefono) { this->telefono = telefono; }
void Persona::setDireccion(std::string direccion) { this->direccion = direccion; }

void Persona::mostrarInfo() const {
    std::cout << "DUI: " << dui 
              << "\nNombre: " << nombre << " " << apellido
              << "\nEmail: " << email 
              << "\nTeléfono: " << telefono
              << "\nDirección: " << direccion << std::endl;
}