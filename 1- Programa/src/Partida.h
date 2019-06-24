
#ifndef PARTIDA_H_
#define PARTIDA_H_

#include "Tablero.h"
#include "Jugador.h"
#include "Jugada.h"
#include "Consola.h"
#include "Dibujante.h"
#include "Einstein.h"
#include "Juez.h"
#include <string>


class Partida {

private:

	Lista<Jugador*> *listaDeJugadores, *jugadoresEliminados;
	Jugador* cartaColor;
	Tablero* tablero;
	Consola* consola;
	Dibujante* dibujante;
	Juez* juez;
	Jugada *jugadaAnterior, *jugadaActual;
	bool terminoLaPartida, robarFichas;
	int dificultad, turno;


public:

	/*
	 * POST: Crea una nueva Partida lista para ser jugada.
	 */
	Partida();


	/*
	 * POST: Indica de quien es el turno actual, comienza una
	 * 		 nueva ronda de juego y elimina a los jugadores que
	 * 		 se hayan quedado sin fichas.
	 */
	void jugarPartida();


	/*
	 * POST: Libera los recursos solicitados.
	 */
	~Partida();


private:

	/*
	 * POST: Devuelve un entero que representa la cantidad de fichas
	 * 		 que se asignara a cada jugador en base a la dificultad elegida.
	 */
	int repartirFichas();


	/*
	 * POST: Se encarga de verificar si el jugador actual tiene fichas
	 * 		 para jugar, en caso de contar con fichas le pide que realice
	 * 		 su jugada, caso contrario lo anota en la lista de jugadores
	 * 		 a eliminar y pasa al siguiente turno.
	 */
	void jugarRonda();


	/*
	 * POST: Llama a los metodos necesarios para que un jugador
	 * 		 juegue su turno.
	 *
	 *		 - Le pregunta donde quiere guardar la ficha al jugador.
	 *		 - Guarda dicha ficha en el tablero
	 *		 - Muestra el estado del tablero por consola
	 *		 - Genera una imagen del tablero
	 *		 - Verifica si el juego termino (hubo empate o cuatro en linea)
	 *		 - Le pregunta al jugador si quiere usar alguna carta de poder (si tiene)
	 *		 - Le asigna una nueva carta (si corresponde)
	 */
	void jugarTurno();


	/*
	 * POST: Le asigna una nueva carta de poder al jugador actual, si
	 *       el Juez decide que corresponde, y si el jugador cuenta con
	 *       lugar para guardarla.
	 */
	void darCarta();


	/*
	 * POST: Le consulta al jugador actual si quiere usar alguna de sus
	 * 		 cartas si es que tiene alguna en su pilon.
	 */
	void preguntarSiQuiereUsarCarta();


	/*
	 * POST: llama al metodo correspondiente en funcion de la carta elegida.
	 */
	void usarCarta(int cartaElegida);


	/*
	 * POST: Cambia el color de una ficha al azar del tablero, muestra como
	 * 		 quedo el tablero por consola, imprime una imagen del tablero y
	 * 		 corrobora si esta jugada hizo que termine el juego.
	 */
	void usarCarta1();


	/*
	 * POST: Elimina una ficha al azar del tablero, muestra como quedo
	 * 		 el tablero por consola, imprime una imagen del tablero y
	 * 		 corrobora si esta jugada hizo que termine el juego.
	 */
	void usarCarta2();


	/*
	 * POST: Solicita al usuario dos fichas del tablero para intercambiar,
	 * 		 valida si dichas fichas son vecinas y efectivamente pueden
	 * 		 intercambiarse, muestra como quedo el tablero por consola,
	 * 		 imprime una imagen del tablero y corrobora si esta jugada hizo
	 * 		 que termine el juego.
	 */
	void usarCarta3();


	/*
	 * POST: Intenta abrir un portal entre dos celdas laterales de una misma
	 * 		 cara del tablero, en caso de ser posible verifica si el portal
	 * 		 ocasiono que termine el juego.
	 */
	void usarCarta4();


	/*
	 * POST: Borra la jugada realizada en el turno anterior, muestra como
	 * 		 quedo el tablero por consola, imprime una imagen del tablero
	 * 		 y corrobora si esta jugada hizo que termine le juego.
	 */
	void usarCarta5();


	/*
	 * POST: Le quita todas sus cartas de poder y 10 fichas al jugador
	 * 		 siguiente.
	 */
	void usarCarta6();


	/*
	 * POST: Actualiza el color que se asignara a una ficha al azar del
	 * 		 tablero si se utiliza la carta de poder que cambia de color
	 * 		 fichas.
	 *
	 * 		 Dado que el color que entregara esta carta a una ficha depende
	 * 		 de cuantas veces haya sido usada.
	 *
	 * 		 Si tengo una lista de "n" jugadores:
	 *
	 * 		 uso 1 -> cartaColor = jugador1
	 * 		 uso 2 -> cartaColor = jugador2
	 * 		 .
	 * 		 .
	 * 		 uso n -> cartaColor = jugador n
	 * 		 uso n+1 -> cartaColor = jugador1
	 */
	void actualizarColorCarta();


	/*
	 * POST: Quita de la lista de jugadores a los jugadores que se han
	 * 		 quedado sin fichas.
	 */
	void eliminarJugadores();


	/*
	 * POST: Revisa si el juego ha acabado, ya sea porque:
	 *
	 * 		 - Alguien logro formar 4 en linea.
	 *		 - No hay mas lugar en el tablero.
	 *		 - Nadie tiene fichas para continuar jugando.
	 */
	void terminoElJuego(Jugada* jugada);


	/*
	 * PRE:	 Posicion pertenece al intervalor [1, listaDeJugadores->contarElementos()]
	 * POST: Avanza la lista de jugadores hasta posicionFinal.
	 */
	void avanzarListaHasta(unsigned int posicionFinal);

};

#endif /* PARTIDA_H_ */
