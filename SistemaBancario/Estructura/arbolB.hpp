#pragma once

#include <functional>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "../Roles/cliente.hpp"

class ArbolB {
private:
    static constexpr int kMinDegree = 2;

    struct Nodo {
        bool esHoja;
        std::vector<std::string> claves;
        std::vector<Cliente> valores;
        std::vector<std::unique_ptr<Nodo>> hijos;

        explicit Nodo(bool hoja);
    };

    std::unique_ptr<Nodo> raiz_;
    std::size_t cantidad_ = 0;

    const Cliente* buscarInterno(const std::string& dui, const Nodo* nodo) const;
    Cliente* buscarInterno(const std::string& dui, Nodo* nodo);
    void dividirHijo(Nodo* padre, std::size_t indice);
    void insertarNoLleno(Nodo* nodo, const Cliente& cliente);
    bool eliminarInterno(Nodo* nodo, const std::string& dui);
    void fusionarHijos(Nodo* nodo, std::size_t indice);
    void tomarDeIzquierda(Nodo* nodo, std::size_t indice);
    void tomarDeDerecha(Nodo* nodo, std::size_t indice);
    std::pair<std::string, Cliente> obtenerPredecesor(Nodo* nodo, std::size_t indice) const;
    std::pair<std::string, Cliente> obtenerSucesor(Nodo* nodo, std::size_t indice) const;
    void recorrerInorden(const Nodo* nodo, const std::function<void(const Cliente&)>& accion) const;
    void recolectarInorden(const Nodo* nodo, std::vector<Cliente>& acumulador) const;

public:
    ArbolB() = default;

    bool insertar(const Cliente& cliente);
    bool buscar(const std::string& dui, Cliente& resultado) const;
    bool eliminar(const std::string& dui);
    bool estaVacio() const;
    std::size_t obtenerCantidad() const;

    void imprimir(std::ostream& salida) const;
    void imprimirEnArchivo(std::ostream& archivo) const;

    std::vector<Cliente> obtenerClientes() const;

    void recorrer(const std::function<void(const Cliente&)>& accion) const;
};
