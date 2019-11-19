/* 
 * Brief:   Clase que representa coordenadas UTM de geografia
 * File:    UTM.h
 * Author:  Javier Serrano Casas
 * Date:    12 de noviembre de 2018
 */

#ifndef UTM_H
#define UTM_H

class UTM {
public:
    UTM();
    UTM(double _latitud, double _longitud);
    UTM(const UTM& orig);
    UTM& operator=(const UTM& orig);
    virtual ~UTM();
    void SetLongitud(float longitud);
    float GetLongitud() const;
    void SetLatitud(float latitud);
    float GetLatitud() const;
private:
    double latitud;    // Latitud de las coordenadas
    double longitud;   // Longitud de las coordenadas
};

#endif /* UTM_H */

