#include "../include/tablaPersonas.h"

struct rep_tablaPersonas {
    TPersonasLDE * arreglo;
    nat tamanio;
};

nat funcionDeDispersion(const char nombre[100]){
    nat res = 0;
    int i = 0;
    while(i< 100 && nombre[i] != '\0'){
        res += int(nombre[i]);
        i++;
    }
    return res;
}

TTablaPersonas crearTTablaPersonas(int max){
    TTablaPersonas tabla = new rep_tablaPersonas;
    tabla->tamanio = max;
    tabla->arreglo = new TPersonasLDE[max];
    for (int i = 0; i < max; i++)
    {
        tabla->arreglo[i] = crearTPersonasLDE();
    }
    return tabla;
}

void insertarPersonaEnTabla(TTablaPersonas &tabla, TPersona persona){
    nat hash = funcionDeDispersion(nombreTPersona(persona))%tabla->tamanio;
    insertarInicioDeTPersonasLDE(tabla->arreglo[hash],persona);
}
void eliminarPersonaDeTTablaPersonas(TTablaPersonas &tabla, const char nombre[100]){
    nat hash = funcionDeDispersion(nombre)%tabla->tamanio;
    eliminarPersonaConNombreTPersonasLDE(tabla->arreglo[hash],nombre);
}

bool perteneceATTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    nat hash = funcionDeDispersion(nombre)%tabla->tamanio;
    return estaPersonaConNombreEnTPersonasLDE(tabla->arreglo[hash],nombre);
}

TPersona obtenerPersonaDeTTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    nat hash = funcionDeDispersion(nombre)%tabla->tamanio;
    return obtenerPersonaConNombreTPersonasLDE(tabla->arreglo[hash],nombre);
}
void liberarTTablaPersonas(TTablaPersonas &tabla){
   for (nat i = 0; i < tabla->tamanio; i++)
   {
        if (tabla->arreglo[i]!=NULL)
        {
            liberarTPersonasLDE(tabla->arreglo[i]);
        }
   }
   delete[] tabla->arreglo;
   delete tabla;
   tabla=NULL;
}
void imprimirTTablaPersonas(TTablaPersonas tabla){
    for (nat i = 0; i < tabla->tamanio; i++)
    {
        imprimirTPersonasLDE(tabla->arreglo[i]);
    }
}