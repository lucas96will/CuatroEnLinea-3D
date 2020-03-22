#ifndef CARTAROBARCARTA_H_
#define CARTAROBARCARTA_H_

#include "CartaAbstracta.h"

class CartaRobarCarta : public CartaAbstracta {

private:

	Jugador* usuarioDeLaCarta;


  /*Se le consulta al jugador que uso esta carta a que jugador le quiere sacar otra
  *Pre:
  *Post:devuelve el puntero al jugador al que el usuario quierer sacar la carta
  */
	Jugador* consultarQueJugadorRobarleCarta();

  /*Pre:
  *Post:devuelve true si hay una carta la cual se puede robar
  */
  bool hayJugadoresAQuienRobarle();

  /*Se le consulta al usuario nuevamente que carta le quiere robar al jugador elegido
  *Pre:el jugador a robar tiene que tener Cartas disponibles en su mano
  *Post:Devuelve el identificador de la carta que se quiere robar
  */
	unsigned consultarQueCartaRobarleAlJugador(Jugador* jugadorAlCualRobar);

	/*
	*Pre:
	*Post:El usuario de la carta usada recibe la carta robada del jugador afectado
	*	  luego se descarta la carta del afectado.
	*/
	void robarCartaDe(Jugador* afectado, unsigned int posicionCarta);


public:
	using CartaAbstracta::CartaAbstracta;

	/*Pre:Los otros jugadores deben tener al menos una carta disponible
	 *Post: Ejecuta la habilidad de la carta y luego desaparece.
   *Roba la carta de algun jugador
	 */
	void activar();
};


#endif /* CARTAROBARCARTA_H_ */
