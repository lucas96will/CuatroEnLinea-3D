#ifndef CARTAINTERCAMBIODEFICHAS_H_
#define CARTAINTERCAMBIODEFICHAS_H_

#include "CartaAbstracta.h"

class CartaIntercambioDeFichas : public CartaAbstracta {

   public:

	using CartaAbstracta::CartaAbstracta;

	   /*Pre:Deben haber al menos dos fichas vecinas entre si para intercambiar
           dentro del tablero
      *Post:Se cambian de lugar las dos fichas
      */
    void activar();
};



#endif /* CARTAINTERCAMBIODEFICHAS_H_ */
