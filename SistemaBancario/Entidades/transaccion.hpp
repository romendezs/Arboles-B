#pragma once
#include <iostream>
#include <string>
#include "Cliente.hpp" 

class Transaccion {
private:
    std::string id;
    Cliente* cliente;       
    std::string numeroCuenta;
    std::string tipo;        // "Deposito", "Retiro", "Transferencia"
    double monto;
    std::string fecha;
    std::string estado;      // "Pendiente", "Completada", "Rechazada"

public:
    // Constructores
    Transaccion();
    Transaccion(std::string id, Cliente* cliente, std::string numeroCuenta,
                std::string tipo, double monto);
    
    // Setters
    void setId(std::string nuevoId);
    void setCliente(Cliente* nuevoCliente);
    void setNumeroCuenta(std::string nuevoNumero);
    void setTipo(std::string nuevoTipo);
    void setMonto(double nuevoMonto);
    void setFecha(std::string nuevaFecha);
    void setEstado(std::string nuevoEstado);
    
    // Getters
    std::string getId() const;
    Cliente* getCliente() const;
    std::string getNumeroCuenta() const;
    std::string getTipo() const;
    double getMonto() const;
    std::string getFecha() const;
    std::string getEstado() const;
    
    // Métodos estáticos
    static std::string generarId();
    static std::string obtenerFechaActual();
    
    // Métodos de utilidad
    void mostrarInfo() const;
    bool esTransaccionValida() const;
    std::string getDuiCliente() const;  
};
/* LISTADO DE METODOS
  -Constructor 
  -getters y setters
  -Validación 
  -mostrarInfo() este se usa para mostrar un menú dependiendo
  si eres un Administrador o un usuario
*/