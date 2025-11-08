#include <iostream>
#include <string>
#include <ctime>
#include "../Entidades/Persona.hpp"
#include "../Roles/cliente.hpp"

class cliente : public Persona {
private:
    std::string estado;
    std::string usuario;
    std::string fechaRegistro;
    Cuenta* cuenta;

public:
    Cliente();
    Cliente(std::string dui, std::string nombre, std::string apellido, 
            std::string email, std::string telefono, std::string direccion,std::string estado = "ACTIVO");
    
   //gets
    std::string getUsuario() const;
    std::string getFechaRegistro() const;
    Cuenta* getCuenta()const;
//sets
    void setUsuario(std::string usuario);
    void setCuenta(Cuenta* cuenta);

    //mostrar info
    void mostrarInfo() const override;
    //estados
    void activar();
    void desactivar();
    void bloquear();
    bool estaActivo() const; 

    //operaciones
     bool depositar(double monto);
    bool retirar(double monto);
    bool transferir(Cliente& clienteDestino, double monto);
    double consultarSaldo() const;

    // Operadores para el árbol B
    bool operator<(const Cliente& otro);
    bool operator==(const Cliente& otro);
    bool operator>(const Cliente& otro);
};
/* LISTADO DE METODOS
  -Constructor 
  -getters y setters
  -Validación de credenciales
  -mostrarInfo() este se usa para mostrar un menú dependiendo
  si eres un Administrador o un usuario
*/