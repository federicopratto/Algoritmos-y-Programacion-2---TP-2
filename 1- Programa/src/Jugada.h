
#ifndef JUGADA_H_
#define JUGADA_H_

#include "Celda.h"
#include "Jugador.h"
#include "Tablero.h"
#include "Consola.h"

class Celda;	// forward declaration.
class Jugador;	// forward declaration.
class Tablero;	// forward declaration.
class Consola;	// forward declaration.


class Jugada {

private:

	Jugador* jugador;
	int fila, columna, piso;
	int numeroDeJugada;

public:

	/*
	 * POST: Crea una nueva Jugada.
	 */
	Jugada(int fila, int columna, int piso, Jugador* jugador, int numero);


	/*
	 * POST: Crea una nueva Jugada en base a otra existente.
	 */
	Jugada(Jugada* otraJugada);


	/*
	 * POST: Devuelve una referencia al valor fila de mi Jugada.
	 */
	int& darFila();


	/*
	 * POST: Devuelve una referencia al valor columna de mi Jugada.
	 */
	int& darColumna();


	/*
	 * POST: Devuelve una referencia al valor piso de mi Jugada.
	 */
	int& darPiso();


	/*
	 * POST: Devuelve al Jugador que realizo la Jugada.
	 */
	Jugador* darJugador();


	/*
	 * POST: Cambia al Jugador por nuevoJugador
	 */
	void cambiarJugador(Jugador* nuevoJugador);


	/*
	 * POST: Devuelve la Ficha correspondiente al Jugador que realizo
	 * 		 la Jugada.
	 */
	Ficha* darFicha();


	/*
	 * POST: Devuelve el color de la Ficha correpondiente al Jugador
	 * 		 que realizo la Jugada.
	 */
	Color* darColorFicha();


	/*
	 * POST: Devuelve el numero de Jugada.
	 */
	int& darNumero();


	/*
	 * POST: Libera los recursos solicitados.
	 */
	~Jugada();

};

#endif /* JUGADA_H_ */
