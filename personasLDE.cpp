#include "../include/personasLDE.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////

struct nodo{
    TPersona persona;
    nodo *ant;
    nodo *sig; 
};
typedef struct nodo *Tnodo;
//a.k.a cabezal
struct rep_personasLDE {
    nat cantPersonas;
    Tnodo ini;
    Tnodo fin;
};
TPersonasLDE crearTPersonasLDE(){
    TPersonasLDE persona = new rep_personasLDE;
    persona->cantPersonas = 0; 
    persona->ini = NULL;
    persona->fin = NULL;
    return persona;
}
void insertarTPersonasLDE(TPersonasLDE &personas, TPersona persona, nat pos){
    //ERROR EN INSERTAR DOS PERSONAS EN LA MISMA POSICION 
    Tnodo aInsertar = new nodo;
    aInsertar->persona = persona;
    if (personas->ini == NULL)
    {
        personas->ini = personas->fin = aInsertar;
        aInsertar->ant = NULL;
        aInsertar->sig = NULL;
    }
    else if(pos==1)
    {
        aInsertar->sig = personas->ini;
        personas->ini->ant = aInsertar;
        aInsertar->ant = NULL;
        personas->ini = aInsertar;
    }
    else if (pos > personas->cantPersonas){
        //insertar al final
        personas->fin->sig = aInsertar;
        aInsertar->ant = personas->fin;
        aInsertar->sig=NULL;
        personas->fin = aInsertar;
       
    }
    else //insertar en el medio
    {
        Tnodo iter = personas->ini;
        while ((pos-1) != 1 && iter->sig!=NULL)
        {
            iter=iter->sig;
            pos--;
        }
        aInsertar->sig = iter->sig;
        iter->sig->ant = aInsertar;
        aInsertar->ant = iter;
        iter->sig = aInsertar;
    }
    personas->cantPersonas++;
}
void liberarTPersonasLDE(TPersonasLDE &personasLDE){
  if (personasLDE!=NULL)
  {
    while(personasLDE->ini!=NULL){
        Tnodo aBorrar = personasLDE->ini;
        personasLDE->ini = personasLDE->ini->sig;
        liberarTPersona(aBorrar->persona);
        personasLDE->cantPersonas--;
        delete aBorrar;        
    }
    delete personasLDE->ini;
    delete personasLDE;
    personasLDE = NULL;
  }
}
void imprimirTPersonasLDE(TPersonasLDE personas){
    if (personas->ini!=NULL )
    {
        nodo *aux = personas->ini;  
        while (aux !=NULL)
        {
            imprimirTPersona(aux->persona);
            aux=aux->sig;
        }
    }
    
}
nat cantidadTPersonasLDE(TPersonasLDE personas){
    return personas->cantPersonas;
}
void eliminarInicioTPersonasLDE(TPersonasLDE &personas){
    if (personas != NULL)
    {
        Tnodo aBorrar = personas->ini;
        if (aBorrar->sig != NULL)
        {
            personas->ini = personas->ini->sig;
            personas->ini->ant= NULL;
        }
        else{
            personas->ini = NULL;
            personas->fin = NULL;
        }
        personas->cantPersonas--;
        liberarTPersona(aBorrar->persona);
        delete aBorrar;
        aBorrar=NULL;
    }
}
void eliminarFinalTPersonasLDE(TPersonasLDE &personas){
    if (personas!=NULL)
    {
        Tnodo aBorrar = personas->fin;
        if (cantidadTPersonasLDE(personas) > 1)
        {   
          aBorrar->ant->sig = NULL;
          personas->fin = aBorrar->ant;
        }
        else{
            personas->ini=NULL;
            personas->fin=NULL;
        }
        personas->cantPersonas--;
        liberarTPersona(aBorrar->persona);
        delete aBorrar;
        aBorrar=NULL;
    }
}
bool estaEnTPersonasLDE(TPersonasLDE personas, nat id){
    Tnodo aux = personas->ini;
    bool esta = false;
    while (aux != NULL && idTPersona(aux->persona) != id)
    {
        aux=aux->sig;        
    }
    esta = (aux != NULL);
    return esta;
}

TPersona obtenerDeTPersonasLDE(TPersonasLDE personas, nat id){
    Tnodo iter = personas->ini;
    while (iter != NULL && idTPersona(iter->persona) != id )
    {
        iter=iter->sig;
    }
    return iter->persona;
}
TPersonasLDE concatenarTPersonasLDE(TPersonasLDE personas1, TPersonasLDE personas2){
    if(personas1!=NULL || personas2 != NULL)
    {
        TPersonasLDE listaConcat = crearTPersonasLDE();
        if (personas1->ini == NULL && personas2->ini != NULL)
        {
            listaConcat->cantPersonas = cantidadTPersonasLDE(personas2);
            listaConcat->ini = personas2->ini;
            listaConcat->fin = personas2->fin;

        }
        else if (personas1->ini != NULL && personas2->ini == NULL)
        {
            listaConcat->cantPersonas = cantidadTPersonasLDE(personas1);
            listaConcat->ini = personas1->ini;
            listaConcat->fin = personas1->fin;
        }
        else
        {
            listaConcat->ini = personas1->ini;
            personas1->fin->sig = personas2->ini;   
            personas2->ini->ant = personas1->fin;
            listaConcat->fin = personas2->fin;
            listaConcat->cantPersonas = (cantidadTPersonasLDE(personas1) + cantidadTPersonasLDE(personas2));
        }
        delete personas1;
        delete personas2;
        return listaConcat;  
    }
    else
    {
        return NULL;
    }
}
void insertarInicioDeTPersonasLDE(TPersonasLDE &personas, TPersona persona){
    Tnodo aInsertar = new nodo;
    aInsertar->persona = persona;
    if (personas->ini!=NULL)
    {
        Tnodo aux = personas->ini;
        personas->ini = aInsertar;
        aInsertar->ant = NULL;
       // aInsertar->ant = personas->ini;
        aInsertar->sig = aux;
        aux->ant = aInsertar;
    }
    else{
        personas->ini = personas->fin =aInsertar;
        aInsertar->ant = NULL;
        //aInsertar->ant=personas->ini;
        aInsertar->sig = NULL;
    }
    personas->cantPersonas++;
}

void insertarFinalDeTPersonasLDE(TPersonasLDE &personas, TPersona persona){
  
    Tnodo aInsertar = new nodo;
    aInsertar->persona = persona;
    if (personas->fin == NULL)
    {
        personas->ini = personas->fin = aInsertar;
        aInsertar->ant = personas->ini;
        aInsertar->sig=NULL;
    }
    else
    {
        aInsertar->ant = personas->fin;
        personas->fin->sig = aInsertar;
        aInsertar->sig=NULL;
        personas->fin = aInsertar;
    }
    personas->cantPersonas++;   
}

TPersona obtenerInicioDeTPersonasLDE(TPersonasLDE personas){
    return personas->ini->persona;
}

TPersona obtenerFinalDeTPersonasLDE(TPersonasLDE personas){
    return personas->fin->persona;
}

///////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void eliminarPersonaConNombreTPersonasLDE(TPersonasLDE &personas, const char nombre[100]){
    if (personas!=NULL)
    {
        if ((strcmp(nombreTPersona(personas->ini->persona),nombre))==0)
        {   
        //Tnodo aBorrar = personas->ini;
        //     if (personas->ini->sig != NULL)
        //     {
        //         personas->ini = personas->ini->sig;
        //         personas->ini->ant = NULL;
        //     }
        //     else{
        //         personas->ini=NULL;
        //     }
        //     delete aBorrar;
        //     liberarTPersona(aBorrar->persona);
            eliminarInicioTPersonasLDE(personas);
        }
        else if (strcmp(nombreTPersona(personas->fin->persona),nombre)==0)
        {
            // Tnodo aBorrar = personas->fin;
            // if (personas->fin->ant!=NULL)
            // {
            //     personas->fin = personas->fin->ant;
            //     personas->fin->sig = NULL;
            // }
            // else{
            //     personas->ini=personas->fin=NULL;
            // }
            // liberarTPersona(aBorrar->persona);
            // delete aBorrar;
            eliminarFinalTPersonasLDE(personas);   
        }
        else{
            Tnodo aux = personas->ini->sig;
            while (aux != NULL && (strcmp(nombreTPersona(aux->persona),nombre) != 0 ))
            {
                aux = aux->sig;
            }
            if (aux!=NULL)
            {
                aux->ant->sig = aux->sig;
                aux->sig->ant = aux->ant;
                liberarTPersona(aux->persona);
            }
            delete aux;
            aux=NULL;
            personas->cantPersonas--;
        }
    }
}
bool estaPersonaConNombreEnTPersonasLDE(TPersonasLDE personas, const char nombre[100]){
    if (personas!=NULL)
    {
        Tnodo aux = personas->ini;
        while (aux !=NULL && strcmp(nombreTPersona(aux->persona),nombre) != 0)
        {
            aux = aux->sig;
        }
        return aux!=NULL;
    }
    else
    {
        return false;
    }
}
TPersona obtenerPersonaConNombreTPersonasLDE(TPersonasLDE personas, const char nombre[100]){
    if (personas!=NULL)
    {
        Tnodo aux= personas->ini;
        while (aux !=NULL && strcmp(nombreTPersona(aux->persona),nombre) != 0)
        {
            aux = aux->sig;
        }
        return aux->persona;
    }
    else{return NULL;}
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

