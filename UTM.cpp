/* 
 * Brief:   
 * File:    UTM.cpp
 * Author:  Javier Serrano Casas
 * Date:    12 de noviembre de 2018
 */

#include "UTM.h"

UTM::UTM() : latitud(0), longitud(0){
}

UTM::UTM(double _latitud, double _longitud) : latitud(_latitud), longitud(_longitud){
}

UTM::UTM(const UTM& orig) : latitud(orig.latitud), longitud(orig.longitud){
}

UTM& UTM::operator=(const UTM& orig){
    if( this != &orig ){
        latitud = orig.latitud;
        longitud = orig.longitud;
    }
    
    return *this;
}

UTM::~UTM() {
}

void UTM::SetLongitud(float longitud) {
    this->longitud = longitud;
}

float UTM::GetLongitud() const {
    return longitud;
}

void UTM::SetLatitud(float latitud) {
    this->latitud = latitud;
}

float UTM::GetLatitud() const {
    return latitud;
}

