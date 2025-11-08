#include "Persona.hpp"
#include <string>

class administrador : public Persona {
private:
    std::string usuario;
    std::string fechaContratacion;

public:
    // Constructores
    administrador();
    administrador(std::string dui, std::string nombre, std::string apellido, 
                  std::string email, std::string telefono, std::string direccion,
                  std::string usuario);

    // Getters
    std::string getUsuario() const;
    std::string getFechaContratacion() const;

    // Setter
    void setUsuario(std::string usuario);


    // Sobrescribir método de Persona
    void mostrarInfo() const override;
};