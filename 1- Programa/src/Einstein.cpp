
#include "Einstein.h"

using std::string;


Einstein::Einstein(){

	this->portalCreado = false;
	this->tipoDePortal = 1;
	this->ladoA = new Jugada(0, 0, 0, NULL, 0);
	this->ladoB = new Jugada(0, 0, 0, NULL, 0);
}


bool Einstein::crearPortal(Tablero* tablero, Consola* consola){

	this->portalCreado = this->obtenerCeldas(tablero);

	if (this->portalCreado) {

		tablero->abrirPortal(this->ladoA, this->ladoB, this->tipoDePortal);
		consola->mostrarEfectoJugada(this->ladoA, "Se abrio un extremo del portal en -> ");
		consola->mostrarEfectoJugada(this->ladoB, "Se abrio otro extremo del portal en -> ");

	} else {

		consola->mostrarEfectoJugada("No es posible abrir mas portales por el momento "
									"has pedido tu carta.");
	}

	return this->portalCreado;
}


Jugada* Einstein::darLadoA(){

	if(!this->portalCreado){

		throw string("Se ha intentado obtener informacion de un portal inexistente.");
	}

	return this->ladoA;
}


Einstein::~Einstein(){

	delete this->ladoA;
	delete this->ladoB;
}


bool Einstein::obtenerCeldas(Tablero* tablero){

	bool celdasEncontradas;

	this->reiniciarLado(this->ladoA, 1, 1, 1);
	celdasEncontradas = tablero->buscarCeldaSinPortal1(this->ladoA, this->ladoB);

	if(!celdasEncontradas){
		this->reiniciarLado(this->ladoA, 1, 1, tablero->darPisos());
		celdasEncontradas = tablero->buscarCeldaSinPortal1(this->ladoA, this->ladoB);
	}

	if(!celdasEncontradas){
		this->reiniciarLado(this->ladoA, 1, 1, 1);
		celdasEncontradas = tablero->buscarCeldaSinPortal2(this->ladoA, this->ladoB);
		this->tipoDePortal = 2;
	}

	if(!celdasEncontradas){
		this->reiniciarLado(this->ladoA, 1, tablero->darColumnas(), 1);
		celdasEncontradas = tablero->buscarCeldaSinPortal2(this->ladoA, this->ladoB);
	}

	if(!celdasEncontradas){
		this->reiniciarLado(this->ladoA, 1, 2, 1);
		celdasEncontradas = tablero->buscarCeldaSinPortal3(this->ladoA, this->ladoB);
		this->tipoDePortal = 3;
	}

	if(!celdasEncontradas){
		this->reiniciarLado(this->ladoA, tablero->darFilas(), 2, 1);
		celdasEncontradas = tablero->buscarCeldaSinPortal3(this->ladoA, this->ladoB);
	}

	return celdasEncontradas;
}


void Einstein::reiniciarLado(Jugada* lado, int a, int b, int c){

	lado->darFila() = a;
	lado->darColumna() = b;
	lado->darPiso() = c;
}
