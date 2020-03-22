#include "CartaCrearPortal.h"

void CartaCrearPortal::activar(){

  Coordenada casilleroUno;
  Coordenada casilleroDos;

  Jugador* jugadorActual = this->obtenerJugadorActual();
  obtenerCasillerosLaterales(casilleroUno, casilleroDos, this->tablero, jugadorActual->consultarColor());
  Jugador* jugadorGanador = this->hallarGanadorDelPortalUniendo(casilleroUno, casilleroDos);

  if(jugadorGanador != NULL){
	  jugadorGanador->asignarSiGanoPartida(jugadorGanador);
  } else {
	  mostrarMensaje("El portal que una vez se abrio se cerro, has perdido tu oportunidad", "");
  }

}

Jugador* CartaCrearPortal::hallarGanadorDelPortalUniendo(Coordenada casilleroUno, Coordenada casilleroDos){
  unsigned contador = 0;
  Jugador* jugadorGanador = NULL;
  Jugador* jugadorEnPosicionUno = this->tablero->obtenerFichaEnCelda(casilleroUno);
  Jugador* jugadorEnPosicionDos = this->tablero->obtenerFichaEnCelda(casilleroDos);

  unsigned distanciaEntreCasilleros = this->tablero->distanciaEntre(casilleroUno, casilleroDos);

  if(jugadorEnPosicionUno == jugadorEnPosicionDos && distanciaEntreCasilleros > PORTAL_DISTANCIA_MINIMA){
    contador = this->tablero->obtenerFichasMaximasEnLinea(casilleroUno);
    contador += this->tablero->obtenerFichasMaximasEnLinea(casilleroDos);
    if(contador >= FICHAS_MINIMAS_PARA_GANAR){
      jugadorGanador = jugadorEnPosicionUno;
    }
  }
  return jugadorGanador;
}
