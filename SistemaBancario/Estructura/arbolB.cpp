#include "arbolB.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <utility>

ArbolB::Nodo::Nodo(bool hoja) : esHoja(hoja) {
    claves.reserve(2 * kMinDegree - 1);
    valores.reserve(2 * kMinDegree - 1);
    hijos.reserve(2 * kMinDegree);
}

bool ArbolB::insertar(const Cliente& cliente) {
    const std::string& dui = cliente.getDui();

    if (Cliente* existente = buscarInterno(dui, raiz_.get()); existente != nullptr) {
        *existente = cliente;
        return false;
    }

    if (!raiz_) {
        raiz_ = std::make_unique<Nodo>(true);
        raiz_->claves.push_back(dui);
        raiz_->valores.push_back(cliente);
        cantidad_ = 1;
        return true;
    }

    if (raiz_->claves.size() == static_cast<std::size_t>(2 * kMinDegree - 1)) {
        auto nuevaRaiz = std::make_unique<Nodo>(false);
        nuevaRaiz->hijos.push_back(std::move(raiz_));
        raiz_ = std::move(nuevaRaiz);
        dividirHijo(raiz_.get(), 0);
    }

    insertarNoLleno(raiz_.get(), cliente);
    ++cantidad_;
    return true;
}

bool ArbolB::buscar(const std::string& dui, Cliente& resultado) const {
    const Cliente* encontrado = buscarInterno(dui, raiz_.get());
    if (!encontrado) {
        return false;
    }
    resultado = *encontrado;
    return true;
}

bool ArbolB::eliminar(const std::string& dui) {
    if (!raiz_) {
        return false;
    }

    if (!eliminarInterno(raiz_.get(), dui)) {
        return false;
    }

    --cantidad_;

    if (!raiz_->esHoja && raiz_->claves.empty()) {
        raiz_ = std::move(raiz_->hijos.front());
    } else if (raiz_->claves.empty()) {
        raiz_.reset();
    }

    return true;
}

bool ArbolB::estaVacio() const {
    return cantidad_ == 0;
}

std::size_t ArbolB::obtenerCantidad() const {
    return cantidad_;
}

void ArbolB::imprimir(std::ostream& salida) const {
    if (!raiz_) {
        salida << "Árbol vacío" << std::endl;
        return;
    }

    salida << std::left << std::setw(12) << "DUI" << std::setw(20) << "Nombre"
           << std::setw(20) << "Apellido" << std::setw(12) << "Estado"
           << std::setw(12) << "Saldo" << std::endl;
    salida << std::string(76, '-') << std::endl;

    recorrerInorden(raiz_.get(), [&salida](const Cliente& cliente) {
        double saldo = cliente.consultarSaldo();
        salida << std::left << std::setw(12) << cliente.getDui()
               << std::setw(20) << cliente.getNombre()
               << std::setw(20) << cliente.getApellido()
               << std::setw(12) << cliente.getEstado()
               << std::setw(12) << std::fixed << std::setprecision(2) << saldo
               << std::endl;
    });
}

void ArbolB::imprimirEnArchivo(std::ostream& archivo) const {
    imprimir(archivo);
}

std::vector<Cliente> ArbolB::obtenerClientes() const {
    std::vector<Cliente> resultado;
    resultado.reserve(cantidad_);
    recolectarInorden(raiz_.get(), resultado);
    return resultado;
}

void ArbolB::recorrer(const std::function<void(const Cliente&)>& accion) const {
    recorrerInorden(raiz_.get(), accion);
}

const Cliente* ArbolB::buscarInterno(const std::string& dui, const Nodo* nodo) const {
    if (!nodo) {
        return nullptr;
    }

    auto it = std::lower_bound(nodo->claves.begin(), nodo->claves.end(), dui);
    std::size_t indice = static_cast<std::size_t>(it - nodo->claves.begin());

    if (it != nodo->claves.end() && *it == dui) {
        return &nodo->valores[indice];
    }

    if (nodo->esHoja) {
        return nullptr;
    }

    return buscarInterno(dui, nodo->hijos[indice].get());
}

Cliente* ArbolB::buscarInterno(const std::string& dui, Nodo* nodo) {
    if (!nodo) {
        return nullptr;
    }

    auto it = std::lower_bound(nodo->claves.begin(), nodo->claves.end(), dui);
    std::size_t indice = static_cast<std::size_t>(it - nodo->claves.begin());

    if (it != nodo->claves.end() && *it == dui) {
        return &nodo->valores[indice];
    }

    if (nodo->esHoja) {
        return nullptr;
    }

    return buscarInterno(dui, nodo->hijos[indice].get());
}

void ArbolB::dividirHijo(Nodo* padre, std::size_t indice) {
    Nodo* hijo = padre->hijos[indice].get();
    auto derecho = std::make_unique<Nodo>(hijo->esHoja);

    const std::string claveMedio = hijo->claves[kMinDegree - 1];
    const Cliente valorMedio = hijo->valores[kMinDegree - 1];

    derecho->claves.insert(derecho->claves.end(), hijo->claves.begin() + kMinDegree, hijo->claves.end());
    derecho->valores.insert(derecho->valores.end(), hijo->valores.begin() + kMinDegree, hijo->valores.end());

    hijo->claves.resize(kMinDegree - 1);
    hijo->valores.resize(kMinDegree - 1);

    if (!hijo->esHoja) {
        std::size_t totalHijos = hijo->hijos.size();
        for (std::size_t i = kMinDegree; i < totalHijos; ++i) {
            derecho->hijos.push_back(std::move(hijo->hijos[i]));
        }
        hijo->hijos.resize(kMinDegree);
    }

    padre->claves.insert(padre->claves.begin() + indice, claveMedio);
    padre->valores.insert(padre->valores.begin() + indice, valorMedio);
    padre->hijos.insert(padre->hijos.begin() + indice + 1, std::move(derecho));
}

void ArbolB::insertarNoLleno(Nodo* nodo, const Cliente& cliente) {
    const std::string& clave = cliente.getDui();

    if (nodo->esHoja) {
        auto it = std::lower_bound(nodo->claves.begin(), nodo->claves.end(), clave);
        std::size_t indice = static_cast<std::size_t>(it - nodo->claves.begin());
        nodo->claves.insert(it, clave);
        nodo->valores.insert(nodo->valores.begin() + indice, cliente);
        return;
    }

    auto it = std::lower_bound(nodo->claves.begin(), nodo->claves.end(), clave);
    std::size_t indice = static_cast<std::size_t>(it - nodo->claves.begin());

    if (nodo->hijos[indice]->claves.size() == static_cast<std::size_t>(2 * kMinDegree - 1)) {
        dividirHijo(nodo, indice);

        if (clave > nodo->claves[indice]) {
            ++indice;
        } else if (clave == nodo->claves[indice]) {
            nodo->valores[indice] = cliente;
            return;
        }
    }

    insertarNoLleno(nodo->hijos[indice].get(), cliente);
}

bool ArbolB::eliminarInterno(Nodo* nodo, const std::string& dui) {
    auto it = std::lower_bound(nodo->claves.begin(), nodo->claves.end(), dui);
    std::size_t indice = static_cast<std::size_t>(it - nodo->claves.begin());

    if (it != nodo->claves.end() && *it == dui) {
        if (nodo->esHoja) {
            nodo->claves.erase(it);
            nodo->valores.erase(nodo->valores.begin() + indice);
            return true;
        }

        if (nodo->hijos[indice]->claves.size() >= static_cast<std::size_t>(kMinDegree)) {
            auto pred = obtenerPredecesor(nodo, indice);
            nodo->claves[indice] = pred.first;
            nodo->valores[indice] = pred.second;
            return eliminarInterno(nodo->hijos[indice].get(), pred.first);
        }

        if (nodo->hijos[indice + 1]->claves.size() >= static_cast<std::size_t>(kMinDegree)) {
            auto succ = obtenerSucesor(nodo, indice);
            nodo->claves[indice] = succ.first;
            nodo->valores[indice] = succ.second;
            return eliminarInterno(nodo->hijos[indice + 1].get(), succ.first);
        }

        fusionarHijos(nodo, indice);
        return eliminarInterno(nodo->hijos[indice].get(), dui);
    }

    if (nodo->esHoja) {
        return false;
    }

    bool ultimo = (indice == nodo->claves.size());

    if (nodo->hijos[indice]->claves.size() < static_cast<std::size_t>(kMinDegree)) {
        if (indice > 0 && nodo->hijos[indice - 1]->claves.size() >= static_cast<std::size_t>(kMinDegree)) {
            tomarDeIzquierda(nodo, indice);
        } else if (indice < nodo->hijos.size() - 1 &&
                   nodo->hijos[indice + 1]->claves.size() >= static_cast<std::size_t>(kMinDegree)) {
            tomarDeDerecha(nodo, indice);
        } else {
            if (indice < nodo->hijos.size() - 1) {
                fusionarHijos(nodo, indice);
            } else {
                fusionarHijos(nodo, indice - 1);
                --indice;
            }
        }
    }

    if (ultimo && indice > nodo->claves.size()) {
        indice = nodo->claves.size();
    }

    return eliminarInterno(nodo->hijos[indice].get(), dui);
}

void ArbolB::fusionarHijos(Nodo* nodo, std::size_t indice) {
    auto& izquierdo = nodo->hijos[indice];
    auto derecho = std::move(nodo->hijos[indice + 1]);

    izquierdo->claves.push_back(nodo->claves[indice]);
    izquierdo->valores.push_back(nodo->valores[indice]);

    izquierdo->claves.insert(izquierdo->claves.end(), derecho->claves.begin(), derecho->claves.end());
    izquierdo->valores.insert(izquierdo->valores.end(), derecho->valores.begin(), derecho->valores.end());

    if (!izquierdo->esHoja) {
        for (auto& hijo : derecho->hijos) {
            izquierdo->hijos.push_back(std::move(hijo));
        }
    }

    nodo->claves.erase(nodo->claves.begin() + indice);
    nodo->valores.erase(nodo->valores.begin() + indice);
    nodo->hijos.erase(nodo->hijos.begin() + indice + 1);
}

void ArbolB::tomarDeIzquierda(Nodo* nodo, std::size_t indice) {
    auto& hijo = nodo->hijos[indice];
    auto& izquierdo = nodo->hijos[indice - 1];

    hijo->claves.insert(hijo->claves.begin(), nodo->claves[indice - 1]);
    hijo->valores.insert(hijo->valores.begin(), nodo->valores[indice - 1]);

    if (!izquierdo->esHoja) {
        hijo->hijos.insert(hijo->hijos.begin(), std::move(izquierdo->hijos.back()));
        izquierdo->hijos.pop_back();
    }

    nodo->claves[indice - 1] = izquierdo->claves.back();
    nodo->valores[indice - 1] = izquierdo->valores.back();

    izquierdo->claves.pop_back();
    izquierdo->valores.pop_back();
}

void ArbolB::tomarDeDerecha(Nodo* nodo, std::size_t indice) {
    auto& hijo = nodo->hijos[indice];
    auto& derecho = nodo->hijos[indice + 1];

    hijo->claves.push_back(nodo->claves[indice]);
    hijo->valores.push_back(nodo->valores[indice]);

    if (!derecho->esHoja) {
        hijo->hijos.push_back(std::move(derecho->hijos.front()));
        derecho->hijos.erase(derecho->hijos.begin());
    }

    nodo->claves[indice] = derecho->claves.front();
    nodo->valores[indice] = derecho->valores.front();

    derecho->claves.erase(derecho->claves.begin());
    derecho->valores.erase(derecho->valores.begin());
}

std::pair<std::string, Cliente> ArbolB::obtenerPredecesor(Nodo* nodo, std::size_t indice) const {
    Nodo* actual = nodo->hijos[indice].get();
    while (!actual->esHoja) {
        actual = actual->hijos.back().get();
    }
    return {actual->claves.back(), actual->valores.back()};
}

std::pair<std::string, Cliente> ArbolB::obtenerSucesor(Nodo* nodo, std::size_t indice) const {
    Nodo* actual = nodo->hijos[indice + 1].get();
    while (!actual->esHoja) {
        actual = actual->hijos.front().get();
    }
    return {actual->claves.front(), actual->valores.front()};
}

void ArbolB::recorrerInorden(const Nodo* nodo, const std::function<void(const Cliente&)>& accion) const {
    if (!nodo) {
        return;
    }

    for (std::size_t i = 0; i < nodo->claves.size(); ++i) {
        if (!nodo->esHoja) {
            recorrerInorden(nodo->hijos[i].get(), accion);
        }
        accion(nodo->valores[i]);
    }

    if (!nodo->esHoja) {
        recorrerInorden(nodo->hijos.back().get(), accion);
    }
}

void ArbolB::recolectarInorden(const Nodo* nodo, std::vector<Cliente>& acumulador) const {
    recorrerInorden(nodo, [&acumulador](const Cliente& cliente) { acumulador.push_back(cliente); });
}
