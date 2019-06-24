
#include "Consola.h"

using namespace std;


Consola::Consola() {

	cout << "|------ Bievenido al 4 en linea ------|"  << endl
		 << endl;
}


void Consola::pedirDificultad(int& dificultad) {

	do {
		cout << endl
			 <<	"Elija la dificultad." << endl
			 << "--------------------" << endl
			 << endl
			 << "1) Facil." << endl
			 << "2) Medio." << endl
			 << "3) Dificil." << endl
			 << endl
			 << "Opcion elegida: ";
		cin >> dificultad;
		cout << endl;

		if (dificultad < 1 || dificultad > 3) {
			cout << endl
			     << "---------------------------------------" << endl
				 <<	"- ¡Opcion invalida! intente de nuevo. -" << endl
				 << "---------------------------------------" << endl
				 << endl;
		}
	} while (dificultad < 1 || dificultad > 3);
}


void Consola::pedirTamanioTablero(int& filas, int& columnas, int& pisos){

	cout << endl
		 <<	"Ingrese el tamaño del tablero deseado." << endl
		 << "--------------------------------------" << endl
		 << endl;

	do{
		this->pedirTamanio("Filas", filas);
		this->pedirTamanio("Columnas", columnas);
		this->pedirTamanio("Pisos", pisos);

		if((filas*columnas*pisos) < 4){
			cout << endl
				 << "-----------------------------------------------------------" << endl
				 << "- El tamaño total del tablero debe ser mayor o igual a 4. -" << endl
				 << "-----------------------------------------------------------" << endl
				 << endl;
		}
	}while ((filas*columnas*pisos) < 4);
	cout << endl;
}


int Consola::pedirCantidadDeJugadores(){

		int jugadores = 0;

		do{
			cout << endl
				 << "Indique la cantidad de jugadores." << endl
				 << "---------------------------------" << endl
				 << endl
				 << "Jugadores: ";
			cin >> jugadores;
			cout << endl;
			if(jugadores < 2){
				cout << endl
					 << "--------------------------------------------------------" << endl
					 << "- ¡Numero invalido! Debe haber al menos dos jugadores. -" << endl
					 << "--------------------------------------------------------" << endl
					 << endl;
			}
		}while(jugadores < 2);

		return jugadores;
}


string Consola::pedirNombreJugador(int nro){

	string nombre;

	cout << "Ingrese el nombre del jugador N° " << nro <<": ";
	cin >> nombre;

	return nombre;
}


void Consola::indicarTurnoActual(Jugador* jugadorActual){

	cout << endl
		 << "---------------------------------------------" << endl
		 << endl
		 << "Es el turno del jugador N° " << jugadorActual->darNumero()
		 << " - " << jugadorActual->darNombre() << endl
		 << "Fichas restantes: " << jugadorActual->contarFichas() << endl
		 << endl;
}


void Consola::pedirPosicionFicha(Jugada* jugadaActual, Tablero* tablero){

	if(tablero->estaLleno()){

		throw string("Se intento pedir una ficha para un tablero lleno.");
	}

	bool hileraLlena = true;

	do{

		this->pedirPosicion("fila", jugadaActual->darFila(), tablero->darFilas());
		this->pedirPosicion("columna", jugadaActual->darColumna(), tablero->darColumnas());
		hileraLlena = tablero->hileraLlena(jugadaActual);

		if(hileraLlena){

			cout << "La posición elegida esta llena, selecciona otra." << endl;
		}

	}while(hileraLlena);

	tablero->guardarFicha(jugadaActual);
	string efecto = "Tu ficha se guardo en -> (Fila, Columna, Piso) = ";
	this->mostrarEfectoJugada(jugadaActual, efecto);
}


void Consola::mostrarEfectoJugada(Jugada* jugada, string efecto){

	cout << efecto << "(" << jugada->darFila() << ", "
				   << jugada->darColumna() << ", "
				   << jugada->darPiso() << ")" << endl
				   << endl;
}


void Consola::mostrarEfectoJugada(string efecto){

	cout << efecto << endl << endl;
}


void Consola::mostrarEncabezado(int fila, int pisos, int espaciosMax) {

	cout << "Fila: " << fila << endl;
	cout << "| PISO/COLUMNA | ";

	for (int piso = 1; piso <= pisos; piso++) {

		int digitosPiso = contarDigitos(piso);
		for (int i = 0; i < espaciosMax - digitosPiso; i++) {

			cout << " ";
		}
		cout << piso << " | ";
	}
	cout << endl;

	this->mostrarSeparador(espaciosMax, pisos);
}


void Consola::mostrarNumeroDeColumna(int columna){

	cout << "| ";
	int digitosColumna = this->contarDigitos(columna);
	for(int i = 0; i < 12 - digitosColumna; i++){

		cout << " ";
	}
	cout << columna << " | ";
}


void Consola::mostrarFicha(int ficha, int espaciosMax){

	int digitosFicha = this->contarDigitos(ficha);
	for (int i = 0; i < espaciosMax - digitosFicha; i++) {
		cout << " ";
	}
	if(ficha != 0){
		cout << ficha;
	}
	cout << " | ";
}


void Consola::mostrarPieDePagina(int pisos, int espaciosMax){

	this->mostrarSeparador(espaciosMax, pisos);
	cout << endl;
}


int Consola::quiereUsarCarta(Jugador* jugadorActual){

	int eleccion = 0;
	Lista<Carta*>* cartas = jugadorActual->mostrarCartas();

	do{
		this->mostrarCartasDisponibles(cartas);
		cout << "Opcion elegida: ";
		cin >> eleccion;
		cout << endl;

		if(eleccion < 0 || eleccion > (int)cartas->contarElementos()){
			eleccion = -1;
			cout << "Valor incorrecto, intente de nuevo." << endl
				 << endl;
		}
	}while(eleccion == -1);

	return eleccion;

}


void Consola::pedirFichasACambiar(Tablero* tablero, Jugada* ficha1, Jugada* ficha2){

	do{
		cout << "Ficha 1" << endl
			 << "-------" << endl << endl;
		this->pedirPosicion("fila", ficha1->darFila(), tablero->darFilas());
		this->pedirPosicion("columna", ficha1->darColumna(), tablero->darColumnas());
		this->pedirPosicion("piso", ficha1->darPiso(), tablero->darPisos());

		cout << "Ficha 2" << endl
			 << "-------" << endl << endl;
		this->pedirPosicion("fila", ficha2->darFila(), tablero->darFilas());
		this->pedirPosicion("columna", ficha2->darColumna(), tablero->darColumnas());
		this->pedirPosicion("piso", ficha2->darPiso(), tablero->darPisos());

	} while(!tablero->sePuedenCambiarLasFichas(ficha1, ficha2, this));

	tablero->intercambiarFichas(ficha1, ficha2);
	cout << "Se han intercambiado de posicion las fichas seleccionadas" << endl << endl;
}


void Consola::mostrarResultado(Jugador* jugadorActual, int resultado){

	if(resultado == 1){
		cout << "¡Felicidades " << jugadorActual->darNombre() << " has ganado el juego!"
		 << endl;
	} else if(resultado == 2){
		cout << "El tablero se lleno, el juego ha termino en empate." << endl;
	} else {
		cout << "Ningun jugador tiene fichas para continuar, "
				"el juego termino en empate." << endl;
	}
}


Consola::~Consola() {

}


void Consola::pedirTamanio(string parteDelTablero, int& posicion){

	parteDelTablero += ": ";

	do{
		cout << parteDelTablero;
		cin >> posicion;

		if(posicion < 0){

			cout << endl
				 << "----------------------------------------------------" << endl
				 << "- Tamaño invalido, el valor debe ser mayor a cero. -" << endl
				 << "----------------------------------------------------" << endl
				 << endl;
		}
	}while(posicion < 0);
}


void Consola::pedirPosicion(string parteDelTablero, int& posicion, int limite){

	bool seguir = true;

	do{
		cout << "Ingresa una " << parteDelTablero << " entre 1 y " << limite << ": ";
		cin >> posicion;
		cout << endl;

		seguir = (posicion < 1 || posicion > limite);

		if(seguir){

			cout << "Valor invalido, intenta de nuevo." << endl;
		}

	}while(seguir);
}


void Consola::mostrarSeparador(int espaciosMax, int pisos){

	int rayasMax = 16 + (espaciosMax + 3) * pisos;
	for (int rayas = 0; rayas < rayasMax; rayas++) {
		cout << "-";
	}

	cout << endl;
}


int Consola::contarDigitos(unsigned int numero){

	int digitos = 0;
	int resto = numero;

	while(resto > 0){

		resto /= 10;
		digitos++;
	}

	return digitos;
}


void Consola::mostrarCartasDisponibles(Lista<Carta*>* cartas){

	cout << "¿Deseas usar alguna de tus cartas de poder?" << endl
		 << endl
		 << "Cartas disponibles:" << endl
		 << endl
		 << "0 - No usar ninguna carta." << endl
		 << endl;

	int nroDeCarta = 1;
	cartas->iniciarCursor();

	while (cartas->avanzarCursor()) {

		cout << nroDeCarta << " - "
			 << cartas->obtenerCursor()->mostrarPoder() << endl;
		nroDeCarta++;
	}
}
