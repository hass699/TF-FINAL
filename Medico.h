#ifndef Medico_h
#define Medico_h

#include <iostream>

using namespace std;

struct Medico
{
  public:
    int dni;
    string nombre;
    string apellido;
    int edad;
    int especialidad;

    Medico() {};

    Medico(int dni, string nombre, string apellido, int edad, int especialidad)
    {
      this->dni = dni;
      this->nombre = nombre;
      this->apellido = apellido;
      this->edad = edad;
      this->especialidad = especialidad;
    }
};

#endif