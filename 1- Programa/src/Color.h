
#ifndef COLOR_H_
#define COLOR_H_

#include "EasyBMP.h"


class Color {

private:

	RGBApixel* colores;

public:

	/*
	 * PRE:  rojo, verde y azul son enteros entre 0 y 255.
	 * POST: Genera un color del modelo RGB.
	 */
	Color(ebmpBYTE rojo, ebmpBYTE verde, ebmpBYTE azul);


	/*
	 * PRE: 'nuevoRojo' es un entero entre 0 y 255.
	 * POST: Asigna una nueva cantidad de rojo.
	 */
	void asignarRojo(ebmpBYTE nuevoRojo);


	/*
	 * PRE: 'nuevoVerde' es un entero entre 0 y 255.
	 * POST: Asigna una nueva cantidad de verde.
	 */
	void asignarVerde(ebmpBYTE nuevoVerde);


	/*
	 * PRE: 'nuevoAzul' es un entero entre 0 y 255.
	 * POST: Asigna una nueva cantidad de azul.
	 */
	void asignarAzul(ebmpBYTE nuevoAzul);


	/*
	 * POST: Devuelve un RGBApixel con los colores asociados.
	 */
	RGBApixel obtenerPixel();


	/*
	 * POST: libera los recursos utilizados
	 */
	~Color();

};

#endif /* COLOR_H_ */
