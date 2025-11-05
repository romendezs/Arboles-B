#include <iostream>

const int GRADO_MINIMO = 2; //2
const int MAX_CLAVES = 2*GRADO_MINIMO -1; //3
const int GRADO = 2* GRADO_MINIMO; //4


//Arbol B, Base
typedef struct bnodo{
     int clavesUsadas, nhijos; //Claves usadas en el nodo
    int *claves[GRADO]; //Arreglo de claves del nodo
    struct bnodo *hijo[GRADO]; //Arreglo de punteros a bnodo
    struct nodo *padre;//Puntero a nodo padre
}bNODO;

typedef bNODO *pbnodo;

/* LISTADO DE METODOS
 insertar
 buscar
 eliminar

 Recorridos
*/