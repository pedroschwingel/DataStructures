#include "../include/personasABB.h"
#include "../include/colaPersonasABB.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 2 //////
///////////////////////////////////
struct rep_personasAbb {
    TPersona elem;
    TPersonasABB Left;
    TPersonasABB Right;
};

TPersonasABB crearTPersonasABB() {
    TPersonasABB PersonaABB;
    PersonaABB = NULL;
    return PersonaABB;
}

bool esVacioTPersonasABB(TPersonasABB personasABB) {
    return (personasABB == NULL);
}

void insertarTPersonasABB(TPersonasABB &personasABB, TPersona p) {
    //arbol vacio
    if (esVacioTPersonasABB(personasABB))
    {
        personasABB = new rep_personasAbb;
        personasABB->elem = p;
        personasABB->Left = personasABB->Right = NULL;
    }
    else
    {
        if (idTPersona(p) > idTPersona(personasABB->elem))
        {
            insertarTPersonasABB(personasABB->Right,p);
        }
        if (idTPersona(p) < idTPersona(personasABB->elem))
        {
            insertarTPersonasABB(personasABB->Left,p);
        }
    }
}

void liberarTPersonasABB(TPersonasABB &personasABB) {
    if (personasABB != NULL)
    {
        liberarTPersonasABB(personasABB->Left);
        liberarTPersonasABB(personasABB->Right);
        liberarTPersona(personasABB->elem);
        delete personasABB;
        personasABB = NULL; 
    }
}

void imprimirTPersonasABB(TPersonasABB personasABB) {
   if (personasABB != NULL)
   {
        imprimirTPersonasABB(personasABB->Left);
        imprimirTPersona(personasABB->elem);
        imprimirTPersonasABB(personasABB->Right);
   }
}

nat cantidadTPersonasABB(TPersonasABB personasABB) {
    if (personasABB != NULL)
    {
        //llgamos a una hoja
        if (personasABB->Left == NULL && personasABB->Right == NULL)
        {
            return 1;
        }
        else{
            // el nodo mas los subarboles izq y der
            return 1 + cantidadTPersonasABB(personasABB->Left) + cantidadTPersonasABB(personasABB->Right);
        }
    }
    else{
        return 0;
    }
}

TPersona maxIdPersona(TPersonasABB personasABB) {
  if (personasABB !=NULL)
  {  
    if (personasABB->Right == NULL)
    {
        return personasABB->elem;
    }
    else{
        return maxIdPersona(personasABB->Right);
    }
  }
  else
  {
    return NULL;
  }
}

void removerTPersonasABB(TPersonasABB &personasABB, nat id) {
    if (personasABB != NULL)
    {    
        if (idTPersona(personasABB->elem) == id)
        {
            if (personasABB->Left == NULL && personasABB->Right == NULL)
            {
                liberarTPersona(personasABB->elem);
                delete personasABB;
                personasABB = NULL;
            }
            else if (personasABB->Right == NULL)
            {
                TPersonasABB aux = personasABB->Left;
                liberarTPersona(personasABB->elem);
                delete personasABB;
                personasABB = aux;
            }
            else if (personasABB->Left == NULL)
            {
                TPersonasABB aux = personasABB->Right;
                liberarTPersona(personasABB->elem);
                delete personasABB;
                personasABB = aux;
            }
            else
            {
                TPersona aux = copiarTPersona(maxIdPersona(personasABB->Left));
                liberarTPersona(personasABB->elem);
                personasABB->elem = aux;
                removerTPersonasABB(personasABB->Left,idTPersona(personasABB->elem));
            }
        }
        else if (id < idTPersona(personasABB->elem))
        {
            removerTPersonasABB(personasABB->Left,id);
        }
        else{
            removerTPersonasABB(personasABB->Right,id);
        }  
    }
}

bool estaTPersonasABB(TPersonasABB personasABB, nat id) {
    if (personasABB != NULL)
    {
        if (idTPersona(personasABB->elem) == id)
        {
            return true;
        }
        else if (idTPersona(personasABB->elem) < id)
        {
            return estaTPersonasABB(personasABB->Right,id);
        }
        else if (idTPersona(personasABB->elem) > id)
        {
            return estaTPersonasABB(personasABB->Left,id);
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

TPersona obtenerDeTPersonasABB(TPersonasABB personasABB, nat id) {
    if (personasABB!=NULL)
    {
        if (idTPersona(personasABB->elem) == id)
        {
            return personasABB->elem;
        }
        else if (idTPersona(personasABB->elem) < id)
        {
           return obtenerDeTPersonasABB(personasABB->Right,id);
        }
        else if (idTPersona(personasABB->elem) > id)
        {
            return obtenerDeTPersonasABB(personasABB->Left,id);
        }
        else{
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}
nat alturaTPersonasABB(TPersonasABB personasABB) {
    //CAMINO DE MAYOR LARGO
    if (personasABB==NULL)
    {
        return 0;
    }
    else{
        int alturaLeft = alturaTPersonasABB(personasABB->Left);
        int alturaRight = alturaTPersonasABB(personasABB->Right);
        if (alturaLeft > alturaRight)
        {
            return alturaLeft + 1;
        }
        else{
            return alturaRight +1;
        }
    }
}
bool esPerfectoTPersonasABB(TPersonasABB personasABB) {
    if (personasABB == NULL)
    {
        return true;
    }
    else
    {
        int alturaLeft = alturaTPersonasABB(personasABB->Left);
        int alturaRIght =  alturaTPersonasABB(personasABB->Right);
        if (alturaLeft != alturaRIght)
        {
            return false;
        }
        return (esPerfectoTPersonasABB(personasABB->Right) && esPerfectoTPersonasABB(personasABB->Left));
    }
}

TPersonasABB mayoresTPersonasABB(TPersonasABB personasABB, nat edad) {
    // Función que retorna un nuevo TPersonasABB con las personas de personasABB que son mayores a cierta edad
    // El árbol retornado NO comparte memoria con el árbol pasado por parámetro.
    // En caso de que deba elegir un nuevo nodo como raíz seleccione el nodo con el id más grande del 
    // subárbol izquierdo.
    // La funcion es Theta(n) peor caso, siendo n la cantidad de personas en el árbol binario
    if (personasABB == NULL)
    {
        return NULL;
    }
    else{
        TPersonasABB mayoresCiertaEdad;
        TPersonasABB mayoresCiertaEdadDerecha = mayoresTPersonasABB(personasABB->Right,edad);
        TPersonasABB mayoresCiertaEdadIzquierda = mayoresTPersonasABB(personasABB->Left,edad);
        //caso base(el elemento si va)
        if (edadTPersona(personasABB->elem) > edad)
        {
            mayoresCiertaEdad = new rep_personasAbb;
            mayoresCiertaEdad->elem = copiarTPersona(personasABB->elem);
            mayoresCiertaEdad->Right = mayoresCiertaEdadDerecha;
            mayoresCiertaEdad->Left = mayoresCiertaEdadIzquierda;
        }
        else if (mayoresCiertaEdadDerecha == NULL)
        {
            mayoresCiertaEdad = mayoresCiertaEdadIzquierda;
        }
         else if (mayoresCiertaEdadIzquierda == NULL)
        {
            mayoresCiertaEdad = mayoresCiertaEdadDerecha;
        }
        else if(mayoresCiertaEdadDerecha != NULL && mayoresCiertaEdadIzquierda != NULL){
                //estoy parado en el nodo y el nodo no va
                TPersona aux = copiarTPersona(maxIdPersona(personasABB->Left));
                removerTPersonasABB(personasABB->Left,idTPersona(aux));
                mayoresCiertaEdad = new rep_personasAbb;
                mayoresCiertaEdad->elem = aux;
                mayoresCiertaEdad->Right = mayoresCiertaEdadDerecha;
                mayoresCiertaEdad->Left = mayoresCiertaEdadIzquierda;
        }
        return mayoresCiertaEdad;

    }
    

    return NULL;
}
void agregarCopiaPrincipio(TPersonasLDE &L,TPersonasABB personasABB){
    if (personasABB !=NULL)
    {  
        agregarCopiaPrincipio(L,personasABB->Right);
        insertarTPersonasLDE(L,copiarTPersona(personasABB->elem),1);
        agregarCopiaPrincipio(L,personasABB->Left);
    }
    }
TPersonasLDE aTPersonasLDE(TPersonasABB personasABB) {
    TPersonasLDE personaLDE = crearTPersonasLDE();
    agregarCopiaPrincipio(personaLDE,personasABB);
    return personaLDE;
}
///////////////////////////////////
////// FIN CÓDIGO TAREA 2 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
nat amplitudTPersonasABB(TPersonasABB personasABB)
{
    if (personasABB!=NULL)
    {   
        nat resultado=1;
        TColaPersonasABB c = crearTColaPersonasABB();
        encolarEnTColaPersonasABB(personasABB,c);
        encolarEnTColaPersonasABB(NULL,c);
        while (cantidadEnTColaPersonasABB(c) > 0)
        {
            TPersonasABB frente = frenteDeTColaPersonasABB(c);
            if (frente!=NULL)
            {
                if (frente->Left!=NULL){ encolarEnTColaPersonasABB(frente->Left,c); }
            
                if(frente->Right!=NULL) { encolarEnTColaPersonasABB(frente->Right,c); }
                //desencolamos el dato que procesamos
                desencolarDeTColaPersonasABB(c);
            }
            else{
                desencolarDeTColaPersonasABB(c);
                if (cantidadEnTColaPersonasABB(c) > 0)
                {
                    if (resultado<cantidadEnTColaPersonasABB(c))
                    {
                        resultado = cantidadEnTColaPersonasABB(c);
                    }
                    encolarEnTColaPersonasABB(NULL,c);
                }
            }
        }
    liberarTColaPersonasABB(c);
    return resultado;
    }
    else
    {
        return 0;
    }
 }
TPilaPersona invertirpila(TPilaPersona &p){
    TPilaPersona invertirpila = crearTPilaPersona();
    while (cantidadEnTPilaPersona(p)>0)
    {
        TPersona cima = cimaDeTPilaPersona(p);
        apilarEnTPilaPersona(invertirpila,cima);
        desapilarDeTPilaPersona(p);
    }
    liberarTPilaPersona(p);
    return invertirpila; 
}
TPilaPersona serializarTPersonasABB(TPersonasABB personasABB) {
    if (personasABB!=NULL)
    {
        TPilaPersona pila = crearTPilaPersona();
        TColaPersonasABB cola = crearTColaPersonasABB();
        encolarEnTColaPersonasABB(personasABB,cola);
        while (cantidadEnTColaPersonasABB(cola) > 0)
        {
            TPersonasABB frenteCola =  frenteDeTColaPersonasABB(cola);
            if (frenteCola->Left!=NULL)
            {
                encolarEnTColaPersonasABB(frenteCola->Left,cola);
            }
            if (frenteCola->Right!=NULL)
            {
                encolarEnTColaPersonasABB(frenteCola->Right,cola);
            }
            apilarEnTPilaPersona(pila,frenteCola->elem);
            desencolarDeTColaPersonasABB(cola);
        }
        liberarTColaPersonasABB(cola);
        return invertirpila(pila);
    }
    else{
        return NULL;
    }
}
TPersonasABB deserializarTPersonasABB(TPilaPersona &pilaPersonas) {
if (pilaPersonas != NULL)
    {
        TPersonasABB abb = crearTPersonasABB();
        TColaPersonasABB cola = crearTColaPersonasABB();
        TPersona cima = cimaDeTPilaPersona(pilaPersonas);
        insertarTPersonasABB(abb,copiarTPersona(cima));
        encolarEnTColaPersonasABB(abb,cola);
        desapilarDeTPilaPersona(pilaPersonas);
        while(cantidadEnTPilaPersona(pilaPersonas)>0){

            TPersonasABB cimaCola = frenteDeTColaPersonasABB(cola);
            insertarTPersonasABB(cimaCola,copiarTPersona(cimaDeTPilaPersona(pilaPersonas)));
            desapilarDeTPilaPersona(pilaPersonas);

            insertarTPersonasABB(cimaCola,copiarTPersona(cimaDeTPilaPersona(pilaPersonas)));
            desapilarDeTPilaPersona(pilaPersonas);
        }
        liberarTColaPersonasABB(cola);
        liberarTPilaPersona(pilaPersonas);
        return abb;
    }
    else{
        return NULL;
    }
}
///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

