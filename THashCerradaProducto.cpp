#include "THashCerradaProducto.h"


THashCerradaProducto& THashCerradaProducto::operator=(const THashCerradaProducto& orig){
    if ( this != &orig ){
        totalColis = orig.totalColis;         
        nProductos = orig.nProductos;        
        nElementos = orig.nElementos;   
        maxColis = orig.maxColis;
    }
    
    return *this;
}
    
// Exploracion cuadratica
unsigned long THashCerradaProducto::exploracionCuadratica(unsigned long hash, int i){
    return (hash + i * i) % tamaTabla(); 
}

// Exploracion doble division
unsigned long THashCerradaProducto::exploracionDoble(unsigned long hash, int i){
    unsigned long hash1, hash2;
    hash1 = 1 + (hash % 5171);
    hash2 = 5093 - (hash % 5171) ;
    return  (hash1 + i * hash2) % tamaTabla();         
}

/**
 * @brief Inserta un dato en la tabla a partir de la clave
 * @param clave long Clave del dato para buscarlo en la tabla
 * @param dato T dato que queremos insertar
 * @return Devuelve el resultado de si se ha realizado correctamente la insercion
 */
bool THashCerradaProducto::insertar(unsigned long clave, const std::string &termino, Producto* dato) {
    int i = 0, colisiones = 0;
    auto hash = clave % tamaTabla();

    while (i < intentos && tabla[hash].marca == OCUPADO && tabla[hash].termino != termino) {
        hash = exploracionCuadratica(hash, i);
        //hash = exploracionDoble(hash ,i);
        colisiones++;
        totalColis++;
        i++;
    }
    
    if (i == intentos){ // Si llega al número máximo de colisiones
        return false;
    }
    
    if (colisiones > maxColis)
        maxColis = colisiones;

    if (tabla[hash].marca != OCUPADO) {
        tabla[hash].termino = termino;
        tabla[hash].marca = OCUPADO;
        nElementos++;
    } 
    
    tabla[hash].datos.push_back(dato);
    nProductos++;
    
    return true;
}

/**
 * @brief Busca un dato a partir de su clave y lo devuelve.
 * @param clave long Clave del dato para buscarlo en la tabla
 * @param dato T dato que queremos insertar
 * @return Devuelve si el vector del termino o en caso contrario vector vacio
 */
std::vector<Producto*> THashCerradaProducto::buscar(long int clave, const std::string &termino) {
    std::vector<Producto*> vectorVacio;
    auto hash = clave % tamaTabla();
    
    int i = 0;

    while (i < intentos && tabla[hash].marca == OCUPADO && tabla[hash].termino != termino) {
        hash = exploracionCuadratica(hash, i);
        //hash = exploracionDoble(hash ,i);
        ++i;
    }

    if (i == intentos)
        return vectorVacio;

    // Si encuentra el termino devuelve el vector
    if (tabla[hash].marca != LIBRE) {
        return tabla[hash].datos;
    }

    // Si no devuelve un vector vacio
    return vectorVacio;
}

/**
 * @brief Obtiene el tamaño de la tabla de dispersion
 * @return Devuelve el tamaño de la tabla de dispersion
 */
unsigned int THashCerradaProducto::tamaTabla() {
    return tabla.size();
}

/**
 * @brief Obtiene el numero de productos insertados en la tabla
 * @return Devuelve el numero de productos insertados en la tabla
 */
unsigned int THashCerradaProducto::numProductos() {
    return nProductos;
}

/**
 * @brief Obtiene el numero de terminos insertados en la tabla
 * @return Devuelve el numero de terminos insertados en la tabla
 */
unsigned int THashCerradaProducto::numTerminos() {
    return nElementos;
}

/**
 * @brief Devuelve el número máximo de colisiones que se han producido
 * en cualquier operación de inserción realizada sobre la tabla.
 * @return Devuelve el número máximo de colisiones
 */
unsigned int THashCerradaProducto::maxColisiones() {
    return maxColis;
}

/**
 * @brief Devuelve el promedio de colisiones por operación de inserción
 * realizada sobre la tabla
 * @return Devuelve de promedio de colisiones
 */
unsigned int THashCerradaProducto::promedioColisiones() {
    return totalColis / (numTerminos() * 1.0);
}

/**
 * @brief el factor de carga
 * @return Devuelve el factor de carga
 */
float THashCerradaProducto::factorCarga() {
    return nElementos / (tamaTabla() * 1.0);
}
