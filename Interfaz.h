#include "Declaraciones.h"
#include "CuatroEnLinea.h"
#include "Tablero.h"
#include "EasyBMP.h"
#include "EasyBMP_SimpleArray.h"
#include "EasyBMP_Font.h"
#include "EasyBMP_Geometry.h"
#include <iostream>


#define FICHA "██"//"■"
#define MEDIA_FICHA_SUPERIOR "▄▄"
#define MEDIA_FICHA_INFERIOR "▀▀"
#define BORDE_SUPERIOR "█▀▀▀▀"
#define BORDE_INFERIOR "█▄▄▄▄"
#define BORDE_INFERIOR_SIN_ESQUINA "▀▀▀▀▀"
#define BORDE_LATERAL "█"
#define LATERAL_SUPERIOR "▀▀▀▀"
#define LATERAL_INFERIOR "▄▄▄▄"
#define ESPACIO_VACIO "    "
#define CASO_UNO 1
#define CASO_DOS 2
#define CASO_TRES 3
#define LATERAL_IZQUIERDO "█          "
#define LATERAL_DERECHO "          █"
#define LATERAL_IZQUIERDO_ESQUINA "█▄▄▄▄▄▄▄▄▄▄"
#define LATERAL_DERECHO_ESQUINA "▄▄▄▄▄▄▄▄▄▄█"
#define BORDE_SUPERIOR_TABLERO "▄▄▄▄▄▄▄▄▄▄▄"
#define BORDE_INFERIOR_TABLERO "▀▀▀▀▀▀▀▀▀▀▀"
#define GRAN_ESPACIO_VACIO "          "
#define RELLENO_BAJO "▄"
#define RELLENO_ALTO "▀"
#define RELLENO " "
#define RELLENO_MEDIO "█"

#define AZUL "\e[1;94m"
#define ROJO "\e[0;31m"
#define VERDE "\e[1;92m"
#define AMARILLO "\e[1;93m"
#define BLANCO "\e[1;97m"
#define NARANJA "\e[38;5;208m"
#define ROSADO "\e[38;5;200m"
#define CELESTE "\e[38;5;117m"
#define OCRE "\e[38;5;94m"
#define ROSA "\e[1;95m"
#define HOJA "\e[38;5;28m"
#define AQUAMARINA "\e[0;36m"
#define MARRON "\e[0;33m"
#define PURPURA "\e[0;35m"
#define GRIS "\e[0;90m"
#define BORDO "\e[38;5;52m"
#define MARINO "\e[1;34m"
#define RESET "\e[0m"

/*Pre:Tiene que ser valida la dimension ingresada
 *Post:Le pide al usuario ingresar las dimensiones del tablero y devuelve
 *la dimension ingresada
 */
Dimension pedirDimensionDelTablero();

/*Pre:
 *Post:le pide la cantidad de jugadores al usuario
  *    y la devuelve.
 */
int pedirCantidadDeJugadores(unsigned cantidadDeCeldas);

/*Pre:Las dificultades del juego pueden ser las siguientes:
 * DIFICULTAD_FACIL = 'f'
 * DIFICULTAD_MODERADA = 'm'
 * DIFICULTAD_DIFICIL = 'd'
 *Post:devuelve la dificultad ingresada representada por un char
 */
char pedirDificultadDeJuego();

/*Pre:el tablero debe estar iniciado
 *Post:Imprime el color de la ficha, en caso de estar vacia imprime un lugar vacio
 */
void imprimirFicha(std::string color, unsigned caso);

/*Pre:
 *Post:devuelve true en caso de que la dimension ingresada sea valida dentro
 *del tablero
 */
bool esValidaLa(Dimension dimensionIngresada);

/*Pre:Las dificultades del juego pueden ser las siguientes:
 * DIFICULTAD_FACIL = 'f'
 * DIFICULTAD_MODERADA = 'm'
 * DIFICULTAD_DIFICIL = 'd'
 *Post: Siempre devuelve verdadero si la dificultad ingresada es alguna definida
 *previamente, false en otro caso
 */
bool esValidaLa(char dificultadIngresada);

/*Pre: debe estar asignado la cantidad de jugadores y el tamaño del tablero
 *Post: valida si la cantidad de jugadores x la celdas es valida.
 */
bool esValidaLa(unsigned cantidadDeJugadores, unsigned cantidadDeCeldas);

/*Pre:
 *Post:
 */
void mostrarMenu();

/*Pre: Necesita tener un tablero pregenerado
 *Post: Imprime el tablero en la consola
 */
void mostrar(Tablero* tablero);

void imprimirPorcionDeTableroSuperior(size_t largo, size_t altura, Dimension delTablero, Tablero *tablero);
void imprimirPorcionDeTableroIntermedia(size_t largo, size_t altura, Dimension delTablero, Tablero *tablero);

/*Pre:Necesita tener un array de jugadores y cantidadDeJugadores inicializados
 *Post:imprime por consola los jugadores y su color asignado
 */
void mostrar(ListaSimple<Jugador*>* jugadores);

/*Pre:
 *Post:muestra por consola al numeroJugador con su color
 */
void mostrarJugador(unsigned numeroJugador, std::string color);

/*Pre:
 *Post:muestra por consola la cantidad de cartas de cada jugador excepto por el jugador activo
 *Ejemplo: Con 4 jugadores y el jugador activo Nr 3, se muestra
 *		  Cartas en mano : 3 del Jugador N°1
 *	  	  Cartas en mano : 2 del Jugador N°2
 *		  Cartas en mano : 1 del Jugador N°4
 *
 *
 */
void mostrarJugadoresParaRobar(ListaSimple<Jugador*>* jugadores);

/*Pre:
 *Post:imprime por pantalla al jugadorGanador
 */
void mostrarResultados(unsigned jugadorGanador, std::string color);

/*Pre:
 *Post:imprime por consola el color asociado a la ficha en la celda, si no hay ficha
 *     en la celda, se imprime un espacio en blanco
 */
void imprimirFicha(Jugador* ficha, unsigned caso);

/*Pre:
 *Post:devuelve true si la celda esta vacia (no hay fichas) o false en otro caso
 */
bool esCeldaVacia(Jugador* celda);

/*Pre:
 *Post:imprime por consola el numero de ronda
 */
void cartelNroDeRonda(unsigned numero,unsigned cantidadDeFilas);

/*Pre:
 *Post:Se imprime por pantalla la presentacion del juego
 */
void mostrarPresentacionJuego();


/*Pre:
 *Post:Se imprime por pantalla al ganador de la instancia
 */
void mostrarResultados();

/*Pre:
 *Post:devuelve true si el tablero cumple con los requisitos minimos de las dimensiones
 *     para las cuales se puedan formar 4 en linea en las 3 dimensiones (xyz)
 */
bool esTableroMinimo(size_t dimension1,size_t dimension2,size_t dimension3);

/*Pre:La ficha ingresada es valida dentro de las dimensiones del tablero
 *Post: devuelve la coordenada en la que se puede ingresar la ficha dentro del tablero
 */
Coordenada pedirIngresarFicha(Tablero* tablero, std::string color);

/*Pre: Se necesita tener una mano de cartas inicializada.
 *Post:Muestra por pantalla la mano de cartas (de algun jugador)
 */
void mostrar(ListaSimple<CartaAbstracta*>* mano);

/*Pre:
 *Post:Muestra por pantalla un texto, del Turno del numero de jugador .
 */
void mostrar(Jugador* jugador, unsigned cantidadDeFilas);


/*Pre:
 *Post:Muestra por pantalla un texto, una opcion para ingresar.
 *devuelve true si el usuario ingresar opcionVerdadera, false si ingreso opcionFalsa
 */
bool preguntar(std::string texto, char opcionVerdadero, char opcionFalsa);

/*Pre:
 *Post:Muestra por pantalla si el usuario quiere robar una carta
 *devuelve true si el usuario quiere robar una carta, false en otro caso
 */
bool preguntaRobarCarta();

/*Pre:
 *Post:Muestra por pantalla si el usuario quiere robar una carta al jugador
 *devuelve true si el usuario quiere robarle una carta, false en otro caso
 */
bool preguntaRobarCartaJugador();

/*
 *Post:Le pide al usuario una carta a robar de cierta mano de otro jugador
 *Pre:devuelve el identificador de la carta a robar
 */
unsigned obtenerCualCartaRobarAlJugador(ListaSimple<CartaAbstracta*>* manoDeCartas);

/*
 *Pre:
 *Post:devuelve true si la carta es incorrecta y no se le puede robar
 *     false en otro caso
 */
bool esCartaValida(ListaSimple<CartaAbstracta*>* manoDeCartas, unsigned posicionCarta);

/*
 *Pre:
 *Post:Devuelve true si el jugador es incorrecto para robar
 *     o false en otro caso
 */
bool esValidoElJugadorParaRobar(ListaSimple<Jugador*>* jugadores, unsigned posicionJugador, Jugador* jugadorActual);

/*
 *Pre:cantidadJugadores debe ser el tope de jugadores en el juego
 *Post:devuelve el jugador a ser robado (por uso de la carta especial)
 */
Jugador* obtenerJugadorASerRobado(ListaSimple<Jugador*>* jugadores, Jugador* jugadorActual);

/*
 *Pre:
 *Post:Devuelve si es posible ingresar la ficha en la posicion ingresada
 */
bool sePuedeIngresarFichaEn(Dimension &posicion, Tablero* tablero);

/*
 *Pre:
 *Post:devuelve true si hay jugadores con cartas disponibles a ser robadas
 */
bool consultarJugadorJugarCarta();

/*Le pide al usuario que ingrese una carta de su mano a jugar
 *Pre:
 *Post:devuelve un identificador de la carta que eligio el usuario para jugar
 */
unsigned elegirCartaParaJugar(ListaSimple<CartaAbstracta*>* manoDeCartas);

/*
 *Pre:
 *Post:devuelve true si la posicion de cartas esta dentro del rango o false en otro caso
 */
bool rangoPosicionValida(ListaSimple<CartaAbstracta*>* manoDeCartas, unsigned posicion);

/*
 *Pre:
 *Post:devuelve la  coordenada de la ficha que va a ser ingresada dentro de tablero
 */
Coordenada pedirCoordenadaDeFicha(Tablero* tablero, std::string colorJugador, std::string descripcionPosicion);



/*
 *Se pide por consola la fila, columna y altura de una coordenada dentro de tablero
 *Tambien se puede ingresar una descripcion de la posicion a ingresar por ejemplo:
 *Ingrese la fila <descripcionPosicion>
 *Post:Devuelve la coordenada, dentro del rango de tablero, que el usuario ingreso
 */
Coordenada pedirPosicion(Tablero* tablero, std::string descripcionPosicion, std::string color);

/*
 *Post: devuelve true si posicionUno = posicionDos, false en otro caso
 */
bool sonIguales(Coordenada* posicionUno, Coordenada* posicionDos);

/*Se le pide al usuario dos casilleros laterales del tablero
 *Post:se modifica casilleroUno y casilleroDos a casilleros laterales
 *     del tablero
 */
void obtenerCasillerosLaterales(Coordenada &casilleroUno, Coordenada &casilleroDos, Tablero* tablero, std::string color);

/*
 *Post: si el valor del dato es falso, se imprime texto por pantalla
 */
void imprimirSiNo(bool valor, std::string texto);
/*
 *
 */
void mostrarMensaje(std::string texto, std::string color);
std::string repetir(char letra, unsigned cantidadDeVeces);
std::string repetir(std::string letra, unsigned cantidadDeVeces);
std::string extraerIzquierda(std::string texto, unsigned cantidadDePalabras);
std::string extraerDerecha(std::string texto, unsigned cantidadDePalabras);
std::string extraerCentrado(std::string texto, unsigned cantidadDePalabras);
std::string justo(std::string texto, unsigned cantidadDePalabras);
std::string justoCentrado(std::string texto, unsigned cantidadDePalabras);
std::string justoIzquierda(std::string texto, unsigned cantidadDePalabras);
unsigned cantidadLetras(unsigned numero);
unsigned cantidadLetras(std::string texto);
void imprimirCartelDe(unsigned altura, unsigned largoTablero);
void imprimirSuperficieDeTablero(unsigned largoTablero);
void imprimirFondoDeTablero(unsigned largoTablero);
void imprimirMiniTablero(unsigned largoTablero, unsigned dimensionY);
unsigned calcularCorrimiento(unsigned largo);

void crearMatriz(BMP &Sample, int filas,int columnas,int origenX, int origenY,int grosor, RGBApixel color);
void crearFicha(BMP & Sample,int origenX, int origenY,RGBApixel color);
void mostrarBPM(Tablero * tablero);
RGBApixel buscarColorRGBA(std::string colorJugador, ListaSimple<Color>* colores);
void inicializarColores(ListaSimple<Color>* colores);
