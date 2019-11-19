/* 
 * File:   Producto.cpp
 * Author: Javier Serrano Casas
 * Date:   27 de septiembre de 2018
 */

#include "Producto.h"

/**
 * @brief Constructor por defecto.
 * @post  Construye un objeto inicializandolo por defecto
 */
Producto::Producto() : codigo(""), descripcion(""), pvp(0){
}

/**
 * @brief Constructor por defecto.
 * @post  Construye un objeto inicializandolo por defecto
 */
Producto::Producto(std::string _codigo, std::string _descripcion, float _pvp) :
    codigo(_codigo), descripcion(_descripcion), pvp(_pvp){
}

/**
 * @brief Constructor de copia de la clase Producto
 * @param orig Producto que se copiará.
 */
Producto::Producto(const Producto& orig) : codigo(orig.codigo), 
                    descripcion(orig.descripcion), pvp(orig.pvp){
}

/**
 * @brief Operador de asignación.
 * @param orig Objeto que vamos a copiar.
 * @post Realiza una asignación entre objetos, copiando los valores del objeto orig.
 * @return  Devuelve el objeto con los valores copiados
 */
Producto& Producto::operator=(const Producto& orig) {
    if (this != &orig) {
        codigo = orig.codigo;
        descripcion = orig.descripcion;
        pvp = orig.pvp;
    }
    return *this;
}

/**
 * @brief Destruye el objeto una vez deja de utilizarse.  
 */
Producto::~Producto() {
}

// ------------------ Métodos Getter y Setter del producto ------------------
void Producto::setDescripcion(std::string descripcion) {
    this->descripcion = descripcion;
}

std::string Producto::getDescripcion(){
    return this->descripcion;
}

void Producto::setCodigo(std::string codigo) {
    this->codigo = codigo;
}

std::string Producto::getCodigo(){
    return this->codigo;
}

void Producto::setPvp(float pvp) {
    this->pvp = pvp;
}

float Producto::getPvp(){
    return this->pvp;
}
// --------------------------------------------------------------------------