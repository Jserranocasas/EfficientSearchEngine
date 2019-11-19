/* 
 * Brief:  Clase que sera la encargada de llevar los pedidos a los clientes del sistema
 * File:   Dron.h
 * Author: Javier Serrano Casas
 * Date:   09 de Diciembre de 2018
 */

#ifndef DRON_H
#define DRON_H

#include "UTM.h"
#include "Cliente.h"

enum EstadoDron {ACTIVO, DISPONIBLE};

class PharmaDron; //Declaracion forward
class Cliente;

class Dron {
public:
    Dron();
    Dron(int _id, UTM _pos);
    Dron(const Dron& orig);
    virtual ~Dron();
    
    void aniadeCliente(Cliente *c);
    void setEstado(EstadoDron e);
    bool estaDisponible();
    UTM& getUTM();
private:
    int id;
    UTM pos;
    EstadoDron estado;
    std::vector<Cliente*> llevaA;
};

#endif /* DRON_H */

