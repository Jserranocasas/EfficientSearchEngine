/* 
 * File:   Pedido.cpp
 * Author: Javier Serrano Casas
 * Date:   16 de octubre de 2018
 */

#include "Pedido.h"

Pedido::Pedido() : id("") {
    estado = ENTRANSITO;
}

Pedido::Pedido(std::string _id) : id(_id){
    estado = ENTRANSITO;
}

Pedido::Pedido(const Pedido& orig) : id(orig.id), estado(orig.estado), 
     cesta(orig.cesta) {
}

Pedido& Pedido::operator=(const Pedido& orig){
    if(this != &orig){
        id = orig.id;
        estado = orig.estado; 
        cesta = orig.cesta;
    }
    return *this;
}

Pedido::~Pedido() {
}

// ------------------------ Métodos getters y setters --------------------------

void Pedido::setEstado(Estado estado) {
    this->estado = estado;
}

Estado Pedido::getEstado() const {
    return estado;
}

void Pedido::setId(std::string id) {
    this->id = id;
}

std::string Pedido::getId() const {
    return id;
}

std::vector<Producto*> Pedido::getCesta() const {
    return cesta;
}
// -----------------------------------------------------------------------------

/**
 * @brief Metodo para insertar un nuevo producto a la cesta
 * @param producto Puntero que apunta al producto a introducir en la cesta
 */
void Pedido::nuevoProducto(Producto *p){
    cesta.push_back(p);
}

/**
 * @brief Metodo que calcula el importe de los productos que se encuentran en la cesta
 * @return Devuelve el importe total de dinero que cuesta el pedido
 */
float Pedido::importe(){
    float total=0;
    
    for(int i=0; i<cesta.size(); i++){
        total += cesta[i]->getPvp();
    }
    return total;
}
