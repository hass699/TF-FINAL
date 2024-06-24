#ifndef Paciente_h
#define Paciente_h

#include <iostream>

using namespace std;

struct Paciente
{
  public:
    int dni;
    string nombre;
    string apellido;
    string sexo;
    int edad;
    float peso;
    float altura;

  Paciente() {}

  Paciente(int dni, string nombre, string apellido, string sexo, int edad,                 float peso, float altura)
  {
    this->dni = dni;
    this->nombre = nombre;
    this->apellido = apellido;
    this->sexo = sexo;
    this->edad = edad;
    this->peso = peso;
    this->altura = altura;
  }

};

#endif