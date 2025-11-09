#pragma once

#include <string>

class Transaccion {
private:
    std::string id_;
    std::string duiCliente_;
    std::string numeroCuenta_;
    std::string tipo_;
    double monto_;
    std::string fecha_;
    std::string estado_;

public:
    Transaccion();
    Transaccion(std::string id,
                std::string duiCliente,
                std::string numeroCuenta,
                std::string tipo,
                double monto,
                std::string fecha,
                std::string estado = "Completada");

    const std::string& getId() const;
    const std::string& getDuiCliente() const;
    const std::string& getNumeroCuenta() const;
    const std::string& getTipo() const;
    double getMonto() const;
    const std::string& getFecha() const;
    const std::string& getEstado() const;

    std::string aLineaCsv() const;
    static Transaccion desdeLineaCsv(const std::string& linea);
};
