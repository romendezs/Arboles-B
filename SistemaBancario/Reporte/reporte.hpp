#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "../Estructura/arbolB.hpp"
#include "../Entidades/transaccion.hpp"

class Reporte {
private:
    std::string nombreArchivo_;
    std::ofstream archivoReporte_;

    bool abrirArchivo(std::ios_base::openmode modo);
    void cerrarArchivo();
    std::string encriptar(const std::string& texto) const;
    std::string desencriptar(const std::string& texto) const;

    static std::string rutaClientes();
    static std::string rutaCredencialesClientes();
    static std::string rutaCredencialesAdmin();
    static std::string rutaTransacciones(const std::string& dui);

public:
    explicit Reporte(std::string nombreArchivo = {});
    ~Reporte();

    const std::string& obtenerRutaReporte() const;

    bool generarReporteClientes(const ArbolB& arbolClientes);

    bool guardarClientes(const ArbolB& arbolClientes) const;
    bool cargarClientes(ArbolB& arbolClientes) const;

    bool guardarTransaccion(const Transaccion& transaccion) const;
    bool cargarTransaccionesCliente(const std::string& dui,
                                    std::vector<Transaccion>& transacciones) const;

    bool guardarCredencialesCliente(const std::string& dui, const std::string& password) const;
    bool guardarCredencialesAdmin(const std::string& usuario, const std::string& password) const;
    bool verificarCliente(const std::string& dui, const std::string& password) const;
    bool verificarAdmin(const std::string& usuario, const std::string& password) const;
    bool eliminarCredencialesCliente(const std::string& dui) const;
};
