#include "CartaIgnorarMovimiento.h"


void CartaIgnorarMovimiento::activar(){

	Jugador* jugadorEnUltimaPosicion = this->tablero->obtenerUltimoEnIngresarFicha();
	Coordenada ultimaPosicion = jugadorEnUltimaPosicion->consultarUltimaPosicion();

    this->tablero->eliminarFicha(ultimaPosicion);

    Jugador* posibleGanador = this->tablero->obtenerFichaEnCelda(ultimaPosicion);

    if(posibleGanador != NULL){

    	posibleGanador->asignarSiGanoPartida(this->tablero->hayCuatroEnLinea(ultimaPosicion, posibleGanador));
    }
    mostrar(this->tablero);
}



