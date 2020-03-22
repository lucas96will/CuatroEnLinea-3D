#include "CartaEliminarFicha.h"

void CartaEliminarFicha::activar(){
	Jugador* jugadorActual = this->obtenerJugadorActual();
	Coordenada posicionFichaAEliminar = pedirCoordenadaDeFicha(this->tablero, jugadorActual->consultarColor(), "de la ficha que desees eliminar");
	this->tablero->eliminarFicha(posicionFichaAEliminar);

    Jugador* posibleGanador = this->tablero->obtenerFichaEnCelda(posicionFichaAEliminar);
    if(posibleGanador != NULL){
    	posibleGanador->asignarSiGanoPartida(this->tablero->hayCuatroEnLinea(posicionFichaAEliminar, posibleGanador));
    }

	mostrar(this->tablero);
}
