#include "arbolB.hpp"

#include <iomanip>
#include <iostream>

bool ArbolB::insertar(const Cliente& cliente) {
    const std::string& dui = cliente.getDui();
    auto [it, inserted] = clientes_.emplace(dui, cliente);
    if (!inserted) {
        it->second = cliente;
    }
    return inserted;
}

bool ArbolB::buscar(const std::string& dui, Cliente& resultado) const {
    auto it = clientes_.find(dui);
    if (it == clientes_.end()) {
        return false;
    }
    resultado = it->second;
    return true;
}

bool ArbolB::estaVacio() const {
    return clientes_.empty();
}

std::size_t ArbolB::obtenerCantidad() const {
    return clientes_.size();
}

void ArbolB::imprimir(std::ostream& salida) const {
    if (clientes_.empty()) {
        salida << "Árbol vacío" << std::endl;
        return;
    }

    salida << std::left << std::setw(12) << "DUI" << std::setw(20) << "Nombre"
           << std::setw(20) << "Apellido" << std::setw(12) << "Estado"
           << std::setw(12) << "Saldo" << std::endl;
    salida << std::string(76, '-') << std::endl;

    for (const auto& [dui, cliente] : clientes_) {
        double saldo = cliente.consultarSaldo();
        salida << std::left << std::setw(12) << dui
               << std::setw(20) << cliente.getNombre()
               << std::setw(20) << cliente.getApellido()
               << std::setw(12) << cliente.getEstado()
               << std::setw(12) << std::fixed << std::setprecision(2) << saldo
               << std::endl;
    }
}

void ArbolB::imprimirEnArchivo(std::ostream& archivo) const {
    imprimir(archivo);
}

std::vector<Cliente> ArbolB::obtenerClientes() const {
    std::vector<Cliente> resultado;
    resultado.reserve(clientes_.size());
    for (const auto& [_, cliente] : clientes_) {
        resultado.push_back(cliente);
    }
    return resultado;
}

void ArbolB::recorrer(const std::function<void(const Cliente&)>& accion) const {
    for (const auto& [_, cliente] : clientes_) {
        accion(cliente);
    }
}
