
#include "Partida.h"

int main(){

	Partida* nuevaPartida = new Partida();
	nuevaPartida->jugarPartida();
	delete nuevaPartida;

	return 0;
}
