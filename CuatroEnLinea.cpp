#include "CuatroEnLinea.h"
#include "Declaraciones.h"
#include "CartaRobarCarta.h"
#include "CartaCrearPortal.h"
#include "CartaEliminarFicha.h"
#include "CartaIgnorarMovimiento.h"
#include "CartaIntercambioDeFichas.h"
#include "CartaCambiarColorDeUnaFicha.h"
#include "ExcepcionError.h"


using namespace std;

CuatroEnLinea::CuatroEnLinea(){

  mostrarPresentacionJuego();

  Dimension dimensionTablero = pedirDimensionDelTablero();
  this->tablero = new Tablero(dimensionTablero);
  this->dificultad = pedirDificultadDeJuego();
  this->jugadores = new ListaSimple<Jugador*>();
  this->tiposDeCartas = new ListaSimple<CartaAbstracta*>();
  this->cantidadMaximaDeFichasLibres = this->tablero->obtenerCantidadDeCeldas();
  unsigned int cantidadDeJugadores = pedirCantidadDeJugadores(this->cantidadMaximaDeFichasLibres);
  this->cargarTiposCartas();

  int cantidadDeFichasPorJugador = fichasSegunDificultad();
  this->crearJugadores(cantidadDeFichasPorJugador, cantidadDeJugadores);
  mostrar(this->jugadores);
  this->jugadorActual = PRIMERO;
  this->cantidadTotalDeFichasDeJugadores = cantidadDeFichasPorJugador*cantidadDeJugadores;

  this->iniciarJuego();
}


void CuatroEnLinea::crearJugadores(int fichasPorJugador, unsigned int cantidadDeJugadores){
  string listaColores[] = {AZUL, ROJO, VERDE, AMARILLO,  NARANJA, ROSADO, CELESTE,
                                OCRE, ROSA, HOJA,  AQUAMARINA, MARRON,  PURPURA, GRIS,   BORDO,
                                MARINO, BLANCO}; /* 17 COLORES DIFERENCIABLES */

  for(unsigned i = 1 ; i <= cantidadDeJugadores ; i++){
	Jugador* nuevo = new Jugador(this->tablero, i,  (char)this->dificultad, fichasPorJugador ,listaColores[i-1]);
    this->jugadores->agregar(nuevo);
  }
}

void CuatroEnLinea::cargarTiposCartas(){

  CartaRobarCarta* robar = new CartaRobarCarta(this->tablero, this->jugadores, NUMERO_CARTA_ROBAR, IDENTIFICADOR_CARTA_ROBAR_CARTA, DESCRIPCION_CARTA_ROBAR_CARTA);
  CartaCambiarColorDeUnaFicha* cambiarColor = new CartaCambiarColorDeUnaFicha(this->tablero, this->jugadores, NUMERO_CARTA_CAMBIAR_COLOR,IDENTIFICADOR_CARTA_CAMBIAR_COLOR, DESCRIPCION_CARTA_CAMBIAR_COLOR);
  CartaEliminarFicha* eliminar = new CartaEliminarFicha(this->tablero, this->jugadores, NUMERO_CARTA_ELIMINAR_FICHA, IDENTIFICADOR_CARTA_ELIMINAR_FICHA, DESCRIPCION_CARTA_ELIMINAR_FICHA);
  CartaCrearPortal* crearPortal = new CartaCrearPortal(this->tablero, this->jugadores, NUMERO_CARTA_PORTAL, IDENTIFICADOR_CARTA_CREAR_PORTAL, DESCRIPCION_CARTA_CREAR_PORTAL);
  CartaIgnorarMovimiento*  ignorarMovimiento = new CartaIgnorarMovimiento(this->tablero, this->jugadores, NUMERO_CARTA_IGNORAR_ANTERIOR, IDENTIFICADOR_CARTA_IGNORAR_ANTERIOR, DESCRIPCION_CARTA_IGNORAR_ANTERIOR);
  CartaIntercambioDeFichas* intercambio = new CartaIntercambioDeFichas(this->tablero, this->jugadores, NUMERO_CARTA_INTERCAMBIO, IDENTIFICADOR_CARTA_INTERCAMBIO, DESCRIPCION_CARTA_INTERCAMBIO);

  this->tiposDeCartas->agregar(robar);
  this->tiposDeCartas->agregar(cambiarColor);
  this->tiposDeCartas->agregar(eliminar);
  this->tiposDeCartas->agregar(crearPortal);
  this->tiposDeCartas->agregar(ignorarMovimiento);
  this->tiposDeCartas->agregar(intercambio);

}

int CuatroEnLinea::fichasSegunDificultad(){
  int fichasPorJugador;
  int cantidadDeCeldas = (this->tablero->obtenerCantidadDeCeldas());
	if(this->dificultad == DIFICULTAD_FACIL){
		fichasPorJugador = (cantidadDeCeldas/2);
    }
    else if(this->dificultad == DIFICULTAD_MODERADA){
    	fichasPorJugador = (cantidadDeCeldas/3);
    }
    else if(this->dificultad == DIFICULTAD_DIFICIL){
    	fichasPorJugador = (2 + (cantidadDeCeldas/(2*this->obtenerCantidadDeJugadores())));
    }
    else{
      throw ExcepcionError("Dificultad incorrecta");
    }
	return fichasPorJugador;
}

void CuatroEnLinea::iniciarJuego(){

  int numeroRonda = 1;
  Jugador* ganador = NULL;
  do{
      cartelNroDeRonda(numeroRonda, (unsigned)this->tablero->consultarDimensiones().y);

      ganador = this->ronda();
      numeroRonda++;

  }while(!ganador && !this->hayEmpate());

  if(ganador != NULL){
	  mostrarResultados(ganador->consultarNumero() , ganador->consultarColor());
  } else {
	  mostrarMensaje("Ha ocurrido un empate entre los jugadores!", "");
  }
}


Jugador* CuatroEnLinea::ronda(){

  Jugador* ganadorDeLaRonda = NULL;
  this->jugadores->iniciarCursor();
  jugadores->avanzarCursor();

  mostrar(this->tablero);

  this->jugadorActual = PRIMERO;
  do{
    Jugador* jugadorRonda = this->jugadores->obtenerCursor();
    jugadorRonda->iniciarTurno();


    mostrar(jugadorRonda, (unsigned)this->tablero->consultarDimensiones().y);
    this->etapaJugarCarta(jugadorRonda);


    if(this->obtenerGanador() == NULL){
        this->probabilidadGanarCarta(jugadorRonda);
        jugadorRonda->ingresarFicha();
        mostrar(this->tablero);
        this->restarFichas();
    }

    ganadorDeLaRonda = this->estadoDelJuego();
    jugadorRonda->terminarTurno();
    this->siguienteJugador();

  }while(jugadores->avanzarCursor() && !ganadorDeLaRonda && !this->hayEmpate());

    mostrarBPM(this->tablero);
  return ganadorDeLaRonda;
}

void CuatroEnLinea::etapaJugarCarta(Jugador* jugadorActivo){
	bool quiereJugarCarta = false;
	unsigned posicionCarta;

	if(jugadorActivo->consultarCantidadDeCartas() >= 1){
		ListaSimple<CartaAbstracta*>* manoDeCartas = jugadorActivo->obtenerCartas();
		mostrar(manoDeCartas);

		quiereJugarCarta = consultarJugadorJugarCarta();

		if(quiereJugarCarta){
			posicionCarta = elegirCartaParaJugar(manoDeCartas);
			if(posicionCarta != CARTA_NULA){
				this->preUsoDeCartas(jugadorActivo, posicionCarta);
			}
		}
	}
}

void CuatroEnLinea::preUsoDeCartas(Jugador* jugadorActivo, unsigned posicionCarta){
	unsigned identificadorCartaUsada = jugadorActivo->obtenerCartas()->obtener(posicionCarta)->obtenerIdentificadorNumero();

		switch(identificadorCartaUsada) {

			case(NUMERO_CARTA_CAMBIAR_COLOR):
					jugadorActivo->usarCarta(posicionCarta);
					mostrar(this->tablero);
				break;

			case(NUMERO_CARTA_ELIMINAR_FICHA):
					jugadorActivo->usarCarta(posicionCarta);
					mostrar(this->tablero);
				break;

			case(NUMERO_CARTA_INTERCAMBIO):
					jugadorActivo->usarCarta(posicionCarta);
					mostrar(this->tablero);
				break;

			case(NUMERO_CARTA_PORTAL):
					jugadorActivo->usarCarta(posicionCarta);
				break;

			case(NUMERO_CARTA_IGNORAR_ANTERIOR):
					jugadorActivo->usarCarta(posicionCarta);
					mostrar(this->tablero);
				break;

			case(NUMERO_CARTA_ROBAR):
				mostrarJugadoresParaRobar(this->jugadores);
				if(preguntaRobarCarta()){
					jugadorActivo->usarCarta(posicionCarta);
					mostrar(jugadorActivo->obtenerCartas());
				}
				break;
		}
}

void CuatroEnLinea::restarFichas(){
	this->cantidadMaximaDeFichasLibres--;
	this->cantidadTotalDeFichasDeJugadores--;
}


void CuatroEnLinea::probabilidadGanarCarta(Jugador* jugador){
	if(ganaCarta(jugador->probabilidadGanarCarta()) && jugador->consultarCantidadDeCartas() < CARTAS_JUGADOR_MAX){
	    this->darCartaAlJugador(jugador);
	    jugador->bajarProbabilidadGanarCarta();
	 }else {
		 jugador->subirProbabilidadGanarCarta();
	 }
}

bool CuatroEnLinea::ganaCarta(unsigned probabilidadDeGanarCarta){
    return sortearPosibilidades(probabilidadDeGanarCarta,100);
}

void CuatroEnLinea::darCartaAlJugador(Jugador* jugador){
  CartaAbstracta* cartaElegida = this->designarUnaCartaParaJugador();
  string mensaje = ("Obtuviste la carta => " + cartaElegida->consultarIdentificador());
  mostrarMensaje(mensaje, jugador->consultarColor());
  cartaElegida->aumentarVecesRepartida();
  jugador->recibeCarta(cartaElegida);
}

CartaAbstracta* CuatroEnLinea::designarUnaCartaParaJugador(){

  CartaAbstracta* cartaDesignada = NULL;
  unsigned baseDeCartaMasRepartida = this->vecesRepartidaCartaMasRepartida() + CANTIDAD_DE_TIPOS_DE_CARTAS;
  unsigned baseDeCartaDeMasUso = this->vecesDeUsoCartaMasUsada() + CANTIDAD_DE_TIPOS_DE_CARTAS;

  this->tiposDeCartas->iniciarCursor();
  while(tiposDeCartas->avanzarCursor() && hay(cartaDesignada)){
	  unsigned cartaRand = (1+rand()%CANTIDAD_DE_TIPOS_DE_CARTAS);
	  if(this->esCartaDesignada(this->tiposDeCartas->obtener(cartaRand), baseDeCartaDeMasUso, baseDeCartaMasRepartida)){
	          cartaDesignada = this->tiposDeCartas->obtener(cartaRand);
	  }
  }

  if( cartaDesignada == NULL){
    cartaDesignada = this->cartaConMenorApariciones();
  }
  if(cartaDesignada == NULL){
    throw ExcepcionError("ERROR EN DESIGNAR UNA CARTA AL DEVOLVER UN NULL");
  }
  return cartaDesignada;
}

bool CuatroEnLinea::hay(CartaAbstracta* cartaDesignada){
  return cartaDesignada == NULL;
}

unsigned CuatroEnLinea::vecesRepartidaCartaMasRepartida(){

  unsigned mayorVecesRepartida = 0;
  unsigned vecesRepartida;

  this->tiposDeCartas->iniciarCursor();
  while(this->tiposDeCartas->avanzarCursor()){

	  vecesRepartida = this->tiposDeCartas->obtenerCursor()->obtenerVecesRepartida();
	  if(mayorVecesRepartida < vecesRepartida){
		   mayorVecesRepartida = vecesRepartida;
	  }
  }
  return mayorVecesRepartida;
}


unsigned CuatroEnLinea::vecesDeUsoCartaMasUsada(){

  unsigned mayorVecesUsada = 0;
  unsigned vecesUsada;

  this->tiposDeCartas->iniciarCursor();
  while(this->tiposDeCartas->avanzarCursor()){
	  vecesUsada =  this->tiposDeCartas->obtenerCursor()->obtenerVecesUsada();
	  if(mayorVecesUsada < vecesUsada){
		  mayorVecesUsada = vecesUsada;
	  }
  }

  return mayorVecesUsada;
}

CartaAbstracta* CuatroEnLinea::cartaConMenorApariciones(){

  CartaAbstracta* cartaDesignada = NULL;
  unsigned menorAparicion = 0;
  unsigned aparicionesCarta = 0;

  this->tiposDeCartas->iniciarCursor();
  while(this->tiposDeCartas->avanzarCursor()){
	  aparicionesCarta = this->tiposDeCartas->obtenerCursor()->obtenerVecesRepartida();
	  if(menorAparicion < aparicionesCarta){
		  menorAparicion = aparicionesCarta;
	  	  cartaDesignada = this->tiposDeCartas->obtenerCursor();
	  }
  }

  return cartaDesignada;
}


bool CuatroEnLinea::esCartaDesignada(CartaAbstracta* carta,unsigned baseDeCartaDeMasUso,unsigned baseDeCartaMasRepartida){

  bool designio = false;
  unsigned vecesRepartidaEnElJuego = carta->obtenerVecesRepartida();

  if(sortearPosibilidadesBalanceado(vecesRepartidaEnElJuego, baseDeCartaMasRepartida)){

	  unsigned vecesUsadaEnElJuego = carta->obtenerVecesUsada();
    if(sortearPosibilidadesBalanceado(vecesUsadaEnElJuego, baseDeCartaDeMasUso)){
        designio = true;
    }
  }

  return designio;
}

bool CuatroEnLinea::sortearPosibilidadesBalanceado(unsigned casosPosibles, unsigned casosTotales){
  return (rand()%casosTotales > casosPosibles);
}

bool CuatroEnLinea::sortearPosibilidades(unsigned casosPosibles, unsigned casosTotales){
  return (rand()%casosTotales <= casosPosibles);
}

Jugador* CuatroEnLinea::obtenerJugador(unsigned posicion){
    if(posicion > this->jugadores->contarElementos() || posicion < 1){
      throw ExcepcionError("Error al acceder a una posicion de jugadores no definida");
    }
    return this->jugadores->obtener(posicion);
}


bool CuatroEnLinea::hayEmpate(){
	return(this->cantidadMaximaDeFichasLibres < 1 || this->cantidadTotalDeFichasDeJugadores < 1);
}


Jugador* CuatroEnLinea::estadoDelJuego(){
	Jugador* jugador = this->obtenerGanador();
	bool jugadorGano = jugador != NULL;

	if(!jugadorGano){
		jugador = this->jugadores->obtener(this->jugadorActual);
		Coordenada ultimaPosicion = jugador->consultarUltimaPosicion();
		jugadorGano = this->tablero->hayCuatroEnLinea(ultimaPosicion, jugador);
	}

	jugador->asignarSiGanoPartida(jugadorGano);

	return jugadorGano ? jugador : NULL;
}



unsigned CuatroEnLinea::obtenerCantidadDeJugadores(){
   return this->jugadores->contarElementos();
}

void CuatroEnLinea::siguienteJugador(){
  this->jugadorActual++;
}

bool CuatroEnLinea::esElUltimoJugador(){
    return this->jugadorActual == this->jugadores->contarElementos();
}

Tablero* CuatroEnLinea::consultarTablero(){
    return this->tablero;
}


unsigned CuatroEnLinea:: obtenerJugadorActual(){
   return this->jugadorActual;
}

bool CuatroEnLinea::hay(unsigned ganador){
  return ganador != NINGUN_JUGADOR;
}

Jugador* CuatroEnLinea::obtenerGanador(){

	unsigned i = 1;
	bool hayGanador = false;
	Jugador* jugador;
	while(i <= this->jugadores->contarElementos() && !hayGanador){
		jugador = this->jugadores->obtener(i);
		hayGanador = jugador->consultarSiGanoLaPartida();
		i++;
	}

	if(jugador->consultarSiGanoLaPartida()){
		return jugador;
	}
	else {
		return NULL;
	}
}

CuatroEnLinea::~CuatroEnLinea(){

	this->tiposDeCartas->iniciarCursor();
	while(this->tiposDeCartas->avanzarCursor()){
		delete this->tiposDeCartas->obtenerCursor();
	}
	this->jugadores->iniciarCursor();
	while(this->jugadores->avanzarCursor()){
		delete this->jugadores->obtenerCursor();
	}
	delete this->tiposDeCartas;
	delete this->jugadores;
	delete this->tablero;
}
