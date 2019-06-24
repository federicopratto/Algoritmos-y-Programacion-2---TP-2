
#ifndef JUEZ_H_
#define JUEZ_H_

#include "Tablero.h"
#include <string>

using std::string;

/*
 * El Juez es el encargado de realizar todas las acciones que tengan que ver
 * con el desarrollo de la partida: ver si alguien gano, ver si el tablero esta
 * lleno, ver si todos perdieron, repartir cartas a los jugadores, etc.
 */

class Juez {

private:

	Lista<Celda*>* hilera;
	Lista<Celda*>* hileraPortal;

public:

	/*
	 * POST: Crea un nuevo Juez listo para trabajar.
	 */
	Juez();


	/*
	 * POST: Decide si el jugador actual debe o no recibir una carta.
	 */
	bool darCartaA(Jugador* jugadorActual, int dificultad);


	/*
	 * POST: Indica si el jugador actual logro hacer un cuatro en linea, ya
	 * 		 sea porque alineo cuatro fichas
	 */
	bool hay4EnLinea(Tablero* tablero, Jugada* ultimaJugada);


	/*
	 * POST: Indica ocurrio un empate porque el tablero se ha llenado.
	 */
	bool huboEmpate(Tablero* tablero);


	/*
	 * POST: Le quita diez fichas a un jugador al que se le ha lanzado una carta
	 * 		 roba fichas y todas sus cartas de poder.
	 */
	void robarFichas(Jugador* jugador);


	/*
	 * POST: Libera los recursos solicitados.
	 */
	~Juez();

private:

	/*
	 * POST: Revisa una hilera de celdas del tablero, tomando la ficha de
	 * 		 la primera celda de dicha hilera como referencia y comparandola
	 * 		 con la ficha de la celda siguiente, si la siguiente es igual,
	 * 		 suma 1 a un contador y pasa a la proxima.
	 * 		 Caso contrario, coloca el contador en 1 y toma como ficha de
	 * 		 referencia la ultima ficha que habia revisado y fue distinta.
	 *
	 * 		 Ej: hilera -> X X O X X O  -> contador = 1  y ref = X
	 *
	 * 		 ref: X  ,  ¿X==X? si -> contador++
	 * 		 ref: X  ,  ¿X==O? no -> ref: O  y contador = 1
	 * 		 ref: O  ,  ¿O==X? no -> ref: X  y contador = 1
	 *
	 * 		 Ademas de lo dicho arriba, en cada celda que va visitando
	 * 		 de la hilera antes de ponerse a comparar la ficha de su interior
	 * 		 revisa si tiene un portal a otra celda.
	 *
	 * 		 En caso de que esta celda cuente con un portal, llama a otro metodo
	 * 		 el cual se encarga de revisar las posibles hileras entre los extremos
	 * 		 del portal y ver si hay 4 en linea en esas hilerasPortal.
	 *
	 *		 Si llega a encontrar cuatro en linea en una hilera del portal, deja
	 *		 de revisar el resto de la hilera de celdas con la que empezo esto.
	 *
	 *		 Devuelve por ultimo un valor de verdad que indica si hubo o no
	 *		 4 en linea.
	 *
	 */
	bool revisarHilera(Tablero* tablero);


	/*
	 * POST: Revisa si existe un portal en una celda, y en caso de existir
	 * 		 llama al metodo "cargarHileraPortal" la cual le retornara si
	 * 		 hay cuatro en linea en dicho portal.
	 */
	bool hayPortal(Celda* celda, Tablero* tablero);


	/*
	 * POST: Carga de a una las hileras de fichas posibles entre dos
	 * 		 extremos de un portal y envia las mismas de a una al
	 * 		 metodo "revisarHileraPortal", el mismo retornara un valor
	 * 		 en funcion de si detecto o no que alguna hilera contiene un
	 * 		 un 4 en linea.
	 *
	 * 		 Devuelve un valor en base a si alguna de las hileras cargadas
	 * 		 contenia un cuatro en linea.
	 */
	bool cargarHileraPortal(Tablero* tablero, Jugada* ladoA, Jugada* ladoB, int tipoDePortal);


	/*
	 * POST: Indica si en la hilera formada por las fichas que se encuentran
	 *  	 junto a los extremos de un portal se formo cuatro en linea.
	 *
	 *  	 LADO A --> X O X |<-PORTAL->| X O X <-- LADO B
	 */
	bool revisarHileraPortal();


	/*
	 * POST: Carga una lista de direcciones posibles en el espacio en las cuales
	 * 		 se ha podido formar cuatro en linea por la existencia de un portal.
	 *
	 * 		 Dependiendo del tipo de portal (la cara en la cual esta ubicado) estas
	 * 		 direcciones seran distintas.
	 */
	void cargarHilerasARevisar(Lista<int>* direccion, int tipoDePortal);


	/*
	 * POST: Vacia la lista Hilera donde se guardaron las celdas del tablero
	 * 		 para ver si hubo cuatro en linea.
	 */
	void vaciarHilera(Lista<Celda*>* hilera);

};

#endif /* JUEZ_H_ */
