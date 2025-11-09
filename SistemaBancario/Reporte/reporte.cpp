#include "reporte.hpp"

#include <array>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace fs = std::filesystem;

namespace {
std::string fechaHoraActual() {
    std::time_t ahora = std::time(nullptr);
    std::tm* tiempoLocal = std::localtime(&ahora);
    std::ostringstream ss;
    ss << std::put_time(tiempoLocal, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

fs::path baseDatos() {
    static const std::array<fs::path, 3> candidatos = {
        fs::path("data"),
        fs::path("SistemaBancario/data"),
        fs::path("../data")
    };

    for (const auto& candidato : candidatos) {
        if (fs::exists(candidato)) {
            return candidato;
        }
    }

    return candidatos.front();
}
}

Reporte::Reporte(std::string nombreArchivo)
    : nombreArchivo_(std::move(nombreArchivo)) {}

Reporte::~Reporte() {
    cerrarArchivo();
}

bool Reporte::abrirArchivo(std::ios_base::openmode modo) {
    cerrarArchivo();
    fs::create_directories(fs::path(nombreArchivo_).parent_path());
    archivoReporte_.open(nombreArchivo_, modo);
    return archivoReporte_.is_open();
}

void Reporte::cerrarArchivo() {
    if (archivoReporte_.is_open()) {
        archivoReporte_.close();
    }
}

std::string Reporte::encriptar(const std::string& texto) const {
    std::string resultado = texto;
    for (char& c : resultado) {
        c = static_cast<char>(c + 3);
    }
    return resultado;
}

std::string Reporte::desencriptar(const std::string& texto) const {
    std::string resultado = texto;
    for (char& c : resultado) {
        c = static_cast<char>(c - 3);
    }
    return resultado;
}

std::string Reporte::rutaClientes() {
    return (baseDatos() / "clientes" / "clientes.csv").string();
}

std::string Reporte::rutaCredencialesClientes() {
    return (baseDatos() / "clientes" / "credenciales_clientes.txt").string();
}

std::string Reporte::rutaCredencialesAdmin() {
    return (baseDatos() / "admin" / "credenciales_admin.txt").string();
}

std::string Reporte::rutaTransacciones(const std::string& dui) {
    return (baseDatos() / "transacciones" / ("transacciones-" + dui + ".csv")).string();
}

bool Reporte::generarReporteClientes(const ArbolB& arbolClientes) {
    if (!abrirArchivo(std::ios::out | std::ios::trunc)) {
        return false;
    }

    archivoReporte_ << "Reporte generado: " << fechaHoraActual() << '\n';
    archivoReporte_ << std::string(60, '=') << '\n';
    arbolClientes.imprimirEnArchivo(archivoReporte_);
    archivoReporte_ << std::string(60, '=') << '\n';

    cerrarArchivo();
    return true;
}

bool Reporte::guardarClientes(const ArbolB& arbolClientes) const {
    const fs::path ruta = rutaClientes();
    fs::create_directories(ruta.parent_path());

    std::ofstream archivo(ruta, std::ios::out | std::ios::trunc);
    if (!archivo.is_open()) {
        return false;
    }

    archivo << "dui,nombre,apellido,email,telefono,direccion,estado,fecha_registro" << '\n';
    arbolClientes.recorrer([&archivo](const Cliente& cliente) {
        archivo << cliente.getDui() << ','
                << cliente.getNombre() << ','
                << cliente.getApellido() << ','
                << cliente.getEmail() << ','
                << cliente.getTelefono() << ','
                << cliente.getDireccion() << ','
                << cliente.getEstado() << ','
                << cliente.getFechaRegistro() << '\n';
    });

    return true;
}

bool Reporte::cargarClientes(ArbolB& arbolClientes) const {
    const fs::path ruta = rutaClientes();
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        return false;
    }

    std::string linea;
    if (!std::getline(archivo, linea)) {
        return false;
    }

    bool cargado = false;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) {
            continue;
        }

        std::stringstream ss(linea);
        std::string campos[8];
        std::size_t indice = 0;
        while (indice < 8 && std::getline(ss, campos[indice], ',')) {
            ++indice;
        }
        if (indice != 8) {
            continue;
        }

        Cliente cliente(campos[0], campos[1], campos[2], campos[3], campos[4], campos[5], campos[6]);
        cliente.setFechaRegistro(campos[7]);
        arbolClientes.insertar(cliente);
        cargado = true;
    }

    return cargado;
}

bool Reporte::guardarTransaccion(const Transaccion& transaccion) const {
    const fs::path ruta = rutaTransacciones(transaccion.getDuiCliente());
    fs::create_directories(ruta.parent_path());

    std::ofstream archivo(ruta, std::ios::out | std::ios::app);
    if (!archivo.is_open()) {
        return false;
    }

    archivo << transaccion.aLineaCsv() << '\n';
    return true;
}

bool Reporte::cargarTransaccionesCliente(const std::string& dui,
                                         std::vector<Transaccion>& transacciones) const {
    const fs::path ruta = rutaTransacciones(dui);
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        return false;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) {
            continue;
        }
        try {
            transacciones.push_back(Transaccion::desdeLineaCsv(linea));
        } catch (const std::exception&) {
        }
    }

    return !transacciones.empty();
}

bool Reporte::guardarCredencialesCliente(const std::string& dui, const std::string& password) const {
    const fs::path ruta = rutaCredencialesClientes();
    fs::create_directories(ruta.parent_path());

    std::ofstream archivo(ruta, std::ios::out | std::ios::app);
    if (!archivo.is_open()) {
        return false;
    }

    archivo << encriptar(dui) << '|' << encriptar(password) << '\n';
    return true;
}

bool Reporte::guardarCredencialesAdmin(const std::string& usuario, const std::string& password) const {
    const fs::path ruta = rutaCredencialesAdmin();
    fs::create_directories(ruta.parent_path());

    std::ofstream archivo(ruta, std::ios::out | std::ios::app);
    if (!archivo.is_open()) {
        return false;
    }

    archivo << encriptar(usuario) << '|' << encriptar(password) << '\n';
    return true;
}

bool Reporte::verificarCliente(const std::string& dui, const std::string& password) const {
    const fs::path ruta = rutaCredencialesClientes();
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        return false;
    }

    const std::string objetivoDui = encriptar(dui);
    const std::string objetivoPass = encriptar(password);
    std::string linea;
    while (std::getline(archivo, linea)) {
        const std::size_t separador = linea.find('|');
        if (separador == std::string::npos) {
            continue;
        }
        const std::string duiGuardado = linea.substr(0, separador);
        const std::string passGuardado = linea.substr(separador + 1);
        if (duiGuardado == objetivoDui && passGuardado == objetivoPass) {
            return true;
        }
    }
    return false;
}

bool Reporte::verificarAdmin(const std::string& usuario, const std::string& password) const {
    const fs::path ruta = rutaCredencialesAdmin();
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        return false;
    }

    const std::string usuarioObjetivo = encriptar(usuario);
    const std::string passwordObjetivo = encriptar(password);
    std::string linea;
    while (std::getline(archivo, linea)) {
        const std::size_t separador = linea.find('|');
        if (separador == std::string::npos) {
            continue;
        }
        const std::string usuarioGuardado = linea.substr(0, separador);
        const std::string passGuardado = linea.substr(separador + 1);
        if (usuarioGuardado == usuarioObjetivo && passGuardado == passwordObjetivo) {
            return true;
        }
    }
    return false;
}
