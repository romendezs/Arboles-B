#include "transaccion.hpp"

#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace {
constexpr char kSeparador = ',';
}

Transaccion::Transaccion()
    : id_(),
      duiCliente_(),
      numeroCuenta_(),
      tipo_(),
      monto_(0.0),
      fecha_(),
      estado_("Pendiente") {}

Transaccion::Transaccion(std::string id,
                         std::string duiCliente,
                         std::string numeroCuenta,
                         std::string tipo,
                         double monto,
                         std::string fecha,
                         std::string estado)
    : id_(std::move(id)),
      duiCliente_(std::move(duiCliente)),
      numeroCuenta_(std::move(numeroCuenta)),
      tipo_(std::move(tipo)),
      monto_(monto),
      fecha_(std::move(fecha)),
      estado_(std::move(estado)) {}

const std::string& Transaccion::getId() const { return id_; }
const std::string& Transaccion::getDuiCliente() const { return duiCliente_; }
const std::string& Transaccion::getNumeroCuenta() const { return numeroCuenta_; }
const std::string& Transaccion::getTipo() const { return tipo_; }
double Transaccion::getMonto() const { return monto_; }
const std::string& Transaccion::getFecha() const { return fecha_; }
const std::string& Transaccion::getEstado() const { return estado_; }

std::string Transaccion::aLineaCsv() const {
    std::ostringstream ss;
    ss << id_ << kSeparador
       << duiCliente_ << kSeparador
       << numeroCuenta_ << kSeparador
       << tipo_ << kSeparador
       << std::fixed << std::setprecision(2) << monto_ << kSeparador
       << fecha_ << kSeparador
       << estado_;
    return ss.str();
}

Transaccion Transaccion::desdeLineaCsv(const std::string& linea) {
    std::istringstream ss(linea);
    std::string campo;
    std::string datos[7];
    std::size_t indice = 0;

    while (std::getline(ss, campo, kSeparador) && indice < 7) {
        datos[indice++] = std::move(campo);
    }

    if (indice != 7) {
        throw std::runtime_error("Línea de transacción inválida: " + linea);
    }

    double monto = std::stod(datos[4]);
    return Transaccion(datos[0], datos[1], datos[2], datos[3], monto, datos[5], datos[6]);
}
