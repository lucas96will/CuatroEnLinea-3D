#include "CartaRobarCarta.h"



bool CartaRobarCarta::hayJugadoresAQuienRobarle()
{
	unsigned cantidadDeCartas = 0;
	unsigned contador = 1;
	Jugador* actual;
	while(contador <= this->jugadores->contarElementos()){
		actual = this->jugadores->obtener(contador);
		if(actual != this->usuarioDeLaCarta){
			cantidadDeCartas += actual->consultarCantidadDeCartas();
		}
		contador++;
	}

	return (cantidadDeCartas >= 1);
}

unsigned CartaRobarCarta::consultarQueCartaRobarleAlJugador(Jugador* jugadorAlCualRobar){
  unsigned posicionCarta = NO_ENCONTRO_CARTAS;

  ListaSimple<CartaAbstracta*>* manoJugador = jugadorAlCualRobar->obtenerCartas();
  mostrar(manoJugador);
  posicionCarta = obtenerCualCartaRobarAlJugador(manoJugador);

  return posicionCarta;
}

Jugador* CartaRobarCarta::consultarQueJugadorRobarleCarta(){

  Jugador* jugadorASerRobado = NULL;

  if(this->hayJugadoresAQuienRobarle()){
	  jugadorASerRobado = obtenerJugadorASerRobado(this->jugadores, this->usuarioDeLaCarta);
  }
  return jugadorASerRobado;
}


void CartaRobarCarta::robarCartaDe(Jugador* afectado, unsigned int posicionCarta){
	CartaAbstracta* robada = afectado->obtenerCartas()->obtener(posicionCarta);
	this->usuarioDeLaCarta->recibeCarta(robada);
	std::string mensaje = ("Robaste la carta " + robada->consultarIdentificador());
	mostrarMensaje(mensaje, this->usuarioDeLaCarta->consultarColor());
	afectado->descartarCarta(posicionCarta);
}


void CartaRobarCarta::activar(){
	this->usuarioDeLaCarta = this->obtenerJugadorActual();
  Jugador* jugadorRobado = this->consultarQueJugadorRobarleCarta();

  if(jugadorRobado != NULL){
		unsigned posicionCarta = this->consultarQueCartaRobarleAlJugador(jugadorRobado);
			if(posicionCarta != NO_ENCONTRO_CARTAS){
				this->robarCartaDe(jugadorRobado, posicionCarta);
			}
  }
}
