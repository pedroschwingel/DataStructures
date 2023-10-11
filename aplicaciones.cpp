#include "../include/aplicaciones.h"

TPilaPersona menoresQueElResto(TPersonasLDE lista) {
    if (lista!=NULL)
    {
        TPilaPersona pilaResultado = crearTPilaPersona();
        apilarEnTPilaPersona(pilaResultado,obtenerInicioDeTPersonasLDE(lista));
        eliminarInicioTPersonasLDE(lista);
        while (cantidadTPersonasLDE(lista) > 0)
        {
            TPersona primerElemLista = obtenerInicioDeTPersonasLDE(lista);
            //sacamos el elemento de la pila mientras tengamos un menor
            while (cantidadEnTPilaPersona(pilaResultado)>0 && edadTPersona(primerElemLista)< edadTPersona(cimaDeTPilaPersona(pilaResultado)))
            {
                desapilarDeTPilaPersona(pilaResultado);
            }
            apilarEnTPilaPersona(pilaResultado,primerElemLista);
            eliminarInicioTPersonasLDE(lista);
        }
        return pilaResultado; 
    }
    else
    {
        return NULL;
    }

}
bool sumaPares(nat k, TConjuntoIds c){
   nat contador = 1;
   while (contador <= k/2)
   {
        //Tenés que agregar una condición a los ifs de que k-i ≠ i
        if (contador!= k-contador && perteneceTConjuntoIds(contador,c) && perteneceTConjuntoIds(k-contador,c))
        {
            return true;   
        }
        contador++;
   }
    return false;
}