
#ifndef TABLERO_H_
#define TABLERO_H_

#include "Celda.h"
#include "Lista.h"
#include "Consola.h"
#include "Jugada.h"
#include <string>
#include <algorithm>

class Consola;	// forward declaration.
class Jugada;	// forward declaration.
class Celda;	// forward declaration.


class Tablero {

private:

	Lista<Lista<Lista<Celda*>*>*>* tablero;
	int filas, columnas, pisos;

public:

	/*
	 * POST: Crea un tablero listo para usar.
	 */
	Tablero(Consola* consola);


	/*
	 * POST: Devuelve la cantidad de filas que tiene el Tablero.
	 */
	int& darFilas();


	/*
	 * POST: Devuelve la cantidad de columnas que tiene el Tablero.
	 */
	int& darColumnas();

	/*
	 * POST: Devuelve la cantidad de pisos que tiene el Tablero.
	 */
	int& darPisos();


	/*
	 * PRE:  La ubicacion donde se quiere guardar la ficha cuenta con lugar.
	 * POST: Agrega una nueva ficha al tablero en la ubicacion solicitada.
	 */
	void guardarFicha(Jugada* jugada);


	/*
	 * PRE:  Los valores pasados de ubicacion son validos.
	 * POST: Devuelve un valor de verdad en funcion de si la cantidad de elementos
	 * 		 que puede almacenar una hilera(fila i, columna j) ha llegado a su
	 * 		 numero maximo.
	 */
	bool hileraLlena(Jugada* jugada);


	/*
	 * POST: Devuelve un valor de verdad en funcion de si la cantidad de elementos
	 * 		 que puede almacenar el tablero ha llegado a su numero maximo.
	 */
	bool estaLleno();


	/*
	 * POST: Muestra el estado actual del tablero por consola.
	 */
	void mostrarEstado(Consola* consola, int cantDeJugadores);


	/*
	 * POST: Copia en la Lista hilera las fichas circundantes a la ultima
	 * 		 ficha colocada para que se corrobore si hubo cuatro en linea.
	 */
	void copiarHilera(int nroDeHilera, Lista<Celda*>* hilera, Jugada* ultimaJugada);


	/*
	 * POST: Reemplaza una ficha al azar por una nueva ficha y almacena la
	 * 		 posicion de la ficha que fue cambiada en posicion.
	 */
	void cambiarColorFicha(Jugada* posicion);


	/*
	 * POST: Elimina una ficha al azar y almacena la posicion
	 * 		 de la ficha que fue borrada en posicion.
	 * 		 Ademas, si otra ficha ocupo dicha posicion, almacena
	 * 		 el Jugador al que corresponde dicha Ficha en posicion.
	 */
	void eliminarFichaAlAzar(Jugada* posicion);


	/*
	 * POST: Elimina la celda de jugadaAnterior. Ademas, si otra Ficha
	 * 		 ocupa dicha posicion, almacena el Jugador al que corresponde
	 * 		 dicha Ficha en posicion.
	 */
	void eliminarJugadaAnterior(Jugada* jugadaAnterior);


	/*
	 * POST: Devuelve un valor de verdad en funcion de si hay al menos dos
	 * 		 fichas en el tablero que puedan intercambiarse.
	 */
	bool hayVecinas();


	/*
	 * POST: Devuelve un valor de verdad en funcion de si dos fichas
	 * 	 	 pueden intercambiarse.
	 */
	bool sePuedenCambiarLasFichas(Jugada* ficha1, Jugada* ficha2, Consola* consola);


	/*
	 * POST: Intercambia de posicion las fichas de dos celdas vecinas.
	 */
	void intercambiarFichas(Jugada* ficha1, Jugada* ficha2);


	/*
	 * POST: Abre un portal entre dos celdas.
	 */
	void abrirPortal(Jugada* ladoA, Jugada* ladoB, int tipoDePortal);


	/*
	 * POST: Busca entre las celdas del tablero si hay dos celdas adyacentes
	 * 		 tales que sea posible formar un Portal de tipo 1.
	 */
	bool buscarCeldaSinPortal1(Jugada* ladoA, Jugada* ladoB);


	/*
	 * POST: Busca entre las celdas del tablero si hay dos celdas adyacentes
	 * 		 tales que sea posible formar un Portal de tipo 2.
	 */
	bool buscarCeldaSinPortal2(Jugada* ladoA, Jugada* ladoB);


	/*
	 * POST: Busca entre las celdas del tablero si hay dos celdas adyacentes
	 * 		 tales que sea posible formar un Portal de tipo 3.
	 */
	bool buscarCeldaSinPortal3(Jugada* ladoA, Jugada* ladoB);


	/*
	 * POST: Libera los recursos solicitados.
	 */
	~Tablero();

private:

	/*
	 * POST: Devuelve un valor de verdad en funcion de si una celda dada
	 * 		 no existe (la posicion esta vacia)
	 */
	bool posicionVacia(Jugada* posicion);


	/*
	 * POST: Devuelve un valor de verdad en funcion de si dos celdas
	 * 		 son vecinas en el tablero.
	 */
	bool verSiSonVecinas(Jugada* ficha1, Jugada* ficha2);


	/*
	 * POST: Devuelve en la lista Hilera, la hilera de fichas que estan por
	 * debajo de la ultima ficha colocada (fila cte, columna cte, piso decreciente)
	 * para que se analice si hubo cuatro en linea.
	 *
	 * Ej:
	 *
	 * U: última ficha colocada.
	 * X: fichas a copiar.
	 * -: fichas a omitir
	 *
	 * 		- - - - - 4
	 * 		- - U - - 3 PISO
	 * 		- - X - - 2
	 * 		- - X - - 1
	 *		1 2 3 4 5
	 *		  FILA
	 */
	void copiarHilera1(Lista<Celda*>* hilera, Jugada* ultimaJugada);


	/*
	 * POST: Devuelve en la lista Hilera, la hilera de fichas que estan
	 * horizontales a la ultima ficha colocada (fila creciente, piso cte,
	 * columna cte) para que se analice si hubo cuatro en linea.
	 *
	 * Ej:
	 *
	 * U: última ficha colocada.
	 * X: fichas a copiar.
	 * -: fichas a omitir
	 *
	 * 		- - - - - 4
	 * 		X X U X X 3 PISO
	 * 		- - - - - 2
	 * 		- - - - - 1
	 *		1 2 3 4 5
	 *		  FILA
	 */
	void copiarHilera2(Lista<Celda*>* hilera, Jugada* ultimaJugada);


	/*
	 * POST: Devuelve en la lista Hilera, la hilera de fichas que estan
	 * en diagonal (fila creciente, piso creciente, columna cte.) a la
	 * ultima ficha colocada para que se analice si hubo cuatro en linea.
	 *
	 * Ej:
	 *
	 * U: última ficha colocada.
	 * X: fichas a copiar.
	 * -: fichas a omitir
	 *
	 *		- - - X - 4
	 * 		- - U - - 3 PISO
	 * 		- X - - - 2
	 * 		X - - - - 1
	 *		1 2 3 4 5
	 *		  FILA
	 */
	void copiarHilera3(Lista<Celda*>* hilera, Jugada* ultimaJugada);


	/*
	 * POST: Devuelve en la lista Hilera, la hilera de fichas que estan
	 * en diagonal (fila creciente, piso decreciente, columna cte.) a la
	 * ultima ficha colocada para que se analice si hubo cuatro en linea.
	 *
	 * Ej:
	 *
	 * U: última ficha colocada.
	 * X: fichas a copiar.
	 * -: fichas a omitir
	 *
	 *		- X - - - 4
	 * 		- - U - - 3 PISO
	 * 		- - - X - 2
	 * 		- - - - X 1
	 *		1 2 3 4 5
	 *		  FILA
	 */
	void copiarHilera4(Lista<Celda*>* hilera, Jugada* ultimaJugada);


	/*
	 * POST: Devuelve en la lista Hilera, la hilera de fichas que estan
	 * horizontales a la ultima ficha colocada (fila cte, piso cte,
	 * columna creciente) para que se analice si hubo cuatro en linea.
	 *
	 * Ej:
	 *
	 * U: última ficha colocada.
	 * X: fichas a copiar.
	 * -: fichas a omitir
	 *
	 *		- - - - - 4
	 * 		X X U X X 3 PISO
	 * 		- - - - - 2
	 * 		- - - - - 1
	 *		1 2 3 4 5
	 *		 COLUMNA
	 */
	void copiarHilera5(Lista<Celda*>* hilera, Jugada* ultimaJugada);


	/*
	 * POST: Devuelve en la lista Hilera, la hilera de fichas que estan
	 * en diagonal a la ultima ficha colocada (fila cte, piso creciente,
	 * columna creciente) para que se analice si hubo cuatro en linea.
	 *
	 * Ej:
	 *
	 * U: última ficha colocada.
	 * X: fichas a copiar.
	 * -: fichas a omitir
	 *
	 *		- - - X - 4
	 * 		- - U - - 3 PISO
	 * 		- X - - - 2
	 * 		X - - - - 1
	 *		1 2 3 4 5
	 *		 COLUMNA
	 */
	void copiarHilera6(Lista<Celda*>* hilera, Jugada* ultimaJugada);


	/*
	 * POST: Devuelve en la lista Hilera, la hilera de fichas que estan
	 * en diagonal a la ultima ficha colocada (fila cte, piso decreciente,
	 * columna creciente) para que se analice si hubo cuatro en linea.
	 *
	 * Ej:
	 *
	 * U: última ficha colocada.
	 * X: fichas a copiar.
	 * -: fichas a omitir
	 *
	 *		- X - - - 4
	 * 		- - U - - 3 PISO
	 * 		- - - X - 2
	 * 		- - - - X 1
	 *		1 2 3 4 5
	 *		 COLUMNA
	 */
	void copiarHilera7(Lista<Celda*>* hilera, Jugada* ultimaJugada);


	/*
	 * POST: Devuelve en la lista Hilera, la hilera de fichas que estan
	 * en diagonal a la ultima ficha colocada (fila creciente, piso cte,
	 * columna creciente) para que se analice si hubo cuatro en linea.
	 *
	 * Ej:
	 *
	 * U: última ficha colocada.
	 * X: fichas a copiar.
	 * -: fichas a omitir
	 *
	 *		- - - X - 4
	 * 		- - U - - 3 COLUMNA
	 * 		- X - - - 2
	 * 		X - - - - 1
	 *		1 2 3 4 5
	 *		  FILA
	 */
	void copiarHilera8(Lista<Celda*>* hilera, Jugada* ultimaJugada);


	/*
	 * POST: Devuelve en la lista Hilera, la hilera de fichas que estan
	 * en diagonal a la ultima ficha colocada (fila creciente, piso cte,
	 * columna decreciente) para que se analice si hubo cuatro en linea.
	 *
	 * Ej:
	 *
	 * U: última ficha colocada.
	 * X: fichas a copiar.
	 * -: fichas a omitir
	 *
	 *		- X - - - 4
	 * 		- - U - - 3 COLUMNA
	 * 		- - - X - 2
	 * 		- - - - X 1
	 *		1 2 3 4 5
	 *		  FILA
	 */
	void copiarHilera9(Lista<Celda*>* hilera, Jugada* ultimaJugada);


	/*
	 * POST: Devuelve en la lista Hilera, la hilera de fichas que estan
	 * en diagonal a la ultima ficha colocada (fila creciente, piso creciente,
	 * columna creciente) para que se analice si hubo cuatro en linea.
	 *
	 * Ej:
	 *
	 * U: última ficha colocada.
	 * X: fichas a copiar.
	 * -: fichas a omitir
	 *
	 *		 4 - - - X - 4
	 * 	PISO 3 - - U - - 3 COLUMNA
	 * 		 2 - X - - - 2
	 * 		 1 X - - - - 1
	 *		   1 2 3 4 5
	 *		     FILA
	 */
	void copiarHilera10(Lista<Celda*>* hilera, Jugada* ultimaJugada);


	/*
	 * POST: Devuelve en la lista Hilera, la hilera de fichas que estan
	 * en diagonal a la ultima ficha colocada (fila creciente, piso decreciente,
	 * columna creciente) para que se analice si hubo cuatro en linea.
	 *
	 * Ej:
	 *
	 * U: última ficha colocada.
	 * X: fichas a copiar.
	 * -: fichas a omitir
	 *
	 *		 1 - - - X - 4
	 * 	PISO 2 - - U - - 3 COLUMNA
	 * 		 3 - X - - - 2
	 * 		 4 X - - - - 1
	 *		   1 2 3 4 5
	 *		     FILA
	 */
	void copiarHilera11(Lista<Celda*>* hilera, Jugada* ultimaJugada);


	/*
	 * POST: Devuelve en la lista Hilera, la hilera de fichas que estan
	 * en diagonal a la ultima ficha colocada (fila creciente, piso decreciente,
	 * columna decreciente) para que se analice si hubo cuatro en linea.
	 *
	 * Ej:
	 *
	 * U: última ficha colocada.
	 * X: fichas a copiar.
	 * -: fichas a omitir
	 *
	 *		 4 - X - - - 4
	 * 	PISO 3 - - U - - 3 COLUMNA
	 * 		 2 - - - X - 2
	 * 		 1 - - - - X 1
	 *		   1 2 3 4 5
	 *		     FILA
	 */
	void copiarHilera12(Lista<Celda*>* hilera, Jugada* ultimaJugada);


	/*
	 * POST: Devuelve en la lista Hilera, la hilera de fichas que estan
	 * en diagonal a la ultima ficha colocada (fila creciente, piso creciente,
	 * columna decreciente) para que se analice si hubo cuatro en linea.
	 *
	 * Ej:
	 *
	 * U: última ficha colocada.
	 * X: fichas a copiar.
	 * -: fichas a omitir
	 *
	 *		 1 - X - - - 4
	 * 	PISO 2 - - U - - 3 COLUMNA
	 * 		 3 - - - X - 2
	 * 		 4 - - - - X 1
	 *		   1 2 3 4 5
	 *		     FILA
	 */
	void copiarHilera13(Lista<Celda*>* hilera, Jugada* ultimaJugada);


	/*
	 * POST: Vacia la lista hilera de elementos.
	 */
	void vaciarHilera(Lista<Celda*>* hilera);


	/*
	 * PRE:	 posicionFinal pertenece al intervalo [1, filas]
	 * POST: Avanza la lista tablero del tablero hasta una fila indicada.
	 */
	void avanzarFilaHasta(int posicionFinal);


	/*
	 * PRE:	 posicionFinal pertenece al intervalo [1, columnas]
	 * POST: Avanza una sublista (columnas) de la lista tablero hasta
	 * 		 la columna indicada.
	 */
	void avanzarColumnaHasta(int posicionFinal);


	/*
	 * POST: Intenta avanzar una sub-sublista (pisos) de la lista
	 * 		 tablero hasta un piso indicada, y retorna un valor de verdad
	 * 		 en funcion del resultado obtenido.
	 */
	bool avanzarPisoHasta(int posicionFinal);


	/*
	 * PRE:  Los valores cotaInf y cotaSup deben estan inicializados en
	 *		 el numero 3 la primera vez que sea llamado el metodo.
	 * POST: Devuelve los limites entre los cuales puede alejarse uno de
	 *		 la ultima ficha colocada en el tablero, sin salirse de los limites
	 *		 del mismo.
	 */
	void determinarCotas(int& cotaInf, int& cotaSup, int numero, int maximo);


	/*
	 * POST: Devuelve una posicion al azar dentro del tablero en la cual
	 * 		 hay una ficha.
	 */
	void posicionAlAzar(int& fila, int& columna, int& hayFichas);


	/*
	 * PRE:  El tipo de dato ingresado es valido.
	 * POST: Devuelve la cantidad de digitos de dicho numero.
	 */
	int contarDigitos(unsigned int numero);

};

#endif /* TABLERO_H_ */
