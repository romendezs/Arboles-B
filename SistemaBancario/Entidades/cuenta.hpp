#include <iostream>
#include <string>
/*Guardar cuenta en árbol*/
class Cuenta{
  public:
  Cuenta(int id = 0, int num = 0, int p = 0, std::string tip = "", 
           double sal = 0.0, bool act = true, int idClt = 0)
        : idCuenta(id), numeroCuenta(num), pin(p), tipo(tip),
          saldo(sal), activa(act), idCliente(idClt) {}
private:
int idCuenta;
    int numeroCuenta;  
    int pin;
    std::string tipo;
    double saldo;     
    bool activa;         
    int idCliente;
};
/* LISTADO DE METODOS
  -Constructor 
  -getters y setters
  -Depositar
  -Retirar 
  -Consultar --> Todo: saldo, transacciones....
  -Validación de credenciales(Debe de ser manejando archivos)
*/