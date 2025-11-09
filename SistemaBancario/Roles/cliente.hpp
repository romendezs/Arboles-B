#pragma once

#include <memory>
#include <string>

#include "../Entidades/Persona.hpp"
#include "../Entidades/cuenta.hpp"

class Cliente : public Persona {
private:
    std::string estado_;
    std::string fechaRegistro_;
    std::shared_ptr<Cuenta> cuenta_;

public:
    Cliente();
    Cliente(std::string dui,
            std::string nombre,
            std::string apellido,
            std::string email,
            std::string telefono,
            std::string direccion,
            std::string estado = "ACTIVO");

    const std::string& getEstado() const;
    const std::string& getFechaRegistro() const;
    std::shared_ptr<Cuenta> getCuenta() const;

    void setEstado(const std::string& estado);
    void setFechaRegistro(const std::string& fechaRegistro);
    void setCuenta(std::shared_ptr<Cuenta> cuenta);

    void mostrarInfo() const override;

    void activar();
    void desactivar();
    void bloquear();
    bool estaActivo() const;

    bool depositar(double monto);
    bool retirar(double monto);
    bool transferir(Cliente& clienteDestino, double monto);
    double consultarSaldo() const;

    bool operator<(const Cliente& otro) const;
};
