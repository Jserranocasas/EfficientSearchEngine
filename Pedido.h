/* 
 * Brief:  Clase que representa pedido con los productos de un cliente
 * File:   Pedido.h
 * Author: Javier Serrano Casas
 * Date:   16 de octubre de 2018
 */

#ifndef PEDIDO_H
#define PEDIDO_H

#include <string>
#include <vector>
#include <iostream>

#include "Producto.h"

enum Estado {PAGADO, ENALMACEN, ENTRANSITO, ENTREGADO};

class Pedido {
public:
    Pedido();
    Pedido(std::string id);
    Pedido(const Pedido& orig);
    Pedido& operator=(const Pedido& orig);
    virtual ~Pedido();
    
    std::vector<Producto*> getCesta() const;
    std::string getId() const;
    Estado getEstado() const;
    void setEstado(Estado estado);
    void setId(std::string id);
    
    void nuevoProducto(Producto *p);
    float importe();
private:
    std::vector<Producto*> cesta;   // Cesta de la compra del cliente
    std::string id;                 // Id del pedido
    Estado estado;                  // Estado de envio del pedido
};

#endif /* PEDIDO_H */
