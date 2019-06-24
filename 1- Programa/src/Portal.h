
#ifndef PORTAL_H_
#define PORTAL_H_

#include "Celda.h"

class Celda;

/*
 * Un portal es una conexion que existe entre dos celdas contiguas de una misma
 * cara del cubo tridimensional que conforma el tablero de juego.
 *
 * Un portal solo puede ser abierto en las caras externas del tablero, y existen
 * tres tipos de portales posibles:
 *
 * 1- Portal fila-columna: Este portal se crea entre celdas cuyo numero de piso
 * es el mismo.
 *
 * 2- Portal fila-piso: Este portal se crea entre celdas cuyo numero de columna
 * es el mismo.
 *
 * 3- Portal columna-piso: Este portal se crea entre celdas cuyo numero de fila
 * es el mismo.
 */

class Portal {

private:

	Celda* salida;
	int tipoDePortal;

public:

	/*
	 * POST: Crea un nuevo Portal de un determinado tipo y con una salida
	 * 		 establecida.
	 */
	Portal(Celda* salida, int tipoDePortal);


	/*
	 * POST: Devuelve de que tipo es Portal.
	 */
	int indicarTipo();


	/*
	 * POST: Devuelve la celda a la cual se llega al cruzar Portal.
	 */
	Celda* indicarSalida();


	/*
	 * POST: Libera los recursos solicitados.
	 */
	~Portal();
};

#endif /* PORTAL_H_ */
