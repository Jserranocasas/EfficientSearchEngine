/* 
 * Brief   Clase que representa un producto que compran los clientes
 * File:   Producto.h
 * Author: Javier Serrano Casas
 * Date:   27 de septiembre de 2018
 */

#include <string>
#include <iostream>

#ifndef PRODUCTO_H
#define PRODUCTO_H

class Producto {
public:
    Producto();
    Producto(std::string codigo, std::string descripcion, float pvp);
    Producto(const Producto& orig);
    Producto& operator=(const Producto& orig);
    virtual ~Producto();
    void setDescripcion(std::string descripcion);
    std::string getDescripcion();
    void setCodigo(std::string codigo);
    std::string getCodigo();
    void setPvp(float pvp);
    float getPvp();
    
private:
    std::string codigo;         // Código de un producto
    std::string descripcion;    // Descripción de un producto
    float pvp;                  // Pvp de un producto
};

#endif /* PRODUCTO_H */

