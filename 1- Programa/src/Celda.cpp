
#include "Celda.h"

using std::string;


Celda::Celda(Jugada* contenido){

	this->contenido = new Jugada(contenido);
	this->portal = NULL;
}


Jugada* Celda::verContenido(){

	return this->contenido;
}


void Celda::cambiarJugada(Jugador* nuevoJugador){

	this->contenido->cambiarJugador(nuevoJugador);
}


void Celda::abrirPortal(Celda* salida, int tipoDePortal){

	if(this->portalEstaAbierto()){

		throw string("Se intento abrir un portal donde ya existe uno.");
	}

	this->portal = new Portal(salida, tipoDePortal);
}


bool Celda::portalEstaAbierto(){

	bool abierto = (this->portal != NULL);
	return abierto;
}


Portal* Celda::cruzarPortal(){

	if(!this->portalEstaAbierto()){

		throw string("Se intento cruzar un portal que no existe.");
	}

	return (this->portal);
}


Celda::~Celda() {

	delete this->contenido;

	if (this->portalEstaAbierto()) {

		delete this->cruzarPortal()->indicarSalida()->portal;
		delete this->portal;
	}
}
