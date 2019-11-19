/* 
 * Brief:   Clase encargada de encapsular y gestionar todos los clientes y productos
 * File:    PharmaDron.h
 * Author:  Javier Serrano Casas
 * Date:    12 de noviembre de 2018
 */

#include "Cliente.h"

#ifndef PHARMADRON_H
#define PHARMADRON_H

#include <set>
#include <map>
#include <list>
#include <vector>
#include "Dron.h"
#include "THashCerradaProducto.h"
#include "MallaRegular.h"
#include "Producto.h"
#include "UTM.h"

class Cliente;
class Dron;

class PharmaDron {
public:
    PharmaDron(std::string rutaProductos, std::string rutaClientes, float xMin,
                        float yMin, float xMax, float yMax, int nDivX, int nDivY);
    PharmaDron(const PharmaDron& orig);
    virtual ~PharmaDron();
    
    std::vector<Producto*> buscaProducto(std::string subcadena);
    Cliente& ingresaCliente(std::string dni, std::string pass);
    int llevarPedidosZona(Dron &d, UTM pos, float tama);
    void definirNumeroZonas(int filas, int columnas);
    std::map<std::string, Cliente*>& getClientes();
    std::list<Producto>& getProductos();
    void aniadeProducto(Producto &p);
    void nuevoCliente(Cliente *c);
    Pedido verPedido(Cliente &c);
    void ingresaDron(Dron &dron);
    int maxElementosPorColumna();
    int maxElementosPorCelda();
    int maxElementosPorFila();
    Dron& getDronDisponible();
    int getNumClientes();

private:
    std::map<std::string, Cliente*> *clientes;    // Conjunto de clientes
    MallaRegular<Cliente*> *accesoUTM;           // Malla de clientes 
    std::list<Producto> *productos;             // Lista de productos
    THashCerradaProducto *buscaTermino;         // Hash que encapsula los terminos
    std::vector<Dron> drones;                   // Vector de drones
    
    int tamTablaHash(std::string fileNameProductos);
    void creaClientes(std::string fileNameClientes);
    bool cargaProductos(std::string fileNameProductos);
    std::vector<Cliente*> buscaClienteCuadr(UTM pos, float tama);
};

#endif /* PHARMADRON_H */

