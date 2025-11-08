#define CUENTA_HPP

#include <string>

class Cuenta {
private:
    std::string numeroCuenta;
    std::string duiCliente;  // Cambié de dniCliente a duiCliente para consistencia
    std::string tipo;
    double saldo;
    double limiteSobregiro;
    std::string fechaApertura;
    std::string estado;

public:
    Cuenta();
    Cuenta(std::string numeroCuenta, std::string duiCliente, std::string tipo, 
           double saldoInicial = 0.0, double limiteSobregiro = 0.0);
    
    // Getters
    std::string getNumeroCuenta() const;
    std::string getDuiCliente() const;
    std::string getTipo() const;
    double getSaldo() const;
    double getLimiteSobregiro() const;
    std::string getFechaApertura() const;
    std::string getEstado() const;
    
    // Setters
    void setTipo(std::string tipo);
    void setLimiteSobregiro(double limite);
    void setEstado(std::string estado);
    
    // Operaciones bancarias
    bool depositar(double monto);
    bool retirar(double monto);
    bool transferir(Cuenta& cuentaDestino, double monto);
    
    // Validaciones
    bool tieneFondosSuficientes(double monto) const;
    bool estaActiva() const;
    
    // Mostrar información
    void mostrarInfo() const;
    
    // Operadores para árbol B (CORREGIDOS)
    bool operator<(const Cuenta& otro) const;
    bool operator==(const Cuenta& otro) const;
};

/* LISTADO DE METODOS
  -Constructor 
  -getters y setters
  -Depositar
  -Retirar 
  -Consultar --> Todo: saldo, transacciones....
  -Validación de credenciales(Debe de ser manejando archivos)
*/