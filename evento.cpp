#include "../include/evento.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////

struct rep_evento
{
    /************ Parte 4.1 ************/
    /*Escriba el código a continuación */
    int indentificador;
    char descripcion[MAX_DESCRIPCION];
    TFecha fecha;
    /****** Fin de parte Parte 4.1 *****/
};

TEvento crearTEvento(int id, const char descripcion[MAX_DESCRIPCION], TFecha fecha)
{
    TEvento nuevoEvento = NULL;
    /************ Parte 4.2 ************/
    /*Escriba el código a continuación */
    nuevoEvento = new rep_evento;
    nuevoEvento->indentificador = id;
    strcpy(nuevoEvento->descripcion, descripcion);
    nuevoEvento->fecha = fecha;
    /****** Fin de parte Parte 4.2 *****/
    return nuevoEvento;
}

void imprimirTEvento(TEvento evento)
{
    /************ Parte 4.3 ************/
    /*Escriba el código a continuación */
    printf("Evento %d: %s\n", evento->indentificador, evento->descripcion);
    printf("Fecha: ");
    imprimirTFecha(evento->fecha);
    /****** Fin de parte Parte 4.3 *****/
}

void liberarTEvento(TEvento &evento)
{
    /************ Parte 4.4 ************/
    /*Escriba el código a continuación */
    // liberamos la memoria de la fecha
    liberarTFecha(evento->fecha);
    // liberamos memoria del evento
    delete evento;
    evento = NULL;
    /****** Fin de parte Parte 4.4 *****/
}

int idTEvento(TEvento evento)
{
    int res = 0;
    /************ Parte 4.4 ************/
    /*Escriba el código a continuación */
    if (evento!=NULL)
    {
        res = evento->indentificador;
    }    
    /****** Fin de parte Parte 4.4 *****/
    return res;
}

TFecha fechaTEvento(TEvento evento)
{
    TFecha fecha = NULL;
    /************ Parte 4.4 ************/
    /*Escriba el código a continuación */
    fecha = evento->fecha;
    /****** Fin de parte Parte 4.4 *****/
    return fecha;
}

void posponerTEvento(TEvento &evento, int dias)
{
    /************ Parte 4.5 ************/
    /*Escriba el código a continuación */
    aumentarTFecha(evento->fecha, dias);
    /****** Fin de parte Parte 4.5 *****/
}
// Retorna una copia del evento
TEvento copiarTEvento(TEvento evento)
{
    TEvento copEvento = crearTEvento(evento->indentificador, evento->descripcion, copiarTFecha(evento->fecha));
    return copEvento;
}

/////////////////////////////////
////// FIN CÓDIGO TAREA 2 //////
/////////////////////////////////

/////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
/////////////////////////////////
