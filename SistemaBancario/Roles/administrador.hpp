#pragma once

#include <string>

#include "../Entidades/Persona.hpp"

class Administrador : public Persona {
private:
    std::string usuario_;
    std::string fechaContratacion_;
    std::string departamento_;

public:
    Administrador();
    Administrador(std::string dui,
                  std::string nombre,
                  std::string apellido,
                  std::string email,
                  std::string telefono,
                  std::string direccion,
                  std::string usuario,
                  std::string departamento = "SISTEMAS");

    const std::string& getUsuario() const;
    const std::string& getFechaContratacion() const;
    const std::string& getDepartamento() const;

    void setUsuario(const std::string& usuario);
    void setDepartamento(const std::string& departamento);

    void mostrarInfo() const override;
};
