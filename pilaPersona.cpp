#include "../include/pilaPersona.h"
#include "../include/personasLDE.h"

struct rep_pilaPersona {
  TPersonasLDE listaPersonas;
  nat cantPersonas;
};

TPilaPersona crearTPilaPersona() {
  TPilaPersona pila = new rep_pilaPersona;
  pila->listaPersonas = crearTPersonasLDE();
  pila->cantPersonas = 0;
  return pila ;
}

void liberarTPilaPersona(TPilaPersona &p) {
  if (p!=NULL)
  {
    p->cantPersonas = 0;
    liberarTPersonasLDE(p->listaPersonas);
  }
  delete p;
  p=NULL;
}

nat cantidadEnTPilaPersona(TPilaPersona p) { 
  return p->cantPersonas;
}

void apilarEnTPilaPersona(TPilaPersona &p, TPersona persona) {
  insertarInicioDeTPersonasLDE(p->listaPersonas,copiarTPersona(persona));
  p->cantPersonas++;
}

TPersona cimaDeTPilaPersona(TPilaPersona p) { 
  return obtenerInicioDeTPersonasLDE(p->listaPersonas);
}

void desapilarDeTPilaPersona(TPilaPersona &p) {
  if (p!=NULL)
  {
    // if (obtenerInicioDeTPersonasLDE(p->listaPersonas)!=NULL)
    // {
    //   TPersona aBorrar = obtenerInicioDeTPersonasLDE(p->listaPersonas);
    //   liberarTPersona(aBorrar);
    // }
    
    eliminarInicioTPersonasLDE(p->listaPersonas);
    p-> cantPersonas-- ; 
  }
  
}
