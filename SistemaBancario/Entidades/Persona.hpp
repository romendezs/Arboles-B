#pragma once

#include <string>

class Persona {
protected:
    std::string dui_;
    std::string nombre_;
    std::string apellido_;
    std::string email_;
    std::string telefono_;
    std::string direccion_;

public:
    Persona();
    Persona(std::string dui,
            std::string nombre,
            std::string apellido,
            std::string email,
            std::string telefono,
            std::string direccion);

    // Getters
    const std::string& getDui() const;
    const std::string& getNombre() const;
    const std::string& getApellido() const;
    const std::string& getEmail() const;
    const std::string& getTelefono() const;
    const std::string& getDireccion() const;

    // Setters
    void setDui(const std::string& dui);
    void setNombre(const std::string& nombre);
    void setApellido(const std::string& apellido);
    void setEmail(const std::string& email);
    void setTelefono(const std::string& telefono);
    void setDireccion(const std::string& direccion);

    virtual void mostrarInfo() const;
    virtual ~Persona() = default;
};
