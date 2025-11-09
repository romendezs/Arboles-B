#pragma once

#include <string>

class Cuenta {
private:
    std::string numeroCuenta_;
    std::string duiCliente_;
    std::string tipo_;
    double saldo_;
    double limiteSobregiro_;
    std::string fechaApertura_;
    std::string estado_;

public:
    Cuenta();
    Cuenta(std::string numeroCuenta,
           std::string duiCliente,
           std::string tipo,
           double saldoInicial = 0.0,
           double limiteSobregiro = 0.0);

    const std::string& getNumeroCuenta() const;
    const std::string& getDuiCliente() const;
    const std::string& getTipo() const;
    double getSaldo() const;
    double getLimiteSobregiro() const;
    const std::string& getFechaApertura() const;
    const std::string& getEstado() const;

    void setTipo(const std::string& tipo);
    void setLimiteSobregiro(double limite);
    void setEstado(const std::string& estado);

    bool depositar(double monto);
    bool retirar(double monto);
    bool transferir(Cuenta& cuentaDestino, double monto);

    bool tieneFondosSuficientes(double monto) const;
    bool estaActiva() const;

    void mostrarInfo() const;
};
