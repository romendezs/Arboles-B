#include <string>

class Persona {
protected:
    std::string dui;
    std::string nombre;
    std::string apellido;
    std::string email;
    std::string telefono;
    std::string direccion;

public:
    // Constructores
    Persona();
    Persona(std::string dui, std::string nombre, std::string apellido, 
            std::string email, std::string telefono, std::string direccion);
    
    // Getters
    std::string getDui() const;
    std::string getNombre() const;
    std::string getApellido() const;
    std::string getEmail() const;
    std::string getTelefono() const;
    std::string getDireccion() const;
    
    // Setters
    void setDui(std::string dui);
    void setNombre(std::string nombre);
    void setApellido(std::string apellido);
    void setEmail(std::string email);
    void setTelefono(std::string telefono);
    void setDireccion(std::string direccion);
    
    // Métodos virtuales
     virtual void mostrarInfo() const;
    
};
/* LISTADO DE METODOS
  -Constructor 
  -getters y setters
  -Validación de credenciales
  -mostrarInfo() este se usa para mostrar un menú dependiendo
  si eres un Administrador o un usuario
*/