
#include "Color.h"


Color::Color(ebmpBYTE rojo, ebmpBYTE verde, ebmpBYTE azul){

	this->colores = new RGBApixel;
	this->colores->Red = rojo;
	this->colores->Green = verde;
	this->colores->Blue = azul;
}


void Color::asignarRojo(ebmpBYTE nuevoRojo){

	this->colores->Red = nuevoRojo;
}


void Color::asignarVerde(ebmpBYTE nuevoVerde){

	this->colores->Green = nuevoVerde;
}


void Color::asignarAzul(ebmpBYTE nuevoAzul){

	this->colores->Blue = nuevoAzul;
}


RGBApixel Color::obtenerPixel(){

	return *this->colores;
}


Color::~Color(){

	delete this->colores;
}
