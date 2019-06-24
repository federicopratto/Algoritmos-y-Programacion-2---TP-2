
#include "Portal.h"


Portal::Portal(Celda* salida, int tipoDePortal){

	this->salida = salida;
	this->tipoDePortal = tipoDePortal;
}


int Portal::indicarTipo(){

	return this->tipoDePortal;
}


Celda* Portal::indicarSalida(){

	return this->salida;
}


Portal::~Portal(){

}
