
#ifndef FICHA_H_
#define FICHA_H_

#include <cstdlib>
#include "Color.h"


class Ficha{

private:

	int numero;
	Color* color;

public:

	/*
	 * POST: Crea una Ficha lista para su uso.
	 */
	Ficha(int numero);


	/*
	 * POST: Devuelve el numero del jugador al que corresponde esta ficha.
	 */
	int darNumero();


	/*
	 * POST: Devuelve el color de la ficha.
	 */
	Color* darColor();


	/*
	 * POST: Libera los recursos solicitados.
	 */
	~Ficha();

};

#endif /* FICHA_H_ */
