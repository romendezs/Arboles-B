#include "Transaccion.hpp"
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

// Constructor por defecto
Transaccion::Transaccion() 
    : id(""), cliente(nullptr), numeroCuenta(""), tipo(""), 
      monto(0.0), fecha(""), estado("Pendiente") {}

// Constructor con parámetros
Transaccion::Transaccion(string id, Cliente* cliente, string numeroCuenta,
                         string tipo, double monto)
    : id(id), cliente(cliente), numeroCuenta(numeroCuenta), 
      tipo(tipo), monto(monto), fecha(obtenerFechaActual()), estado("Pendiente") {}

// Setters
void Transaccion::setId(string nuevoId) {
    id = nuevoId;
}

void Transaccion::setCliente(Cliente* nuevoCliente) {
    cliente = nuevoCliente;
}

void Transaccion::setNumeroCuenta(string nuevoNumero) {
    numeroCuenta = nuevoNumero;
}

void Transaccion::setTipo(string nuevoTipo) {
    tipo = nuevoTipo;
}

void Transaccion::setMonto(double nuevoMonto) {
    monto = nuevoMonto;
}

void Transaccion::setFecha(string nuevaFecha) {
    fecha = nuevaFecha;
}

void Transaccion::setEstado(string nuevoEstado) {
    estado = nuevoEstado;
}

// Getters
string Transaccion::getId() const {
    return id;
}

Cliente* Transaccion::getCliente() const {
    return cliente;
}

string Transaccion::getNumeroCuenta() const {
    return numeroCuenta;
}

string Transaccion::getTipo() const {
    return tipo;
}

double Transaccion::getMonto() const {
    return monto;
}

string Transaccion::getFecha() const {
    return fecha;
}

string Transaccion::getEstado() const {
    return estado;
}

// Para compatibilidad con código existente
string Transaccion::getDuiCliente() const {
    if (cliente != nullptr) {
        return cliente->getDui();  
    }
    return "";
}

// Generar ID único para transacción
string Transaccion::generarId() {
    static int contador = 1000;
    return "TRAN" + to_string(contador++);
}

// Obtener fecha actual
string Transaccion::obtenerFechaActual() {
    time_t ahora = time(0);
    tm* tiempoLocal = localtime(&ahora);
    
    stringstream ss;
    ss << setw(2) << setfill('0') << tiempoLocal->tm_mday << "/"
       << setw(2) << setfill('0') << (tiempoLocal->tm_mon + 1) << "/"
       << (tiempoLocal->tm_year + 1900);
    
    return ss.str();
}

// Mostrar información de la transacción
void Transaccion::mostrarInfo() const {
    cout << "=== INFORMACION DE TRANSACCION ===" << endl;
    cout << "ID: " << id << endl;
    if (cliente != nullptr) {
        cout << "Cliente: " << cliente->getNombre() << endl;
        cout << "DUI: " << cliente->getDui() << endl;
    }
    cout << "Cuenta: " << numeroCuenta << endl;
    cout << "Tipo: " << tipo << endl;
    cout << "Monto: $" << monto << endl;
    cout << "Fecha: " << fecha << endl;
    cout << "Estado: " << estado << endl;
    cout << "=================================" << endl;
}

// Validar si la transacción es válida
bool Transaccion::esTransaccionValida() const {
    if(!id.empty() && 
           cliente != nullptr && 
           !numeroCuenta.empty() && 
           !tipo.empty() && 
           monto > 0.0 && 
           !fecha.empty();){

            return true;
           }
    
    
    return false;
}
