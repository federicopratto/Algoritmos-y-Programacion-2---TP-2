
#include "Tablero.h"

using namespace std;


Tablero::Tablero(Consola* consola){

	consola->pedirTamanioTablero(this->filas, this->columnas, this->pisos);

	this->tablero = new Lista<Lista<Lista<Celda*>*>*>;

	for(int fila = 1; fila <= this->filas; fila++){

		this->tablero->agregar(new Lista<Lista<Celda*>*>);
	}

	this->tablero->iniciarCursor();
	while(this->tablero->avanzarCursor()){

		for (int columna = 1; columna <= this->columnas; columna++){

			this->tablero->obtenerCursor()->agregar(new Lista<Celda*>);
		}
	}
}


int& Tablero::darFilas(){

	return this->filas;
}


int& Tablero::darColumnas(){

	return this->columnas;
}


int& Tablero::darPisos(){

	return this->pisos;
}


void Tablero::guardarFicha(Jugada* jugada){

	if(this->hileraLlena(jugada)){

		throw string("La hilera donde se quizo guardar la ficha estaba llena.");
	}

	this->avanzarFilaHasta(jugada->darFila());
	this->avanzarColumnaHasta(jugada->darColumna());

	Lista<Celda*>* pisos = this->tablero->obtenerCursor()->obtenerCursor();
	jugada->darPiso() = pisos->contarElementos();
	jugada->darPiso()++;
	pisos->agregar(new Celda(jugada));
}


bool Tablero::hileraLlena(Jugada* jugada){

	this->avanzarFilaHasta(jugada->darFila());
	this->avanzarColumnaHasta(jugada->darColumna());

	Lista<Celda*>* pisos = this->tablero->obtenerCursor()->obtenerCursor();
	return ((int)pisos->contarElementos() == this->pisos);
}


bool Tablero::estaLleno(){

	bool lleno = true;

	this->tablero->iniciarCursor();
	while(lleno && this->tablero->avanzarCursor()){

		Lista<Lista<Celda*>*>* columnas = this->tablero->obtenerCursor();
		columnas->iniciarCursor();
		while(lleno && columnas->avanzarCursor()){

			Lista<Celda*>* pisos = columnas->obtenerCursor();
			int fichasColocadas = pisos->contarElementos();
			lleno = (fichasColocadas == this->pisos);
		}
	}

	return lleno;
}


void Tablero::mostrarEstado(Consola* consola, int cantDeJugadores){

	int ficha = 0, fila = 0;
	int espaciosMax = this->contarDigitos(max(this->pisos, cantDeJugadores));

	this->tablero->iniciarCursor();
	while(this->tablero->avanzarCursor()){

		int columna = 0;
		Lista<Lista<Celda*>*>* columnas = this->tablero->obtenerCursor();
		columnas->iniciarCursor();

		fila++;
		consola->mostrarEncabezado(fila, this->pisos, espaciosMax);

		while(columnas->avanzarCursor()){

			Lista<Celda*>* pisos = columnas->obtenerCursor();
			int fichasColocadas = pisos->contarElementos();
			pisos->iniciarCursor();

			columna++;
			consola->mostrarNumeroDeColumna(columna);

			for(int piso = 1; piso <= this->pisos; piso++){

				if(piso <= fichasColocadas){

					pisos->avanzarCursor();
					ficha = pisos->obtenerCursor()->verContenido()->darFicha()->darNumero();

				} else {

					ficha = 0;
				}

				consola->mostrarFicha(ficha, espaciosMax);
			}
			cout << endl;
		}
		consola->mostrarPieDePagina(this->pisos, espaciosMax);
	}
}


void Tablero::copiarHilera(int nroDeHilera, Lista<Celda*>* hilera, Jugada* ultimaJugada){

	this->vaciarHilera(hilera);

	switch(nroDeHilera){

	case 1:
		this->copiarHilera1(hilera, ultimaJugada);
		break;
	case 2:
		this->copiarHilera2(hilera, ultimaJugada);
		break;
	case 3:
		this->copiarHilera3(hilera, ultimaJugada);
		break;
	case 4:
		this->copiarHilera4(hilera, ultimaJugada);
		break;
	case 5:
		this->copiarHilera5(hilera, ultimaJugada);
		break;
	case 6:
		this->copiarHilera6(hilera, ultimaJugada);
		break;
	case 7:
		this->copiarHilera7(hilera, ultimaJugada);
		break;
	case 8:
		this->copiarHilera8(hilera, ultimaJugada);
		break;
	case 9:
		this->copiarHilera9(hilera, ultimaJugada);
		break;
	case 10:
		this->copiarHilera10(hilera, ultimaJugada);
		break;
	case 11:
		this->copiarHilera11(hilera, ultimaJugada);
		break;
	case 12:
		this->copiarHilera12(hilera, ultimaJugada);
		break;
	case 13:
		this->copiarHilera13(hilera, ultimaJugada);
		break;
	}

}


void Tablero::cambiarColorFicha(Jugada* posicion){

	int hayFichas = 0;

	this->posicionAlAzar(posicion->darFila(), posicion->darColumna(), hayFichas);
	posicion->darPiso() = (1 + rand() % hayFichas);

	Celda* celda = this->tablero->obtenerCursor()->obtenerCursor()->obtener(posicion->darPiso());
	celda->cambiarJugada(posicion->darJugador());
}


void Tablero::eliminarFichaAlAzar(Jugada* posicion){

	int hayFichas = 0;

	this->posicionAlAzar(posicion->darFila(), posicion->darColumna(), hayFichas);
	posicion->darPiso() = (1 + rand() % hayFichas);

	delete this->tablero->obtenerCursor()->obtenerCursor()->obtener(posicion->darPiso());
	this->tablero->obtenerCursor()->obtenerCursor()->remover(posicion->darPiso());

	if(this->avanzarPisoHasta(posicion->darPiso())){

		Celda* celda = this->tablero->obtenerCursor()->obtenerCursor()->obtener(posicion->darPiso());
		posicion->cambiarJugador(celda->verContenido()->darJugador());
	}
}


void Tablero::eliminarJugadaAnterior(Jugada* jugadaAnterior){

	this->avanzarFilaHasta(jugadaAnterior->darFila());
	this->avanzarColumnaHasta(jugadaAnterior->darColumna());
	this->avanzarPisoHasta(jugadaAnterior->darPiso());

	delete this->tablero->obtenerCursor()->obtenerCursor()->obtenerCursor();
	this->tablero->obtenerCursor()->obtenerCursor()->remover(jugadaAnterior->darPiso());

	if(this->avanzarPisoHasta(jugadaAnterior->darPiso())){

		Celda* celda = this->tablero->obtenerCursor()->obtenerCursor()->obtener(jugadaAnterior->darPiso());
		jugadaAnterior->cambiarJugador(celda->verContenido()->darJugador());

	} else {

		jugadaAnterior->cambiarJugador(NULL);
	}
}


bool Tablero::hayVecinas(){

	bool hayVecinas = false;
	Lista<Celda*>* hilera = new Lista<Celda*>;
	Lista<int>* direcciones = new Lista<int>;

	// Direcciones en el espacio en las cuales puede haber una vecina.
	direcciones->agregar(1);
	direcciones->agregar(2);
	direcciones->agregar(5);
	direcciones->agregar(8);
	direcciones->agregar(9);

	int fila = 1, columna = 1;

	while(!hayVecinas && fila <= this->filas){
		while(!hayVecinas && columna <= this->columnas){

			Jugada* posicion = new Jugada(fila, columna, 1, NULL, 0);

			direcciones->iniciarCursor();
			while(!hayVecinas && direcciones->avanzarCursor()){

				this->copiarHilera(direcciones->obtenerCursor(), hilera, posicion);
				hayVecinas = (hilera->contarElementos() > 1);
			}
			delete posicion;
			columna++;
		}
		fila++;
	}
	this->vaciarHilera(hilera);
	delete hilera;
	delete direcciones;

	return hayVecinas;
}


bool Tablero::sePuedenCambiarLasFichas(Jugada* ficha1, Jugada* ficha2, Consola* consola){

	bool sonVecinas = false;

	bool hayFicha = !this->posicionVacia(ficha1);

	if(!hayFicha){
		consola->mostrarEfectoJugada(ficha1, "No hay ninguna ficha en la posicion -> ");
	} else {
		hayFicha = this->posicionVacia(ficha2);
		if(!hayFicha){
			consola->mostrarEfectoJugada(ficha2, "No hay ninguna ficha en la posicion -> ");
		}
	}

	// Veo si dichas fichas son vecinas.
	if(hayFicha){
		sonVecinas = this->verSiSonVecinas(ficha1, ficha2);
		if(!sonVecinas){
			consola->mostrarEfectoJugada("Las fichas elegidas no son vecinas");
		}
	}

	return sonVecinas;
}


void Tablero::intercambiarFichas(Jugada* ficha1, Jugada* ficha2){

	this->avanzarFilaHasta(ficha1->darFila());
	this->avanzarColumnaHasta(ficha1->darColumna());
	this->avanzarPisoHasta(ficha1->darPiso());

	Celda* celda1 = this->tablero->obtenerCursor()->obtenerCursor()->obtenerCursor();
	ficha1->cambiarJugador(celda1->verContenido()->darJugador());

	this->avanzarFilaHasta(ficha2->darFila());
	this->avanzarColumnaHasta(ficha2->darColumna());
	this->avanzarPisoHasta(ficha2->darPiso());

	Celda* celda2 = this->tablero->obtenerCursor()->obtenerCursor()->obtenerCursor();
	ficha2->cambiarJugador(celda2->verContenido()->darJugador());

	celda1->cambiarJugada(ficha2->darJugador());
	celda2->cambiarJugada(ficha1->darJugador());

	ficha1->cambiarJugador(celda1->verContenido()->darJugador());
	ficha2->cambiarJugador(celda2->verContenido()->darJugador());
}


void Tablero::abrirPortal(Jugada* ladoA, Jugada* ladoB, int tipoDePortal){

	this->avanzarFilaHasta(ladoA->darFila());
	this->avanzarColumnaHasta(ladoA->darColumna());
	this->avanzarPisoHasta(ladoA->darPiso());

	Celda* celdaA = this->tablero->obtenerCursor()->obtenerCursor()->obtenerCursor();

	this->avanzarFilaHasta(ladoB->darFila());
	this->avanzarColumnaHasta(ladoB->darColumna());
	this->avanzarPisoHasta(ladoB->darPiso());

	Celda* celdaB = this->tablero->obtenerCursor()->obtenerCursor()->obtenerCursor();

	celdaA->abrirPortal(celdaB, tipoDePortal);
	celdaB->abrirPortal(celdaA, tipoDePortal);
}


bool Tablero::buscarCeldaSinPortal1(Jugada* ladoA, Jugada* ladoB){

	bool parar = false;

	this->tablero->iniciarCursor();
	while(!parar && this->tablero->avanzarCursor()){

		Lista<Lista<Celda*>*>* columnas = this->tablero->obtenerCursor();
		columnas->iniciarCursor();
		while(!parar && ladoA->darColumna() < this->columnas && columnas->avanzarCursor()){

			if(this->avanzarPisoHasta(ladoA->darPiso())){
				Celda* celda = this->tablero->obtenerCursor()->obtenerCursor()->obtenerCursor();
				parar = !celda->portalEstaAbierto();
			}

			if(!parar){
				ladoA->darColumna()++;
			}
		}

		if(!parar){
			ladoA->darColumna() = 1;
			ladoA->darFila()++;
		}
	}

	bool celdaEncontrada = false;

	if(parar){
		ladoB->darFila() = ladoA->darFila();
		ladoB->darColumna() = ladoA->darColumna() + 1;
		ladoB->darPiso() = ladoA->darPiso();
		if(!this->posicionVacia(ladoB)){

			Celda* celda = this->tablero->obtenerCursor()->obtenerCursor()->obtenerCursor();
			celdaEncontrada = !celda->portalEstaAbierto();
		}
	}

	return celdaEncontrada;
}


bool Tablero::buscarCeldaSinPortal2(Jugada* ladoA, Jugada* ladoB){

	bool parar = false;

	this->tablero->iniciarCursor();
	while(!parar && this->tablero->avanzarCursor()){

		this->avanzarColumnaHasta(ladoA->darColumna());
		Lista<Celda*>* pisos = this->tablero->obtenerCursor()->obtenerCursor();
		pisos->iniciarCursor();

		while (!parar && (ladoA->darPiso() < (this->pisos - 1)) && pisos->avanzarCursor()) {

			if(ladoA->darPiso() >= 2){
				Celda* celda = pisos->obtenerCursor();
				parar = !celda->portalEstaAbierto();
			}

			if (!parar) {
				ladoA->darPiso()++;
			}
		}

		if(!parar){
			ladoA->darPiso() = 1;
			ladoA->darFila()++;
		}
	}

	bool celdaEncontrada = false;

	if(parar){
		ladoB->darFila() = ladoA->darFila();
		ladoB->darColumna() = ladoA->darColumna();
		ladoB->darPiso() = ladoA->darPiso() + 1;
		if(!this->posicionVacia(ladoB)){

			Celda* celda = this->tablero->obtenerCursor()->obtenerCursor()->obtenerCursor();
			celdaEncontrada = !celda->portalEstaAbierto();
		}
	}

	return celdaEncontrada;
}


bool Tablero::buscarCeldaSinPortal3(Jugada* ladoA, Jugada* ladoB){

	bool parar = false;

	this->avanzarFilaHasta(ladoA->darFila());
	Lista<Lista<Celda*>*>* columnas = this->tablero->obtenerCursor();
	columnas->iniciarCursor();
	columnas->avanzarCursor();

	while(!parar && (ladoA->darColumna() < this->columnas) && columnas->avanzarCursor()){

		Lista<Celda*>* pisos = columnas->obtenerCursor();
		pisos->iniciarCursor();

		while(!parar && (ladoA->darPiso() < (this->pisos - 1)) && pisos->avanzarCursor()){

			if(ladoA->darPiso() >= 2){
				Celda* celda = pisos->obtenerCursor();
				parar = !celda->portalEstaAbierto();
			}
			if(!parar){
				ladoA->darPiso()++;
			}
		}

		if(!parar){
			ladoA->darPiso() = 1;
			ladoA->darColumna()++;
		}
	}

	bool celdaEncontrada = false;

	if(parar){
		ladoB->darFila() = ladoA->darFila();
		ladoB->darColumna() = ladoA->darColumna();
		ladoB->darPiso() = ladoA->darPiso() + 1;
		if(!this->posicionVacia(ladoB)){

			Celda* celda = this->tablero->obtenerCursor()->obtenerCursor()->obtenerCursor();
			celdaEncontrada = !celda->portalEstaAbierto();
		}
	}

	return celdaEncontrada;
}


Tablero::~Tablero(){

	this->tablero->iniciarCursor();
	while(this->tablero->avanzarCursor()){

		this->tablero->obtenerCursor()->iniciarCursor();
		while(this->tablero->obtenerCursor()->avanzarCursor()){

			this->tablero->obtenerCursor()->obtenerCursor()->iniciarCursor();
			while(this->tablero->obtenerCursor()->obtenerCursor()->avanzarCursor()){

				delete this->tablero->obtenerCursor()->obtenerCursor()->obtenerCursor();
			}
			delete this->tablero->obtenerCursor()->obtenerCursor();
		}
		delete this->tablero->obtenerCursor();
	}
	delete this->tablero;
}


bool Tablero::posicionVacia(Jugada* posicion){

	this->avanzarFilaHasta(posicion->darFila());
	this->avanzarColumnaHasta(posicion->darColumna());
	return (!this->avanzarPisoHasta(posicion->darPiso()));

}


bool Tablero::verSiSonVecinas(Jugada* ficha1, Jugada* ficha2){

	bool sonVecinas = true;
	int mismaFicha = 0;
	int i = 0, posicion1, posicion2;

	while(sonVecinas && i < 3){

		if(i == 0){
			posicion1 = ficha1->darFila();
			posicion2 = ficha2->darFila();
		} else if(i == 1){
			posicion1 = ficha1->darColumna();
			posicion2 = ficha2->darColumna();
		} else {
			posicion1 = ficha1->darPiso();
			posicion2 = ficha2->darPiso();
		}

		if(posicion1 == posicion2){

			mismaFicha++;
		}
		sonVecinas = ((std::abs(posicion1 - posicion2)) < 2);
		i++;
	}

	if(mismaFicha == 3){

		sonVecinas = false;
	}

	return sonVecinas;
}


void Tablero::copiarHilera1(Lista<Celda*>* hilera, Jugada* ultimaJugada){

	this->avanzarFilaHasta(ultimaJugada->darFila());
	this->avanzarColumnaHasta(ultimaJugada->darColumna());

	Lista<Celda*>* pisos = this->tablero->obtenerCursor()->obtenerCursor();
	hilera->agregar(*pisos);
}


void Tablero::copiarHilera2(Lista<Celda*>* hilera, Jugada* ultimaJugada){

	int cotaInf = 3, cotaSup = 3;
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darFila(), this->filas);

	int filaMax = ultimaJugada->darFila() + cotaSup;
	int filaDestino = ultimaJugada->darFila() - cotaInf;

	bool parar = false;

	this->avanzarFilaHasta(filaDestino);
	while(!parar && filaDestino <= filaMax){

		this->avanzarColumnaHasta(ultimaJugada->darColumna());

		if(avanzarPisoHasta(ultimaJugada->darPiso())){
			Lista<Celda*>* pisos = this->tablero->obtenerCursor()->obtenerCursor();
			hilera->agregar(pisos->obtenerCursor());
		} else if(filaDestino < ultimaJugada->darFila()){
			this->vaciarHilera(hilera);
		} else {
			parar = true;
		}

		this->tablero->avanzarCursor();
		filaDestino++;
	}
}


void Tablero::copiarHilera3(Lista<Celda*>* hilera, Jugada* ultimaJugada){

	int cotaInf = 3, cotaSup = 3;
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darFila(), this->filas);
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darPiso(), this->pisos);

	int filaMax = ultimaJugada->darFila() + cotaSup;
	int filaDestino = ultimaJugada->darFila() - cotaInf;
	int columnaDestino = ultimaJugada->darColumna();
	int pisoDestino = ultimaJugada->darPiso() - cotaInf;

	bool parar = false;

	this->avanzarFilaHasta(filaDestino);
	while(!parar && filaDestino <= filaMax){

		this->avanzarColumnaHasta(columnaDestino);

		if(avanzarPisoHasta(pisoDestino)){
			Lista<Celda*>* pisos = this->tablero->obtenerCursor()->obtenerCursor();
			hilera->agregar(pisos->obtenerCursor());
		} else if(filaDestino < ultimaJugada->darFila()){
			this->vaciarHilera(hilera);
		} else {
			parar = true;
		}

		this->tablero->avanzarCursor();
		filaDestino++;
		pisoDestino++;
	}
}


void Tablero::copiarHilera4(Lista<Celda*>* hilera, Jugada* ultimaJugada){

	int cotaInf = 3, cotaSup = 3;
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darFila(), this->filas);
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darPiso(), this->pisos);

	int filaMax = ultimaJugada->darFila() + cotaSup;
	int filaDestino = ultimaJugada->darFila() - cotaInf;
	int columnaDestino = ultimaJugada->darColumna();
	int pisoDestino = ultimaJugada->darPiso() + cotaSup;

	bool parar = false;

	this->avanzarFilaHasta(filaDestino);
	while(!parar && filaDestino <= filaMax){

		this->avanzarColumnaHasta(columnaDestino);

		if(avanzarPisoHasta(pisoDestino)){
			Lista<Celda*>* pisos = this->tablero->obtenerCursor()->obtenerCursor();
			hilera->agregar(pisos->obtenerCursor());
		} else if(filaDestino < ultimaJugada->darFila()){
			this->vaciarHilera(hilera);
		} else {
			parar = true;
		}

		this->tablero->avanzarCursor();
		filaDestino++;
		pisoDestino--;
	}
}


void Tablero::copiarHilera5(Lista<Celda*>* hilera, Jugada* ultimaJugada){

	int cotaInf = 3, cotaSup = 3;
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darColumna(), this->columnas);

	int columnaMax = ultimaJugada->darColumna() + cotaSup;
	int filaDestino = ultimaJugada->darFila();
	int columnaDestino = ultimaJugada->darColumna() - cotaInf;
	int pisoDestino = ultimaJugada->darPiso();

	bool parar = false;

	this->avanzarFilaHasta(filaDestino);
	this->avanzarColumnaHasta(columnaDestino);
	while(!parar && columnaDestino <= columnaMax){

		if(avanzarPisoHasta(pisoDestino)){
			Lista<Celda*>* pisos = this->tablero->obtenerCursor()->obtenerCursor();
			hilera->agregar(pisos->obtenerCursor());
		} else if(columnaDestino < ultimaJugada->darColumna()){
			this->vaciarHilera(hilera);
		} else {
			parar = true;
		}

		this->tablero->obtenerCursor()->avanzarCursor();
		columnaDestino++;
	}
}


void Tablero::copiarHilera6(Lista<Celda*>* hilera, Jugada* ultimaJugada){

	int cotaInf = 3, cotaSup = 3;
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darColumna(), this->columnas);
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darPiso(), this->pisos);

	int columnaMax = ultimaJugada->darColumna() + cotaSup;
	int filaDestino = ultimaJugada->darFila();
	int columnaDestino = ultimaJugada->darColumna() - cotaInf;
	int pisoDestino = ultimaJugada->darPiso() - cotaInf;

	bool parar = false;

	this->avanzarFilaHasta(filaDestino);
	this->avanzarColumnaHasta(columnaDestino);
	while(!parar && columnaDestino <= columnaMax){

		if(avanzarPisoHasta(pisoDestino)){
			Lista<Celda*>* pisos = this->tablero->obtenerCursor()->obtenerCursor();
			hilera->agregar(pisos->obtenerCursor());
		} else if(columnaDestino < ultimaJugada->darColumna()){
			this->vaciarHilera(hilera);
		} else {
			parar = true;
		}

		this->tablero->obtenerCursor()->avanzarCursor();
		columnaDestino++;
		pisoDestino++;
	}
}


void Tablero::copiarHilera7(Lista<Celda*>* hilera, Jugada* ultimaJugada){

	int cotaInf = 3, cotaSup = 3;
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darColumna(), this->columnas);
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darPiso(), this->pisos);

	int columnaMax = ultimaJugada->darColumna() + cotaSup;
	int filaDestino = ultimaJugada->darFila();
	int columnaDestino = ultimaJugada->darColumna() - cotaInf;
	int pisoDestino = ultimaJugada->darPiso() + cotaSup;

	bool parar = false;

	this->avanzarFilaHasta(filaDestino);
	this->avanzarColumnaHasta(columnaDestino);
	while(!parar && columnaDestino <= columnaMax){

		if(avanzarPisoHasta(pisoDestino)){
			Lista<Celda*>* pisos = this->tablero->obtenerCursor()->obtenerCursor();
			hilera->agregar(pisos->obtenerCursor());
		} else if(columnaDestino < ultimaJugada->darColumna()){
			this->vaciarHilera(hilera);
		} else {
			parar = true;
		}

		this->tablero->obtenerCursor()->avanzarCursor();
		columnaDestino++;
		pisoDestino--;
	}
}


void Tablero::copiarHilera8(Lista<Celda*>* hilera, Jugada* ultimaJugada){

	int cotaInf = 3, cotaSup = 3;
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darFila(), this->filas);
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darColumna(), this->columnas);

	int filaMax = ultimaJugada->darFila() + cotaSup;
	int filaDestino = ultimaJugada->darFila() - cotaInf;
	int columnaDestino = ultimaJugada->darColumna() - cotaInf;
	int pisoDestino = ultimaJugada->darPiso();

	bool parar = false;

	this->avanzarFilaHasta(filaDestino);
	while(!parar && filaDestino <= filaMax){

		this->avanzarColumnaHasta(columnaDestino);

		if(avanzarPisoHasta(pisoDestino)){
			Lista<Celda*>* pisos = this->tablero->obtenerCursor()->obtenerCursor();
			hilera->agregar(pisos->obtenerCursor());
		} else if(filaDestino < ultimaJugada->darFila()){
			this->vaciarHilera(hilera);
		} else {
			parar = true;
		}

		this->tablero->avanzarCursor();
		filaDestino++;
		columnaDestino++;
	}
}


void Tablero::copiarHilera9(Lista<Celda*>* hilera, Jugada* ultimaJugada){

	int cotaInf = 3, cotaSup = 3;
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darFila(), this->filas);
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darColumna(), this->columnas);

	int filaMax = ultimaJugada->darFila() + cotaSup;
	int filaDestino = ultimaJugada->darFila() - cotaInf;
	int columnaDestino = ultimaJugada->darColumna() + cotaSup;
	int pisoDestino = ultimaJugada->darPiso();

	bool parar = false;

	this->avanzarFilaHasta(filaDestino);
	while(!parar && filaDestino <= filaMax){

		this->avanzarColumnaHasta(columnaDestino);

		if(avanzarPisoHasta(pisoDestino)){
			Lista<Celda*>* pisos = this->tablero->obtenerCursor()->obtenerCursor();
			hilera->agregar(pisos->obtenerCursor());
		} else if(filaDestino < ultimaJugada->darFila()){
			this->vaciarHilera(hilera);
		} else {
			parar = true;
		}

		this->tablero->avanzarCursor();
		filaDestino++;
		columnaDestino--;
	}
}


void Tablero::copiarHilera10(Lista<Celda*>* hilera, Jugada* ultimaJugada){

	int cotaInf = 3, cotaSup = 3;
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darFila(), this->filas);
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darColumna(), this->columnas);
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darPiso(), this->pisos);

	int filaMax = ultimaJugada->darFila() + cotaSup;
	int filaDestino = ultimaJugada->darFila() - cotaInf;
	int columnaDestino = ultimaJugada->darColumna() - cotaInf;
	int pisoDestino = ultimaJugada->darPiso() - cotaInf;

	bool parar = false;

	this->avanzarFilaHasta(filaDestino);
	while(!parar && filaDestino <= filaMax){

		this->avanzarColumnaHasta(columnaDestino);

		if(avanzarPisoHasta(pisoDestino)){
			Lista<Celda*>* pisos = this->tablero->obtenerCursor()->obtenerCursor();
			hilera->agregar(pisos->obtenerCursor());
		} else if(filaDestino < ultimaJugada->darFila()){
			this->vaciarHilera(hilera);
		} else {
			parar = true;
		}

		this->tablero->avanzarCursor();
		filaDestino++;
		columnaDestino++;
		pisoDestino++;
	}
}


void Tablero::copiarHilera11(Lista<Celda*>* hilera, Jugada* ultimaJugada){

	int cotaInf = 3, cotaSup = 3;
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darFila(), this->filas);
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darColumna(), this->columnas);
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darPiso(), this->pisos);

	int filaMax = ultimaJugada->darFila() + cotaSup;
	int filaDestino = ultimaJugada->darFila() - cotaInf;
	int columnaDestino = ultimaJugada->darColumna() - cotaInf;
	int pisoDestino = ultimaJugada->darPiso() + cotaSup;

	bool parar = false;

	this->avanzarFilaHasta(filaDestino);
	while(!parar && filaDestino <= filaMax){

		this->avanzarColumnaHasta(columnaDestino);

		if(avanzarPisoHasta(pisoDestino)){
			Lista<Celda*>* pisos = this->tablero->obtenerCursor()->obtenerCursor();
			hilera->agregar(pisos->obtenerCursor());
		} else if(filaDestino < ultimaJugada->darFila()){
			this->vaciarHilera(hilera);
		} else {
			parar = true;
		}

		this->tablero->avanzarCursor();
		filaDestino++;
		columnaDestino++;
		pisoDestino--;
	}
}


void Tablero::copiarHilera12(Lista<Celda*>* hilera, Jugada* ultimaJugada){

	int cotaInf = 3, cotaSup = 3;
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darFila(), this->filas);
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darColumna(), this->columnas);
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darPiso(), this->pisos);

	int filaMax = ultimaJugada->darFila() + cotaSup;
	int filaDestino = ultimaJugada->darFila() - cotaInf;
	int columnaDestino = ultimaJugada->darColumna() + cotaSup;
	int pisoDestino = ultimaJugada->darPiso() + cotaSup;

	bool parar = false;

	this->avanzarFilaHasta(filaDestino);
	while(!parar && filaDestino <= filaMax){

		this->avanzarColumnaHasta(columnaDestino);

		if(avanzarPisoHasta(pisoDestino)){
			Lista<Celda*>* pisos = this->tablero->obtenerCursor()->obtenerCursor();
			hilera->agregar(pisos->obtenerCursor());
		} else if(filaDestino < ultimaJugada->darFila()){
			this->vaciarHilera(hilera);
		} else {
			parar = true;
		}

		this->tablero->avanzarCursor();
		filaDestino++;
		columnaDestino--;
		pisoDestino--;
	}
}


void Tablero::copiarHilera13(Lista<Celda*>* hilera, Jugada* ultimaJugada){

	int cotaInf = 3, cotaSup = 3;
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darFila(), this->filas);
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darColumna(), this->columnas);
	this->determinarCotas(cotaInf, cotaSup, ultimaJugada->darPiso(), this->pisos);

	int filaMax = ultimaJugada->darFila() + cotaSup;
	int filaDestino = ultimaJugada->darFila() - cotaInf;
	int columnaDestino = ultimaJugada->darColumna() + cotaSup;
	int pisoDestino = ultimaJugada->darPiso() - cotaInf;

	bool parar = false;

	this->avanzarFilaHasta(filaDestino);
	while(!parar && filaDestino <= filaMax){

		this->avanzarColumnaHasta(columnaDestino);

		if(avanzarPisoHasta(pisoDestino)){
			Lista<Celda*>* pisos = this->tablero->obtenerCursor()->obtenerCursor();
			hilera->agregar(pisos->obtenerCursor());
		} else if(filaDestino < ultimaJugada->darFila()){
			this->vaciarHilera(hilera);
		} else {
			parar = true;
		}

		this->tablero->avanzarCursor();
		filaDestino++;
		columnaDestino--;
		pisoDestino++;
	}
}


void Tablero::vaciarHilera(Lista<Celda*>* hilera){

	int elementos = hilera->contarElementos();

	while(elementos > 0){
		hilera->remover(1);
		elementos--;
	}
}


void Tablero::avanzarFilaHasta(int posicionFinal){

	if(posicionFinal > this->filas){

		throw string("Se ha intentado ir a una posicion inexistente del Tablero.");
	}

	this->tablero->iniciarCursor();
	for(int fila = 1; fila <= posicionFinal; fila++){
		this->tablero->avanzarCursor();
	}
}


void Tablero::avanzarColumnaHasta(int posicionFinal){

	if(posicionFinal > this->columnas){

		throw string("Se ha intentado ir a una posicion inexistente del Tablero.");
	}

	this->tablero->obtenerCursor()->iniciarCursor();
	for(int columna = 1; columna <= posicionFinal; columna++){
		this->tablero->obtenerCursor()->avanzarCursor();
	}
}


bool Tablero::avanzarPisoHasta(int posicionFinal){

	Lista<Celda*>* pisos = this->tablero->obtenerCursor()->obtenerCursor();
	pisos->iniciarCursor();
	int piso = 0;

	while(piso < posicionFinal && pisos->avanzarCursor()){
		piso++;
	}

	return (piso == posicionFinal);
}


void Tablero::determinarCotas(int& cotaInf, int& cotaSup, int numero, int maximo){

	if(cotaInf > numero - 1){
		cotaInf = numero -1;
	}

	if(cotaSup > maximo - numero){
		cotaSup = maximo - numero;
	}
}


void Tablero::posicionAlAzar(int& fila, int& columna, int& hayFichas){

	do{
		fila = (1 + rand() % this->filas);
		columna = (1 + rand() % this->columnas);

		this->avanzarFilaHasta(fila);
		this->avanzarColumnaHasta(columna);

		hayFichas = this->tablero->obtenerCursor()->obtenerCursor()->contarElementos();

	}while(hayFichas == 0);
}


int Tablero::contarDigitos(unsigned int numero){

	int digitos = 0;
	int resto = numero;

	while(resto > 0){

		resto /= 10;
		digitos++;
	}

	return digitos;
}
