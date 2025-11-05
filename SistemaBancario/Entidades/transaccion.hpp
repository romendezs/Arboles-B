#include <iostream>
#include <string>

// Estructura de Transaccion 
struct Transaccion {
    int idTransaccion;
    std::string tipo;
    std::string fecha;
    double monto;        
    int cuentaOrigen;    
    int cuentaDestino;    
    std::string descripcion;
    double saldoResultante;
    //Es un constructor que inicializa todo 
    Transaccion(int id = 0, std::string tip = "", std::string fec = "",
                double mon = 0.0, int ctOrigen = 0, int ctDestino = 0,
                std::string = "", double salRes = 0.0)
        : idTransaccion(id), tipo(tip), fecha(fec), monto(mon),
          cuentaOrigen(ctOrigen), cuentaDestino(ctDestino),
          descripcion(descripcion), saldoResultante(salRes) {}
};
/* LISTADO DE METODOS
  -Constructor 
  -getters y setters
  -Validación 
  -mostrarInfo() este se usa para mostrar un menú dependiendo
  si eres un Administrador o un usuario
*/