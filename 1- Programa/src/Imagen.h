
#ifndef IMAGEN_H_
#define IMAGEN_H_

#include "EasyBMP.h"
#include "Color.h"
#include <string>

using std::string;


class Imagen {

private:

	BMP* imagen;
	unsigned int alto;
	unsigned int ancho;

public:

	/*
	 * PRE:  ancho y alto deben ser mayores a cero.
	 * POST: crea una imagen de ancho x alto en pixeles totalmente blanca.
	 * 		 El origen de coordenadas se encuentra en el extremo superior
	 * 		 izquierdo de la imagen.
	 */
	Imagen(unsigned int ancho, unsigned int alto);


	/*
	 * PRE:  ancho y alto deben ser mayores a cero.
	 * POST: crea una imagen de ancho x alto en pixeles del color solicitado.
	 * 		 El origen de coordenadas se encuentra en el extremo superior
	 * 		 izquierdo de la imagen.
	 */
	Imagen(unsigned int ancho, unsigned int alto, Color* colorFondo);


	/*
	 * POST: Crea un nuevo objeto imagen en base a una imagen existente.
	 */
	Imagen(string rutaImagenACargar);


	/*
	 * POST: Devuelve el alto en pixeles de la imagen.
	 */
	unsigned int darAlto();


	/*
	 * POST: Devuelve el ancho en pixeles de la imagen.
	 */
	unsigned int darAncho();


	/*
	 * POST: Reemplaza todos los pixeles de la imagen que tengan
	 *       "colorAnterior" por "nuevoColor"
	 */
	void cambiarColor(Color* colorAnterior, Color* nuevoColor);


	/*
	 * PRE:  La otraImagen a copiar debe ser mayor o igual en tamaño a la imagen
	 * 		 actual, la ubicacion formada por pixelX y pixelY no hace que la
	 * 		 porcion a copiar de otraImagen sea mas pequeña que imagen actual.
	 * POST: copia una porcion de otraImagen del tamaño de la imagen actual
	 *       dentro de esta imagen.
	 */
	void copiar(Imagen* otraImagen, unsigned int pixelX, unsigned int pixelY);


	/*
	 * PRE:  La otraImagen a insertar debe ser menor o igual en tamaño a la imagen
	 * 		 actual, la ubicacion formada por pixelX y pixelY no hace que otraImagen
	 * 		 quede sobresaliendo con resto a la imagen actual.
	 * POST: Inserta otraImagen en la posicion solicitada dentro de la imagen actual.
	 */
	void insertar(Imagen* otraImagen, unsigned int pixelX, unsigned int pixelY);


	/*
	 * POST: Guarda la imagen con nombre 'nombreDeArchivo.bmp" en la carpeta
	 * 		 "salida"
	 */
	void guardar(string nombreDeArchivo);


	/*
	 * POST: libera los recursos solicitados.
	 */
	~Imagen();

private:

	/*
	 * PRE:  la posicion ingresada es valida.
	 * POST: asigna al pixel ubicado en (pixelX, pixelY) el color indicado.
	 */
	void asignar(Color* nuevoColor, unsigned int pixelX, unsigned int pixelY);

};

#endif /* IMAGEN_H_ */
