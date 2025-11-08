/*Implementación de la clase cliente.hpp 
  Generar reporte de las transaciones 
  Hacer un depostio
  sacar dinero
*/

//VALIDACIONES
#include "cliente.hpp"
#include <iostream>
#include <ctime>

// Constructores
Cliente::Cliente() 
    : Persona(), estado("ACTIVO"), fechaRegistro("") , cuenta(nullptr){}

Cliente::Cliente(std::string dui, std::string nombre, std::string apellido, 
                 std::string email, std::string telefono, std::string direccion,
                 std::string estado)
    : Persona(dui, nombre, apellido, email, telefono, direccion), 
      estado(estado), cuenta(nullptr) {
    
    // Establecer fecha de registro actual
    time_t ahora = time(nullptr);
    tm* tiempoLocal = localtime(&ahora);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", tiempoLocal);
    fechaRegistro = buffer;
}

// Getters
std::string Cliente::getEstado() const { return estado; }
std::string Cliente::getFechaRegistro() const { return fechaRegistro; }
Cuenta* Cliente::getCuenta()const {return cuenta};
//Setters
void Cliente::setEstado(std::string estado) { this->estado = estado; }
void Cliente::setFechaRegistro(std::string fechaRegistro) { this->fechaRegistro = fechaRegistro; }
void Cliente::setCuenta(Cuenta *cuenta){this->cuenta = cuenta; }

// Métodos de estado
void Cliente::activar() { estado = "ACTIVO"; }
void Cliente::desactivar() { estado = "INACTIVO"; }
void Cliente::bloquear() { estado = "BLOQUEADO"; }
bool Cliente::estaActivo() const { return estado == "ACTIVO"; }

void Cliente::mostrarInfo() const {
    Persona::mostrarInfo();
    std::cout << "Estado: " << estado
              << "\nFecha Registro: " << fechaRegistro << std::endl;
}
//Operaciones bancarias
bool Cliente::depositar(double monto){
  if(!estaActivo || cuenta== nullptr) return false;
  return cuenta->depositar(monto);
}

bool Cliente::retirar(double monto) {
    if (!estaActivo() || cuenta == nullptr) return false;
    return cuenta->retirar(monto);
}

bool Cliente::transferir(Cliente& clienteDestino, double monto) {
    if (!estaActivo() || cuenta == nullptr || 
        !clienteDestino.estaActivo() || clienteDestino.getCuenta() == nullptr) {
        return false;
    }
    return cuenta->transferir(*(clienteDestino.getCuenta()), monto);
}

double Cliente::consultarSaldo() const {
    if (cuenta == nullptr) return 0.0;
    return cuenta->getSaldo();
}

bool Cliente::operator<(const Cliente& otro) const {
    return dui < otro.dui;  // Ordenar por DUI
}

bool Cliente::operator==(const Cliente& otro) const {
    return dui == otro.dui;  // Comparar por DUI
}

bool Cliente::operator>(const Cliente& otro) const {
    return dui > otro.dui;  // Ordenar por DUI
}