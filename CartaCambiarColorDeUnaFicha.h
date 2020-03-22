#ifndef CARTACAMBIARCOLORDEUNAFICHA_H_
#define CARTACAMBIARCOLORDEUNAFICHA_H_

#include "CartaAbstracta.h"

class CartaCambiarColorDeUnaFicha : public CartaAbstracta{

private:
	unsigned jugadorAlternante;

  /*Pre:
  *Post: Cambia jugadorAlternante al numero del proximo jugador
  */
	void siguienteJugadorAlternante();

public:

  using CartaAbstracta::CartaAbstracta;
  
    /*Pre:
     *Post: Ejecuta el poder de la carta: se cambia el color de una ficha
     *a pedido del usuario. El color resultante de la ficha va a depender
     *del total de usos de esta carta, cambiando el color al jugador del mismo numero
     *Ejemplo: Se uso 5 veces esta carta y hay 6 jugadores
     *         el color resultante de la ficha sera del color del jugador Nr 6
     *Ejemplo: Se uso 5 veces esta carta y 5 jugadores
     *         el color resultante de la ficha sera del color del jugador Nr 1
     */
	void activar();
};



#endif /* CARTACAMBIARCOLORDEUNAFICHA_H_ */
