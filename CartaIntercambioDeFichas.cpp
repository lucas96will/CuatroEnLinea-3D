#include "CartaIntercambioDeFichas.h"

void CartaIntercambioDeFichas::activar(){

	Coordenada posicionFichaBase;
	Coordenada posicionFichaVecina;
	unsigned distanciaMinima;
	bool posicionesAceptadas = false;
	do{
		posicionFichaBase = pedirCoordenadaDeFicha(this->tablero,"" ," de la ficha que desees cambiar con su vecina");
		posicionFichaVecina = pedirCoordenadaDeFicha(this->tablero, "", " de la ficha vecina");

		distanciaMinima = this->tablero->distanciaEntre(posicionFichaBase, posicionFichaVecina);
		posicionesAceptadas = distanciaMinima == DISTANCIA_MINIMA_ENTRE_FICHAS;
		imprimirSiNo(posicionesAceptadas, "Las fichas no son vecinas entre si, por favor re-ingrese");

	} while(this->tablero->distanciaEntre(posicionFichaBase, posicionFichaVecina) > 1);

	Jugador* jugadorBase = tablero->obtenerFichaEnCelda(posicionFichaBase);
	Jugador* jugadorVecino = tablero->obtenerFichaEnCelda(posicionFichaVecina);

	this->tablero->cambiarColorEnCeldaEn(posicionFichaVecina,jugadorBase);
	this->tablero->cambiarColorEnCeldaEn(posicionFichaBase,jugadorVecino);

	/*Checkeo si gano el jugador de la ficha base que se cambio a la posicion del jugador vecino*/
	bool enPosicion = this->tablero->hayCuatroEnLinea(posicionFichaVecina, jugadorBase);
    jugadorBase->asignarSiGanoPartida(enPosicion);

    /*Si el jugadorBase no gano, checkeo el jugador vecino si formo cuatro en linea en la posicion del jugador base*/
    if(!enPosicion){
    	enPosicion = this->tablero->hayCuatroEnLinea(posicionFichaBase, jugadorVecino);
    	jugadorVecino->asignarSiGanoPartida(enPosicion);
    }


}
