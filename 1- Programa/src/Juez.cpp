
#include "Juez.h"


Juez::Juez(){

	this->hilera = new Lista<Celda*>;
	this->hileraPortal = new Lista<Celda*>;
}


bool Juez::darCartaA(Jugador* jugadorActual, int dificultad){

	if(jugadorActual->pozoLleno()){
		throw string("El jugador no tenia lugar para guardar mas cartas.");
	}

	bool asignar;
	int probabilidad = 1 + (rand() % 10);

	switch(dificultad){

	case 1:
		asignar = (probabilidad <= 8);
		break;
	case 2:
		asignar = (probabilidad <= 5);
		break;
	case 3:
		asignar = (probabilidad < 3);
		break;
	}

	return asignar;
}


bool Juez::hay4EnLinea(Tablero* tablero, Jugada* ultimaJugada){

	int indice = 1;
	bool hay4EnLinea = false;

	while(!hay4EnLinea && indice <= 13){

		tablero->copiarHilera(indice, this->hilera, ultimaJugada);
		hay4EnLinea = this->revisarHilera(tablero);
		this->vaciarHilera(this->hilera);
		indice++;
	}

	return hay4EnLinea;
}


bool Juez::huboEmpate(Tablero* tablero){

	return tablero->estaLleno();
}


void Juez::robarFichas(Jugador* jugador){

		jugador->perderFichas();
}


Juez::~Juez(){

	this->vaciarHilera(this->hilera);
	this->vaciarHilera(this->hileraPortal);

	delete this->hilera;
	delete this->hileraPortal;
}


bool Juez::revisarHilera(Tablero* tablero){

	Celda *celdaRevisada, *celdaActual;
	int contador = 1;
	bool hay4EnLinea = false;

	this->hilera->iniciarCursor();

	// Guardo la primera ficha de mi hilera.
	if(this->hilera->avanzarCursor()){

		celdaActual = this->hilera->obtenerCursor();
		hay4EnLinea = hayPortal(celdaActual, tablero);
	}

	// Comienzo a compararla con las demas fichas.
	while(!hay4EnLinea && this->hilera->avanzarCursor()){

		celdaRevisada = this->hilera->obtenerCursor();
		hay4EnLinea = hayPortal(celdaRevisada, tablero);

		if(!hay4EnLinea){

			Ficha* fichaActual = celdaActual->verContenido()->darFicha();
			Ficha* fichaRevisada = celdaRevisada->verContenido()->darFicha();

			if(fichaActual == fichaRevisada){
				contador++;
			} else {
				contador = 1;
				celdaActual = celdaRevisada;
			}
			hay4EnLinea = (contador == 4);
		}
	}

	return hay4EnLinea;
}


bool Juez::hayPortal(Celda* celda, Tablero* tablero){

	bool hay4EnLinea = false;

	if(celda->portalEstaAbierto()){

		Jugada* ladoA = celda->verContenido();
		Jugada* ladoB = celda->cruzarPortal()->indicarSalida()->verContenido();
		int tipoDePortal = celda->cruzarPortal()->indicarTipo();
		hay4EnLinea = this->cargarHileraPortal(tablero, ladoA, ladoB, tipoDePortal);
	}

	return hay4EnLinea;
}


bool Juez::cargarHileraPortal(Tablero* tablero, Jugada* ladoA, Jugada* ladoB, int tipoDePortal){

	bool hay4EnLinea = false;

	Lista<Celda*> *hileraAux = new Lista<Celda*>;
	Lista<int>* direccion = new Lista<int>();
	this->cargarHilerasARevisar(direccion, tipoDePortal);

	direccion->iniciarCursor();
	while(!hay4EnLinea && direccion->avanzarCursor()){

		tablero->copiarHilera(direccion->obtenerCursor(), hileraAux, ladoA);
		hileraAux->invertir();
		this->hileraPortal->agregar(*hileraAux);

		tablero->copiarHilera(direccion->obtenerCursor(), hileraAux, ladoB);
		this->hileraPortal->agregar(*hileraAux);

		hay4EnLinea = this->revisarHileraPortal();
		this->vaciarHilera(this->hileraPortal);
		this->vaciarHilera(hileraAux);
	}

	delete hileraAux;
	delete direccion;

	return hay4EnLinea;
}


bool Juez::revisarHileraPortal(){

	Ficha *fichaRevisada, *fichaActual;
	int contador = 1;

	this->hileraPortal->iniciarCursor();

	// Guardo la primera ficha de mi hilera.
	if(this->hileraPortal->avanzarCursor()){
		fichaActual = this->hileraPortal->obtenerCursor()->verContenido()->darFicha();
	}

	// Comienzo a compararla con las demas fichas.
	while(contador < 4 && this->hileraPortal->avanzarCursor()){

		fichaRevisada = this->hileraPortal->obtenerCursor()->verContenido()->darFicha();

		if(fichaActual == fichaRevisada){
			contador++;
		} else {
			contador = 1;
			fichaActual = fichaRevisada;
		}
	}
	return (contador == 4);
}


void Juez::cargarHilerasARevisar(Lista<int>* direccion, int tipoDePortal){

	if(tipoDePortal == 1){

		direccion->agregar(1);
		direccion->agregar(3);
		direccion->agregar(4);
		direccion->agregar(6);
		direccion->agregar(7);

	} else if (tipoDePortal == 2) {

		direccion->agregar(5);
		direccion->agregar(6);
		direccion->agregar(7);
		direccion->agregar(8);
		direccion->agregar(9);

	} else {

		direccion->agregar(2);
		direccion->agregar(3);
		direccion->agregar(4);
		direccion->agregar(8);
		direccion->agregar(9);
	}

	direccion->agregar(10);
	direccion->agregar(11);
	direccion->agregar(12);
	direccion->agregar(13);
}


void Juez::vaciarHilera(Lista<Celda*>* hilera){

	int elementos = hilera->contarElementos();

	while(elementos > 0){

		hilera->remover(1);
		elementos--;
	}
}
