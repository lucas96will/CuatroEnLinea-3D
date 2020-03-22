#ifndef CARTAELIMINARFICHA_H_
#define CARTAELIMINARFICHA_H_

#include "CartaAbstracta.h"

class CartaEliminarFicha : public CartaAbstracta {

   public:

	using CartaAbstracta::CartaAbstracta;

    /*Pre:debe haber al menos una ficha en el tablero
     *Post: Se elimina una ficha del tablero a peticion del usuario
     *      luego se ordena correspondientemente las fichas
     */
    void activar();
};



#endif /* CARTAELIMINARFICHA_H_ */
