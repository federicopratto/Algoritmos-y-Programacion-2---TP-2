
#ifndef CARTA_H_
#define CARTA_H_

#include <cstdlib>
#include <string>

using std::string;

class Carta {

private:

	int poder;
	string descripcion;

public:

	/*
	 * POST: Crea una nueva Carta lista para usar.
	 */
	Carta();


	/*
	 * POST: Devuelve el poder de la carta.
	 */
	int esUsada();


	/*
	 * POST: Devuelve la decripcion de los poderes que posee
	 * 		 la carta.
	 */
	string mostrarPoder();


	/*
	 * POST: Libera los recursos solicitados.
	 */
	~Carta();

private:

	/*
	 * POST: Se le asigna la descripción correspondiente a su poder
	 * 		 a la carta.
	 */
	void asignarDescripcion();

};

#endif /* CARTA_H_ */
