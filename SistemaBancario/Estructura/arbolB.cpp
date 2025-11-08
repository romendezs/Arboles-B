#include <iostream>
#include "../Roles/cliente.hpp"

#define ORDEN 2
typedef struct bnodo
{
 unsigned int clavesUsadas, nhijos; // Claves usadas en el nodo
 Cliente *claves[2 * ORDEN]; // Arreglo de claves del nodo
 struct bnodo *hijo[2*ORDEN]; // Arreglo de punteros a bnodo
 struct bnodo *padre; // Puntero a nodo padre
} NODO;

typedef NODO *pbnodo;

class ArbolB{

    private:

    void crearNodo(NODO **x)
{
 int i;
 (*x) = (NODO *)malloc(sizeof(NODO));
 (*x)->padre = NULL;
 (*x)->clavesUsadas = (*x)->nhijos = 0;
 for (i = 0; i < 2 * ORDEN; i++){
 (*x)->claves[i] = NULL;
 (*x)->hijo[i] = NULL;
 }
}

void insertarClave(Cliente &cliente, pbnodo *nodo, pbnodo hijo1, pbnodo hijo2, pbnodo *Entrada)
{
 pbnodo padre, nuevo, *listapunt;
 int i, j, lista[2 * ORDEN + 1];
 int salir = 0;
 // Insertar nueva clave en nodo:
 do
 {
 if (!(*nodo))
 {
 crearNodo(nodo);
 *Entrada = *nodo;
 }
 padre = (*nodo)->padre;

 if ((*nodo)->clavesUsadas == 2 * ORDEN) // overflow
 {
 // Nodo derecho
 crearNodo(&nuevo);

 // Construye lista ordenada:
 i = 0;
 while (i <= 2 * ORDEN -1 && *((*nodo)->claves[i]) < clave )
 {
 lista[i] = *((*nodo)->claves[i]);
 listapunt[i] = (*nodo)->hijo[i];
 i++;
 }
lista[i] = new Cliente(cliente);
 listapunt[i] = hijo1;
 listapunt[i+1] = hijo2;

 while (i < (*nodo)->clavesUsadas)
 {
 lista[i + 1] = *((*nodo)->claves[i]);
listapunt[i + 2] = (*nodo)->hijo[i + 1];
 i++;
 }

 // Dividir nodos:
 // Nodo izquierdo:
 (*nodo)->clavesUsadas = ORDEN;
 for (j = 0; j < (*nodo)->clavesUsadas; j++)
 {
 *((*nodo)->claves[j]) = lista[j];
 (*nodo)->hijo[j] = listapunt[j];
 }

 ((*nodo)->hijo[(*nodo)->clavesUsadas]) = listapunt[(*nodo)->clavesUsadas];
 
 // Nodo derecho:
 nuevo->clavesUsadas = 2 * ORDEN - (*nodo)->clavesUsadas;
 for (j = 0; j < nuevo->clavesUsadas; j++)
 {
 (nuevo->claves[j]) = (int *)malloc(sizeof(int));
 *(nuevo->claves[j]) = lista[j + (ORDEN) + 1];
 nuevo->hijo[j] = listapunt[j + (ORDEN - 1) + 1];
 }

nuevo->hijo[nuevo->clavesUsadas] = listapunt[2 * ORDEN];

 for (j = 0; j <= (*nodo)->clavesUsadas; j++)
     if ((*nodo)->hijo[j])
     ((*nodo)->hijo[j])->padre = *nodo;

 for (j = 0; j <= nuevo->clavesUsadas; j++)
      if (nuevo->hijo[j])
      (nuevo->hijo[j])->padre = nuevo;
 Cliente claveMedio = *lista[ORDEN];
 hijo1 = *nodo;
 hijo2 = nuevo;
 *nodo = padre;
cliente = claveMedio;

 } else {
 // Inserta nueva clave en su lugar:
 i = 0;
 if ((*nodo)->clavesUsadas > 0)
 {
 while (i < (*nodo)->clavesUsadas && *((*nodo)->claves[i]) < clave )
 i++;

 for (j = (*nodo)->clavesUsadas; j > i; j--)
     (*nodo)->claves[j] = (*nodo)->claves[j - 1];

 for (j = (*nodo)->clavesUsadas + 1; j > i; j--)
     (*nodo)->hijo[j] = (*nodo)->hijo[j - 1];
 }
 
 (*nodo)->claves[i] = new Cliente(cliente);
 (*nodo)->hijo[i] = hijo1;
 (*nodo)->hijo[i + 1] = hijo2;
 (*nodo)->clavesUsadas++;

 if (hijo1)
    hijo1->padre = *nodo;
 if (hijo2)
    hijo2->padre = *nodo;
 salir = 1;
 }
 } while (!salir);
}
bool buscarRec(NODO* nodo, const std::string& dui, Cliente& resultado) {
        if (nodo == nullptr) return false;
        
        int i = 0;
        while (i < nodo->clavesUsadas && nodo->claves[i]->getDui() < dui) {
            i++;
        }
        
        if (i < nodo->clavesUsadas && nodo->claves[i]->getDui() == dui) {
            resultado = *(nodo->claves[i]);
            return true;
        }
if (nodo->hijo[i] == nullptr) return false;
        
        return buscarRec(nodo->hijo[i], dui, resultado);
}

void imprimirRec(NODO* nodo, int nivel) {
        if (nodo == nullptr) return;
        
        for (int i = 0; i < nivel; i++) {
            std::cout << "  ";
        }
        
        std::cout << "Nivel " << nivel << ": [";
        for (int i = 0; i < nodo->clavesUsadas; i++) {
            std::cout << nodo->claves[i]->getDui();
            if (i < nodo->clavesUsadas - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
        
        for (int i = 0; i <= nodo->clavesUsadas; i++) {
            imprimirRec(nodo->hijo[i], nivel + 1);
        }
    }
    void imprimirEnArchivoRec(NODO* nodo, std::ofstream& archivo, int nivel) {
    if (nodo == nullptr) return;
    
    // Sangría para el nivel
    for (int i = 0; i < nivel; i++) {
        archivo << "  ";
    }
    
    // Imprimir claves del nodo
    archivo << "Nivel " << nivel << ": [";
    for (int i = 0; i < nodo->clavesUsadas; i++) {
        archivo << nodo->claves[i].getDui();
        if (i < nodo->clavesUsadas - 1) archivo << ", ";
    }
    archivo << "]" << endl;
    
    // Recorrer hijos
    for (int i = 0; i <= nodo->numClaves; i++) {
        imprimirEnArchivoRec(nodo->hijo[i], archivo, nivel + 1);
    }
}
   void destruirArbol(NODO* nodo) {
        if (nodo == nullptr) return;
        
        for (int i = 0; i <= nodo->clavesUsadas; i++) {
            destruirArbol(nodo->hijo[i]);
        }
        
        for (int i = 0; i < nodo->clavesUsadas; i++) {
            delete nodo->claves[i];
        }
        
        free(nodo);
    }
  int contarNodosRec(NODO* nodo) {
        if (nodo == nullptr) return 0;
        
        int contador = 1;
        for (int i = 0; i <= nodo->clavesUsadas; i++) {
            contador += contarNodosRec(nodo->hijo[i]);
        }
        
        return contador;
    }
 public:   
int Insertar(Cliente &cliente, pbnodo *Entrada)
{
   if (raiz == nullptr) {
            crearNodo(&raiz);
            raiz->claves[0] = new Cliente(cliente);
            raiz->clavesUsadas = 1;
            return true;
        }
        
        Cliente temp;
        if (buscar(cliente.getDui(), temp)) {
            return false;
        }
        
        insertarClave(cliente, &raiz, nullptr, nullptr);
        return true;
}
//Busca por numero de DUI
bool buscar(const std::string& dui, Cliente& resultado) {
        return buscarRec(raiz, dui, resultado);
 }
 
 // Métodos de utilidad
    bool estaVacio() const {
        return raiz == nullptr;
    }
void imprimirArbolB(pbnodo nodo)
{
 int i;
 if (nodo)
 {
 for (i = 0; i < nodo->clavesUsadas; i++)
 printf(" %d ", *(nodo->claves[i]));
 getch();
 printf("\n");
 for (i = 0; i < nodo->clavesUsadas + 1; i++)
 imprimirArbolB(nodo->hijo[i]);
 }
 return;
}
void imprimirArbolEnArchivo(ofstream& archivo) {
    if (raiz == nullptr) {
        archivo << "Árbol vacío" << endl;
        return;
    }
    
    archivo << "=== ESTRUCTURA DEL ÁRBOL B ===" << endl;
    imprimirEnArchivoRec(raiz, archivo, 0);
    archivo << "==============================" << endl;
}
int obtenerCantidad() {
        return contarNodosRec(raiz);
    }
};