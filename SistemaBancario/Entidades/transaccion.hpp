#include <iostream>
#include <string>

class Transaccion {
private:
    std::string id;
    std::string duiCliente;
    std::string numeroCuenta;
    std::string tipo;
    double monto;
    std::string fecha;
    std::string estado;

public:
    Transaccion();
    Transaccion(std::string id, std::string duiCliente, std::string numeroCuenta,
                std::string tipo, double monto);
    
    // Getters...
    void setEstado(std::string estado);
   
    static std::string generarId();
    static std::string obtenerFechaActual();
    void mostrarInfo() const;
};
/* LISTADO DE METODOS
  -Constructor 
  -getters y setters
  -Validación 
  -mostrarInfo() este se usa para mostrar un menú dependiendo
  si eres un Administrador o un usuario
*/