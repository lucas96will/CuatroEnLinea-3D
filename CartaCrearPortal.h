#ifndef CARTACREARPORTAL_H_
#define CARTACREARPORTAL_H_

#include "CartaAbstracta.h"


class CartaCrearPortal : public CartaAbstracta {

private:

  /*Pre: casilleroUno y casilleroDos deben ser validas dentro del tablero
   *Post:En caso de que haya un jugador ganador, devuelve el mismo. En otro caso
   *     devuelve un Jugador* NULL
   *
   */
  Jugador* hallarGanadorDelPortalUniendo(Coordenada casilleroUno, Coordenada casilleroDos);


public:

	using CartaAbstracta::CartaAbstracta;

	 /*Pre: casilleroUno y casilleroDos deben ser casi casilleros laterales
    *Post: Ejecuta la habilidad de esta carta: se unen dos casilleros laterales
    *      dados por posicionUno y posicionDos
    *      continuando la secuencia de formar 4 en linea por un momento
    *      Modifica el 'Jugador*' al ganador en caso de que se haya formado 4 en linea
    *      en otro caso se modifica a NULL
    *
    */
    void activar();
};





#endif /* CARTACREARPORTAL_H_ */
