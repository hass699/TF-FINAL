#ifndef Habitacion_h
#define Habitacion_h

#include <iostream>
#include "NodoPaciente.h"
#include "NodoMedico.h"

using namespace std;

class Habitacion
{
  public:
    int id;
    int tam;
    NodoP *paciente;
    NodoM *medico;
    bool estado;

    Habitacion() {}

    Habitacion(int id, int tam, NodoP *p, NodoM *m, bool estado)
    {
      this->id = id;
      this->tam = tam;
      this->paciente = p;
      this->medico = m;
      this->estado = estado;
    }
};

#endif