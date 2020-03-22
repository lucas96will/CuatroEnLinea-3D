
#ifndef CUATROENLINEA_H_
#define CUATROENLINEA_H_

#include "Declaraciones.h"
#include "Tablero.h"
#include "Jugador.h"
#include "Interfaz.h"
#include "ExcepcionError.h"

/*Axiomas de CuatroEnLinea: CuatroEnLinea es la clase que se encarga del funcionamiento
 *del juego, el cual tiene acceso al tablero, a los jugadores creados, a los tipos
 *de cartas, a la dificultad del juego.
 */
class CuatroEnLinea{

  private:

    unsigned dificultad;
    ListaSimple<Jugador*>* jugadores;
    Tablero* tablero;
    unsigned jugadorActual;
    ListaSimple<CartaAbstracta*>* tiposDeCartas;
    unsigned cantidadTotalDeFichasDeJugadores;
    unsigned cantidadMaximaDeFichasLibres;

  private:
    /*pre:
    *post:crea un arreglo de jugadores, cada uno con una cantidad de fichas
    *de fichasPorJugador, carga a cada uno un color especifico y crea la lista de
    *tipos de cartas.
    */
    void crearJugadores(int fichasPorJugador, unsigned int cantidadDeJugadores);

    /*
     *Pre:
     *Post:aumenta en uno al jugador actual.
     */
    void siguienteJugador();

    /*
     *Pre:
     *Post:devuelve la cantidad de fichas basada en la dificultad del juego
     */
     int fichasSegunDificultad();

      /*pre:
      *post: devuelve si gano algun jugador de la siguiente forma:
      *      0: Sigue el juego
      *      1: si gano el jugador 1
      *      2: si gano el jugador 2
      *      ...
      *      n: si gano el jugador n
      */
     Jugador* estadoDelJuego();

     /*
      *Pre:
      *Post:Devuelve true si el tipo de carta es designada en base a una probablidad
      *entre usos del mismo tipo y la base de la carta mas repetida.
      */
     bool esCartaDesignada(CartaAbstracta* carta,unsigned baseDeCartaDeMasUso,unsigned baseDeCartaMasRepartida);

     /*
      *Pre:
      *Post:devuelve true o false dependiendo de una posibilidad balanceada
      *entre casos totales y casos posibles
      */
     bool sortearPosibilidadesBalanceado(unsigned casosPosibles, unsigned casosTotales);

     /*
      *Pre:
      *Post:devuelve true o false dependiendo en un sorteo entre casos casosPosibles
      *y casos totales
      */
     bool sortearPosibilidades(unsigned casosPosibles, unsigned casosTotales);

     /*
      *Pre:
      *Post:Aumenta en 1 jugadorActual si el jugadorActual no es el ultimo y devuelve false
      *si es el ultimo, lo reestablece al primer jugador y devuelve true
      */
     bool esElUltimoJugador();

     /*
      *Pre:
      *Post:Carga los tiposDeCartas predeterminados y los deja listo para usarse
      *
      */
     void cargarTiposCartas();

     /*
      *Pre:
      *Post:Genera una nueva carta y se le agrega al mazo del jugador
      *se imprime por pantalla un mensaje de la carta ganada
      *aumenta el numero de veces repartida de la carta
      */
     void darCartaAlJugador(Jugador* jugador);

     /*
      *Pre:
      *Post:devuelve true o false dependiendo de la probabilidadDeGanarCarta
      */
     bool ganaCarta(unsigned probabilidadDeGanarCarta);

     /*
      *Pre:
      *Post:El jugador recibe una carta en base a una probabilidad
      */
     void probabilidadGanarCarta(Jugador* jugador);

     /*pre:Para que el jugador eliga una carta que jugar debera tener alguna disponible
      *post:Se muestra por consola las cartas en mano y se le pide al usuario
      *ingresar cual carta quiere jugar.
      */
     void etapaJugarCarta(Jugador* jugadorActivo);

     /*
      *pre: posicionCarta debe estar dentro del rango [1 - jugador->obtenerCartas->contarElementos()]
      *post:Se ejecuta una accion dependiendo de la posicion de la carta antes de ser usada
      *
      */
     void preUsoDeCartas(Jugador* jugadorActivo, unsigned posicionCarta);

     /*
      *pre:
      *post: Devuelve el jugador ganador, en otro caso devuelve NULL
      *
      */
     Jugador* obtenerGanador();

     /*
      *pre:
      *post: resta la cantidad de fichas que pueden ingresarse al tablero, como tambien la cantidad
      *		 de fichas totales entre todos los jugadores
      *
      */
     void restarFichas();


  public:

    /*
     *Pre:la posicion no puede ser mayor a la cantidad de jugadores actuales o menor a 1
     *Post:devuelve el puntero asociado al jugador en la posicion dada
     */
    Jugador* obtenerJugador(unsigned posicion);

    /*
     *Pre:
     *Post:devuelve la cantidad de jugadores
     */
    unsigned obtenerCantidadDeJugadores();

    /*
     *Pre:
     *Post:devuelve el numero del jugador actual
     */
    unsigned obtenerJugadorActual();


    /*pre:
     *post:devuelve el puntero al tablero
     */
    Tablero* consultarTablero();

    /*
     *Pre:
     *Post:Inicia el juego
     */
    void iniciarJuego();

    /*
     *Pre:
     *Post:inicia la ronda que consiste en:
     *1.iniciar el turno del jugador
     *2.iniciar la etapa de jugar cartas del jugador
     *3.inicia el ingreso a la ficha del jugador
     *4.posibilidad de darle carta al jugador
     *5.termina el turno del jugador
     *6.verifica si el jugador ha ganado
     *7.llama al siguiente jugador
     *se repite el proceso hasta que:
     *algun jugador gane o empaten al no poder ingresar mas fichas en el tablero
     *devuelve el el jugador ganador o NULL si ninguno ha formado cuatro en linea
     */
    Jugador* ronda();

    /*
     *Pre:
     *Post:devuelve true si posibleGanador es el ganador, false en otro caso
     */
    bool hay(unsigned posibleGanador);

    /*
     *Pre:
     *Post:devuelve true si la carta Designada existe como tipo de carta
     *dentro de CuatroEnLinea
     */
    bool hay(CartaAbstracta* cartaDesignada);

    /*
     *Pre:
     *Post:develve una carta de un tipo de carta aceptada dentro del juego
     */
    CartaAbstracta* designarUnaCartaParaJugador();


    /*
     *Pre:
     *Post:Devuelve si hay empate, false en otro caso
     */
    bool hayEmpate();

    /*
     *Pre:
     *Post:devuelve un numero igual a las veces repartida de la carta mas repartida
     */
    unsigned vecesRepartidaCartaMasRepartida();

    /*
     *Pre:
     *Post:devuelve el numero igual a las veces usada de la carta mas usada
     */
    unsigned vecesDeUsoCartaMasUsada();

    /*
     *Pre:
     *Post:Devuelve la carta con menos apariciones durante la ejecucion del juego
     */
    CartaAbstracta* cartaConMenorApariciones();

    /*pre:
     *post:
     *1. muestra la presentacion del juego
     *2. le pide al usuario que ingrese las dimensiones del juego
     *3. le pide al usuario que ingrese la dificultad del juego
     *4. le pide al usuario que ingrese la cantidad de jugadores
     *5. crea los jugadores
     *6. crea el tablero
     *7. Muestra por pantalla a los jugadores con su respectivo color
     *8. asigna al jugadorActual
     *9. inicia el juego
     */
    CuatroEnLinea();

    /*pre:
     *post:libera la memoria reservada
     */
     ~CuatroEnLinea();

};

#endif //CUATROENLINEA_H_
