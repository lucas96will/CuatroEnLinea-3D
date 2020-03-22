#ifndef _TABLERO_H_
#define _TABLERO_H_


#include <string>
#include <iostream>

#include "Declaraciones.h"
#include "Celda.h"
#include "Jugador.h"
#include "Lista.h"
#include "ExcepcionError.h"

typedef Lista<Jugador*> Columna;
typedef Lista<Columna*> Fila;
typedef Lista<Fila*> Base;


/*Axiomas de Tablero: El tablero se encarga de regular las posiciones de las fichas
 *que pueden ser consultadas, cambiadas o de poder realizar ciertas operaciones sobre
 *ellas. En el tablero es donde se ingresan las fichas de los jugadores.
 *
 */
class Tablero {

  public:

	/*
	 * pre:
	 * post: cambia el color de la ficha en la posicion indicada
	 */
	void cambiarColorEnCeldaEn(Coordenada posicion, Jugador* jugador );

   /*
    *pre:La dimension ingresada debe ser valida.
    *    Las dimensiones minimas del tablero pueden ser:
    *    4x4x1 (x,y,z)
    *    4x1x4 (x,y,z)
    *    1x4x4 (x,y,z)
    *post:Se crea el tablero con la dimensionIngresada y se deja listo para usarse
    */
    Tablero(Dimension dimensionIngresada);


    /*
    *Pre:Las dimensiones minimas del tablero pueden ser:
    *    4x4x1 (x,y,z)
    *    4x1x4 (x,y,z)
    *    1x4x4 (x,y,z)
    post:Devuelve true si el tamanio del tablero es valido, false en otro caso
    */
    bool tamanioValido();

    /*
    *pre:
    *post:devuelve true si la posicionIngresada esta dentro del rango del tablero
    *     false en otro caso
    */
    bool esValidaLa(Coordenada posicionIngresada);

    /*
     *pre:
     *post:devuelve la cantidad de celdas que tiene el tablero
     */
    unsigned obtenerCantidadDeCeldas();

    /*
     *pre:
     *post:Devuelve las dimensiones del tablero
     */
    Dimension consultarDimensiones();


    /*
     *pre:La posicionIngresada debe ser valida en el tablero
     *post:Agrega una ficha en una celda del tablero
     */
    void agregarFichaEnCelda(Coordenada posicionIngresada, Jugador* jugador);

    /*
     *pre:La coordenadaFicha debe ser valida dentro del tablero
     *post:devuelve la celda de la ficha
     */
    Jugador* obtenerFichaEnCelda(Coordenada posicionFicha);

    /*
     *pre:La coordenadaFicha debe ser valida dentro del tablero
     *post:devuelve el color de la ficha en la celda
     */
    std::string obtenerColorFichaEnCelda(Coordenada posicionFicha);


    /*
     *pre:la posicion debe ser valida dentro del tablero
     *post:remueve la ficha en la posicion del tablero
     */
    void eliminarFicha(Coordenada posicion);

    /*
     *pre:
     *post: Develve la distancia entre ambas posiciones
     *		Por ejemplo
     *		posicionUno = {1,1,1}
     *		posicionDos = {2,2,2}
     *		La distancia es 1
     *
     *		posicionUno = {1,1,1}
     *		posicionDos = {1,1,3}
     *		La distancia es 2
     */
    unsigned distanciaEntre(Coordenada posicionUno, Coordenada posicionDos);

    /*
     *pre:
     *post:Devuelve true si 'posicionUno' es igual a 'posicionDos'
     */
    bool sonIguales(Coordenada posicionUno, Coordenada posicionDos);

//
//
// falta
//
//
    bool hayCuatroEnLinea(Coordenada posicionIngresada, Jugador* elegido);
//
//
// falta
//
//
    unsigned int obtenerFichasMaximasEnLinea(Coordenada posicionIngresada);

    /*
     *pre: this->esValidaLa(posicion)
     *post:Devuelve la altura de la columna ubicada en 'posicion'
     */
    size_t obtenerAlturaDeLa(Coordenada posicion);

    /*
     *
     *post:Devuelve verdadero si la 'posicion' se encuentra en una posicion lateral
     *     dentro del tablero por ejemplo:
     *     (1,y,z), (x,1,z), (x,this->tamanio.y, z) son laterales
     */
    bool esLateralEl(Coordenada casillero);

    /*
    *pre:Se debio agregarFichaEnCelda al menos una vez
    *post:Devuelve el ultimo jugador en ingresar ficha
    */
    Jugador* obtenerUltimoEnIngresarFicha();

    /*
    *pre:
    *post:Se libera el espacio de memoria reservado utilizado
    */
    ~Tablero();

    //void descenderFicha(Dimension posicion);

  private:
    Dimension tamanio;
    Base* tablero;
    Jugador* ultimoEnJugar;

    /* El siguiente atributo esta pensado para tener una lista con 13 de los 26
       corrimientos posibles, para obtener la coordenada de una celda vecina, es
       decir, si tengo una coordenada de mi celda A = (x, y, z) un corrimiento
       posible para obtener una de las celdas vecinas seria, c = ( 1, 0, 0), de
       modo que si sumo la coordenada de el corrimiento c a la coordenada de la
       celda A obtendria V = (x+1, y, z), la coordenada de una posible celda vecina.
       Basta con tener 13 de los 26 corrimientos posibles ya que los otros 13 son
       los mismos pero con signos cambiados.*/

    ListaSimple<Corrimiento>* corrimientosPosibles;



    /*** Metodos para Cubo ***/

    /*
     *pre:Se debe haber ingresado un tamanio
     *post:Arma el tablero de acuerdo al tamanio y lo deja listo para usarse
     */
    void armarTablero();

    /*
     *pre:
     *post:Inicializa todos los corrimientos posibles de una posicion a sus
     *posiciones consiguientes.
     */
    void inicializarCorrimientosPosibles();

    /*
     *pre:
     *post:Agrega un corrimiento posible a this->corrimientosPosibles.
     */
    void agregarCorrimiento(int x, int y, int z);

    /*
     *pre:
     *post:libera el espacio reservado en memoria usado para armar el tablero
     */
    void desarmarTablero();


    /*
     *pre:
     *post:devuelve true si la posicion ingresada no es negativa, false en otro caso
     */
    bool posicionMayorACero(Dimension posicionIngresada);

    /*
     *pre:
     *post:devuelve true si la posicion ingresada coincide con el color ingresado
     */
    bool posicionCoincideConElColorIngresado(Dimension posicion, std::string colorIngresado);


    /*
     *pre:la posicion debe ser valida dentro del tablero en cuestion
     *post:copia el contenido de posicionACopiar dentro de posicion
     */
    void copiarContenidoCelda(Coordenada posicion, Coordenada posicionACopiar);

    /*
     *pre: Los componentes X e Y de la coordenada ingresada deben estar entre
     *[1, this->tamanio.x] y [1, this->tamanio.y] respectivamente.
     * La coordenada recibida debe estar en el plano XY, por lo que su componente
     *z debe ser igual a 0, Ejem: (1, 2, 0), (3, 8, 0).
     *post: Devuelve la columna ubicada en esa posicion del plano o NULL, en caso
     *de que la misma no exista.
     */
    Columna* obtenerColumnaEn(Coordenada planoXY);

    /*
     *post:devuelve el mayor numero entre numeroUno y numeroDos
     */
    unsigned int devolverElMayorEntre(unsigned numeroUno, unsigned numeroDos);

    bool tieneCuatroEnLineaEn(Coordenada estaPosicion,
                              Corrimiento haciaEstaDireccion,
                              unsigned &contadorDeFichasIguales,
							  Jugador* fichaInicial);

    Coordenada suma(Coordenada posicionIngresada, Corrimiento corrimiento);

    Corrimiento ContrarioDe(Corrimiento corrimientoActual);

    Jugador* buscarFichaVecina(Coordenada posicionFichaVecina);



};

#endif /* Tablero_h */
