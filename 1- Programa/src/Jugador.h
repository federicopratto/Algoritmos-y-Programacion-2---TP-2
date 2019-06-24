
#ifndef JUGADOR_H_
#define JUGADOR_H_

#include <string>
#include "Lista.h"
#include "Carta.h"
#include "Ficha.h"
#include "Tablero.h"
#include "Jugada.h"
#include "Consola.h"

using std::string;

class Consola;	// forward declaration.
class Jugada;	// forward declaration.


class Jugador {

private:

	string nombre;
	Ficha* ficha;
	int cantidadDeFichas;
	Lista<Carta*>* pozoDeCartas;

public:

	/*
	 * POST: Genera un nuevo Jugador.
	 */
	Jugador(string nombre, int numero, int fichas);


	/*
	 * POST: Devuelve el nombre del Jugador.
	 */
	string darNombre();


	/*
	 * POST: Devuelve el numero del Jugador.
	 */
	int darNumero();


	/*
	 * POST: Devuelve la Ficha del Jugador.
	 */
	Ficha* darFicha();


	/*
	 * POST: Devuelve la cantidad de fichas que tiene el Jugador.
	 */
	int contarFichas();


	/*
	 * PRE:  El jugador tiene al menos una Ficha.
	 * POST: Se reduce en una la cantidad de Fichas del jugador.
	 */
	void realizarJugada();


	/*
	 * POST: Devuelve un valor de verdad en funcion de si el jugador
	 * 		 cuenta con alguna carta de poder.
	 */
	bool tieneCartas();


	/*
	 * POST: Devuelve un valor de verdad en funcion de si el pozoDeCartas
	 * 		 tiene lugar para almacenar mas cartas de poder.
	 */
	bool pozoLleno();


	/*
	 * PRE:  El jugador cuenta con lugar en su pozoDeCartas para almacenar otra.
	 * POST: Almacena una nueva carta de poder en el pozoDeCartas.
	 */
	Carta* recibirCarta();


	/*
	 * POST: Devuelve la lista de cartas con que cuenta el Jugador.
	 */
	Lista<Carta*>* mostrarCartas();


	/*
	 * PRE:  El jugador debe tener alguna carta de poder.
	 * POST: Se utiliza una carta de poder y se quita la misma del pozoDeCartas.
	 */
	int usarCarta(int numeroDeCarta);


	/*
	 * POST: Quita todas las cartas de poder al Jugador y 10 fichas,
	 * 		 si tiene menos fichas, le quita todas.
	 */
	void perderFichas();


	/*
	 * POST: Se liberan los recursos solicitados.
	 */
	~Jugador();

};

#endif /* JUGADOR_H_ */
