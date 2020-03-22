#ifndef _JUGADOR_H_
#define _JUGADOR_H_

#include "Declaraciones.h"
#include "Tablero.h"
#include "CuatroEnLinea.h"
#include "ListaSimple.h"
#include "CartaAbstracta.h"
#include "ExcepcionError.h"

/*Axiomas Jugador: El jugador asimila los rasgos del usuario, es el encargado de tener fichas
 * y de ingresarlas al tablero, de tener un mazo de cartas y poder usarlas.
 *El jugador tiene asociado si mismo un color del cual sus fichas van a ser
 *representadas sobre el tablero.
 *
 */
class Jugador {

  private:
    Dimension ultimaPosicionFichaIngresada;
    std::string color;
    int cantidadDeFichas;
    char dificultad; // Solo se usa para calcular las fichas iniciales
    bool esSuTurno;
    bool ganador;
    unsigned probabilidadDeCarta;
    ListaSimple<CartaAbstracta*>* manoDeCartas;
    Tablero* tablero;
    unsigned numero;

  private:
  /*pre:dificultad entre 1-3 (predefinidas)
   * DIFICULTAD_FACIL 1
   * DIFICULTAD_MODERADA 2
   * DIFICULTAD_DIFICIL 3

   *post:devuelve la cantidad de fichas segun la dificultad elegida
   */
  int fichasSegunDificultad(char dificultad, Dimension dimension);

  public:
    /*pre:Se elige la dificultad con la que empiezan los jugadores de 1 a 3. Se debe pasar
    * el tablero del juego por parametros
    *post:Se crea al jugador y listo para usarse, el color se da aleatoriamente
    *la cantidad de fichas varia segun la dificultad y empiezan con ninguna cartas
    *
    *Dificultad F (DIFICULTAD_FACIL) = x*y*z/2 Cantidad de fichas
    *Dificultad M (DIFICULTAD_MODERADA) = x*y*z/4 Cantidad de fichas
    *Dificultad D (DIFICULTAD_DIFICIL) = x*y*z/6 Cantidad de fichas
    *
    *BLANCO RESERVADO A ESPACIOS LIBRES
    *Colores segun el numero de jugadores empezando de:
    *Rojo, Azul, Amarillo, violeta, naranja, celeste, etc
    */
    Jugador(Tablero* tablero, unsigned numeroJugador ,char dificultad, unsigned fichasPorJugador , std::string color);

    /*
     *Pre:
     *Post:libera el espacio de memoria reservada
     */
    ~Jugador();



    /*pre:El jugador debe tener fichas disponibles
  	 *post:Se coloca una ficha del jugador en el espacio que desee
     *si el espacio esta ocupado, se le pedira que ingrese otro
  	 */
    void probabilidadDeGanarCarta(Coordenada posicionIngresada);

    /*pre:
  	 *post:Devuelve el color de las fichas del jugador
  	 */
    std::string consultarColor();

    /*pre: el identificadorCartas varia entre 1 y 6 (Max tipo de cartas disponibles)
    *post:devuelve la posicion de la carta en el vector cartas o -1(NO_ENCONTRO_CARTAS) si no la encontro
    */
    unsigned consultarCarta(unsigned identificadorCarta);

    /*pre:El jugador debe haber ingresado al menos una ficha en una posicion
  	 *post:devuelve la posicion de la ultima ficha ingresada
  	 */
    Dimension consultarUltimaPosicion();

    /*pre:
  	 *post:Devuelve la cantidad de fichas restantes del jugador
  	 */
    bool puedeRecibirCarta();

    /*pre:
  	 *post:Devuelve la cantidad de fichas restantes del jugador
  	 */
    int consultarCantidadDeFichas();

    /*pre:
     *post:devuelve la cantidad de cartas que tiene el jugador en dado momento
     */
    int consultarCantidadDeCartas();

    /*pre:
     *post:descuenta una ficha de cantidadDeFichas
     */
     void descontarFicha();

     /*pre:
      *post:devuelve el numero del jugador
      */
     unsigned consultarNumero();

    /*pre:
  	 *post:Devuelve las cartas del jugador
     *
	 */
    ListaSimple<CartaAbstracta*>* obtenerCartas();

    /*pre:Debe haber una carta en la posicion dada
   	 *post:Elimina la carta de la mano en la posicionCarta
      *
   	 */
    void descartarCarta(unsigned posicionCarta);


    /*
   	 *post:determina si el jugado gano la partida
      *
   	 */
    void asignarSiGanoPartida(bool estado);

    /*
   	 *post:Devuelve si el jugador gano la partida
      *
   	 */
    bool consultarSiGanoLaPartida();


    /*pre:El jugador debe tener la carta
  	 *post:Usa una carta a disposicion del jugador, devuelve la carta utilizada
     *
  	 */
    void usarCarta(unsigned posicionCarta);

    /*pre:
     *
     *post: cambia el color asociado al jugador
     */
    void cambiarColor(std::string nuevoColor);

    /*
     *pre:El jugador no debe tener el mano de sus cartas llena (Max 4 cartas)
     *post:agrega nuevaCarta a su mano
     */
    void recibeCarta(CartaAbstracta* nuevaCarta);

    /*
     *pre:
     *post:devuelve la probabilidad que tiene de ganar carta
     */
    unsigned probabilidadGanarCarta();

    /*
     *pre:
     *post:decrementa la probabilidad de ganar carta
     */
    void bajarProbabilidadGanarCarta();

    /*
     *pre:
     *post:aumenta la probabilidad de ganar una carta
     */
    void subirProbabilidadGanarCarta();

    /*
     *pre:
     *post:estabiliza la probabilidad de ganar una carta
     */
    void estabilizarProbabilidadGanarCarta();

    /*
     *pre:la posicion de la ficha a ingresar es valida dentro del tablero
     *post:el jugador ingresa una ficha en una posicion del tablero
     */
    void ingresarFicha();

    /*
     *pre:
     *post:inicia el turno del jugador
     */
    void iniciarTurno();

    /*
     *pre:
     *post:termina el turno del jugador
     */
    void terminarTurno();

    /*
     *pre:
     *post:devuelve true si es el turno del jugador, false en otro caso
     */
    bool consultarSiEsSuTurno();

};

#endif // _JUGADOR_H_
