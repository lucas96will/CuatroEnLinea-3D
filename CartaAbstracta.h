#ifndef CartaAbstracta_h
#define CartaAbstracta_h

#include "Declaraciones.h"
#include "CuatroEnLinea.h"
#include "Interfaz.h"
#include "Tablero.h"


/*Axiomas de Carta:
 *La carta es un objeto cuyo fin es darle al jugador una ventaja sobre
 *sus pares. Este objeto puede tener varios efectos sobre el juego dependiendo
 *del tipo de carta que hereda y varia segun el identificador
 *
 *CARTA_CAMBIAR_COLOR 1
 *CARTA_ELIMINAR_FICHA 2
 *CARTA_INTERCAMBIO 3
 *CARTA_CREAR_PORTAL 4
 *CARTA_IGNORAR_ANTERIOR 5
 *CARTA_ROBAR_CARTA 6
 *
 */


class CartaAbstracta {

protected:

    std::string identificador;
    std::string descripcion;
    Tablero* tablero;
    ListaSimple<Jugador*>* jugadores;
    unsigned vecesUsada;
    unsigned vecesRepartida;
    unsigned identificadorNumero;

public:

    /*Pre:
     *Post: Se le asigna una descripcion dependiendo del tipo de carta previamente
     *      definido y la deja lista para usarse
     */
    CartaAbstracta(Tablero* tableroJuego, ListaSimple<Jugador*>* listaJugadores, unsigned suNumero, std::string suIdentificador, std::string suDescripcion);

    /*Pre:
    *Post: Devuelve el identificador asignado a la carta
    */
    std::string consultarIdentificador();

    /*Pre:
     *Post: devuelve la descripcion asignada a la carta
     */
    std::string consultarDescripcion();

    /*Pre:
     *Post: Devuelve el identificador numero de la carta
     */
    unsigned obtenerIdentificadorNumero();

    /*Pre:  depende de la clase de carta
    *Post:  se modifica dependiendo de la carta ciertos aspectos del juego
    */
    virtual void activar(){}

    /*Pre:
    *Post: Devuelve la cantidad de veces usada
    */
    unsigned obtenerVecesUsada();

    /*Pre:
    *Post: Devuelve la cantidad de veces repartida
    */
    unsigned obtenerVecesRepartida();

    /*Pre:
    *Post: devuelve cuantas veces se repartio la carta
    */
    unsigned obtenerVecesApariciones();

    /*Pre:
    *Post: devuelve el jugador actual
    */
    Jugador* obtenerJugadorActual();

    /*Pre:
    *Post: aumenta la cantidad de veces usada en 1
    */
    void aumentarVecesUsada();

    /*Pre:
    *Post: aumenta la cantidad de veces repartida en 1
    */
    void aumentarVecesRepartida();

    /*Pre:
    *Post: se libera el espacio de memoria reservado
    */
    virtual ~CartaAbstracta(){}

};

#endif /* CartaAbstracta_h */
