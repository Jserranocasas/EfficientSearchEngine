/* 
 * Brief:   Programa Principal
 * File:    main.cpp
 * Author:  Javier Serrano Casas
 * Date:    27 de septiembre de 2018
 */

#include "Producto.h"
#include "PharmaDron.h"
#include "MallaRegular.h"
#include "Cliente.h"
#include "Pedido.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <locale>
#include <list>

using namespace std;

/**
 * @brief   Función para la visualización de un pedido
 * @param   pedido Pedido a visualizar
 */
void visualiza(Pedido pedido){ 
    for( Producto *p : pedido.getCesta()){
        std::cout << "Producto: " << p->getDescripcion() << std::endl;
    }
    
    std::cout << "--------------------------------------------------------------" << std::endl;
    std::cout << "Con un importe total de: " << pedido.importe() << " €." << std::endl;
    std::cout << "--------------------------------------------------------------" << std::endl;

}

/**
 * @brief Metodo auxiliar para insertar productos al 30% de los clientes
 * @param pharma PharmaDron controlador del proyecto
 */
void asignarProductos(PharmaDron &pharma){
int insertados=0;
    
    auto iProductos = pharma.getProductos().begin();
    auto iClientes = pharma.getClientes().begin();
    
    int random;
    while(insertados < 0.3 * pharma.getNumClientes()){
        if(iProductos == pharma.getProductos().end()){ //Si llega al final volvemos al principio
            iProductos = pharma.getProductos().begin();
        }
    
        if(iClientes == pharma.getClientes().end()){ //Si llega al final volvemos al principio
            iClientes = pharma.getClientes().begin();
        }
    
        random = rand() % 2; // Valor aleatorio [0,1]
        
        if(random){
            (*iClientes).second->addProductoPedido(&(*iProductos));
            insertados++;
        }
        
        iProductos++;
        iClientes++;
    }
}

int main(int argc, char** argv) {
    PharmaDron pharmaDron("pharma1.csv", "clientes_v2.csv", -9.274f, 35.867f, 3.282f, 43.273f, 20, 10);
    
    asignarProductos(pharmaDron);

    Cliente *nuevoCliente = new Cliente("C-137", "Rick Sanchez", "WubbaLubbaDubDub", 
            " Planeta Tierra del Universo C-137", UTM(), &pharmaDron);

    pharmaDron.nuevoCliente(nuevoCliente);
    
    Cliente rick = pharmaDron.ingresaCliente("C-137", "WubbaLubbaDubDub");
    
    std::vector<Producto*> lInyectable = pharmaDron.buscaProducto("inyectable");

    for (Producto *p : lInyectable) {
        rick.addProductoPedido(p);
    }
    
    std::cout << "\n----------------- PEDIDO PARA " << rick.GetNombre() << " ------------------- " << std::endl;
    std::cout << "--------------------------------------------------------------" << std::endl;
    
    visualiza(rick.GetPedidos());

    Dron Madrid(123, UTM(40.41692, -3.703822));
    Dron Segovia(456, UTM(40.9424893, -4.1089545));
    Dron Jaen(789, UTM(37.779601, -3.7855061));
    
    pharmaDron.ingresaDron(Madrid);
    pharmaDron.ingresaDron(Segovia);
    pharmaDron.ingresaDron(Jaen);

    int numRepartos = pharmaDron.llevarPedidosZona(pharmaDron.getDronDisponible(), Segovia.getUTM(), 0.25);
    std::cout << "\n------- Malla de [10, 20] -------";
    std::cout << "\nNumero de repartos en Segovia: " << numRepartos;
    std::cout << "\nMaximo por fila: " << pharmaDron.maxElementosPorFila();
    std::cout << "\nMaximo por columna: " << pharmaDron.maxElementosPorColumna();
    std::cout << "\nMaximo por celda: " << pharmaDron.maxElementosPorCelda();
    std::cout << "\n---------------------------------";

    pharmaDron.definirNumeroZonas(10, 10);
    numRepartos = pharmaDron.llevarPedidosZona(pharmaDron.getDronDisponible(), Madrid.getUTM(), 0.35);
    std::cout << "\n\n------- Malla de [10, 10] -------";
    std::cout << "\nNumero de repartos en Madrid: " << numRepartos;
    std::cout << "\nMaximo por fila: " << pharmaDron.maxElementosPorFila();
    std::cout << "\nMaximo por columna: " << pharmaDron.maxElementosPorColumna();
    std::cout << "\nMaximo por celda: " << pharmaDron.maxElementosPorCelda();
    std::cout << "\n---------------------------------";

    pharmaDron.definirNumeroZonas(15, 20);    
    numRepartos = pharmaDron.llevarPedidosZona(pharmaDron.getDronDisponible(), Jaen.getUTM(), 0.3);
    std::cout << "\n\n------- Malla de [15, 20] -------";
    std::cout << "\nNumero de repartos en Jaen: " << numRepartos;
    std::cout << "\nMaximo por fila: " << pharmaDron.maxElementosPorFila();
    std::cout << "\nMaximo por columna: " << pharmaDron.maxElementosPorColumna();
    std::cout << "\nMaximo por celda: " << pharmaDron.maxElementosPorCelda();
    std::cout << "\n---------------------------------";

    std::cout << std::endl;
    
    return 0;
}
