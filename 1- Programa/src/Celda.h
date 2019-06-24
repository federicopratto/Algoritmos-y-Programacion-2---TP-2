
#ifndef CELDA_H_
#define CELDA_H_

#ifndef NULL
#define NULL 0
#endif

#include <string>
#include "Jugador.h"
#include "Jugada.h"
#include "Portal.h"

class Portal;	// forward declaration.
class Jugada;	// forward declaration.

/*
 * Una celda es la unidad fundamental que conforma un tablero, dentro de las celdas
 * se almacenan los elementos del tablero.
 */

class Celda {

private:

	Jugada* contenido;
	Portal* portal;

public:

	/*
	 * POST: Crea una nueva celda del tablero cuyo contenido es:
	 *
	 * 		 fila: fila del tablero donde se encuetra.
	 * 		 columna: columna del tablero donde se encuentra.
	 * 		 piso: piso del tablero donde se encuentra.
	 * 		 jugador: jugador al cual esta asociado la ficha ingresada.
	 * 		 numero: numero de jugada en la cual fue creada la celda.
	 */
	Celda(Jugada* contenido);


	/*
	 * POST: Devuelve el contenido de la celda.
	 */
	Jugada* verContenido();


	/*
	 * POST: Reemplaza el jugador almacenado dentro de la celda
	 * 		 y por consiguiente la ficha.
	 */
	void cambiarJugada(Jugador* nuevoJugador);


	/*
	 * PRE:  No hay ya un portal abierto entre esta celda y otra.
	 * POST: Abre un portal entre dos celdas adyacentes del tablero
	 *       al azar.
	 */
	void abrirPortal(Celda* salida, int tipoDePortal);


	/*
	 * POST: Indica si hay un portal abierto entre esta celda y otra
	 *       adyacente.
	 */
	bool portalEstaAbierto();


	/*
	 * PRE:  Existe un portal entre esta celda y otra.
	 * POST: Devuelve el portal que une esta celda con otra.
	 */
	Portal* cruzarPortal();


	/*
	 * POST: Libera los recursos solicitados.
	 */
	~Celda();

};

#endif /* CELDA_H_ */
