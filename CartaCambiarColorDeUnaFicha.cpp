#include "CartaCambiarColorDeUnaFicha.h"


void CartaCambiarColorDeUnaFicha::activar(){
	if(this->vecesUsada == 0){
		this->jugadorAlternante = 1;
	}
	Jugador* jugadorAlternante = this->jugadores->obtener(this->jugadorAlternante);
	Coordenada posicionACambiar = pedirCoordenadaDeFicha(this->tablero, jugadorAlternante->consultarColor(), " de la ficha desees cambiar de color");
	this->tablero->cambiarColorEnCeldaEn(posicionACambiar,jugadorAlternante);

	Jugador* jugadorRemanente = this->tablero->obtenerFichaEnCelda(posicionACambiar);

	bool jugadorGano = this->tablero->hayCuatroEnLinea(posicionACambiar, jugadorRemanente);
	jugadorAlternante->asignarSiGanoPartida(jugadorGano);
    this->siguienteJugadorAlternante();
}

void CartaCambiarColorDeUnaFicha::siguienteJugadorAlternante(){

	if(this->jugadorAlternante < this->jugadores->contarElementos()){
		 this->jugadorAlternante++;
	} else {
		 this->jugadorAlternante = 1;
	}
}
