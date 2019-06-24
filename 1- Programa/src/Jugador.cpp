
#include "Jugador.h"


Jugador::Jugador(string nombre, int numero, int fichas){

	this->nombre = nombre;
	this->ficha = new Ficha(numero);
	this->cantidadDeFichas = fichas;
	this->pozoDeCartas = new Lista<Carta*>;
}


string Jugador::darNombre(){

	return this->nombre;
}


int Jugador::darNumero(){

	return this->ficha->darNumero();
}


Ficha* Jugador::darFicha(){

	return this->ficha;
}


int Jugador::contarFichas(){

	return (this->cantidadDeFichas);
}


void Jugador::realizarJugada(){

	if(this->contarFichas() == 0){

		throw string("Un jugador sin fichas no puede realizar una jugada.");
	}

	this->cantidadDeFichas--;
}


bool Jugador::tieneCartas(){

	return (this->pozoDeCartas->contarElementos() > 0);
}


bool Jugador::pozoLleno(){

	return (this->pozoDeCartas->contarElementos() == 4);
}


Carta* Jugador::recibirCarta(){

	if(this->pozoLleno()){

		throw string("El jugador no cuenta con espacio para almacenar mas cartas.");
	}

	Carta* nuevaCarta = new Carta;
	this->pozoDeCartas->agregar(nuevaCarta);

	return nuevaCarta;
}


Lista<Carta*>* Jugador::mostrarCartas(){

	return this->pozoDeCartas;
}


int Jugador::usarCarta(int numeroDeCarta){

	if(this->pozoDeCartas->estaVacia()){

		throw string("El jugador no tiene cartas de poder para jugar.");
	}

	Carta* cartaAUsar = this->pozoDeCartas->obtener(numeroDeCarta);
	this->pozoDeCartas->remover(numeroDeCarta);

	int poderUsado = cartaAUsar->esUsada();
	delete cartaAUsar;

	return poderUsado;
}


void Jugador::perderFichas(){

	if(this->contarFichas() > 10){
		this->cantidadDeFichas -= 10;
	} else {
		this->cantidadDeFichas = 0;
	}

	int elementos = this->pozoDeCartas->contarElementos();
	while(elementos > 0){

		delete this->pozoDeCartas->obtener(1);
		this->pozoDeCartas->remover(1);
		elementos--;
	}
}


Jugador::~Jugador(){

	this->pozoDeCartas->iniciarCursor();
	while(this->pozoDeCartas->avanzarCursor()){

		delete this->pozoDeCartas->obtenerCursor();
	}

	delete this->pozoDeCartas;
	delete this->ficha;
}
