#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <functional>
#include "../Estructura/arbolB.hpp"
#include "../Roles/cliente.hpp"
#include "../Entidades/cuenta.hpp"
#include "../Entidades/transaccion.hpp"
/* LISTADO DE METODOS
guardarClientes
cargarClientes
guardarTransaccion
cargarTransaccionesCliente
Uno para las credenciales de cliente y otro para administrador
*/

class ArbolB;
class Cliente;
class Transaccion;
class Cuenta;

class Reporte{
  private:
   std::string carpeta = "data/";
  std::string nombreArchivo;
  std::ofstream archivoReporte;

   std::string encriptar(const std::string& texto);
    std::string desencriptar(const std::string& texto);

 public:
  Reporte(const string& nombreArchivo = "reporte_sistema.txt");

  void generarEncabezado(const string& titulo);
    void generarPiePagina();
    std::string obtenerFechaHoraActual();
    void generarSeparador(char caracter ='=', int longitud = 60);
    
  //Metodos principales de reportes
  bool generarReporteClientes(ArbolB& arbolCliente);
  bool generarReporteTransaccionesCliente(string& dui, ArbolB& arbolTransacciones);
  bool generarReporteCuentas(Arbol& arbolCliente);
  
  //Metodos para guardar la persistencia
  bool guardarClientes(ArbolB& arbolClientes);
  bool cargarClientes(ArbolB& arbolClientes);

  bool guardarTransacciones(Transaccion& transaccion);
  bool cargarTransaccionesClientes(string& dui, string& credencial);
  
  bool cargarCredenciales(ArbolB& arbolCredenciales);
  cliente ClienteDesdeLinea( string& linea);

  string getNombreArchivoTransacciones( string& dui);

  //Guardar las credenciales
  bool guardarCredencialesCliente(string& dui,string& password);
    bool guardarCredencialesAdmin( string& usuario, string& password);
    bool verificarCliente(string& dui,  string& password);
    bool verificarAdmin(string& usuario,  string& password);

 //Utilitarios
 bool abrirArchivo();
 void cerrarArchivo();
 bool estaAbierto();
 std::string getNombreArchivo();
 void setNombreArchivo(string& nombre);
 std::string getNombreArchivoTransacciones(std::string &dui);
};
//SEPARAR CREDENCIALES CON DATOS PER