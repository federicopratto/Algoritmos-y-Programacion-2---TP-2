
#include "Jugada.h"


Jugada::Jugada(int fila, int columna, int piso, Jugador* jugador, int numero){

	this->fila = fila;
	this->columna = columna;
	this->piso = piso;
	this->jugador = jugador;
	this->numeroDeJugada = numero;
}


Jugada::Jugada(Jugada* otraJugada){

	this->fila = otraJugada->darFila();
	this->columna = otraJugada->darColumna();
	this->piso = otraJugada->darPiso();
	this->jugador = otraJugada->darJugador();
	this->numeroDeJugada = otraJugada->darNumero();
}


int& Jugada::darFila(){

	 return this->fila;
}

int& Jugada::darColumna(){

	return this->columna;
}

int& Jugada::darPiso() {

	return this->piso;
}


Jugador* Jugada::darJugador(){

	return this->jugador;
}


void Jugada::cambiarJugador(Jugador* nuevoJugador){

	this->jugador = nuevoJugador;
}


Ficha* Jugada::darFicha(){

	return this->jugador->darFicha();
}


Color* Jugada::darColorFicha(){

	return this->darFicha()->darColor();
}


int& Jugada::darNumero(){

	return this->numeroDeJugada;
}


Jugada::~Jugada(){

}
