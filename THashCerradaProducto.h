/* 
 * File:   THashProducto.h
 * Author: Javier Serrano Casas
 * Date:   25 de noviembre de 2018
 */

#ifndef THASHCERRADAPRODUCTO_H
#define THASHCERRADAPRODUCTO_H

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include "Producto.h"

/* Posibles estados de una posición en la tabla*/
enum Marcado {
    LIBRE,
    OCUPADO
};

class Entrada {
public:
    long int clave;
    std::string termino;
    Marcado marca;
    std::vector<Producto*> datos;

    Entrada() : marca(LIBRE), clave(-1), termino(""), datos() {}
    Entrada(Marcado m, long int c, std::string t) 
    : marca(m), clave(c), datos(), termino(t) {}
    Entrada& operator=(const Entrada& orig){
        if (this != &orig) { 
            marca = orig.marca; 
            clave = orig.clave; 
            termino = orig.termino;
            datos = orig.datos;
        }
        return *this;
    }
};

class THashCerradaProducto {
private:  
    const int intentos;     // Número de intentos permitidos para insertar en la tabla
    int maxColis;           // Número maximo de colisiones producidas en una inserción
    int totalColis;         // Colisiones totales producidas en la inserción
    int nProductos;         // Número de productos en la tabla
    int nElementos;         // Número de elementos en la tabla
    
public:
    THashCerradaProducto() : tabla(0, Entrada()), intentos(15), 
            nElementos(0), maxColis(0), totalColis(0), nProductos(0) {}
    THashCerradaProducto(int tam) : tabla(tam, Entrada()), intentos(15), 
            nElementos(0), maxColis(0), totalColis(0), nProductos(0) {}
    THashCerradaProducto& operator=(const THashCerradaProducto& orig);
    
    bool insertar(unsigned long clave, const std::string& termino, Producto* dato);
    std::vector<Producto*> buscar(long int clave, const std::string& termino);
    unsigned long exploracionDoble(unsigned long hash, int i);
    unsigned long exploracionCuadratica(unsigned long hash, int i);
    unsigned int promedioColisiones();
    unsigned int maxColisiones();
    unsigned int numProductos();
    unsigned int numTerminos();
    unsigned int tamaTabla();
    float factorCarga();

    std::vector<Entrada> tabla;      
};

#endif /* THASHCERRADAPRODUCTO_H */


