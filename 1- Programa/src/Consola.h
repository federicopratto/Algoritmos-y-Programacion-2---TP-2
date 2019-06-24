
#ifndef CONSOLA_H_
#define CONSOLA_H_

#include "Tablero.h"
#include "Jugador.h"
#include "Jugada.h"
#include <iostream>

using std::string;

class Jugador;	// forward declaration.
class Tablero;	// forward declaration.
class Jugada;	// forward declaration.


class Consola {

public:

	/*
	 * POST: Crea una nueva consola lista para usarse, la cual
	 * 		 presenta el juego.
	 */
	Consola();


	/*
	 * POST: Solicita al usuario que elija una dificultad,
	 * 		 valida el dato y lo devuelve por referencia.
	 */
	void pedirDificultad(int& dificultad);


	/*
	 * POST: Solicita al usuario que elija las dimensiones
	 * 		 del tablero del juego y devuelve dichas medidas.
	 */
	void pedirTamanioTablero(int& filas, int& columnas, int& pisos);


	/*
	 * POST: Solicita al usuario una cantidad de jugadores
	 * 		 y devuelve dicho dato.
	 */
	int pedirCantidadDeJugadores();


	/*
	 * POST: Solicita al usuario el nombre de un jugador dado
	 * 		 y devuelve este dato.
	 */
	string pedirNombreJugador(int nro);


	/*
	 * POST: Indica el nombre y numero del jugador actual,
	 * 		 asi como la cantidad de fichas que dispone para jugar.
	 */
	void indicarTurnoActual(Jugador* jugadorActual);


	/*
	 * PRE:	 El tablero no esta lleno.
	 * POST: Le solicita al jugadorActual por consola que eliga
	 * 		 una posicion donde colocar su ficha, y valida si la
	 * 		 misma es valida y no esta llena.
	 */
	void pedirPosicionFicha(Jugada* jugadaActual, Tablero* tablero);


	/*
	 * POST: Muestra el efecto que ha tenido la carta usada en el
	 * 		 desarrollo de la partida.
	 */
	void mostrarEfectoJugada(Jugada* jugada, string efecto);


	/*
	 * POST: Muestra el efecto que ha tenido la carta usada en el
	 * 		 desarrollo de la partida.
	 */
	void mostrarEfectoJugada(string efecto);


	/*
	 * POST: Muestra el encabezado del cuadro encargado
	 * 		 de mostrar el tablero por consola.
	 */
	void mostrarEncabezado(int fila, int pisos, int espaciosMax);


	/*
	 * POST: Muestra el numero de la columna actual cuando se imprime
	 * 		 el tablero por consola.
	 */
	void mostrarNumeroDeColumna(int columna);


	/*
	 * POST: Muestra una ficha en la posicion actual del tablero cuando
	 * 		 se muestra el mismo por consola.
	 */
	void mostrarFicha(int ficha, int espaciosMax);


	/*
	 * POST: Muestra un pie de pagina para finalizar el cuadro al
	 * 		 imprimir el tablero por consola.
	 */
	void mostrarPieDePagina(int pisos, int espaciosMax);


	/*
	 * POST: Muestra al jugadorActual que cartas tiene disponibles, y
	 * 		 le pregunta si desea usar alguna. Devuelve su respuesta.
	 */
	int quiereUsarCarta(Jugador* jugadorActual);


	/*
	 * POST: Le solicita al usuario la posicion de las fichas en el tablero
	 * 		 que desea intercambiar.
	 */
	void pedirFichasACambiar(Tablero* tablero, Jugada* ficha1, Jugada* ficha2);


	/*
	 * POST: Muestra como ha concluido una partida.
	 */
	void mostrarResultado(Jugador* jugadorActual, int resultado);


	/*
	 * POST: Libera los recursos solicitados.
	 */
	~Consola();

private:

	/*
	 * POST: Solicita el tamaño de una parteDelTablero al usuario
	 * 		 para crear un nuevo Tablero.
	 */
	void pedirTamanio(string parteDelTablero, int& posicion);


	/*
	 * POST: Solicita al usuario la posicion de una parteDelTablero
	 * 		 donde desea realizar su jugada.
	 */
	void pedirPosicion(string parteDelTablero, int& posicion, int limite);


	/*
	 * POST: Imprime por consola un separador conformado
	 * 		 por guiones (-) para aportar claridad cuando se muestra
	 * 		 el tablero por consola.
	 */
	void mostrarSeparador(int espaciosMax, int pisos);


	/*
	 * PRE:  El tipo de dato ingresado es valido.
	 * POST: Devuelve la cantidad de digitos de numero.
	 */
	int contarDigitos(unsigned int numero);


	/*
	 * POST: Muestra las cartas que tiene disponibles el jugadorActual
	 */
	void mostrarCartasDisponibles(Lista<Carta*>* cartas);

};

#endif /* CONSOLA_H_ */
