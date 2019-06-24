
#include "Ficha.h"


Ficha::Ficha(int numero){

	this->numero = numero;

	int rojo = (rand() % 254 + 1);
	int verde = (rand() % 254 + 1);
	int azul = (rand() % 254 + 1);

	this->color = new Color(rojo, verde, azul);
}


int Ficha::darNumero(){

	return this->numero;
}


Color* Ficha::darColor(){

	return this->color;
}


Ficha::~Ficha(){

	delete this->color;
}
