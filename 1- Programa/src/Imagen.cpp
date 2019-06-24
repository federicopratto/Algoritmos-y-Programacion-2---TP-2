
#include "Imagen.h"


Imagen::Imagen(unsigned int ancho, unsigned int alto){

	if(ancho < 1 || alto < 1){
		throw string("No se puede crear una imagen de 0 pixeles");
	}

	this->imagen = new BMP;
	this->alto = alto;
	this->ancho = ancho;
	this->imagen->SetSize(ancho, alto);
	this->imagen->SetBitDepth(24);
}


Imagen::Imagen(unsigned int ancho, unsigned int alto, Color* colorFondo){

	if(ancho < 1 || alto < 1){
		throw string("No se puede crear una imagen de 0 pixeles");
	}

	this->imagen = new BMP;
	this->alto = alto;
	this->ancho = ancho;
	this->imagen->SetSize(ancho, alto);
	this->imagen->SetBitDepth(24);
	Color* blanco = new Color(255, 255, 255);
	this->cambiarColor(blanco, colorFondo);
	delete blanco;
}


Imagen::Imagen(string rutaImagenACargar){

	this->imagen = new BMP();
	this->imagen->ReadFromFile(rutaImagenACargar.c_str());
	this->alto = this->imagen->TellHeight();
	this->ancho = this->imagen->TellWidth();
}


unsigned int Imagen::darAlto(){

	return this->alto;
}


unsigned int Imagen::darAncho(){

	return this->ancho;
}


void Imagen::cambiarColor(Color* colorAnterior, Color* nuevoColor){


	for(int i = 0; i < (this->imagen->TellWidth()); i++){

		for(int j = 0; j < (this->imagen->TellWidth()); j++){

			if((this->imagen->GetPixel(i, j)) == (colorAnterior->obtenerPixel())){

				this->asignar(nuevoColor, i, j);
			}
		}
	}
}


void Imagen::copiar(Imagen* otraImagen, unsigned int pixelX, unsigned int pixelY){

	if(otraImagen->darAncho() - pixelX < this->ancho || otraImagen->darAlto() - pixelY < this->alto){

		throw string("Se ha intentado copiar una imagen muy pequeña dentro de otra muy grande.");
	}

	for (unsigned int i = pixelX; i < (pixelX + this->ancho); i++) {

		for (unsigned int j = pixelY; j < (pixelY + this->alto); j++) {

			this->imagen->SetPixel(i - pixelX, j - pixelY, otraImagen->imagen->GetPixel(i, j));
		}
	}
}


void Imagen::insertar(Imagen* otraImagen, unsigned int pixelX, unsigned int pixelY){

	if(pixelX + otraImagen->darAncho() > this->ancho || pixelY + otraImagen->darAlto() > this->alto){

		throw string("Se ha intentado insertar una imagen muy grande dentro de otra muy pequeña");
	}

	for (unsigned int i = pixelX; i < (pixelX + otraImagen->darAncho()); i++) {

		for (unsigned int j = pixelY; j < (pixelY + otraImagen->darAlto()); j++) {

			this->imagen->SetPixel(i, j, otraImagen->imagen->GetPixel(i - pixelX, j - pixelY));
		}
	}
}


void Imagen::guardar(string nombreDeArchivo){

	string nombre = ("salida/" + nombreDeArchivo + ".bmp");
	this->imagen->WriteToFile(nombre.c_str());
}


Imagen::~Imagen() {

	delete this->imagen;
}


void Imagen::asignar(Color* nuevoColor, unsigned int pixelX, unsigned int pixelY){

	if(pixelX > this->ancho || pixelY > this->alto){

		throw string("Se ha intentado acceder a un pixel invalido dentro de la imagen.");
	}

	this->imagen->SetPixel(pixelX, pixelY, nuevoColor->obtenerPixel());
}
