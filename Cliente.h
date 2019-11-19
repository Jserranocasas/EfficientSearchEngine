/* 
 * Brief:  Clase que representa a un cliente de productos
 * File:   Cliente.h
 * Author: Javier Serrano Casas
 * Date:   26 de octubre de 2018
 */


#ifndef CLIENTE_H
#define CLIENTE_H

#include <vector>
#include <string>
#include <iostream>

#include "UTM.h"
#include "Pedido.h"
#include "PharmaDron.h"

class PharmaDron; //Declaracion forward

class Cliente {
public:
    Cliente();
    Cliente(std::string _dni, std::string _nombre, 
            std::string _pass, std::string _direccion, UTM _posicion, PharmaDron *p);
    Cliente(const Cliente& orig);
    Cliente& operator=(const Cliente& orig);
    virtual ~Cliente();
    
    void SetDireccion(std::string direccion);
    std::string GetDireccion() const;
    void SetPass(std::string pass);
    std::string GetPass() const;
    void SetNombre(std::string nombre);
    std::string GetNombre() const;
    void SetDni(std::string dni);
    std::string GetDni() const;
    Pedido GetPedidos();
    void SetPedidos(Estado es);
    float getY();
    float getX();
    std::vector<Producto*> buscarProducto(std::string subcadena);
    void addProductoPedido(Producto *p);
    
private:
    std::string dni;        // DNI del cliente
    std::string pass;       // Contraseña del cliente
    std::string nombre;     // Nombre del cliente
    std::string direccion;  // Direccion del cliente
    PharmaDron *pharma;      // Controlador pharmadron
    Pedido pedidos;         // Pedido realizado
    UTM posicion;           // Coordenadas geograficas
};

#endif /* CLIENTE_H */

