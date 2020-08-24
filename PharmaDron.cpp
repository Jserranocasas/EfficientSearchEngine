/* 
 * Brief:   
 * File:    PharmaDron.cpp
 * Author:  Javier Serrano Casas
 * Date:    12 de noviembre de 2018
 */

#include "PharmaDron.h"
#include "UTM.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <locale>

PharmaDron::PharmaDron(std::string rutaProductos, std::string rutaClientes, float xMin,
                        float yMin, float xMax, float yMax, int nDivX, int nDivY) {
    accesoUTM = new MallaRegular<Cliente*>(xMin, yMin, xMax, yMax, nDivX, nDivY);
    clientes = new std::map<std::string, Cliente*>;
    productos = new std::list<Producto>;
    
    int tam = tamTablaHash(rutaProductos); // Calcula el tamaño inicial de la tabla hash
    
    buscaTermino = new THashCerradaProducto(tam);
    
    bool seguirEntrenando = true;
    while(seguirEntrenando){
        if(!cargaProductos(rutaProductos)){
            delete buscaTermino;  
            tam = tam*1.3; 
            buscaTermino = new THashCerradaProducto(tam);
        } else {
            seguirEntrenando = false;
        }
    }
    
    creaClientes(rutaClientes);
    
    std::cout << "\nTotal de Productos insertados: " << buscaTermino->numProductos() << std::endl;
    std::cout << "Factor de carga: " << buscaTermino->factorCarga() << std::endl;
    std::cout << "Total de colisiones:" << buscaTermino->maxColisiones() << std::endl;
    std::cout << "Total de Terminos:" << buscaTermino->numTerminos() << std::endl;
    std::cout << "Tamaño tabla hash:" << tam << std::endl;
}

PharmaDron::PharmaDron(const PharmaDron& orig) : accesoUTM(orig.accesoUTM){
    buscaTermino = orig.buscaTermino;
    clientes = orig.clientes;
    productos = orig.productos;
}

PharmaDron::~PharmaDron() {
    delete clientes;
    delete accesoUTM;
    delete productos;
    delete buscaTermino;
}

/**
 * @brief Metodo auxiliar para pasar una cadena a entero para el hash
 * @return devuelve el hash correspondiente
 */
unsigned long djb2(const std::string &str) {
    unsigned long hash = 5381;

    for (auto it = str.begin(); it != str.end(); it++)
        hash = ((hash << 5) + hash) + *it; /* hash * 33 + character */

    return hash;
}

/**
 * @brief Metodo auxiliar para pasar un string a minuscula
 * @param termino String a convertir
 * @return Devuelve el termino en minusculas
 */
std::string pasarMinuscula(std::string &termino){
    for(int i = 0; i < termino.size(); i++){
       termino[i] = tolower(termino[i]);  
    }
   
    return termino;
}

/**
 * @brief Comprueba el numero de terminos que hay que sera el tamaño inicial de la tabla hash
 * @param fileNameProductos ruta del fichero a leer
 * @return Devuelve el tamaño inicial de la tabla hash
 */
int PharmaDron::tamTablaHash(std::string fileNameProductos){
    std::ifstream fe;  //Creamos un flujo de entrada, #include <ifstream>
    std::string terminos, linea;
    std::set<std::string> setTerminos;   // Terminos de productos

    setlocale(LC_ALL,"es_ES.UTF8");

    // Asociamos el flujo con un fichero y lo abrimos
    fe.open( fileNameProductos );
    if ( fe.good() ) {
        getline( fe, linea ); // Toma la primera línea del fichero que es descriptiva
        
        // Mientras no se haya llegado al final del fichero
        while ( !fe.eof() ) {
            getline( fe, linea ); // Toma una línea del fichero
            if (linea != "" ) { // Ignoramos líneas en blanco
                std::stringstream ss;
                ss.str(linea);
                ss.ignore(7);
                getline(ss, terminos, ';');                
                ss.str( std::string() );
                
                std::stringstream s(terminos);
                std::string termino; 
                
                for (int i = 0; s >> termino; i++) { 
                    if (termino.size() > 3) { 
                        setTerminos.insert(pasarMinuscula(termino));
                    } 
                }
                
                s.str( std::string() );
            }
            
        }
        fe.close(); //Cerramos el flujo de entrada
        return setTerminos.size();
    } else {
        std::cerr << "No se puede abrir el fichero" << std::endl;
    }
}

/**
 * @brief Carga todos los productos disponibles por medio de un archivo csv
 * @param fileNameProductos ruta del fichero a leer
 */
bool PharmaDron::cargaProductos(std::string fileNameProductos){
    std::ifstream fe;  //Creamos un flujo de entrada, #include <ifstream>
    std::string nombre, linea, cadPrecio;
    float precio;
    int codigo;
    int total=0;
    
    setlocale(LC_ALL,"es_ES.UTF8");

    // Asociamos el flujo con un fichero y lo abrimos
    fe.open( fileNameProductos );
    if ( fe.good() ) {
        getline( fe, linea ); // Toma la primera línea del fichero que es descriptiva
        
        // Mientras no se haya llegado al final del fichero
        while ( !fe.eof() ) {
            getline( fe, linea ); // Toma una línea del fichero
            if (linea != "" ) { // Ignoramos líneas en blanco
                std::stringstream ss;
                ss.str(linea);
                ss >> codigo;
                ss.ignore(1);
                getline(ss, nombre, ';');
                getline(ss, cadPrecio, ';');
                
                ss.str( std::string() );
                total++;

                try {
                  precio = std::stof(cadPrecio);
                }catch (std::invalid_argument &e) {
                  precio = 0;
                }
                
                std::stringstream s(nombre);
                std::string termin; 
                
                Producto *p = new Producto(std::to_string(codigo), nombre, precio);
                productos->push_back(*p);
                
                for (int i = 0; s >> termin; i++) { 
                    if (termin.size() > 3) { 
                        termin = pasarMinuscula(termin);
                        if(!buscaTermino->insertar(djb2(termin), termin, p)){
                           productos->clear();
                            return false;
                        }
                    } 
                }
                
                s.str( std::string() );
            }
        }
        std::cout << "Total de medicamentos en el archivo:" << total << std::endl;
        fe.close(); //Cerramos el flujo de entrada
        
        return true;
    } else {
        std::cerr << "No se puede abrir el fichero" << std::endl;
    }
}

/**
 * @brief Carga todos los clientes disponibles por medio de un archivo csv
 * @param fileNameClientes ruta del fichero a leer
 */
void PharmaDron::creaClientes(std::string fileNameClientes){
    std::ifstream fe;  //Creamos un flujo de entrada, #include <ifstream>
    std::string linea;
    
    std::string nif, clave, nombre, direccion, cadLongitud, cadLatitud;
    double longitud, latitud;
    int total=0;
    
    setlocale(LC_ALL,"es_ES.UTF8");
    
    // Asociamos el flujo con un fichero y lo abrimos
    fe.open( fileNameClientes );
    if ( fe.good() ) {
        getline( fe, linea ); // Toma la primera línea del fichero que es descriptiva

        // Mientras no se haya llegado al final del fichero
        while ( !fe.eof()) {
            getline( fe, linea ); // Toma una línea del fichero
            if (linea != "" ) { // Ignoramos líneas en blanco
                std::stringstream ss;
                ss.str(linea);
                getline(ss, nif, ';');
                getline(ss, clave, ';');
                getline(ss, nombre, ';');
                getline(ss, direccion, ';');
                getline(ss, cadLatitud, ';');
                getline(ss, cadLongitud, ';');

                ss.str( std::string() );
                total++;

                try {
                    latitud = std::stof(cadLatitud);
                }catch (std::invalid_argument &e) {
                    latitud = 0;
                }
                
                try {
                    longitud = std::stof(cadLongitud);
                }catch (std::invalid_argument &e) {
                    longitud = 0;
                }
                
                Cliente *c = new Cliente(nif, nombre, clave, direccion, UTM(latitud, longitud), this);
                nuevoCliente(c);
                
                accesoUTM->insertar(longitud, latitud, c);
            }
        }
        std::cout << "Total de clientes en el archivo:" << total << std::endl;
        fe.close(); //Cerramos el flujo de entrada
    } else {
        std::cerr << "No se puede abrir el fichero" << std::endl;
    }
}

/**
 * @brief Metodo que añade un producto a la lista de productos
 * @param p Producto a añadir
 */
void PharmaDron::aniadeProducto(Producto &p){
    productos->push_back(p);
}

/**
 * @brief Metodo que inserta un nuevo cliente 
 * @param c Cliente nuevo a insertar
 */
void PharmaDron::nuevoCliente(Cliente *c){
    (*clientes)[c->GetDni()] = c;
}

/**
 * @brief Metodo que busca los productos que contienen una subcadena
 * @param subcadena a buscar
 * @return Devuelve un vector con los producto o un vector vacio si no se encuentra
 */
std::vector<Producto*> PharmaDron::buscaProducto(std::string subcadena){
    subcadena = pasarMinuscula(subcadena);
    
    return  buscaTermino->buscar(djb2(subcadena), subcadena);
}

/**
 * @brief Metodo que busca un cliente en el arbol
 * @param dni string Identificacion del cliente
 * @param pass string contraseña del ciente
 * @return Devuelve el cliente en caso de que todo sea correcto
 */
Cliente& PharmaDron::ingresaCliente(std::string dni, std::string pass){
    std::map<std::string, Cliente*>::iterator i;
    i = (*clientes).find(dni);
    
    if((*i).second->GetPass() != pass){
        throw std::logic_error("PharmaDron::ingresaCliente : Contraseña incorrecta");
    }
    
    return *(*i).second;
}

/**
 * @brief Busca los clientes correspondientes a un rango cuadrado
 * @param pos Coordenada UTM correspondiente al centro del rango
 * @param tama float Total de grados que se extiende en x e y el rango a partir de pos
 * @return 
 */
std::vector<Cliente*> PharmaDron::buscaClienteCuadr(UTM pos, float tama){
    return accesoUTM->buscarRango(pos.GetLongitud() - tama, pos.GetLatitud() - tama, 
                                  pos.GetLongitud() + tama, pos.GetLatitud() + tama);
}
    
/**
 * @brief Metodo que obtiene un pedido de un cliente
 * @param c Cliente del cual obtener el pedido
 * @return Devuelve el pepido si lo tiene
 */
Pedido PharmaDron::verPedido(Cliente &c){
    return c.GetPedidos();
}

/**
 * @brief Obtiene el primer dron disponible encontrado
 * @return Devuelve el dron que este disponible
 */
Dron& PharmaDron::getDronDisponible(){
    int i = 0;
    while(!drones[i].estaDisponible()){
        if(i == drones.size()){
            i = 0;
        }
        
        i++;
    }    
    
    return drones[i];
}

/**
 * @brief Lleva los pedidos a los clientes que se encuentre en la zona
 * @param d Dron que llevará los pedidos
 * @param pos Coordenada UTM correspondiente al centro del rango
 * @param tama float Total de grados que se extiende en x e y el rango a partir de pos
 * @return Devuelve el numero de pedidos entregados
 */
int PharmaDron::llevarPedidosZona(Dron &d, UTM pos, float tama){
    d.setEstado(ACTIVO);
    
    auto v = buscaClienteCuadr(pos, tama);
    int pedidosEntregados = 0;
    
    for (auto cli : v){
        if (cli->GetPedidos().getCesta().size() > 0){
            cli->SetPedidos(ENTREGADO);
            d.aniadeCliente(cli);
            pedidosEntregados++;
        }
    }
    
    return pedidosEntregados;
}

/**
 * @brief Reajusta la malla regular con un numero de divisiones en x e y nuevo
 * @param filas int Numero de division en y
 * @param columnas int Numero de division en y
 */
void PharmaDron::definirNumeroZonas(int filas, int columnas){
    accesoUTM->reajustar(filas, columnas);
}

/**
 * @brief Inserta un dron al vector de drones
 * @param dron a insertar
 */
void PharmaDron::ingresaDron(Dron& dron){
    drones.push_back(dron);
}

/**
 * @brief Obtiene la lista de productos
 * @return  Devuelve la lista de productos
 */
std::list<Producto>& PharmaDron::getProductos() {
    return *productos;
}

/**
 * @brief Obtiene el numero de clientes
 * @return  Devuelve el numero de clientes
 */
int PharmaDron::getNumClientes(){
    return clientes->size();
}

/**
 * @brief Obtiene el mapa de clientes
 * @return  Devuelve el mapa de clientes
 */
std::map<std::string, Cliente*>& PharmaDron::getClientes() {
    return *clientes;
}

/**
 * @brief Obtiene el numero maximo de elementos por fila
 * @return Devuelve el numero maximo de elementos por fila
 */
int PharmaDron::maxElementosPorFila(){
    return accesoUTM->maxElementosPorFila();
}

/**
 * @brief Obtiene el numero maximo de elementos por columna
 * @return Devuelve el numero maximo de elementos por columna
 */
int PharmaDron::maxElementosPorColumna(){
    return accesoUTM->maxElementosPorColumna();
}

/**
 * @brief Obtiene el numero maximo de elementos por celda
 * @return Devuelve el numero maximo de elementos por celda
 */
int PharmaDron::maxElementosPorCelda(){
    return accesoUTM->maxElementosPorCelda();
}