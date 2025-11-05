#include <string>

class Persona {
public:
    // Constructor, métodos, etc.
    Persona(int id, const std::string& nombre, const std::string& usuario, const std::string& contra);

    // Getters
    int getId() const;
    std::string getNombre() const;


private:
    int idPersona;
    std::string nombre;
    std::string apellido;
    std::string telefono;
    std::string usuario;
    std::string contra; 
};

/* LISTADO DE METODOS
  -Constructor 
  -getters y setters
  -Validación de credenciales
  -mostrarInfo() este se usa para mostrar un menú dependiendo
  si eres un Administrador o un usuario
*/