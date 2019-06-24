
#include "Carta.h"


Carta::Carta() {

	this->poder = (1 + rand() % 6);
	this->asignarDescripcion();
}


int Carta::esUsada() {

	return this->poder;
}


string Carta::mostrarPoder(){

	return this->descripcion;
}


Carta::~Carta() {

}


void Carta::asignarDescripcion(){

	switch(this->poder){

	case 1:
		this->descripcion =
				"CARTA COLOR\n"
				"Al usar esta carta se cambiara el color "
				"de una ficha al azar en el tablero, el color resultante\n"
				"de la ficha dependera de la cantidad de veces que ha "
				"sido jugada esta carta. La primera vez que se juegue,\n"
				"tomara el color del jugador 1, la segunda vez del jugador 2, etc.\n";
		break;
	case 2:
		this->descripcion =
				"CARTA DE ELIMINACIÓN\n"
				"Al usar esta carta se borrara una ficha al azar en el tablero.\n";
			break;
	case 3:
		this->descripcion =
				"CARTA DE INTERCAMBIO\n"
				"Al usar esta carta se intercambiaran dos fichas vecinas que "
				"elijas dentro del tablero.\n"
				"(Si no hay ninguna ficha que tenga una vecina en todo el tablero "
				"perderas esta carta al intentar usarla)\n";
			break;
	case 4:
		this->descripcion =
				"CARTA PORTAL\n"
				"Al usar esta carta se crea un portal entre dos casilleros "
				"laterales en los extremos del tablero,\n"
				"continuando la secuencia de fichas para formar 4 en línea.\n";
			break;
	case 5:
		this->descripcion =
				"CARTA DE IGNORANCIA\n"
				"Al usar esta carta el juego ignorara el movimiento del "
				"jugador anterior, eliminando\n"
				"su ficha del tablero.\n";
			break;
	case 6:
		this->descripcion =
				"CARTA LADRONA\n"
				"Al usar esta carta le seran quitadas 10 fichas al jugador "
				"siguiente de su pozo, junto con\n"
				"todas sus cartas de poder.\n";
	break;
	}
}
