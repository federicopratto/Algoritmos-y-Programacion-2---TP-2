
#ifndef EINSTEIN_H_
#define EINSTEIN_H_

#include <string>
#include "Tablero.h"
#include "Jugada.h"
#include "Juez.h"

/*
 * Einstein es un tipo de objeto cuya función es, en caso de ser posible, crear un
 * portal entre dos celdas contiguas de una misma cara del cubo tridimensional que
 * conforma el tablero de juego.
 */

class Einstein {

private:

	bool portalCreado;
	int tipoDePortal;
	Jugada* ladoA;
	Jugada* ladoB;

public:

	/*
	 * POST: Crea un Einstein listo para crear un portal
	 * 		 entre dos celdas del tablero, si es que hay
	 * 		 lugar en el mismo para hacerlo.
	 */
	Einstein();


	/*
	 * POST: Si hay al menos dos celdas sin portales en el tablero,
	 * 		 crea un portal entre ellas y devuelve un valor
	 * 		 de verdad que indica que sucedio.
	 */
	bool crearPortal(Tablero* tablero, Consola* consola);


	/*
	 * PRE:  Fue creado un portal.
	 * POST: Devuelve una jugada dentro de la cual esta la direccion
	 * 		 de la celda donde se abrio un extremo del portal.
	 */
	Jugada* darLadoA();


	/*
	 * POST: Libera los recursos solicitados.
	 */
	~Einstein();

private:

	/*
	 * POST: Le asigna a los atributos "fila", "columna" y "piso"
	 * 		 del objeto lado, los valores de a, b y c respectivamente.
	 */
	void reiniciarLado(Jugada* lado, int a, int b, int c);


	/*
	 * POST: Devuelve un valor de verdad en función de si fue posible
	 * 		 obtener dos celdas en el tablero para poder abrir un nuevo
	 * 		 portal entre ellas, o el tablero no admite mas portales
	 * 		 de momento.
	 */
	bool obtenerCeldas(Tablero* tablero);

};

#endif /* EINSTEIN_H_ */
