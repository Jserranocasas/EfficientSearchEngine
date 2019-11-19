/* 
 * File:   Cliente.cpp
 * Author: Javier Serrano Casas
 * Date:   26 de octubre de 2018
 */

#include "Cliente.h"

Cliente::Cliente() : dni(""), nombre(""), pass(""), direccion(""), posicion(){
}

Cliente::Cliente(std::string _dni, std::string _nombre, std::string _pass, 
        std::string _direccion, UTM _posicion, PharmaDron *p)  
       : dni(_dni), nombre(_nombre), pass(_pass), direccion(_direccion), 
        posicion(_posicion), pharma(p) {
}

Cliente::Cliente(const Cliente& orig)  
    : dni(orig.dni), nombre(orig.nombre), pass(orig.pass), direccion(orig.direccion),
        posicion(orig.posicion){
}

Cliente& Cliente::operator =(const Cliente& orig){
    if( this != &orig ){
        dni = orig.dni;
        nombre = orig.nombre;
        pass = orig.pass;
        direccion = orig.direccion;
        posicion = orig.posicion;
    }
    
    return *this;
}

Cliente::~Cliente() {
}

// ------------------------ Métodos getters y setters --------------------------
void Cliente::SetDireccion(std::string direccion) {
    this->direccion = direccion;
}

std::string Cliente::GetDireccion() const {
    return direccion;
}

void Cliente::SetPass(std::string pass) {
    this->pass = pass;
}

std::string Cliente::GetPass() const {
    return pass;
}

void Cliente::SetNombre(std::string nombre) {
    this->nombre = nombre;
}

std::string Cliente::GetNombre() const {
    return nombre;
}

void Cliente::SetDni(std::string dni) {
    this->dni = dni;
}

std::string Cliente::GetDni() const {
    return dni;
}

Pedido Cliente::GetPedidos() {
    return pedidos;
}

void Cliente::SetPedidos(Estado es) {
    pedidos.setEstado(es);
}
// -----------------------------------------------------------------------------

/**
 * @brief Método que añade un producto a la lista de pedidos del cliente
 * @param p Puntero que apunta a la posicion del producto elegido
 */
void Cliente::addProductoPedido(Producto *p){
    pedidos.nuevoProducto(p);
}

/**
 * @brief Busca un producto mediante una subcadena
 * @param subcadena a buscar para encontrar producto
 * @return  Devuelve un vector con los productos en caso de encontrarla y
 * un vector vacio en caso de no encontrar la subcadena
 */
std::vector<Producto*> Cliente::buscarProducto(std::string subcadena){
     return pharma->buscaProducto(subcadena);    
}

/**
 * Método necesario para obtener el y de la mallaRegular
 * @return Devuelve la latitud de la posicion UTM
 */
float Cliente::getY(){
    return posicion.GetLatitud();
}

/**
 * Método necesario para obtener el x de la mallaRegular
 * @return Devuelve la longitud de la posicion UTM
 */
float Cliente::getX(){
    return posicion.GetLongitud();
}