#include "Jugador.h"

using namespace std;

Jugador::Jugador(Tablero* tablero, unsigned numeroJugador, char dificultad, unsigned fichasPorJugador , string color){

  this->tablero = tablero;
  this->ultimaPosicionFichaIngresada = {0 , 0 , 0};
  this->color = color;
  this->cantidadDeFichas = fichasPorJugador;
  this->dificultad = dificultad;
  this->ganador = false;
  this->probabilidadDeCarta = PROBABILIDAD_INICIAL_DE_GANAR_CARTA;
  this->esSuTurno = false;
  this->manoDeCartas = new ListaSimple<CartaAbstracta*>();
  this->numero = numeroJugador;

}

Jugador::~Jugador(){
    delete this->manoDeCartas;
}

bool Jugador::puedeRecibirCarta(){
	return this->manoDeCartas->contarElementos() <= CARTAS_JUGADOR_MAX;
}

unsigned Jugador::consultarNumero(){
	return this->numero;
}

void Jugador::recibeCarta(CartaAbstracta* nuevaCarta){
	if(!this->puedeRecibirCarta()){
		throw ExcepcionError("No se puede recibir carta si la mano de cartas esta llena");
	}
	this->manoDeCartas->agregar(nuevaCarta);
}

void Jugador::descartarCarta(unsigned posicionCarta){
	if(posicionCarta > this->manoDeCartas->contarElementos() && posicionCarta < 1){
		throw ExcepcionError("Error al tratar de descartar una carta no hallada");
	}
	this->manoDeCartas->remover(posicionCarta);
}

void Jugador::usarCarta(unsigned int posicionCarta){
	if(posicionCarta < 1 && this->manoDeCartas->contarElementos() < posicionCarta){
		throw ExcepcionError("Error al tratar de jugar una carta no encontrada");
	}

    CartaAbstracta* usada = this->manoDeCartas->obtener(posicionCarta);
    usada->activar();
    usada->aumentarVecesUsada();
    this->descartarCarta(posicionCarta);
}

void Jugador::descontarFicha(){
	if(this->cantidadDeFichas > 0){
		this->cantidadDeFichas--;
	}
}

string Jugador::consultarColor(){
		return this->color;
}

Dimension Jugador::consultarUltimaPosicion(){
	return this->ultimaPosicionFichaIngresada;
}

int Jugador::consultarCantidadDeFichas(){
	return this->cantidadDeFichas;
}

int Jugador::consultarCantidadDeCartas(){
  return this->manoDeCartas->contarElementos();
}


ListaSimple<CartaAbstracta*>* Jugador::obtenerCartas(){
  return this->manoDeCartas;
}

void Jugador::cambiarColor(string nuevoColor){
  this->color = nuevoColor;
}


unsigned Jugador::probabilidadGanarCarta(){
	return this->probabilidadDeCarta;
}

void Jugador::ingresarFicha(){

  Coordenada posicionIngresada = pedirIngresarFicha(this->tablero, this->color);

  this->ultimaPosicionFichaIngresada = posicionIngresada;

  this->tablero->agregarFichaEnCelda(posicionIngresada,this);

  this->descontarFicha();
}



void Jugador::asignarSiGanoPartida(bool estado){
	this->ganador = estado;
}

bool Jugador::consultarSiGanoLaPartida(){
	return this->ganador;
}

void Jugador::bajarProbabilidadGanarCarta(){

	if(this->probabilidadDeCarta > PROBABILIDAD_MINIMA_DE_GANAR_CARTA){

		this->probabilidadDeCarta -= PROBABILIDAD_PERDIDA_DE_GANAR_CARTA;

		if(this->probabilidadDeCarta < PROBABILIDAD_MINIMA_DE_GANAR_CARTA){

			this->probabilidadDeCarta = PROBABILIDAD_MINIMA_DE_GANAR_CARTA;
      cout << "Tu probabilidad de obtener carta se reestablece. ";
		}
    else{
      cout << "Tu probabilidad de obtener una carta es Baja. ";
    }
    cout << "Esta en " << this->probabilidadDeCarta << "." << endl;
	}

}

void Jugador::subirProbabilidadGanarCarta(){

	if(this->probabilidadDeCarta < PROBABILIDAD_MAXIMA_DE_GANAR_CARTA){

		this->probabilidadDeCarta += PROBABILIDAD_AUMENTADA_DE_GANAR_CARTA;

		if(this->probabilidadDeCarta > PROBABILIDAD_MAXIMA_DE_GANAR_CARTA){

			this->probabilidadDeCarta = PROBABILIDAD_MAXIMA_DE_GANAR_CARTA;
      cout << "Tu probabilidad de obtener una  carta se reestablece. ";
		}
    else{
      cout << "Tu probabilidad de obtener una carta Sube. ";
    }
    cout << "Ahora esta en " << this->probabilidadDeCarta << "." << endl;
	}
}

void Jugador::estabilizarProbabilidadGanarCarta(){
	this->probabilidadDeCarta = PROBABILIDAD_INICIAL_DE_GANAR_CARTA;
}

void Jugador::iniciarTurno(){
	this->esSuTurno = !this->esSuTurno;
}

void Jugador::terminarTurno(){
	this->esSuTurno = !this->esSuTurno;
}

bool Jugador::consultarSiEsSuTurno(){
	return this->esSuTurno;
}
