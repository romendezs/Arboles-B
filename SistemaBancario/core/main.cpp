#include <iostream>
#include "../Estructura/arbolB.cpp"
#include "../Roles/cliente.hpp"
#include "../Entidades/cuenta.hpp"

void testArbolB() {
    std::cout << "=== INICIANDO PRUEBAS DEL ÁRBOL B ===" << std::endl;
    
    // 1. Crear árbol
    ArbolB arbol;
    std::cout << "Árbol creado. ¿Está vacío? " << (arbol.estaVacio() ? "Sí" : "No") << std::endl;
    
    // 2. Crear clientes de prueba
    Cliente cliente1("12345678", "Juan", "Perez", "juan@email.com", "5551234", "Calle 123");
    Cliente cliente2("87654321", "Maria", "Lopez", "maria@email.com", "5555678", "Avenida 456");
    Cliente cliente3("11223344", "Carlos", "Gomez", "carlos@email.com", "5559999", "Plaza 789");
    
    // Crear cuentas
    Cuenta cuenta1("001-123456", "12345678", "AHORRO", 1000.0);
    Cuenta cuenta2("001-876543", "87654321", "CORRIENTE", 2000.0);
    Cuenta cuenta3("001-112233", "11223344", "AHORRO", 1500.0);
    
    cliente1.setCuenta(Cuenta*);
    cliente2.setCuenta(Cuenta*);
    cliente3.setCuenta(Cuenta*);
    
    // 3. Insertar clientes
    std::cout << "\n--- Insertando clientes ---" << std::endl;
    std::cout << "Insertar cliente 1: " << (arbol.Insertar(cliente1) ? "Éxito" : "Falló") << std::endl;
    std::cout << "Insertar cliente 2: " << (arbol.Insertar(cliente2) ? "Éxito" : "Falló") << std::endl;
    std::cout << "Insertar cliente 3: " << (arbol.Insertar(cliente3) ? "Éxito" : "Falló") << std::endl;
    
    // 4. Intentar insertar duplicado
    std::cout << "Insertar duplicado: " << (arbol.Insertar(cliente1) ? "Éxito" : "Falló (esperado)") << std::endl;
    
    // 5. Buscar clientes
    std::cout << "\n--- Buscando clientes ---" << std::endl;
    Cliente encontrado;
    
    if (arbol.buscar("12345678", encontrado)) {
        std::cout << "Cliente 12345678 encontrado: " << encontrado.getNombre() << std::endl;
    } else {
        std::cout << "Cliente 12345678 NO encontrado" << std::endl;
    }
    
    if (arbol.buscar("99999999", encontrado)) {
        std::cout << "Cliente 99999999 encontrado" << std::endl;
    } else {
        std::cout << "Cliente 99999999 NO encontrado (esperado)" << std::endl;
    }
    
    // 6. Mostrar estructura del árbol
    std::cout << "\n--- Estructura del árbol ---" << std::endl;
    arbol.imprimirArbolB();
    
    // 7. Mostrar cantidad de nodos
    std::cout << "Nodos en el árbol: " << arbol.obtenerCantidad() << std::endl;
    
    // 8. Probar operaciones bancarias
    std::cout << "\n--- Operaciones bancarias ---" << std::endl;
    if (arbol.buscar("12345678", encontrado)) {
        std::cout << "Saldo inicial: $" << encontrado.consultarSaldo() << std::endl;
        encontrado.depositar(500.0);
        std::cout << "Después de depositar $500: $" << encontrado.consultarSaldo() << std::endl;
        encontrado.retirar(200.0);
        std::cout << "Después de retirar $200: $" << encontrado.consultarSaldo() << std::endl;
    }
    
    std::cout << "\n=== PRUEBAS COMPLETADAS ===" << std::endl;
}

int main() {
    testArbolB();
    return 0;
}
