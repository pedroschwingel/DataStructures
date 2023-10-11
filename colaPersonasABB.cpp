#include "../include/colaPersonasABB.h"
#include "../include/personasLDE.h"

struct nodo{
  TPersonasABB dato;
  nodo*sig;
};
typedef nodo* Tnodo;
struct rep_colaPersonasABB {
      Tnodo ini;
      Tnodo fin;
      nat cantPersonas;
};

TColaPersonasABB crearTColaPersonasABB() {
  TColaPersonasABB cola = new rep_colaPersonasABB;
    cola->cantPersonas=0;
    cola->ini=NULL;
    cola->fin=NULL;
   return cola;
}

void liberarTColaPersonasABB(TColaPersonasABB &c) {
  if (c!=NULL)
  {
    while (c->ini != NULL)
    {
      Tnodo Aux = c->ini;
      c->ini = c->ini->sig;
      c->cantPersonas--;
      delete Aux;
      Aux = NULL; 
      delete c->ini;
      c->ini = NULL;
    }
  }
    delete c;
    c = NULL;
}

nat cantidadEnTColaPersonasABB(TColaPersonasABB c) { 
  return c->cantPersonas;
 }

void encolarEnTColaPersonasABB(TPersonasABB t, TColaPersonasABB &c) {
  Tnodo aInsertar = new nodo;
  aInsertar->dato = t;
    if (c->ini == NULL)
    {
      c->ini = c->fin = aInsertar;
      aInsertar->sig = NULL;
    }
    else
    {
      c->fin->sig = aInsertar;
      c->fin = aInsertar;
      aInsertar->sig=NULL;
    }
    c->cantPersonas++;
   
}

TPersonasABB frenteDeTColaPersonasABB(TColaPersonasABB c) { 
  return c->ini->dato;
}

void desencolarDeTColaPersonasABB(TColaPersonasABB &c) {
    Tnodo aborrar = c->ini;
    c->ini = c->ini->sig;
    c->cantPersonas--;
    delete aborrar;
    aborrar=NULL;
}