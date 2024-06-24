#ifndef TransaccionAbierta_h
#define TransaccionAbierta_h

#include <iostream>
#include "NodoHabitacion.h"

using namespace std;

class TransaccionAbierta
{
  public:
    long id;
    NodoH *h;
    int especialidad;
    string fechaIngreso;
    string fechaEgreso;
    float tarifa;
    int diasInternado;
    float total;
    string motivo;

    TransaccionAbierta() {}

    TransaccionAbierta(long id, int especialidad, string fechaIngreso, string fechaEgreso, float tarifa, int internado, float total, string motivo, NodoH* h) {
        this->id = id;
        this->especialidad = especialidad;
        this->fechaIngreso = fechaIngreso;
        this->fechaEgreso = fechaEgreso;
        this->tarifa = tarifa;
        this->diasInternado = internado;
        this->total = total;
        this->motivo = motivo;
        this->h = h;
    }
};

#endif