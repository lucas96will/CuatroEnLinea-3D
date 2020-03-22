#ifndef CARTAIGNORARMOVIMIENTO_H_
#define CARTAIGNORARMOVIMIENTO_H_

#include "CartaAbstracta.h"

class CartaIgnorarMovimiento : public CartaAbstracta {

	private:

	Jugador* buscarUltimoJugador();

	public:

	using CartaAbstracta::CartaAbstracta;

    /*Pre:
     *Post:Se ignora el movimiento del jugador anterior al jugador que uso la carta
     */
    void activar();
};


#endif /* CARTAIGNORARMOVIMIENTO_H_ */
