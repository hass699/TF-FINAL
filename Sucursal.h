#ifndef Sucursal_h
#define Sucursal_h

#include <iostream>
#include "NodoHabitacion.h"
#include <vector>

using namespace std;

struct Sucursal
{
  public:
    int idSucursal;
    vector<NodoH*> habitaciones;
    Sucursal() {}

    Sucursal(int idSuc) : idSucursal(idSuc) {}

    void agregarHabitacion(NodoH *nodo)
    {
      habitaciones.push_back(nodo);
    }
};

#endif