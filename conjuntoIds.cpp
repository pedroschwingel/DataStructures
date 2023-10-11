#include "../include/conjuntoIds.h"

struct rep_conjuntoIds{
    nat cantidadMax;
    nat cantidadElem;
	bool * booleanIds;
};


TConjuntoIds crearTConjuntoIds(nat cantMax){
	TConjuntoIds nuevo = new rep_conjuntoIds;
	nuevo->cantidadMax = cantMax;
	nuevo->cantidadElem = 0;
	nuevo->booleanIds = new bool[cantMax+1];
	for(nat i=1;i<=cantMax;i++){
		nuevo->booleanIds[i]=0;
	}
	return nuevo;    
};
bool esVacioTConjuntoIds(TConjuntoIds c){
	return (c->cantidadElem == 0);
};


void insertarTConjuntoIds(nat id, TConjuntoIds &c){
    if (id <= c->cantidadMax && id>0 && !c->booleanIds[id])
	{
		c->booleanIds[id] = 1;
		c->cantidadElem++;
	}
	
}; 

void borrarTConjuntoIds(nat id, TConjuntoIds &c){
    if (id>0 && id <= c->cantidadMax)
	{
		c->booleanIds[id] = 0;
		c->cantidadElem--;
	}
};

bool perteneceTConjuntoIds(nat id, TConjuntoIds c){
	if (id>0 && id <= c->cantidadMax)
	{
		return c->booleanIds[id];
	}
	else{
		return false;
	}
};
nat cardinalTConjuntoIds(TConjuntoIds c){
	return c->cantidadElem;
};

nat cantMaxTConjuntoIds(TConjuntoIds c){
	return c->cantidadMax;
};

void imprimirTConjuntoIds(TConjuntoIds c){
	for (nat i = 1; i <= c->cantidadMax; i++)
	{
		if (c->booleanIds[i])
		{
			printf("%u ",i);
		}
	}
	printf("\n");
};

void liberarTConjuntoIds(TConjuntoIds &c){
   delete[] c->booleanIds;
   delete c;
   c=NULL;
};
TConjuntoIds unionTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2){
	TConjuntoIds conjuntoUnion = crearTConjuntoIds(c1->cantidadMax);
	for (nat i = 1; i <= c1->cantidadMax; i++)
	{
		if (perteneceTConjuntoIds(i,c1)||perteneceTConjuntoIds(i,c2))
		{
			insertarTConjuntoIds(i,conjuntoUnion);
		}
		
	}
	return conjuntoUnion;
};

TConjuntoIds interseccionTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2){
	TConjuntoIds conjuntoInterseccion = crearTConjuntoIds(c1->cantidadMax);
	for (nat i = 1; i <= c1->cantidadMax; i++)
	{
		if (perteneceTConjuntoIds(i,c1) && perteneceTConjuntoIds(i,c2))
		{
			insertarTConjuntoIds(i,conjuntoInterseccion);
		}
		
	}
	return conjuntoInterseccion;
};

TConjuntoIds diferenciaTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2){
	TConjuntoIds conjuntoDiferencia = crearTConjuntoIds(c1->cantidadMax);
	for (nat i = 1; i <= c1->cantidadMax; i++)
	{
		if (perteneceTConjuntoIds(i,c1) && !perteneceTConjuntoIds(i,c2))
		{
			insertarTConjuntoIds(i,conjuntoDiferencia);
		}
	}
	return conjuntoDiferencia;
};
