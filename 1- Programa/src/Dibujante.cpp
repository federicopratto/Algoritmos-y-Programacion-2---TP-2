
#include "Dibujante.h"

using std::stringstream;


Dibujante::Dibujante(){

	this->tamanioCelda = 56;
	this->imagenDelTablero = NULL;
	this->imagenAInsertar = NULL;
	this->rutaArchivo = NULL;
	this->negro = new Color(0, 0, 0);
}


void Dibujante::cargarJugada(Tablero* tablero, Jugada* ultimaJugada){

	this->crearImagenTablero(tablero, ultimaJugada);

	string ruta = "salida/Jugada " + this->castearAString(ultimaJugada->darNumero());
	ruta += " Fila " + this->castearAString(ultimaJugada->darFila()) + ".bmp";

	this->imagenDelTablero = new Imagen(ruta);
	this->insertarFicha(ultimaJugada, tablero);
	this->guardarImagen(ultimaJugada->darNumero(), ultimaJugada->darFila());

	delete this->imagenDelTablero;
}


void Dibujante::borrarJugada(Tablero* tablero, Jugada* jugadaBorrada){

	this->crearImagenTablero(tablero, jugadaBorrada);

	string ruta = "salida/Jugada " + this->castearAString(jugadaBorrada->darNumero());
	ruta += " Fila " + this->castearAString(jugadaBorrada->darFila()) + ".bmp";

	this->imagenDelTablero = new Imagen(ruta);
	this->borrarFicha(jugadaBorrada, tablero);
	this->guardarImagen(jugadaBorrada->darNumero(), jugadaBorrada->darFila());

	delete this->imagenDelTablero;
}


void Dibujante::cambiarColorFicha(Tablero* tablero, Jugada* posicionFicha){

	this->crearImagenTablero(tablero, posicionFicha);

	string ruta = "salida/Jugada " + this->castearAString(posicionFicha->darNumero());
	ruta += " Fila " + this->castearAString(posicionFicha->darFila()) + ".bmp";

	this->imagenDelTablero = new Imagen(ruta);
	this->insertarFicha(posicionFicha, tablero);
	this->guardarImagen(posicionFicha->darNumero(), posicionFicha->darFila());

	delete this->imagenDelTablero;
}


void Dibujante::intercambiarFichas(Tablero* tablero, Jugada* ficha1, Jugada* ficha2){

	this->crearImagenTablero(tablero, ficha1);

	string ruta = "salida/Jugada " + this->castearAString(ficha1->darNumero());
	ruta += " Fila " + this->castearAString(ficha1->darFila()) + ".bmp";

	this->imagenDelTablero = new Imagen(ruta);
	this->insertarFicha(ficha1, tablero);
	this->guardarImagen(ficha1->darNumero(), ficha1->darFila());

	delete this->imagenDelTablero;

	ruta = "salida/Jugada " + this->castearAString(ficha2->darNumero());
	ruta += " Fila " + this->castearAString(ficha2->darFila()) + ".bmp";

	this->imagenDelTablero = new Imagen(ruta);
	this->insertarFicha(ficha2, tablero);
	this->guardarImagen(ficha2->darNumero(), ficha2->darFila());

	delete this->imagenDelTablero;
}


Dibujante::~Dibujante(){

	delete this->negro;
}


void Dibujante::crearImagenTablero(Tablero* tablero, Jugada* ultimaJugada){

	if(ultimaJugada->darNumero() == 1){

		this->generarNuevoTablero(tablero);
	}

	for(int fila = 1; fila <= tablero->darFilas(); fila++){

		string ruta = "salida/Jugada " + this->castearAString(ultimaJugada->darNumero() - 1);
		ruta += " Fila " + this->castearAString(fila) + ".bmp";

		this->imagenDelTablero = new Imagen(ruta);
		this->guardarImagen(ultimaJugada->darNumero(), fila);

		delete this->imagenDelTablero;
	}
}


void Dibujante::generarNuevoTablero(Tablero* tablero){

	int ancho = this->tamanioCelda * (tablero->darColumnas() + 2);
	int alto = this->tamanioCelda * (tablero->darPisos() + 2);
	this->imagenDelTablero = new Imagen(ancho, alto, this->negro);

	this->insertarEjes();
	this->dibujarRecuadroTablero();

	for(int fila = 1; fila <= tablero->darFilas(); fila++){

		this->guardarImagen(0, fila);
	}

	delete this->imagenDelTablero;
}


void Dibujante::insertarEjes(){

	if(this->imagenDelTablero == NULL){

		throw string("Se ha intentado dibujar los ejes en un tablero que no fue creado.");
	}

	this->imagenAInsertar = new Imagen("load/ejes.bmp");
	int inicioEje = this->imagenDelTablero->darAlto() - this->tamanioCelda * 2;
	this->insertarImagen(0, inicioEje);
	delete this->imagenAInsertar;
}


void Dibujante::dibujarRecuadroTablero(){

	if(this->imagenDelTablero == NULL){

		throw string("Se ha intentado dibujar un recuadro a un tablero que no fue creado.");
	}

	int ancho = this->imagenDelTablero->darAncho() - (this->tamanioCelda * 2);
	int alto = this->imagenDelTablero->darAlto() - (this->tamanioCelda * 2);
	this->imagenAInsertar = new Imagen(ancho, alto);
	this->insertarImagen(this->tamanioCelda, this->tamanioCelda);
	delete this->imagenAInsertar;
}


void Dibujante::insertarFicha(Jugada* ultimaJugada, Tablero* tablero){

	if(this->imagenDelTablero == NULL){

		throw string("Se ha intentado dibujar una ficha en un tablero que no fue creado.");
	}

	this->imagenAInsertar = new Imagen("load/ficha.bmp");
	this->imagenAInsertar->cambiarColor(this->negro, ultimaJugada->darColorFicha());

	int columnaFicha = ultimaJugada->darColumna() * this->tamanioCelda;
	int pisoFicha = (tablero->darPisos() + 1 - ultimaJugada->darPiso()) * this->tamanioCelda;

	this->insertarImagen(columnaFicha, pisoFicha);
	delete this->imagenAInsertar;
}


void Dibujante::borrarFicha(Jugada* jugadaBorrada, Tablero* tablero){

	if(this->imagenDelTablero == NULL){

		throw string("Se ha intentado dibujar una ficha en un tablero que no fue creado.");
	}

	int ancho = this->tamanioCelda;
	int alto = tablero->darPisos() - jugadaBorrada->darPiso();
	alto *= this->tamanioCelda;

	int pixelX = this->tamanioCelda * jugadaBorrada->darColumna();
	int pixelY = this->tamanioCelda;

	// Copio toda la hilera de fichas por encima de la borrada un lugar mas abajo
	if(alto > 0){

		this->imagenAInsertar = new Imagen(ancho, alto);
		this->imagenAInsertar->copiar(this->imagenDelTablero, pixelX, pixelY);
		this->insertarImagen(pixelX, pixelY + this->tamanioCelda);
		delete this->imagenAInsertar;
	}

	// Pongo un espacio vacio arriba de todo.
	this->imagenAInsertar = new Imagen(this->tamanioCelda, this->tamanioCelda);
	this->insertarImagen(pixelX, pixelY);
	delete this->imagenAInsertar;
}


void Dibujante::insertarImagen(int x, int y){

	if(this->imagenDelTablero == NULL || this->imagenAInsertar == NULL){

		throw string("Se ha intentado insertar una imagen en inexistente.");
	}

	this->imagenDelTablero->insertar(this->imagenAInsertar, x, y);
}


void Dibujante::guardarImagen(int jugada, int fila){

	if(this->imagenDelTablero == NULL || this->imagenAInsertar == NULL){

		throw string("Se ha intentado guardar una imagen en inexistente.");
	}

	string nombreArchivo = "Jugada " + this->castearAString(jugada);
	nombreArchivo += " Fila " + this->castearAString(fila);

	this->imagenDelTablero->guardar(nombreArchivo);
}


string Dibujante::castearAString(int entero){

	stringstream casteado;
	casteado << entero;

	return casteado.str();
}
