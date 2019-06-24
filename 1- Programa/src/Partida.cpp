
#include "Partida.h"

using std::string;


Partida::Partida() {

	this->juez = new Juez;
	this->consola = new Consola;
	this->dibujante = new Dibujante();
	this->consola->pedirDificultad(this->dificultad);
	this->tablero = new Tablero(this->consola);

	int cantidadDeJugadores = this->consola->pedirCantidadDeJugadores();
	int cantDeFichas = this->repartirFichas();

	this->listaDeJugadores = new Lista<Jugador*>;
	for (int nro = 1; nro <= cantidadDeJugadores; nro++) {

		string nombre = this->consola->pedirNombreJugador(nro);
		this->listaDeJugadores->agregar(new Jugador(nombre, nro, cantDeFichas));
	}

	this->jugadoresEliminados = new Lista<Jugador*>;
	this->terminoLaPartida = false;
	this->robarFichas = false;
	this->cartaColor = this->listaDeJugadores->obtener(1);
	this->jugadaActual = new Jugada(0,0,0, NULL, 0);
}


void Partida::jugarPartida() {

	do {

		this->listaDeJugadores->iniciarCursor();
		this->jugarRonda();

		if(!this->terminoLaPartida){

			this->eliminarJugadores();
		}

	} while (!this->terminoLaPartida);
}


Partida::~Partida(){

	delete this->juez;
	delete this->consola;
	delete this->dibujante;
	delete this->tablero;
	delete this->jugadaActual;
	delete this->jugadaAnterior;

	this->listaDeJugadores->iniciarCursor();
	while(this->listaDeJugadores->avanzarCursor()){
		delete this->listaDeJugadores->obtenerCursor();
	}
	delete this->listaDeJugadores;

	this->jugadoresEliminados->iniciarCursor();
	while(this->jugadoresEliminados->avanzarCursor()){
		delete this->jugadoresEliminados->obtenerCursor();
	}
	delete this->jugadoresEliminados;
}


int Partida::repartirFichas(){

	int fichas;
	int espaciosTotales = 1;

	espaciosTotales *= this->tablero->darFilas();
	espaciosTotales *= this->tablero->darColumnas();
	espaciosTotales *= this->tablero->darPisos();

	switch(this->dificultad){

	case 1:
		fichas = espaciosTotales;
		if(fichas < 16){
			fichas = 16;
		}
		break;
	case 2:
		fichas = espaciosTotales/2;
		if(fichas < 12){
			fichas = 12;
		}
		break;
	case 3:
		fichas = 10;
		break;
	}

	return fichas;
}


void Partida::jugarRonda(){

	this->turno = 1;
	while (!this->terminoLaPartida && this->listaDeJugadores->avanzarCursor()) {

		this->jugadaActual->cambiarJugador(this->listaDeJugadores->obtenerCursor());

		if(this->robarFichas){

			this->juez->robarFichas(this->jugadaActual->darJugador());
			this->robarFichas = false;
		}

		this->consola->indicarTurnoActual(this->jugadaActual->darJugador());

		if (this->jugadaActual->darJugador()->contarFichas() > 0) {

			this->jugarTurno();

		} else {

			string efecto = this->jugadaActual->darJugador()->darNombre();
			efecto += " no te quedan mas fichas, has perdido la partida!";

			this->consola->mostrarEfectoJugada(efecto);
			this->jugadoresEliminados->agregar(this->jugadaActual->darJugador());
		}

		this->turno++;
	}
}


void Partida::jugarTurno(){

	this->jugadaActual->darNumero()++;
	this->jugadaActual->darJugador()->realizarJugada();

	this->consola->pedirPosicionFicha(this->jugadaActual, this->tablero);
	this->tablero->mostrarEstado(this->consola, this->listaDeJugadores->contarElementos());
	this->dibujante->cargarJugada(this->tablero, this->jugadaActual);
	this->terminoElJuego(this->jugadaActual);

	if(!this->terminoLaPartida){
		this->preguntarSiQuiereUsarCarta();
		if(!this->terminoLaPartida){
			this->darCarta();
		}
	}

	delete this->jugadaAnterior;
	this->jugadaAnterior = new Jugada(jugadaActual);
}


void Partida::darCarta(){

	bool darCartaAJugador = false;
	Jugador* jugadorActual = this->jugadaActual->darJugador();

	if(!jugadorActual->pozoLleno()){
		darCartaAJugador = this->juez->darCartaA(jugadorActual, this->dificultad);
	}

	if(darCartaAJugador){
		Carta* carta = jugadorActual->recibirCarta();
		this->consola->mostrarEfectoJugada("¡Felicidades has recibido una nueva carta de poder!");
		this->consola->mostrarEfectoJugada(carta->mostrarPoder());
	}
}


void Partida::preguntarSiQuiereUsarCarta(){

	int eleccion;
	Jugador* jugadorActual = this->jugadaActual->darJugador();

	if(jugadorActual->tieneCartas()){

		eleccion = consola->quiereUsarCarta(jugadorActual);

		if(eleccion > 0){

			this->usarCarta(eleccion);
		}
	}
}


void Partida::usarCarta(int cartaElegida){

	int poderCarta = this->jugadaActual->darJugador()->usarCarta(cartaElegida);

	switch(poderCarta){

	case 1:
		this->usarCarta1();
		break;
	case 2:
		this->usarCarta2();
		break;
	case 3:
		this->usarCarta3();
		break;
	case 4:
		this->usarCarta4();
		break;
	case 5:
		this->usarCarta5();
		break;
	case 6:
		this->usarCarta6();
		break;
	}
}


void Partida::usarCarta1(){

	this->jugadaActual->darNumero()++;
	Jugada* posicion = new Jugada(0,0,0, this->cartaColor, this->jugadaActual->darNumero());

	this->tablero->cambiarColorFicha(posicion);

	string efecto = "Se cambio el color en la posicion -> ";
	consola->mostrarEfectoJugada(posicion, efecto);

	this->tablero->mostrarEstado(this->consola, this->listaDeJugadores->contarElementos());
	this->dibujante->cambiarColorFicha(tablero, posicion);
	this->actualizarColorCarta();
	this->terminoElJuego(posicion);

	delete posicion;
}


void Partida::usarCarta2(){

	this->jugadaActual->darNumero()++;
	Jugada* posicion = new Jugada(0,0,0, NULL, this->jugadaActual->darNumero());

	tablero->eliminarFichaAlAzar(posicion);

	string efecto = "Se elimino la ficha en la posicion -> ";
	consola->mostrarEfectoJugada(posicion, efecto);

	this->tablero->mostrarEstado(this->consola, this->listaDeJugadores->contarElementos());
	this->dibujante->borrarJugada(tablero, posicion);

	if(posicion->darJugador() != NULL){

		this->terminoElJuego(posicion);
	}

	delete posicion;
}


void Partida::usarCarta3(){

	if(!tablero->hayVecinas()){

		string efecto = "No hay ninguna ficha en el tablero con una vecina para "
						"poder intercambiarse, perdiste tu carta.";
		this->consola->mostrarEfectoJugada(efecto);

	} else {

		this->jugadaActual->darNumero()++;
		Jugada* ficha1 = new Jugada(0,0,0, NULL, this->jugadaActual->darNumero());
		Jugada* ficha2 = new Jugada(0,0,0, NULL, this->jugadaActual->darNumero());

		this->consola->pedirFichasACambiar(this->tablero, ficha1, ficha2);
		this->tablero->mostrarEstado(this->consola, this->listaDeJugadores->contarElementos());
		this->dibujante->intercambiarFichas(tablero, ficha1, ficha2);

		this->terminoElJuego(ficha1);
		if(!this->terminoLaPartida){
			this->terminoElJuego(ficha2);
		}

		delete ficha1;
		delete ficha2;
	}
}


void Partida::usarCarta4(){

	Einstein* portalero = new Einstein();
	bool portalCreado = portalero->crearPortal(this->tablero, this->consola);

	// Si se pudo crear el portal, revisar si el mismo produce un cuatro en linea.
	if(portalCreado){

		this->terminoElJuego(portalero->darLadoA());
	}
	delete portalero;
}


void Partida::usarCarta5(){

	this->jugadaActual->darNumero()++;
	this->jugadaAnterior->darNumero() += 2;

	string efecto = "Se elimino la ficha en la posicion -> ";
	this->consola->mostrarEfectoJugada(jugadaAnterior, efecto);
	this->tablero->eliminarJugadaAnterior(jugadaAnterior);
	this->tablero->mostrarEstado(this->consola, this->listaDeJugadores->contarElementos());
	this->dibujante->borrarJugada(tablero, jugadaAnterior);

	if(this->jugadaAnterior->darJugador() != NULL){

		this->terminoElJuego(jugadaAnterior);
	}
}


void Partida::usarCarta6(){

	this->robarFichas = true;
	string efecto = "Le has robado 10 fichas y todas sus cartas de poder "
			  	  	"al jugador siguiente.";
	this->consola->mostrarEfectoJugada(efecto);
}


void Partida::actualizarColorCarta() {

	this->listaDeJugadores->iniciarCursor();

	// Avanzo mi lista hasta encontrar el jugador que tiene asignado cartaColor
	do {

		this->listaDeJugadores->avanzarCursor();

	} while (this->cartaColor != this->listaDeJugadores->obtenerCursor());

	// Le asigno a cartaColor el siguiente de la lista.
	if(this->listaDeJugadores->avanzarCursor()){

		this->cartaColor = this->listaDeJugadores->obtenerCursor();

	} else {

		this->listaDeJugadores->iniciarCursor();
		this->listaDeJugadores->avanzarCursor();
		this->cartaColor = this->listaDeJugadores->obtenerCursor();
	}

	// Coloco la lista donde estaba antes.
	this->avanzarListaHasta(this->turno);
}


void Partida::eliminarJugadores(){

	this->jugadoresEliminados->iniciarCursor();
	while (this->jugadoresEliminados->avanzarCursor()) {

		bool encontrado = false;
		int indice = 0;
		Jugador* jugadorAEliminar = this->jugadoresEliminados->obtenerCursor();

		this->listaDeJugadores->iniciarCursor();
		while (!encontrado && this->listaDeJugadores->avanzarCursor()) {

			indice++;
			Jugador* jugadorAComparar = this->listaDeJugadores->obtenerCursor();

			// Veo si el jugador eliminado es el asignado a cartaColor
			encontrado = (jugadorAEliminar == jugadorAComparar);
			if(encontrado){
				if(this->cartaColor == jugadorAEliminar){
					this->cartaColor = NULL;
					if(!this->listaDeJugadores->avanzarCursor()){
						this->listaDeJugadores->iniciarCursor();
						this->listaDeJugadores->avanzarCursor();
					}

					// Le asigno un nuevoColor a cartaColor
					if(this->listaDeJugadores->contarElementos() > 0){
						this->cartaColor = this->listaDeJugadores->obtenerCursor();
					}
				}
				this->listaDeJugadores->remover(indice);
			}
		}
	}

	if(this->listaDeJugadores->contarElementos() == 0){
		this->terminoElJuego(this->jugadaActual);
	}
}


void Partida::terminoElJuego(Jugada* jugada){

	this->terminoLaPartida = true;

	if(this->juez->hay4EnLinea(this->tablero, jugada)){

		this->consola->mostrarResultado(jugada->darJugador(), 1);

	} else if(this->juez->huboEmpate(this->tablero)) {

		this->consola->mostrarResultado(jugada->darJugador(), 2);

	} else if(this->listaDeJugadores->contarElementos() == 0){

		this->consola->mostrarResultado(jugada->darJugador(), 3);

	} else {

		this->terminoLaPartida = false;
	}
}


void Partida::avanzarListaHasta(unsigned int posicionFinal){

	if(posicionFinal > this->listaDeJugadores->contarElementos()){

		throw string("Se ha intentado ir a una posicion inexistente de lista de Jugadores.");
	}

	this->listaDeJugadores->iniciarCursor();
	for(unsigned int posicion = 1; posicion <= posicionFinal; posicion++){

		this->listaDeJugadores->avanzarCursor();
	}
}
