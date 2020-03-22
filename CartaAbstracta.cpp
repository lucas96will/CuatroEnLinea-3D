#include "CartaAbstracta.h"

CartaAbstracta::CartaAbstracta(Tablero* tableroJuego, ListaSimple<Jugador*>* listaJugadores,unsigned suNumero, std::string suIdentificador, std::string suDescripcion) {
  this->identificador = suIdentificador;
  this->tablero = tableroJuego;
  this->jugadores = listaJugadores;
  this->descripcion = suDescripcion;
  this->vecesUsada = 0;
  this->vecesRepartida = 0;
  this->identificadorNumero = suNumero;
}

std::string CartaAbstracta::consultarIdentificador(){
  return this->identificador;
}

std::string CartaAbstracta::consultarDescripcion(){
  return this->descripcion;
}

unsigned CartaAbstracta::obtenerIdentificadorNumero(){
  return this->identificadorNumero;
}

unsigned CartaAbstracta::obtenerVecesUsada(){
  return this->vecesUsada;
}

Jugador* CartaAbstracta::obtenerJugadorActual(){

	unsigned i = 1;
	Jugador* actual = NULL;
	bool encontrado = false;

	while(!encontrado && i <= this->jugadores->contarElementos()){
		actual = this->jugadores->obtener(i);
		encontrado = actual->consultarSiEsSuTurno();
		i++;
	}

	return actual;
}


unsigned CartaAbstracta::obtenerVecesRepartida(){
  return this->vecesRepartida;
}

unsigned CartaAbstracta::obtenerVecesApariciones(){
  return this->vecesUsada + this->vecesRepartida;
}

void CartaAbstracta::aumentarVecesUsada(){
  this->vecesUsada++;
}

void CartaAbstracta::aumentarVecesRepartida(){
  this->vecesRepartida++;
}
