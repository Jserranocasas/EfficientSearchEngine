/* 
 * Brief:   Estructura de datos  multidimensional. Asumimos que el tipo T tiene
 *          los metodos getX() y getY() implementados.
 * File:    MallaRegular.h
 * Author:  Javier Serrano Casas
 * Date:    09 de Diciembre de 2018
 */

#ifndef MALLAREGULAR_H
#define MALLAREGULAR_H

#include <vector>
#include <list>

template<typename T>
class MallaRegular; // Declaración forward de la clase MallaRegular por dependencia circular

/* Clase Casilla */
template<typename T>
class Casilla{
    std::list<T> puntos;
public:
    friend class MallaRegular<T>;
    Casilla(): puntos() {}
    void insertar(const T &dato) { puntos.push_back(dato); }
    T *buscar(const T &dato);
    bool borrar(const T &dato);
};

template<typename T>
T *Casilla<T>::buscar(const T& dato){
    typename std::list<T>::iterator it;
    it = puntos.begin();
    
    for (;it != puntos.end(); ++it){
        if (*it == dato)
            return &(*it);
    }
    return 0;
}

template<typename T>
bool Casilla<T>::borrar(const T& dato){
    typename std::list<T>::iterator it;
    it = puntos.begin();
    for (;it != puntos.end(); ++it){
        if (*it == dato) {
            puntos.erase(it);
            return true;
        }
    }
    return false;
}

/* Estructura de datos Malla Regular*/
template<typename T>   
class MallaRegular {
    Casilla<T> *obtenerCasilla(float x, float y);

    float xMin, yMin, xMax, yMax; // Tamaño real global
    float tamaCasillaX, tamaCasillaY; // Tamaño real de cada casilla
    std::vector<std::vector<Casilla<T> > > mr; // Vector 2D de casillas
    int maxElem; //Maximo de elementos en una casilla de la malla por celda
    int maxElemF; //Maximo de elementos en una casilla de la malla por fila
    int maxElemC; //Maximo de elementos en una casilla de la malla por columna
public:
    MallaRegular();
    MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int nDivX, int nDivY);
    MallaRegular(const MallaRegular& orig);
    MallaRegular& operator=(const MallaRegular& orig);
    virtual ~MallaRegular();
    
    std::vector<T> buscarRango(float rxmin, float rymin, float rxmax, float rymax);
    void insertar(float x, float y, const T &dato);
    T *buscar(float x, float y, const T &dato);
    bool borrar(float x, float y, const T &dato);
    void reajustar(int nDivX, int nDivY);
    float promedioElementosPorCelda();
    unsigned maxElementosPorColumna();
    unsigned maxElementosPorCelda();
    unsigned maxElementosPorFila();
    unsigned numElementos();
};

template<typename T>
MallaRegular<T>::MallaRegular(){
}

/* Constructor Parametrizado de la Estructura Malla Regular */
template<typename T>
MallaRegular<T>::MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, 
        int nDivX, int nDivY) 
: maxElem(-1), xMin(aXMin), yMin(aYMin), xMax(aXMax), yMax(aYMax){
    tamaCasillaX = (xMax - xMin) / nDivX;
    tamaCasillaY = (yMax - yMin) / nDivY;
    mr.insert(mr.begin(), nDivY, std::vector<Casilla<T> >(nDivX));
}

/* Constructor de copia de la Estrutura Malla Regular*/
template<typename T>
MallaRegular<T>::MallaRegular(const MallaRegular& orig)
: maxElem(orig.maxElem), maxElemF(orig.maxElemF), maxElemC(orig.maxElemC), 
  xMin(orig.xMin), yMin(orig.yMin), xMax(orig.xMax), yMax(orig.yMax), mr(orig.mr){
}

/* Operador de asignación de la Estructura Malla Regular */
template<typename T>
MallaRegular<T>& MallaRegular<T>::operator=(const MallaRegular& orig){
    if ( this != &orig){
        maxElem = orig.maxElem;
        maxElemF = orig.maxElemF;
        maxElemC = orig.maxElemC;
        xMin = orig.xMin;
        yMin = orig.yMin;
        xMax = orig.xMax;
        yMax = orig.yMax;
        mr = orig.mr;
    } 
    return *this;
}

/* Destructor de la estructura Malla Regular*/
template<typename T>
MallaRegular<T>::~MallaRegular(){
}

/**
 * @brief Obtiene la casilla que se corresponde con los valores pasados por parámetro
 * @param x int Valor x de un punto
 * @param y int Valor y de un punto
 * @return 
 */
template<typename T>
Casilla<T> *MallaRegular<T>::obtenerCasilla (float x, float y){
    int i = (x - xMin) / tamaCasillaX;
    int j = (y - yMin) / tamaCasillaY;

    return &mr[j][i];
}

/**
 * @brief Inserta un elemento en la malla regular
 * @param x int Valor x de un punto
 * @param y int Valor y de un punto
 * @param dato a insertar de la malla regular
 */
template<typename T>
void MallaRegular<T>::insertar(float x, float y, const T& dato){
    maxElem = maxElemF = maxElemC = -1;  // Reiniciamos el maximo de elementos
    Casilla<T> *c = obtenerCasilla(x,y);
    c->insertar(dato);
}

/**
 * @brief Borra un elemento de la malla regular
 * @param x int Valor x de un punto
 * @param y int Valor y de un punto
 * @param dato a borrar de la malla regular
 * @return Devuelve un booleano con el resultado del éxito de la operación
 */
template<typename T>
bool MallaRegular<T>::borrar(float x, float y, const T& dato){
    maxElem = maxElemF = maxElemC = -1;  // Reiniciamos el maximo de elementos
    Casilla<T> *c = obtenerCasilla(x,y);
    return c->borrar(dato);
}

/**
 * @brief Busca un elemento en la malla regular
 * @param x int Valor x de un punto
 * @param y int Valor y de un punto
 * @param dato a buscar de la malla regular
 * @return Devuelve un booleano con el resultado del éxito de la operación
 */
template<typename T>
T* MallaRegular<T>::buscar(float x, float y, const T& dato){
    Casilla<T> *c = obtenerCasilla(x,y);
    return c->buscar(dato);
}

/**
 * @brief Reajusta la malla con tamaño de casillas diferentes, reorganizando los datos
 * @param nDivX int numero de division en X
 * @param nDivY int numero de division en Y 
 */
template<typename T>
void MallaRegular<T>::reajustar(int nDivX, int nDivY){
    MallaRegular<T> aux(xMin, yMin, xMax, yMax, nDivX, nDivY);
        
    tamaCasillaX = (xMax - xMin) / nDivX;
    tamaCasillaY = (yMax - yMin) / nDivY;
    
    maxElem = maxElemF = maxElemC = -1;  // Reiniciamos el maximo de elementos

    for(auto j : mr){
       for(auto i : j){
           for(T dato : i.puntos){
               aux.insertar(dato->getX(), dato->getY(), dato);
           }
       }
    }
    
    mr = aux.mr;
}

/**
 * @brief Obtiene cual es el número máximo de puntos en una casilla
 * @return Devuelve maxElem
 */
template<typename T>
unsigned int MallaRegular<T>::maxElementosPorCelda(){
    if(maxElem != -1){ //Si no es -1, tenemos el valor y no se ha modificado la malla
        return maxElem;
    } 
    
    int max=0;
    for(auto i : mr){
        for(auto j : i){
            if(j.puntos.size()>max)
                max=j.puntos.size();
        }
    }
    
    maxElem = max;
    return maxElem;  
}

/**
 * @brief Obtiene cual es el número máximo de puntos por fila
 * @return Devuelve maxElemF
 */
template<typename T>
unsigned MallaRegular<T>::maxElementosPorFila(){
    if(maxElemF != -1){ //Si no es -1, tenemos el valor y no se ha modificado la malla
        return maxElemF;
    } 
    
    int max=0;
    for(auto i : mr){
        int aux=0;
        for(auto j : i){
            aux += j.puntos.size(); 
        }
        if(aux>max){
            max = aux;
        }
    }
    
    maxElemF = max;
    return maxElemF; 
}

/**
 * @brief Obtiene cual es el número máximo de puntos por columna
 * @return Devuelve maxElemC
 */
template<typename T>
unsigned MallaRegular<T>::maxElementosPorColumna(){
    if(maxElemC != -1){ //Si no es -1, tenemos el valor y no se ha modificado la malla
        return maxElemC;
    } 
    
    int max=0;
    for(int i=0; i < mr[0].size(); i++){
        int aux=0;
        
        for(int j=0; j < mr.size(); j++){
            aux += mr[j][i].puntos.size(); 
        }
        
        if(aux > max){
            max = aux;
        }
    }
    
    maxElemC = max;
    return maxElemC; 
}

/**
 * @brief Calcula el número de elementos de la Malla Regular
 * @return Devuelve el tamaño de puntos
 */
template<typename T>
unsigned int MallaRegular<T>::numElementos(){
    int total=0;
    for(auto i : mr){
        for(auto j : i)
            total += j.puntos.size(); 
    }
    return total;
}

/**
 * @brief Calcula el número medio de puntos que hay por casilla
 * @return Devuelve el número medio de puntos que hay por casilla
 */
template<typename T>
float MallaRegular<T>::promedioElementosPorCelda(){
    unsigned numElem = numElementos();
    int numCasillasX = (xMax - xMin) / tamaCasillaX; //Obtengo número de casillas por fila
    int numCasillasY = (yMax - yMin) / tamaCasillaY; //Obtengo número de casillas por columna
    
    return numElem / (numCasillasX * numCasillasY * 1.0);  
}

/**
 * @brief Obtiene todos los puntos comprendidos en el rango pasado por parámetro
 * @param xMin float valor minimo de x
 * @param yMin float valor minimo de y
 * @param xMax float valor maximo de x
 * @param yMax float valor maximo de y
 * @return Devuelve un vector de puntos que estan comprendidos en un rango
 */
template<typename T>
std::vector<T> MallaRegular<T>::buscarRango(float _xMin, float _yMin, float _xMax, float _yMax) {
    int x1 = (_xMin - this->xMin) / tamaCasillaX;
    int y1 = (_yMin - this->yMin) / tamaCasillaY;
    int x2 = (_xMax - this->xMin) / tamaCasillaX;
    int y2 = (_yMax - this->yMin) / tamaCasillaY;
    
    typename std::list<T>::iterator it;
    std::vector<T> puntos;
    
    for(int i = x1; i <= x2; i++) {
        for (int j= y1; j <= y2; j++) {
            it = mr[j][i].puntos.begin();
            while (it != mr[j][i].puntos.end()) {
                if((*it)->getX() >= _xMin && (*it)->getX() <= _xMax && 
                    (*it)->getY() >= _yMin && (*it)->getY() <= _yMax)
                    puntos.push_back(*it);
                ++it;
            }
        }
    }

    return puntos;
}

#endif /* MALLAREGULAR_H */



