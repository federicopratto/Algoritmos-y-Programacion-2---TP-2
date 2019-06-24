
#ifndef DIBUJANTE_H_
#define DIBUJANTE_H_

#include <string>
#include "Color.h"
#include "Imagen.h"
#include "Tablero.h"
#include "Jugada.h"


class Dibujante {

private:

	int tamanioCelda;
	Imagen* imagenDelTablero;
	Imagen* imagenAInsertar;
	const char* rutaArchivo;
	Color* negro;

public:

	/*
	 * POST: Crea un nuevo Dibujante listo para trabajar.
	 */
	Dibujante();


	/*
	 * POST: Si es la primer jugada de la partida, crea una imagen
	 * 		 de cada fila del tablero en blanco.
	 *
	 * 		 Crea una copia de la imagen, de la jugada anterior,
	 * 		 de cada fila del tablero.
	 *
	 * 		 Por ultimo carga la imagen correspondiente a la fila
	 * 		 del tablero donde se coloco la ficha en la ultimaJugada,
	 * 		 modifica dicha imagen agregando la nueva ficha y
	 * 		 la guarda.
	 */
	void cargarJugada(Tablero* tablero, Jugada* ultimaJugada);


	/*
	 * POST: Crea una copia de la imagen de cada fila del tablero
	 * 		 de la jugada anterior.
	 * 		 Luego, carga la imagen correspondiente a la fila
	 * 		 del tablero donde esta la jugadaBorrada, modifica
	 * 		 dicha imagen quitando la ficha y la guarda.
	 */
	void borrarJugada(Tablero* tablero, Jugada* jugadaBorrada);


	/*
	 * POST: Crea una copia de la imagen, de la jugada anterior,
	 * 		 de cada fila del tablero.
	 * 		 Luego, carga la imagen correspondiente a la fila
	 * 		 del tablero donde esta la ficha que debe cambiar
	 * 		 de color. Modifica dicha imagen cambiando el color
	 * 		 de la ficha y la guarda.
	 */
	void cambiarColorFicha(Tablero* tablero, Jugada* ficha);


	/*
	 * POST: Crea una copia de la imagen, de la jugada anterior,
	 * 		 de cada fila del tablero.
	 * 		 Luego, carga la imagen correspondiente a la fila
	 * 		 del tablero donde esta la ficha1, modifica dicha
	 * 		 imagen colocando en su lugar ficha2 y la guarda.
	 *
	 * 		 Por ultimo, carga la imagen correspondiente a la fila
	 * 		 del tablero donde esta la ficha2, modifica dicha
	 * 		 imagen colocando en su lugar ficha1 y la guarda.
	 */
	void intercambiarFichas(Tablero* tablero, Jugada* ficha1, Jugada* ficha2);


	/*
	 * POST: Libera los recursos solicitados.
	 */
	~Dibujante();

private:

	/*
	 * POST: Si es la primer jugada de la partida, crea una imagen
	 * 		 de cada fila del tablero en blanco.
	 *
	 * 		 Crea una copia de la imagen, de la jugada anterior,
	 * 		 de cada fila del tablero.
	 */
	void crearImagenTablero(Tablero* tablero, Jugada* ultimaJugada);


	/*
	 * POST: Genera una imagen en blanco de cada fila del tablero
	 * 		 y la guarde con el nombre "Jugada 0 Fila #.bmp"
	 *
	 * 		 # es un numero de fila.
	 */
	void generarNuevoTablero(Tablero* tablero);


	/*
	 * PRE:  La imagenDelTablero ha sido instanciada.
	 * POST: inserta la imagen "ejes.bmp" en el extremo inferior
	 * 		 izquierdo de la imagen del tablero.
	 */
	void insertarEjes();

	/*
	 * PRE:  La imagenDelTablero ha sido instanciada.
	 * POST: Dibuja un recuadro blanco en el interior de imagenDelTablero
	 * 		 donde se colocaran las fichas.
	 */
	void dibujarRecuadroTablero();

	/*
	 * PRE:  La imagenDelTablero ha sido instanciada.
	 * POST: Carga la imagen "ficha.bmp" de la carpeta "load",
	 * 		 la colorea con el color de ultimaJugada y la inserta
	 * 		 en la posicion que corresponda del tablero.
	 */
	void insertarFicha(Jugada* ultimaJugada, Tablero* tablero);


	/*
	 * PRE:  La imagenDelTablero ha sido instanciada.
	 * POST: Crea una imagen de una altura igual a la hilera
	 * 		 de fichas que se encuentra por encima de jugadaBorrada
	 * 		 en el tablero, copia dicha hilera en la imagen, e
	 * 		 inserta esa imagen una posicion mas abajo en imagenDelTablero.
	 *
	 * 		 Finalmente, coloca un cuadrado blanco del tamaño de una
	 * 		 celda por encima de dicha hilera.
	 *
	 * 		hilera	 |O|     O
	 * 		copiada	 |O|    |O|    O
	 * 		 		 |O| -> |O| -> O
	 * 		ficha a  |O|    |O|    O
	 * 		borrar -> X     |O|    O
	 *
	 */
	void borrarFicha(Jugada* jugadaBorrada, Tablero* tablero);


	/*
	 * PRE:  imagenDelTablero ha sido instanciada.
	 * POST: inserta imagenAInsertar en la posicion (x,y) de
	 * 		 imagenDelTablero solicitada.
	 */
	void insertarImagen(int x, int y);


	/*
	 * PRE:  imagenDelTablero ha sido instanciada.
	 * POST: guarda imagenDelTablero como un archivo .bmp
	 */
	void guardarImagen(int jugada, int fila);

};

#endif /* DIBUJANTE_H_ */
