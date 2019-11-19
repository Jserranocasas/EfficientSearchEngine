/* 
 * File:   Dron.cpp
 * Author: Javier Serrano Casas
 * Date:   09 de Diciembre de 2018
 */

#include "Dron.h"

Dron::Dron() {
}

Dron::Dron(int _id, UTM _pos) : id(_id), pos(_pos){
    estado = DISPONIBLE;
}

Dron::Dron(const Dron& orig) : id(orig.id), pos(orig.pos){
    estado = orig.estado;
    llevaA = orig.llevaA;
}

Dron::~Dron() {
}

UTM& Dron::getUTM() {
    return pos;
}

void Dron::setEstado(EstadoDron e){
    estado = e;
}

/**
 * @brief Comprueba si esta disponible el dron
 * @return Devuelve true en caso de estar disponible y false en caso contrario
 */
bool Dron::estaDisponible(){
    if(estado == DISPONIBLE){
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Añade el cliente a repartir
 * @param c Cliente
 */
void Dron::aniadeCliente(Cliente *c){
    llevaA.push_back(c);
}