#include "../include/agendaLS.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////
struct rep_agendaLS
{
    TEvento evento;
    TAgendaLS sig;    
};

TAgendaLS crearAgendaLS()
{
    TAgendaLS agenda;
    agenda = NULL;
    return agenda;
}
void agregarEnAgendaLS(TAgendaLS &agenda, TEvento evento)
{
    TAgendaLS aAgregar = new rep_agendaLS;
    aAgregar->evento = evento;
    if (agenda == NULL)
    {
        agenda = aAgregar;
        aAgregar->sig = NULL;
    }
    else{
        if (compararTFechas(fechaTEvento(agenda->evento),fechaTEvento(aAgregar->evento)) == 1){
            aAgregar->sig = agenda;
            agenda = aAgregar;
        }
        else{
            TAgendaLS iter = agenda;
            while (iter->sig != NULL && compararTFechas(fechaTEvento(iter->sig->evento),fechaTEvento(aAgregar->evento)) == -1){
                iter=iter->sig;
            }
            //ahora hay dos casos, o llegamos al fin de la lista o tenemos que insertar en el medio(iter guarda la posicion anterior)
            aAgregar->sig = iter->sig;
            iter->sig = aAgregar;
        }
    }  
}
void imprimirAgendaLS(TAgendaLS agenda)
{
    while (agenda != NULL)
    {
        imprimirTEvento(agenda->evento);
        agenda = agenda->sig;
    }
}
void liberarAgendaLS(TAgendaLS &agenda)
{
    if (agenda != NULL)
    {
        while (agenda != NULL) 
        {
            TAgendaLS aBorrar = agenda;
            agenda = agenda->sig;
            liberarTEvento(aBorrar->evento);
            delete aBorrar;
            aBorrar = NULL;
        }
        delete agenda;
        agenda=NULL;
    }
    else{
        delete agenda;
        agenda = NULL;
    }
}

bool esVaciaAgendaLS(TAgendaLS agenda)
{
    return (agenda == NULL);
}

TAgendaLS copiarAgendaLS(TAgendaLS agenda)
{
    TAgendaLS copAgenda = crearAgendaLS();
    if (!esVaciaAgendaLS(agenda))
    {
        while (agenda != NULL)
        {
            agregarEnAgendaLS(copAgenda, copiarTEvento(agenda->evento));
            agenda = agenda->sig;
        }
    }
    return copAgenda;  
}
bool estaEnAgendaLS(TAgendaLS agenda, int id)
{
    bool encontre = false;
    while (agenda!=NULL && !encontre)
    {
        if (idTEvento(agenda->evento)==id)
        {
            encontre = true;
        }
        else{
            agenda=agenda->sig;
        }   
    }
    return encontre;
}

TEvento obtenerDeAgendaLS(TAgendaLS agenda, int id)
{
    while (agenda != NULL && idTEvento(agenda->evento)!=id)
    {
        agenda = agenda->sig;
    }
    return agenda->evento;
}
void eliminarEvento(TAgendaLS &agenda, TEvento evento )
{
    //encuentra el elemento en la agenda y lo borra
    //PRE: el elemento pertenece
    if (!esVaciaAgendaLS(agenda))
    {
        TAgendaLS aBorrar;
        if(agenda->evento == evento){
            aBorrar = agenda;
            agenda = agenda->sig;
            liberarTEvento(aBorrar->evento);
            aBorrar->sig = NULL;
            delete aBorrar;
        }
        else{
        TAgendaLS iter = agenda; 
            while (iter!=NULL && iter->sig->evento != evento )
            {
                iter=iter->sig;
            }
            TAgendaLS aBorrar = iter->sig;
            iter->sig = aBorrar->sig;
            liberarTEvento(aBorrar->evento);
            aBorrar->sig = NULL;
            delete aBorrar;
        }
    }
}
void posponerEnAgendaLS(TAgendaLS &agenda, int id, nat n)
{
    TEvento eventoAPos = obtenerDeAgendaLS(agenda,id);
    TEvento copiaEvento = copiarTEvento(eventoAPos);
    eliminarEvento(agenda,eventoAPos);
    posponerTEvento(copiaEvento,n);
    agregarEnAgendaLS(agenda,copiaEvento);
}

void imprimirEventosFechaLS(TAgendaLS agenda, TFecha fecha)
{
    bool yaPase = false;
    TAgendaLS iter = agenda;
    while (iter != NULL && !yaPase)
    {
        if (compararTFechas(fechaTEvento(iter->evento),fecha) == 0)
        {
            imprimirTEvento(iter->evento);
            if (compararTFechas(fechaTEvento(iter->sig->evento),fecha) != 0)
            {
                yaPase = true;
            }
        }
        iter=iter->sig;
    }
}

bool hayEventosFechaLS(TAgendaLS agenda, TFecha fecha)
{
    bool esta = false;
    if (agenda!=NULL)
    {
        while (agenda!=NULL && !esta)
        {
            if (compararTFechas(fechaTEvento(agenda->evento),fecha) == 0)
            {
                esta = true;
            }
            agenda = agenda->sig;
        }
    }
    return esta;
}

void removerDeAgendaLS(TAgendaLS &agenda, int id)
{
    eliminarEvento(agenda,obtenerDeAgendaLS(agenda,id));
}
///////////////////////////////////
////// FIN CÓDIGO TAREA 2 //////

///////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

TEvento primerEventoAgendaLS(TAgendaLS agenda){
    return agenda->evento;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////