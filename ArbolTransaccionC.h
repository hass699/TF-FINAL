#ifndef ArbolTransaccionC_h
#define ArbolTransaccionC_h

#include <iostream>
#include "NodoTransaccionAbierta.h"
#include "ListaDoblePaciente.h"
#include <vector>

using namespace std;

struct ArbolTC
{
  NodoTA *raiz;
};

//Prototipos
void balancearArbolTC(ArbolTC *arbol, NodoTA *nodo);

//Funcion para crear un arbol vacio
ArbolTC *crearArbolTC()
{
  ArbolTC *aux = new ArbolTC();
  aux->raiz = NULL;

  return aux;
}

//Funcion para validar si el arbol esta vacio
bool arbolVacioTC(ArbolTC *arbol) 
{
  if(arbol->raiz == NULL)//La raiz del arbol apunta a NULL
  {
    return true;
  }

  return false;
}

//Funcion para insertar un nodo en el arbol
void insertarNodoTC(ArbolTC *arbol, NodoTA *nodo)
{
  if(arbolVacioTC(arbol))//Validamos si el arbol esta vacio
  {
    arbol->raiz = nodo;//Cumplida la condicion, la raiz del arbol apunta al nodo
  }
  else// De no estar vacio
  {
    NodoTA *aux = arbol->raiz; //Creamos un auxiliar que almacena la raiz del arbol
    NodoTA *padre; // Variable para almacenar el padre del nodo actual

    while(aux != NULL)//Recorrido del arbol hasta el ultimo nodo
    {
      padre = aux; // Guardamos el nodo actual en la variable padre

      if(nodo->trana.id < aux->trana.id)//Si el dato es menor, vamos a la izquierda
      {
        aux = aux->izq;
      }
      else//Si el dato es mayor, vamos a la derecha
      {
        aux = aux->der;
      }
    }
    //Cuando salimos del ciclo, almacenamos el nodo anterior de la posicion actual
    nodo->padre = padre;

    //Ubicamos por la derecha o izquierda al nodo, segun e valor del dato
    if(nodo->trana.id < padre->trana.id)
    {
      padre->izq = nodo;
    }
    else
    {
      padre->der = nodo;
    }
    balancearArbolTC(arbol, padre);
  }
}

//Funcion de busqueda del nodo 
NodoTA *buscarNodoTC(ArbolTC *arbol, int dni)
{
  NodoTA *aux = NULL;

  if(!arbolVacioTC(arbol))
  {
    aux = arbol->raiz;

    while(aux != NULL && aux->trana.h->hab.paciente->paciente.dni != dni)
    {
      if(dni < aux->trana.h->hab.paciente->paciente.dni)
      {
        aux = aux->izq;
      }
      else
      {
        aux = aux->der;  
      }
    }
  }

  //Retorno del nodo
  return aux;
}

void inOrdenTC(NodoTA *nodo, int dni, NodoP *i, NodoP *f)
{
  listaDoblePaciente lp;
  vector<NodoTA*> aux;
  NodoP *auxp = lp.encontrarPaciente(i, f, dni);


  if(nodo != NULL && auxp != NULL)
  {
    inOrdenTC(nodo->izq, dni, i, f);
    if(nodo->trana.h->hab.paciente->paciente.dni == dni)
    {
      aux.push_back(nodo);
    }
    inOrdenTC(nodo->der, dni, i, f);
  }

  for(auto const& i: aux)
  {
    cout << "Transaccion cerrada" << endl;
    cout << "\nID: " << i->trana.id << endl;
    cout << "Paciente: " << i->trana.h->hab.paciente->paciente.nombre << " " << i->trana.h->hab.paciente->paciente.apellido << endl;
    cout << "Medico: Dr. " << i->trana.h->hab.medico->medico.nombre << " " << i->trana.h->hab.medico->medico.apellido << endl;
    cout << "Habitacion: " << i->trana.h->hab.id << endl;
    cout << "Fecha entrada: " << i->trana.fechaIngreso << endl;
    cout << "Fecha salida: " << i->trana.fechaEgreso << endl;
    switch(i->trana.especialidad)
    {  
      case 1:
        cout << "Especialidad: Cardiologia" << endl;
        break;
      case 2:
        cout << "Especialidad: Oncologia" << endl;
        break;
      case 3:
        cout << "Especialidad: Neurologia" << endl;
        break;
      case 4:
        cout << "Especialidad: Traumatologia" << endl;
        break;
    }
    cout << "Motivo: " << i->trana.motivo << endl;
    cout << "Tarifa: " << i->trana.tarifa << endl;
    cout << "Dias internado: " << i->trana.diasInternado << endl;
    cout << "Total a pagar: " << i->trana.total << endl;
    cout << "\n"; 
  }
}

// Funcion de busqueda del nodo por habitacion
NodoTA *buscarNodoHabTC(ArbolTC *arbol, int id) {
  NodoTA *aux = NULL;

  if (!arbolVacioTC(arbol)) // Validamos si el arbol esta vacio
  {
    aux = arbol->raiz; // Guardamos la raiz del arbol
    while (aux != NULL && aux->trana.h->hab.id != id)
    {
      if (id < aux->trana.h->hab.id) {
        aux = aux->izq;
      } else {
        aux = aux->der;
      }
    }
  }

  // Retorno del nodo
  return aux;
}

// Funcion de retorno de suma total de tarifas
int tarifaHabTC(ArbolTC *arbol, int id) {
  NodoTA *aux = NULL;
  int suma = 0;

  if (!arbolVacioTC(arbol)) // Validamos si el arbol esta vacio
  {
    aux = arbol->raiz; // Guardamos la raiz del arbol
    while (aux != NULL) 
    {
      if(aux->trana.h->hab.id == id)
      {
        suma += aux->trana.tarifa;
      }
      else
      {
        suma += 0;
      }

      if (id < aux->trana.h->hab.id)
      {
        aux = aux->izq;
      }
      else
      {
        aux = aux->der;
      }

    }
  }

  return suma;
}

NodoTA *hijoNoNullTC(NodoTA *nodo)
{
  if(nodo->izq != NULL)
  {
    return nodo->izq;
  }
  return nodo->der;
}


//Funcion para calcular la altura de un arbol
int alturaArbolTC(NodoTA *nodo)
{
  if(nodo != NULL)
  {
    int hizq = alturaArbolTC(nodo->izq);
    int hder = alturaArbolTC(nodo->der);
    if(hizq > hder)
    {
      return hizq + 1;
    }
    else
    {
      return hder + 1;
    }
  }
  else
  {
    return 0;
  }
}

//Funcion para calcular el factor de equilibrio de un nodo
int factorEquilibrioTC(NodoTA *nodo)
{
  return alturaArbolTC(nodo->der) - alturaArbolTC(nodo->izq);
}

//Funcion de la rotacion simple a la izquierda
void rotacionIzquierdaTC(ArbolTC *arbol, NodoTA *nodo)
{
  NodoTA *aux, *p, *q;
  aux = nodo->der;
  q = aux->izq;
  p = nodo->padre;

  nodo->der = q;
  aux->izq = nodo;

  if(q != NULL)
  {
    q->padre = nodo;
  }
  nodo->padre = aux;

  if(p == NULL)
  {
    arbol->raiz = aux;
    aux->padre = NULL;
  }
  else
  {
    aux->padre = p;
    if(aux->trana.id < p->trana.id)
    {
      p->izq = aux;
    }
    else
    {
      p->der = aux;
    }
  }

  aux->factorEq = factorEquilibrioTC(aux);
  nodo->factorEq = factorEquilibrioTC(nodo);
}

//Funcion de la rotacion simple a la derecah
void rotacionDerechaTC(ArbolTC *arbol, NodoTA *nodo)
{
  NodoTA *aux, *p, *q;
  aux = nodo->izq;
  q = aux->der;
  p = nodo->padre;

  nodo->izq = q;
  aux->der = nodo;

  if(q != NULL)
  {
    q->padre = nodo;
  }
  nodo->padre = aux;

  if(p == NULL)
  {
    arbol->raiz = aux;
    aux->padre = NULL;
  }
  else
  {
    aux->padre = p;
    if(aux->trana.id < p->trana.id)
    {
      p->izq = aux;
    }
    else
    {
      p->der = aux;
    }
  }

  aux->factorEq = factorEquilibrioTC(aux);
  nodo->factorEq = factorEquilibrioTC(nodo);
}

//Funcion para la rotacion doble izquierda
void rotacionDobleIzquierdaTC(ArbolTC *arbol, NodoTA *nodo)
{
  rotacionDerechaTC(arbol, nodo->der);
  rotacionIzquierdaTC(arbol, nodo);
}

//Funcion para la rotacion doble derecha
void rotacionDobleDerechaTC(ArbolTC *arbol, NodoTA *nodo)
{
  rotacionIzquierdaTC(arbol, nodo->izq);
  rotacionDerechaTC(arbol, nodo);
}

//Funcion para balancear un arbol
void balancearArbolTC(ArbolTC *arbol, NodoTA *nodo)
{
  NodoTA *padre;

  if(nodo != NULL)
  {
    padre = nodo->padre;
    nodo->factorEq = factorEquilibrioTC(nodo);
    if(nodo->factorEq > 1)
    {
      if(factorEquilibrioTC(nodo->der) < 0)
      {
        rotacionDobleIzquierdaTC(arbol, nodo);
      }
      else
      {
        rotacionIzquierdaTC(arbol, nodo);
      }
    }
    else if(nodo->factorEq < -1)
    {
      if(factorEquilibrioTC(nodo->izq) > 0)
      {
        rotacionDobleDerechaTC(arbol, nodo);
      }
      else
      {
        rotacionDerechaTC(arbol, nodo);
      }
    }
    balancearArbolTC(arbol, padre);
  }
}

#endif