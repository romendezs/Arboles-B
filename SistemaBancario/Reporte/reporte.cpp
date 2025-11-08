/* Genera reporte de transacciones, de cuentas, de clientes*/
#include "../Reporte/reporte.hpp"

using namespace std;

// Constructor
Reporte::Reporte(const string& nombreArchivo) : nombreArchivo(nombreArchivo) {
}

// Métodos utilitarios
bool Reporte::abrirArchivo() {
    archivoReporte.open(nombreArchivo, ios::out | ios::app);
    return archivoReporte.is_open();
}

void Reporte::cerrarArchivo() {
    if (archivoReporte.is_open()) {
        archivoReporte.close();
    }
}

bool Reporte::estaAbierto(){
    return archivoReporte.is_open();
}

string Reporte::getNombreArchivo(){
    return nombreArchivo;
}

void Reporte::setNombreArchivo(string& nombre) {
    nombreArchivo = nombre;
}

string Reporte::obtenerFechaHoraActual() {
    time_t ahora = time(nullptr);
    tm* tiempoLocal = localtime(&ahora);
    
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tiempoLocal);
    return string(buffer);
}

void Reporte::generarSeparador(char caracter, int longitud) {
    if (archivoReporte.is_open()) {
        archivoReporte << string(longitud, caracter) << endl;
    }
}

void Reporte::generarEncabezado(const string& titulo) {
    if (!archivoReporte.is_open()) return;

    archivoReporte << endl;
    generarSeparador('=');
    archivoReporte << "\t" << titulo << endl;
    archivoReporte << "Fecha: " << obtenerFechaHoraActual() << endl;
    generarSeparador('=');
    archivoReporte << endl;
}

void Reporte::generarPiePagina() {
    if (!archivoReporte.is_open()) return;

    archivoReporte << endl;
    generarSeparador('-');
    archivoReporte << "Fin del reporte" << endl;
    generarSeparador('-');
    archivoReporte << endl;
}

string Reporte::encriptar(const string& texto) {
    string resultado = texto;
    for (char& c : resultado) {
        c = c + 3; 
    }
    return resultado;
}

string Reporte::desencriptar(const string& texto) {
    string resultado = texto;
    for (char& c : resultado) {
        c = c - 3; // Revertir desplazamiento
    }
    return resultado;
}
bool Reporte::generarReporteClientes(ArbolB& arbolCliente) {
   
    if (!abrirArchivo()) return false;
    
    generarEncabezado("REPORTE DE CLIENTES");
   arbolCuentas.imprimirArbolEnArchivo(archivoReporte);
    generarPiePagina();
    cerrarArchivo();
    return true;
}
 bool Reporte::generarReporteCuentas(ArbolB& arbolCuentas){
    if(!abrirArchivo())return false;

    generarEncabezado("CUENTAS BANCARIAS");
    archivoReporte << "ID CUENTA\t\tDUI CLIENTE\t\tTIPO\t\tSALDO" << endl;
    generarSeparador('-', 80);
    arbolCuentas.imprimirArbolEnArchivo(archivoReporte);

    generarPiePagina();
    cerrarArchivo();
    return true;
 }
bool Reporte::generarReporteTransaccionesCliente(string& dui, ArbolB& transaccionCliente){

    if(!abrirArchivo()) return false;
    if(dui.empty())return false;
   
    if(!cargarTransaccionesCliente(dui, arbolTransacciones)){
     generarEncabezado("REPORTE DE TRANSACCIONES");
     transaccionCliente.imprimirArbolEnArchivo(archivoReporte);
    generarPiePagina();
    cerrarArchivo();
    return true;
    }
    archivoReporte << "ID TRANSACCIÓN\tTIPO\t\tMONTO\t\tFECHA" << endl;
    generarSeparador('-', 80);

    generarPiePagina();
    cerrarArchivo();
    return true;
}

bool Reporte::guardarClientes(ArbolB &arbolCliente){
  ofstream archivo("data/clientes/clientes.txt");

  if(!archivo.is_open()) {
    printf("Error al abrir el archivo");
    return false;
  }
  generarEncabezado("CLIENTES");

  bool resultado = arbolCliente.guardarTodo(archivo);

  archivo.close();
  return resultado;
}

bool Reporte::cargarClientes(ArbolB &arbolCliente){
    ifstream archivo("data/clientes/clientes.txt");

    if(!abrirArchivo()){
          printf("No existe cliente.txt se creara uno nuevo");
          return  false;
    }

    //Verifica que es archivo de clientes
    string linea;
    getline(archivo, linea);

    if(linea != "CLIENTES"){
        printf("El archivo no es de clientes");
        archivo.close;
        return false;
    }
    //Leer cliente por cliente
    int cont = 0;
    while(getline(archivo, linea)){
        if(!linea.empty()){
            Cliente* cliente= crearClienteDesdeLinea(linea);
            if(cliente != nullptr){
                arbolCliente.insertar(*cliente);
                cont++;    
            }
        }
    }
    archivo.close();
    printf("Se cargaron los clientes");
    return cont>0;
}

Cliente* Reporte::crearClienteDesdeLinea( string& linea) {
    // Formato: dni,nombre,apellido,email,telefono,direccion
    string datos[6];
    int indice = 0;
    string dato = "";
    
    for (char c : linea) {
        if (c == ',') {
            if (indice < 6) {
                datos[indice] = dato;
                indice++;
            }
            dato = "";
        } else {
            dato += c;
        }
    }
    
    // Último dato
    if (indice < 6 && !dato.empty()) {
        datos[indice] = dato;
    }
    
    // Verificar que tenemos todos los datos
    if (indice >= 5) {
        return new Cliente(datos[0], datos[1], datos[2], datos[3], datos[4], datos[5]);
    }
    
    return nullptr;
}
//TRANSACCION
string Reporte::getNombreArchivoTransacciones( string& dui){
    return "data/transacciones/transacciones-" + dui + ".txt";
}

bool Reporte::guardarTransacciones( Transaccion& transaccion) {
    string dui = transaccion.getDuiCliente();
    string nombreArchivo = getNombreArchivoTransacciones(dui);
    
    ofstream archivo(nombreArchivo, ios::app | ios::out); // ios::app para agregar al final
    
    if (!archivo.is_open()) {
        printf("No se pudo abrir el archivo");
        return false;
    }
    
    // Guardar transacción en formato simple
    archivo << transaccion.getId() << ","
            << transaccion.getDuiCliente() << ","
            <<transaccion.getNumeroCuenta()<< ","
            << transaccion.getTipo() << ","
            << transaccion.getMonto() << ","
            << transaccion.getFecha() << ","
            <<transaccion.getEstado()<< endl;
    
    archivo.close();
    return true;
}

// Cargar todas las transacciones de un cliente específico
bool Reporte::cargarTransaccionesCliente(string& dui, ArbolB &arbolTransacciones) {
    string nombreArchivo = getNombreArchivoTransacciones(dui);
    
    ifstream archivo(nombreArchivo);
    
    if (!archivo.is_open()) {
        cout << "No hay transacciones para el cliente: " << dui << endl;
        return false;
    }
    
    cout << "=== TRANSACCIONES CLIENTE: " << dui << " ===" << endl;
    
    string linea;
    int contador = 0;
    
    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            // Mostrar transacción
            //
            //
            //
            cout << linea << endl;
            contador++;
        }
    }
    
    archivo.close();
    cout << "Total transacciones: " << contador << endl;
    return contador > 0;
}

//Verifica las credenciales del admin
bool Reporte::verificarAdmin(string& usuario, const string& password){
    ifstream archivo("data/admin/credenciales_admin.txt");

    if (!archivo.is_open()) return false;

    string linea;
    while(getline(archivo, linea)){
        size_t separador = linea.find('|');
        if(separador != string::npos){
            string userGuardado = desencriptar(linea.substr(0, separador));
            string passGuardado = desencriptar(linea.substr(separador+1));
         if (userGuardado==usuario && passGuardado ==password){
            archivo.close();
            return true;
         }
        }
    }
    archivo.close();
    return false;
}
//Verificar las credenciales de clientes
bool Reporte::verificarCliente(string &dui, string& password){
    ifstream archivo("data/clientes/credenciales_clientes.txt");

    if(!archivo.is_open()) return false;

    string linea;
    while(getline(archivo, linea)){
        size_t separador = linea.find('|');
        if(separador != string::npos){
            string idGuardado = desencriptar(linea.substr(0,separador));
            string passGuardado = desencriptar(linea.substr(separador +1));

            if(idGuardado == id && passGuardado == password){
                archivo.close();
                return false;
            }
        }
    }
}
//Guardar las credenciales de Admin
bool Reporte::guardarCredencialesAdmin(string& usuario, string& password){
    ofstream archivo(credenciales_admin.txt);

    if(!archivo.is_open()) return false;

    archivo<< encriptor(usuario) <<"|" <<encriptar(password)<< endl;
    archivo.close();
    return true;
}
//Guardar las credenciales de cliente
bool Reporte::guardarCredencialesCliente(string &dui, string& password){
    ofstream archivo("data/clientes/credenciales_clientes.txt");

      if (!archivo.is_open()) return false;

    archivo << encriptar(dui) << "|" << encriptar(password) << endl;
    archivo.close();
    return true;
}