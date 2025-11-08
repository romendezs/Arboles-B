#include "Persona.hpp"
#include <string>

class Administrador : public Persona {
private:
    std::string usuario;
    std::string fechaContratacion;
    std::string departamento;

public:
    // Constructores
    Administrador();
    Administrador(std::string dni, std::string nombre, std::string apellido, 
                  std::string email, std::string telefono, std::string direccion,
                  std::string usuario, std::string departamento = "SISTEMAS");

    // Getters
    std::string getUsuario() const;
    std::string getFechaContratacion() const;
    std::string getDepartamento() const;

    // Setters
    void setUsuario(std::string usuario);
    void setDepartamento(std::string departamento);

    // Sobrescribir método de Persona
    void mostrarInfo() const override;
};