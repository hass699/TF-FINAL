#include <iostream>
#include "HospitalUtils.h"
#include "ListaDobleMedico.h"
#include "ListaDoblePaciente.h"
#include "ListaDobleSucursal.h"
#include "ArbolHabitacion.h"
#include "ArbolTransaccionA.h"
#include "ArbolTransaccionC.h"

using namespace std;

HospitalUtils h;
//Listas doblemente enlazadas
listaDobleMedico lm;
listaDoblePaciente lp;
listaDobleSucursal ls;

// Función para obtener la fecha como cadena
string obtenerFechaActual() 
{
    time_t tiempo_actual = time(nullptr);
    struct tm *tiempo_info = localtime(&tiempo_actual);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y%m%d", tiempo_info);
    return string(buffer);
}
// Función para generar un ID único usando la fecha y el DNI del paciente
long long generarID(int dni) 
{
    string fecha_actual = obtenerFechaActual();
    string id_str = fecha_actual + to_string(dni);

    return stoll(id_str);
} 
//Registrar medico
void registrarMedico(NodoM *inicioC, NodoM *finC, NodoM *inicioO, NodoM *finO, NodoM *inicioN, NodoM *finN, NodoM *inicioT, NodoM *finT)
{
  NodoM *aux;
  bool existe;
  Medico m;
  int dni;
  string nombre;
  string apellido;
  int edad;
  int especialidad;

  do
  {
    cout << "Ingrese la especialidad del medico " << endl;
    cout << "Cardiologia   = 1 " << endl;
    cout << "Oncologia     = 2 " << endl;
    cout << "Neurologia    = 3 " << endl;
    cout << "Traumatologia = 4 " << endl;
    cout << "Salir = 0" << endl;
    cout << "Especialidad: ";
    cin >> especialidad;
  }while((especialidad < 1 || especialidad > 4) && especialidad != 0); 

  switch(especialidad)
  {
    case 1:
      cout << "Ingrese el dni del medico: ";
      cin >> dni;
      existe = lm.medicoExiste(inicioC, finC, dni);
      break;
    case 2:
      cout << "Ingrese el dni del medico: ";
      cin >> dni;
      existe = lm.medicoExiste(inicioO, finO, dni);
      break;
    case 3:
      cout << "Ingrese el dni del medico: ";
      cin >> dni;
      existe = lm.medicoExiste(inicioN, finN, dni);
      break;
    case 4:
      cout << "Ingrese el dni del medico: ";
      cin >> dni;
      existe = lm.medicoExiste(inicioT, finT, dni);
      break;
  }

  if(existe == false)
  {
    cout << "Ingrese el nombre del medico: ";
    cin >> nombre;
    cout << "Ingrese el apellido del medico: ";
    cin >> apellido;
    do
    {
      cout << "Ingrese la edad: ";
      cin >> edad;
    }while(edad < 0 || edad > 100);


    m = Medico(dni, nombre, apellido, edad, especialidad);
    aux = crearNodoM(m);

    switch(aux->medico.especialidad)
    {
      case 1:
        lm.agregarMedico(inicioC, finC, aux);
        break;
      case 2:
        lm.agregarMedico(inicioO, finO, aux);
        break;
      case 3:
        lm.agregarMedico(inicioN, finN, aux);
        break;
      case 4:
        lm.agregarMedico(inicioT, finT, aux);
        break;
    }
    cout << "\033[2J\033[1;1H";
    cout << "Medico registrado exitosamente!\n" << endl;
  }
  else
  {
    if(especialidad == 0)
    {
      cout << "\033[2J\033[1;1H";
      cout << "Saliendo...\n" << endl;
    }
    else
    {
      cout << "\033[2J\033[1;1H";
      cout << "El medico ya existe\n" << endl;
    }
  }
}
//Registrar Habitacion
void registrarHabitacion(ArbolH *arbolh)
{
  Habitacion h;
  NodoP* p = NULL;
  NodoM* m = NULL;
  NodoH *aux;
  NodoH *auxh;
  int id;
  int tam;
  bool estado = false;


  cout << "Ingrese el id de la habitacion: ";
  cin >> id;
  aux = buscarNodoHabitacion(arbolh, id);
  if(aux == NULL)
  {
    cout << "Ingrese el tamano de la habitacion: ";
    cin >> tam;

    h = Habitacion(id, tam, p, m, estado);

    auxh = crearNodoH(h);
    insertarNodoH(arbolh, auxh);
    cout << "\033[2J\033[1;1H";
    cout << "Paciente registrado exitosamente!\n" << endl;
  }
  else
  {
    cout << "\033[2J\033[1;1H";
    cout << "La habitacion ya existe\n" << endl;
  }
}
//Registrar Transaccion Abierta
void registrarTransaccionAbierta(ArbolTA *arbol, NodoH *h, int esp)
{
  NodoTA *aux;
  TransaccionAbierta ta;
  long id = generarID(h->hab.paciente->paciente.dni);
  string fechaIngreso;
  string fechaEgreso = " ";
  string motivo = " ";
  float tarifa;
  float total = 0;
  int internado = 0;

  cout << "Ingrese la fecha de ingreso(dd/mm/aaaa): ";
  cin >> fechaIngreso;
  cout << "Ingrese la tarifa: ";
  cin >> tarifa;

  ta = TransaccionAbierta(id, esp, fechaIngreso, fechaEgreso, tarifa, internado, total, motivo, h);
  aux = crearNodoTA(ta);
  insertarNodoTA(arbol, aux);
  cout << "\033[2J\033[1;1H";
  cout << "Transaccion registrada exitosamente!\n" << endl;
}
//Registrar Paciente
void registrarPaciente(NodoP *inicio, NodoP *fin)
{
  Paciente p;
  NodoP *aux;
  NodoP *auxp;
  int dni;
  int edad;
  string nombre;
  string apellido;
  string tipoLes;
  string sexo;
  float peso;
  float altura;

  cout << "Ingrese el dni del paciente: ";
  cin >> dni;
  aux = lp.encontrarPaciente(inicio, fin, dni);

  if(aux == NULL)
  {
    cout << "Ingrese el nombre del paciente: ";
    cin >> nombre;
    cout << "Ingrese el apellido del paciente: ";
    cin >> apellido;
    do
    {
      cout << "Ingrese la edad: ";
      cin >> edad;
    }while(edad < 0 || edad > 100);
    cout << "Ingrese el sexo del paciente: ";
    cin >> sexo;
    cout << "Ingrese el peso del paciente: ";
    cin >> peso;
    cout << "Ingrese la altura del paciente: ";
    cin >> altura;

    p = Paciente(dni, nombre, apellido, sexo, edad, peso, altura);

    auxp = crearNodoP(p);
    lp.agregarPaciente(inicio, fin, auxp);
    cout << "\033[2J\033[1;1H";
    cout << "Paciente registrado exitosamente!\n" << endl;
  }
  else
  {
    cout << "\033[2J\033[1;1H";
    cout << "El paciente ya existe\n" << endl;
  }
}
//Registrar especialidad;
int mostrarEspecialidad()
{
  int esp;
  do
  {
    cout << "Ingrese la especialidad del medico " << endl;
    cout << "Cardiologia   = 1 " << endl;
    cout << "Oncologia     = 2 " << endl;
    cout << "Neurologia    = 3 " << endl;
    cout << "Traumatologia = 4 " << endl;
    cout << "Especialidad: ";
    cin >> esp;
  }while(esp < 1 || esp > 4);

  return esp;
}
//Registrar DNI
int mostrarDNI()
{
  int dni;
  cout << "Ingrese el dni: ";
  cin >> dni;

  return dni;
}
//Registrar id 
int mostrarID()
{
  int id;
  cout << "Ingrese el id de la habitacion: ";
  cin >> id;

  return id;
}
//Funcion de retorno booleano para validar el registro
bool registroExitoso(unordered_map<string, string> credenciales, string username,                          string password)
{
  if(h.login(credenciales, username, password)) 
  {
    return true;
  } 
  return false;
}
//mostrar ransaccion
void mostrarTransaccionAbierta(NodoP *i, NodoP *f, ArbolTA * arbol)
{
  NodoTA *auxta;
  NodoP* auxp;
  int dni;

  dni = mostrarDNI();
  auxp = lp.encontrarPaciente(i, f, dni);
  cout << "\033[2J\033[1;1H";
  if (auxp != NULL) 
  {
    auxta = buscarNodoPacienteTA(arbol, auxp->paciente.dni);
    if (auxta != NULL) 
    { 
      cout << "Transaccion abierta" << endl;
      cout << "\nID: " << auxta->trana.id << endl;
      cout << "Paciente: " << auxta->trana.h->hab.paciente->paciente.nombre << " " << auxta->trana.h->hab.paciente->paciente.apellido << endl;
      cout << "Doctor: Dr. " << auxta->trana.h->hab.medico->medico.nombre << " " << auxta->trana.h->hab.medico->medico.apellido << endl;
      cout << "Habitacion: " << auxta->trana.h->hab.id << endl;
      cout << "Fecha entrada: " << auxta->trana.fechaIngreso << endl;
      cout << "Tarifa: " << auxta->trana.tarifa << endl;
      switch(auxta->trana.especialidad)
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

      cout << "\n";
    } 
    else 
    { // Si paciente no tiene transaccion abierta
      cout << "El paciente no tiene una transaccion abierta\n" << endl;
    }
  } 
  else 
  { // Si paciente no existe
    cout << "Paciente no encontrado\n" << endl;
  }
}
//Transaccion cerrada

int main() {
  unordered_map<string, string> credenciales;
  credenciales["usuario1"] = "contrasena1";
  credenciales["usuario2"] = "contrasena2";
  credenciales["u"] = "1234";
  //Arboles
  ArbolH *arbolh = crearArbolH();
  ArbolTA *arbolta = crearArbolTA();
  ArbolTC *arboltc = crearArbolTC();
  //Nodos de lista enlazada
  NodoM *inicioC = NULL;
  NodoM *inicioO = NULL;
  NodoM *inicioT = NULL;
  NodoM *inicioN = NULL;
  NodoM *finC = NULL;
  NodoM *finO = NULL;
  NodoM *finT = NULL;
  NodoM *finN = NULL;
  NodoM *auxm;
  NodoS *inicioS = NULL;
  NodoS *finS = NULL;
  NodoS *auxs;
  NodoH *auxh;
  NodoP *inicioPac = NULL;
  NodoP *finPac = NULL;
  NodoP *auxp;
  NodoTA *auxta;
  //Registro
  string username, password;
  Medico med;
  TransaccionAbierta ta;
  Paciente pac;
  Habitacion hab;
  Sucursal s1 = crearS(1);
  vector<NodoTA*> transaccionC;
  //Validacion
  int opc = 0;
  int dni;
  int id;
  int esp;
  //Lectura de medicos
  lm.leerMedicos(inicioC, finC, 1);
  lm.leerMedicos(inicioO, finO, 2);
  lm.leerMedicos(inicioN, finN, 3);
  lm.leerMedicos(inicioT, finT, 4);
  //Lectura de pacientes
  lp.leerPacientes(inicioPac, finPac);
  //Lectura de habitaciones
  insertarNodoH(arbolh, crearNodoH(crearH(1101, 120, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1102, 120, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1103, 120, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1104, 120, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1105, 120, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1106, 120, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1107, 120, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1108, 120, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1109, 120, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1110, 120, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1201, 110, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1202, 110, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1203, 110, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1204, 110, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1205, 110, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1206, 110, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1207, 110, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1208, 110, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1209, 110, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1210, 110, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1301, 120, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1302, 120, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1303, 120, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1304, 120, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1305, 120, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1306, 120, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1307, 120, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1308, 120, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1309, 120, NULL, NULL, false)));
  insertarNodoH(arbolh, crearNodoH(crearH(1310, 120, NULL, NULL, false)));
  //Insertar habitaciones a una sucursal
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1101));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1102));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1103));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1104));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1105));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1106));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1107));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1108));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1109));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1110));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1201));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1202));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1203));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1204));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1205));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1206));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1207));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1208));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1209));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1210));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1301));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1302));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1303));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1304));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1305));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1306));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1307));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1308));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1309));
  s1.agregarHabitacion(buscarNodoHabitacion(arbolh, 1310));
  //Lectura de sucursales
  ls.agregarSucursal(inicioS, finS, crearNodoS(s1));

  do 
  {
    cout << "****** MENÚ ******" << endl;
    cout << "1. Iniciar sesión" << endl;
    cout << "2. Registrar usuario" << endl;
    cout << "3. Salir" << endl;
    cout << "Opcion: "; cin >> opc;
    cout << "\033[2J\033[1;1H";

    switch (opc) 
    {
      case 1:
        /*
        cout << "Ingrese nombre de usuario: ";
        cin >> username;
        cout << "Ingrese contraseña: ";
        cin >> password;
        */
        username = "u";
        password = "1234";
        if(registroExitoso(credenciales, username, password))
        {
          cout << "\033[2J\033[1;1H";
          do
          {
            cout << "****** HOSPITAL ******" << endl;
            cout << "1. Paciente" << endl; //Completo
            cout << "2. Doctor" << endl; //Completo
            cout << "3. Sucural" << endl;  //Completo
            cout << "4. Habitacion" << endl; //Completo
            cout << "5. Atencion" << endl; //Completo
            cout << "6. Transacciones" << endl; //Completo
            cout << "7. Sala de emergencia" << endl;
            cout << "8. Reporte" << endl;
            cout << "9. Salir" << endl;
            cout << "Opcion: "; cin >> opc;
            cout << "\033[2J\033[1;1H";
            switch(opc)
            {
              case 1:
                do
                {
                  cout << "****** PACIENTE ******" << endl;
                  cout << "1. Registrar Paciente" << endl;
                  cout << "2. Mostrar Pacientes" << endl;
                  cout << "3. Modificar Paciente" << endl;
                  cout << "4. Eliminar Paciente" << endl;
                  cout << "5. Buscar Paciente" << endl;
                  cout << "6. Salir" << endl;
                  cout << "Opcion: "; cin >> opc;
                  cout << "\033[2J\033[1;1H";
                  switch(opc)
                  {
                    case 1:
                      registrarPaciente(inicioPac, finPac);
                      break;
                    case 2:
                      cout << "Pacientes: \n" << endl;
                      lp.mostrarPaciente(inicioPac, finPac);
                      break;
                    case 3:
                      dni = mostrarDNI();
                      cout << "\033[2J\033[1;1H";
                      lp.modificarPaciente(inicioPac, finPac, dni);
                      break;
                    case 4:
                      dni = mostrarDNI();
                      cout << "\033[2J\033[1;1H";
                      lp.eliminarPaciente(inicioPac, finPac, dni);
                      break;
                    case 5:
                      dni = mostrarDNI();
                      cout << "\033[2J\033[1;1H";
                      lp.buscarPaciente(inicioPac, finPac, dni);
                      break;
                    case 6:
                      cout << "\033[2J\033[1;1H";
                      cout << "Saliendo de paciente..." << endl;
                      break;
                    default:
                      cout << "Opcion invalida" << endl << endl;
                      break;
                  }
                  cout << "\n";
                }while(opc != 6);
                break;
              case 2:
                do
                {
                  cout << "****** DOCTOR ******" << endl;
                  cout << "1. Registrar Doctor" << endl;
                  cout << "2. Mostrar Doctores" << endl;
                  cout << "3. Modificar Doctor" << endl;
                  cout << "4. Eliminar Doctor" << endl;
                  cout << "5. Buscar Doctor" << endl;
                  cout << "6. Salir" << endl;
                  cout << "Opcion: "; cin >> opc;
                  cout << "\033[2J\033[1;1H";
                  switch(opc)
                  {
                    case 1:
                      registrarMedico(inicioC, finC, inicioO, finO, inicioN,                                              finN, inicioT, finT);
                      break;
                    case 2:
                      esp = mostrarEspecialidad();
                      cout << "\033[2J\033[1;1H";
                      switch(esp)
                      {
                        case 1:
                          cout << "******Cardiologia******" << endl;
                          lm.mostrarMedico(inicioC, finC);
                          break;
                        case 2:
                          cout << "******Oncologia******" << endl;
                          lm.mostrarMedico(inicioO, finO);
                          break;
                        case 3:
                          cout << "******Neurologia******" << endl;
                          lm.mostrarMedico(inicioN, finN);
                          break;
                        case 4:
                          cout << "******Traumatologia******" << endl;
                          lm.mostrarMedico(inicioT, finT);
                          break;
                      }
                      cout << "\n";
                      break;
                    case 3:
                      dni = mostrarDNI();
                      esp = mostrarEspecialidad();
                      cout << "\033[2J\033[1;1H";
                      switch(esp)
                      {
                        case 1:
                          lm.modificarMedico(inicioC, finC, dni);
                          break;
                        case 2:
                          lm.modificarMedico(inicioO, finO, dni);
                          break;
                        case 3:
                          lm.modificarMedico(inicioN, finN, dni);
                          break;
                        case 4:
                          lm.modificarMedico(inicioT, finT, dni);
                          break;
                        default:
                          cout << "Opcion invalida" << endl << endl;
                      }
                      cout << "\n";
                      break;
                    case 4:
                      dni = mostrarDNI();
                      esp = mostrarEspecialidad();
                      cout << "\033[2J\033[1;1H";
                      switch(esp)
                      {
                        case 1:
                          lm.eliminarMedico(inicioC, finC, dni);
                          break;
                        case 2:
                          lm.eliminarMedico(inicioO, finO, dni);
                          break;
                        case 3:
                          lm.eliminarMedico(inicioN, finN, dni);
                          break;
                        case 4:
                          lm.eliminarMedico(inicioT, finT, dni);
                          break;
                      }
                      cout << "\n";
                      break;
                    case 5:
                      dni = mostrarDNI();
                      esp = mostrarEspecialidad();
                      cout << "\033[2J\033[1;1H";
                      switch(esp)
                      {
                        case 1:
                          lm.buscarMedico(inicioC, finC, dni);
                          break;
                        case 2:
                          lm.buscarMedico(inicioO, finO, dni);
                          break;
                        case 3:
                          lm.buscarMedico(inicioN, finN, dni);
                          break;
                        case 4:
                          lm.buscarMedico(inicioT, finT, dni);
                          break;
                      }
                      cout << "\n";
                      break;
                    case 6:
                      cout << "\033[2J\033[1;1H";
                      cout << "Saliendo de medico...\n" << endl;
                      break;
                    default:
                      cout << "\nOpcion invalida" << endl;
                  }
                }while(opc != 6);
                break;
              case 3:
                do
                {
                  cout << "****** SUCURSAL ******" << endl;
                  cout << "1. Crear Sucursal" << endl;
                  cout << "2. Modificar Sucursal" << endl;
                  cout << "3. Eliminar Sucursal" << endl;
                  cout << "4. Mostrar Sucursal" << endl;
                  cout << "5. Buscar Sucursal" << endl;
                  cout << "6. Salir" << endl;
                  cout << "Opcion: "; cin >> opc;
                  cout << "\033[2J\033[1;1H";
                  switch(opc)
                  {
                    case 1:
                      id = mostrarID();
                      cout << "\033[2J\033[1;1H";
                      if(ls.sucursalExiste(inicioS, finS, id))
                      {
                        cout << "Sucursal existente\n" << endl;
                      }
                      else
                      {
                        auxs = crearNodoS(id);
                        ls.agregarSucursal(inicioS, finS, auxs);
                        cout << "\033[2J\033[1;1H";
                        cout << "Sucursal registrada existosamente!\n" << endl;
                      }
                      break;
                    case 2:
                      id = mostrarID();
                      cout << "\033[2J\033[1;1H";
                      ls.modificarSucursal(inicioS, finS, id);
                      break;
                    case 3:
                      id = mostrarID();
                      cout << "\033[2J\033[1;1H";
                      ls.eliminarSucursal(inicioS, finS, id);
                      break;
                    case 4:
                      ls.mostrarSucursal(inicioS, finS);
                      break;
                    case 5:
                      id = mostrarID();
                      cout << "\033[2J\033[1;1H";
                      ls.buscarSucursal(inicioS, finS, id);
                      break;
                    case 6:
                      cout << "\033[2J\033[1;1H";
                      cout << "Saliendo de sucursal...\n" << endl;
                      break;
                    default:
                      cout << "Opcion invalida\n" << endl;
                  }
                }while(opc != 6);
                break;
              case 4:
                do
                {
                  cout << "****** HABITACION ******" << endl;
                  cout << "1. Crear habitaciones" << endl;
                  cout << "2. Modificar habitacion" << endl;
                  cout << "3. Eliminar habitacion" << endl;
                  cout << "4. Mostrar habitacion" << endl;
                  cout << "5. Buscar habitacion" << endl;
                  cout << "6. Salir" << endl;
                  cout << "Opcion: "; cin >> opc;
                  cout << "\033[2J\033[1;1H";
                  switch(opc)
                  {
                    case 1:
                      registrarHabitacion(arbolh);
                      break;
                    case 2:
                      id = mostrarID();
                      cout << "\033[2J\033[1;1H";
                      modificarNodoH(arbolh, id);
                      break;
                    case 3:
                      id = mostrarID();
                      cout << "\033[2J\033[1;1H";
                      eliminarNodoH(arbolh, id);
                      break;
                    case 4:
                      mostrarHabitaciones(arbolh->raiz);
                      cout << endl << endl;
                      break;
                    case 5:
                      id = mostrarID();
                      cout << "\033[2J\033[1;1H";
                      mostrarNodoHabitacionPac(arbolh, id);
                      break;
                    case 6:
                      cout << "\033[2J\033[1;1H";
                      cout << "Saliendo de habitacion...\n" << endl;
                      break;
                    default:
                      cout << "\nOpcion invalida" << endl;
                      break;
                  }
                }while(opc != 6);
                break;
              case 5:
                int dniD;
                do
                {
                  cout << "****** ATENCION ******" << endl;
                  cout << "1. Asignar paciente y doctor" << endl;
                  cout << "2. Quitar paciente y doctor" << endl;
                  cout << "3. Reasignar paciente y doctor" << endl;
                  cout << "4. Atender paciente" << endl;
                  cout << "5. Salir" << endl;
                  cout << "Opcion: "; cin >> opc;
                  cout << "\033[2J\033[1;1H";
                  switch(opc)
                  {
                    case 1:
                      cout << "Paciente: " << endl << endl;
                      dni = mostrarDNI();
                      auxp = lp.encontrarPaciente(inicioPac, finPac, dni);
                      cout << "\033[2J\033[1;1H";
                      if(auxp != NULL)
                      {
                        cout << "Medico: " << endl << endl;
                        esp = mostrarEspecialidad();
                        cout << "\033[2J\033[1;1H";
                        dniD = mostrarDNI();
                        cout << "\033[2J\033[1;1H";
                        switch(esp)
                        {
                          case 1:
                            auxm = lm.encontrarMedico(inicioC, finC, dniD);
                            break;
                          case 2:
                            auxm = lm.encontrarMedico(inicioO, finO, dniD);
                            break;
                          case 3:
                            auxm = lm.encontrarMedico(inicioN, finN, dniD);
                            break;
                          case 4:
                            auxm = lm.encontrarMedico(inicioT, finT, dniD);
                            break;
                          default:
                            cout << "Opcion invalida\n" << endl;
                        }

                        if(auxm != NULL)
                        {
                            cout << "Habitacion: " << endl << endl;
                            id = mostrarID();
                            auxh = buscarNodoHabitacion(arbolh, id);
                            if(auxh != NULL)
                            {
                              asignarHabitacion(auxh, auxp, auxm);
                              registrarTransaccionAbierta(arbolta, auxh, esp);
                              cout << "\033[2J\033[1;1H";
                              cout << "Paciente y doctor asignado correctamente!\n" << endl;
                            }
                            else
                            {
                              cout << "Habitacion no encontrada\n" << endl;
                            }
                        }
                        else
                        {
                          cout << "No se encontro al medico\n" << endl;
                        }
                      }
                      else
                      {
                        cout << "No se encontro al paciente\n" << endl;
                      }
                      break;
                    case 2:
                      cout << "Habitacion: " << endl;
                      id = mostrarID();
                      auxh = buscarNodoHabitacion(arbolh, id);
                      cout << "\033[2J\033[1;1H";
                      if(auxh != NULL)
                      {
                        if(auxh->hab.paciente != NULL && auxh->hab.medico != NULL)
                        {
                          quitarAsignarHabitacion(auxh);
                          eliminarNodoHabTA(arbolta, auxh->hab.id);
                        }
                        else
                        {
                          cout << "La habitacion no tiene paciente o doctor asignado\n" << endl;
                        }
                      }
                      else
                      {
                        cout << "No se encontro la habitacion\n" << endl;
                      }
                      break;
                    case 3:
                      int id2;
                      cout << "Habitacion: " << endl;
                      id = mostrarID();
                      auxta = buscarNodoHabTA(arbolta, id);
                      cout << "\033[2J\033[1;1H";
                      if(auxta != NULL)
                      {
                        cout << "Habitacion: " << endl;
                        id2 = mostrarID();
                        auxh = buscarNodoHabitacion(arbolh, id2);
                        cout << "\033[2J\033[1;1H";
                        if(auxh != NULL)
                        {
                          if(auxh->hab.paciente == NULL && auxh->hab.medico == NULL)
                          {
                            reasignarHabitacion(auxh, auxta, arbolta);
                          }
                          else
                          {
                            cout << "La habitacion ya tiene paciente o doctor asignado\n" << endl;
                          }
                        }
                        else
                        {
                          cout << "Habitacion no encontrada\n" << endl;
                        }
                      }
                      else
                      {
                        cout << "La habitacion no tiene paciente o doctor asignado\n" << endl;
                      }
                      break;
                    case 4:
                      cout << "Paciente: " << endl << endl;
                      dni = mostrarDNI();
                      auxp = lp.encontrarPaciente(inicioPac, finPac, dni);
                      cout << "\033[2J\033[1;1H";
                      if (auxp != NULL) 
                      {
                        auxta = buscarNodoPacienteTA(arbolta, dni);
                        if (auxta != NULL) 
                        {
                          atenderPaciente(auxta, arboltc, arbolta, dni);
                        }
                        else 
                        {
                          cout << "\nEl paciente no tiene una habitacion" << endl;
                        }
                      } 
                      else 
                      {
                        cout << "\nPaciente no encontrado" << endl;
                      }

                      break;
                    case 5:
                      cout << "\033[2J\033[1;1H";
                      cout << "Saliendo de atencion...\n" << endl;
                      break;
                    default:
                      cout << "Opcion invalida\n" << endl;
                      break;
                  }
                }while(opc != 5);
                break;
              case 6:
                do
                {
                  cout << "***** TRANSACCIONES *****" << endl;
                  cout << "1. Transaccion abierta" << endl;
                  cout << "2. Transaccion cerrada" << endl;
                  cout << "3. Salir" << endl;
                  cout << "Opcion: "; cin >> opc;
                  cout << "\033[2J\033[1;1H";
                  switch(opc)
                  {
                    case 1:
                      do
                      {
                        cout << "***** TRANSACCION ABIERTA *****" << endl;
                        cout << "1. Buscar transaccion" << endl;
                        cout << "2. Modificar transaccion" << endl;
                        cout << "3. Eliminar transaccion" << endl;
                        cout << "4. Salir" << endl;
                        cout << "Opcion: "; cin >> opc;
                        cout << "\033[2J\033[1;1H";
                        switch(opc)
                        {
                          case 1:
                            mostrarTransaccionAbierta(inicioPac, finPac, arbolta);
                            break;
                          case 2:
                            dni = mostrarDNI();
                            cout << "\033[2J\033[1;1H";
                            modificarTransaccionAbierta(arbolta, dni);
                            break;
                          case 3:
                            dni = mostrarDNI();
                            auxta = buscarNodoPacienteTA(arbolta, dni);
                            cout << "\033[2J\033[1;1H";
                            if(auxh != NULL)
                            {
                              eliminarNodoTA(arbolta, dni);
                              quitarAsignarHabitacion(auxta->trana.h);
                            }
                            else
                            {
                              cout << "El paciente no tiene una transaccion abierta\n" << endl;
                            }
                            break;
                          case 4:
                            cout << "\033[2J\033[1;1H";
                            cout << "Saliendo de transaccion...\n" << endl;
                            break;
                          default:
                            cout << "Opcion invalida\n" << endl;
                        }
                      }while(opc != 4);
                      break;
                    case 2:
                      do
                      {
                        cout << "***** TRANSACCION CERRADA *****" << endl;
                        cout << "1. Buscar transaccion" << endl;
                        cout << "2. Salir" << endl;
                        cout << "Opcion: "; cin >> opc;
                        cout << "\033[2J\033[1;1H";
                        switch(opc)
                        {
                          case 1:
                            cout << "Paciente: " << endl << endl;
                            dni = mostrarDNI();
                            cout << "\033[2J\033[1;1H";
                            cout << "Transaccion cerrada: " << endl;
                            inOrdenTC(arboltc->raiz, dni, inicioPac, finPac);
                            break;
                          case 2:
                            cout << "\033[2J\033[1;1H";
                            cout << "Saliendo de transaccion...\n" << endl;
                            break;
                          default:
                            cout << "Opcion invalida\n" << endl;
                        }
                      }while(opc != 2);
                      break;
                    case 3:
                      cout << "\033[2J\033[1;1H";
                      cout << "Saliendo de transacciones...\n" << endl;
                      break;
                    default:
                      cout << "Opcion invalida\n" << endl;
                  }
                }while(opc != 3);
                break;
              case 7:
                do
                {
                  cout << "***** SALA DE EMERGENCIA *****" << endl;
                  cout << "1. Mostrar Salas" << endl;
                  cout << "2. Ruta mas corta" << endl;
                  cout << "3. Salir" << endl;
                  cout << "Opcion: "; cin >> opc;
                  cout << "\033[2J\033[1;1H";
                  switch(opc)
                  {
                    case 1:
                      break;
                    case 2:
                      break;
                    case 3:
                      cout << "\033[2J\033[1;1H";
                      cout << "Saliendo de la sala de emergencias...\n" << endl;
                      break;
                    default:
                      cout << "Opcion invalida\n" << endl;
                  }
                }while(opc != 3);
                break;
              case 8:
                do
                {
                  cout << "***** REPORTES *****" << endl;
                  cout << "1. Transaccion Abierta" << endl;
                  cout << "2. Transaccion Cerrada" << endl;
                  cout << "3. Salir" << endl;
                  cout << "Opcion: "; cin >> opc;
                  cout << "\033[2J\033[1;1H";
                  switch(opc)
                  {
                    case 1:
                      do
                      {
                        cout << "***** TRANSACCION ABIERTA *****" << endl;
                        cout << "1. Paciente" << endl;
                        cout << "2. Habitacion" << endl;
                        cout << "3. Sucursal" << endl;
                        cout << "4. Salir" << endl;
                        cout << "Opcion: "; cin >> opc;
                        cout << "\033[2J\033[1;1H";
                        switch(opc)
                        {
                          case 1:
                            break;
                          case 2:
                            break;
                          case 3:
                            break;
                          case 4:
                            cout << "\033[2J\033[1;1H";
                            cout << "Saliendo de transaccion...\n" << endl;
                            break;
                          default:
                            cout << "Opcion invalida\n" << endl;
                        }
                      }while(opc != 4);
                      break;
                    case 2:
                      do
                      {
                        cout << "***** TRANSACCION CERRADA *****" << endl;
                        cout << "1. Paciente" << endl;
                        cout << "2. Habitacion" << endl;
                        cout << "3. Sucursal" << endl;
                        cout << "4. Salir" << endl;
                        cout << "Opcion: "; cin >> opc;
                        cout << "\033[2J\033[1;1H";
                        switch(opc)
                        {
                          case 1:
                            break;
                          case 2:
                            break;
                          case 3:
                            break;
                          case 4:
                            cout << "\033[2J\033[1;1H";
                            cout << "Saliendo de transaccion...\n" << endl;
                            break;
                          default:
                            cout << "Opcion invalida\n" << endl;
                        }
                      }while(opc != 4);
                      break;
                    case 3:
                      cout << "\033[2J\033[1;1H";
                      cout << "Saliendo de reportes...\n" << endl;
                      break;
                    default:
                      cout << "Opcion invalida\n" << endl;
                  }
                }while(opc != 3);
                break;
              case 9:
                lp.guardarPacientes(inicioPac);
                lm.guardarMedicos(inicioC);
                lm.guardarMedicos(inicioO);
                lm.guardarMedicos(inicioN);
                lm.guardarMedicos(inicioT);
                cout << "Saliendo del hospital...\n" << endl;
                break;
              default:
                cout << "Opcion invalida\n" << endl;
            }
          }while(opc != 9);
        }
        else
        {
          cout << "Credenciales incorrectas\n" << endl;
        }
        break;
      case 2: 
        cout << "Ingrese nombre de usuario para registrar: ";
        cin >> username;
        cout << "Ingrese contraseña para registrar: ";
        cin >> password;
        h.registrarUsuario(credenciales, username, password);
        break;
      case 3:
        cout << "Saliendo del sistema...\n" << endl;
        break;
      default:
        cout << "Opción inválida\n" << endl;
    }  
  }while (opc != 3);

  return 0;
}