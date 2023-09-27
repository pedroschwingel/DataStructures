#include "../include/colaDePrioridadPersona.h"
#include "../include/utils.h"
#include "../include/evento.h"

enum ordenPadre{ mayorIgual=1,menorIgual=-1};
struct rep_colaDePrioridadPersona {
    TPersona * arregloTPersona;
    TPersona * arregloIds;
    ordenPadre ordenDePrioridad;
    nat max;
    nat cantElementos;
};
TColaDePrioridadPersona crearCP(nat N) {
  TColaDePrioridadPersona colaPrioridad = new rep_colaDePrioridadPersona;
  colaPrioridad->arregloIds = new TPersona[N+1];
  colaPrioridad->arregloTPersona = new TPersona[N+1];
  colaPrioridad->cantElementos=0;
  colaPrioridad->max = N;
  for (nat i = 1; i <= N; i++)
  {
    colaPrioridad->arregloTPersona[i] = NULL;
    colaPrioridad->arregloIds[i]=NULL;
  }
  colaPrioridad->ordenDePrioridad = menorIgual;
  return colaPrioridad;
} 
TPersona prioritaria(TColaDePrioridadPersona cp) {
  return cp->arregloTPersona[1];
} 

TFecha obtenerFechaPrioridad(TPersona persona){
  if (persona!=NULL)
  {
    return fechaTEvento(primerEventoDeTPersona(persona));
  }
  else{
    return NULL;
  }
  
}
void filtradoAscendente(TColaDePrioridadPersona &cp, nat pos)
{ 
    if (pos <= cp->cantElementos && pos > 1)
    {
      while (pos > 1 && compararTFechas(obtenerFechaPrioridad(cp->arregloTPersona[pos]),obtenerFechaPrioridad(cp->arregloTPersona[pos/2])) == cp->ordenDePrioridad)
      {
        nat padre = pos/2;
        TPersona aux = cp->arregloTPersona[pos];
        cp->arregloTPersona[pos] = cp->arregloTPersona[padre];
        cp->arregloTPersona[padre] = aux;
        pos = padre;
      }
    }
}
void filtradoDescendente(TColaDePrioridadPersona &cp, nat pos){
  while (2*pos <= cp->cantElementos)
  {
    //mientras tenga hijos (2*pos <= tope) chequeo cual de los dos hijos(2*pos y 2*pos+1) es menor y comparo. SI el hijo menor es menor que el padre(pos) los swapo y ahora mi posicion pasa a ser la posicion del hijo con que swapeé, SINO corto el while con break
      nat hijo = 2*pos;
      //maybe we have 2 children, lets  take the most priority
      if ((hijo+1 <= cp->cantElementos) && 
      (compararTFechas(obtenerFechaPrioridad(cp->arregloTPersona[hijo+1]),obtenerFechaPrioridad(cp->arregloTPersona[hijo])) == cp->ordenDePrioridad))
      {
        hijo = hijo+1;
      }
      //if the children is more priority, swap
      if (compararTFechas(obtenerFechaPrioridad(cp->arregloTPersona[hijo]),obtenerFechaPrioridad(cp->arregloTPersona[pos])) == cp->ordenDePrioridad) 
      {
        TPersona aux = cp->arregloTPersona[hijo];
        cp->arregloTPersona[hijo] = cp->arregloTPersona[pos];
        cp->arregloTPersona[pos] = aux;
        pos=hijo;
      }
      else{
        break;
      }
  }
}
void invertirPrioridad(TColaDePrioridadPersona &cp) {

  if (cp->ordenDePrioridad == menorIgual)
  {
    cp->ordenDePrioridad = mayorIgual;
    for (nat i = 2; i <= cp->cantElementos; i++)
    {
      filtradoAscendente(cp,i);
    }
    
  }
  else{
    cp->ordenDePrioridad = menorIgual;
     for (nat i = cp->cantElementos/2; i>= 1; i--){
      filtradoDescendente(cp,i);
    }
  }
}
void liberarCP(TColaDePrioridadPersona &cp) {
  if (cp!=NULL)
  {
    for (nat i = 1; i <= cp->max; i++)
    {
      cp->arregloIds[i]=NULL;
      if (cp->arregloTPersona[i]!=NULL)
      {
        liberarTPersona(cp->arregloTPersona[i]);
      }
      
    }
    cp->cantElementos=0;
    cp->max=0;
    delete[] cp->arregloTPersona;
    delete[] cp->arregloIds;
  }
  delete cp;
  cp=NULL;
}
void insertarEnCP(TPersona persona, TColaDePrioridadPersona &cp) {
    if (cp->cantElementos + 1 <= cp->max )
    {
      cp->cantElementos++;
      cp->arregloTPersona[cp->cantElementos]= persona;
      cp->arregloIds[idTPersona(persona)] = persona;
      filtradoAscendente(cp,cp->cantElementos);
    }   
}
bool estaVaciaCP(TColaDePrioridadPersona cp) {
  if (cp!=NULL) 
  {
    return (cp->cantElementos == 0);
  }
  else{
    return false;  
  }
}
void eliminarPrioritaria(TColaDePrioridadPersona &cp) {
    if (!estaVaciaCP(cp))
    {
      TPersona aux = cp->arregloTPersona[1];
      cp->arregloTPersona[1] = cp->arregloTPersona[cp->cantElementos];
      cp->arregloTPersona[cp->cantElementos] = aux;
      cp->arregloIds[idTPersona(aux)] = NULL;
      liberarTPersona(cp->arregloTPersona[cp->cantElementos]);
      cp->cantElementos--;
      filtradoDescendente(cp,1);
    }
}
bool estaEnCP(nat id, TColaDePrioridadPersona cp) {
  if (id>=1 && id<=cp->max)
  {
    return (cp->arregloIds[id] != NULL );
  }
  else
  {
    return false;
  }
}

TFecha prioridad(nat id, TColaDePrioridadPersona cp){
  return (obtenerFechaPrioridad(cp->arregloIds[id]));
}