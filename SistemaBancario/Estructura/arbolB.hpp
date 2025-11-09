#pragma once

#include <functional>
#include <map>
#include <ostream>
#include <string>
#include <vector>

#include "../Roles/cliente.hpp"

class ArbolB {
private:
    std::map<std::string, Cliente> clientes_;

public:
    ArbolB() = default;

    bool insertar(const Cliente& cliente);
    bool buscar(const std::string& dui, Cliente& resultado) const;
    bool estaVacio() const;
    std::size_t obtenerCantidad() const;

    void imprimir(std::ostream& salida) const;
    void imprimirEnArchivo(std::ostream& archivo) const;

    std::vector<Cliente> obtenerClientes() const;

    void recorrer(const std::function<void(const Cliente&)>& accion) const;
};
