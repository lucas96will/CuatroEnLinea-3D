#ifndef _DECLARACIONES_H_
#define _DECLARACIONES_H_

#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "EasyBMP.h"
#include "EasyBMP_SimpleArray.h"
#include "EasyBMP_Font.h"
#include "EasyBMP_Geometry.h"

#define FICHAS_MINIMAS_PARA_GANAR 4
#define ESPACIO_LIBRE ""
#define TAMANIO_MINIMO FICHAS_MINIMAS_PARA_GANAR
#define CANTIDAD_DE_TIPOS_DE_CARTAS 6
#define CARTAS_JUGADOR_MAX 4
#define DIFICULTAD_FACIL 'F'
#define DIFICULTAD_MODERADA 'M'
#define DIFICULTAD_DIFICIL 'D'
#define CANTIDAD_MIN_JUGADORES 2
#define NO_ENCONTRO_CARTAS 999
#define PROBABILIDAD_FACIL 60
#define PROBABILIDAD_MODERADA 40
#define PROBABILIDAD_DIFICIL 10
#define PRIMERO 1
#define NINGUN_JUGADOR 0
#define CANTIDAD_JUGADORES_MAX 17
#define CON_DESCRIPCION true
#define CARTA_NULA 0
#define PORTAL_DISTANCIA_MINIMA 2
#define DISTANCIA_MINIMA_ENTRE_FICHAS 1

#define PROBABILIDAD_INICIAL_DE_GANAR_CARTA 30
#define PROBABILIDAD_MINIMA_DE_GANAR_CARTA 10
#define PROBABILIDAD_MAXIMA_DE_GANAR_CARTA 95
#define PROBABILIDAD_PERDIDA_DE_GANAR_CARTA 10
#define PROBABILIDAD_AUMENTADA_DE_GANAR_CARTA 20

#define IDENTIFICADOR_CARTA_CAMBIAR_COLOR "Convertir"
#define IDENTIFICADOR_CARTA_ELIMINAR_FICHA "Eliminar"
#define IDENTIFICADOR_CARTA_INTERCAMBIO "Intercambio"
#define IDENTIFICADOR_CARTA_CREAR_PORTAL "Portal"
#define IDENTIFICADOR_CARTA_IGNORAR_ANTERIOR "Ignorar"
#define IDENTIFICADOR_CARTA_ROBAR_CARTA "Robar"
#define NUMERO_CARTA_CAMBIAR_COLOR 1
#define NUMERO_CARTA_ELIMINAR_FICHA 2
#define NUMERO_CARTA_INTERCAMBIO 3
#define NUMERO_CARTA_PORTAL 4
#define NUMERO_CARTA_IGNORAR_ANTERIOR 5
#define NUMERO_CARTA_ROBAR 6

#define DESCRIPCION_CARTA_CAMBIAR_COLOR "Poderes misticos cambian el color de una ficha en una posicion elegida"
#define DESCRIPCION_CARTA_ELIMINAR_FICHA "Te otorga el poder de eliminar una ficha de cualquier jugador"
#define DESCRIPCION_CARTA_INTERCAMBIO "Esta Carta te permite intercambiar una ficha con una de alrededor de la misma"
#define DESCRIPCION_CARTA_CREAR_PORTAL "Esta carta te permite crear un portal de dos casilleros laterales"
#define DESCRIPCION_CARTA_IGNORAR_ANTERIOR "Usa esta carta para anular el turno del jugador anterior"
#define DESCRIPCION_CARTA_ROBAR_CARTA "Esta carta te otorga el poder de robar otra carta"

#define COLOR_J1 "AZUL"
#define COLOR_J2 "ROJO"
#define COLOR_J3 "VERDE"
#define COLOR_J4 "AMARILLO"

class Jugador;
class CartaAbstracta;
class CartaCambiarColorDeUnaFicha;
class CartaCrearPortal;
class CartaEliminarFicha;
class CartaIgnorarMovimiento;
class CartaIntercambioDeFichas;
class CartaRobarCarta;
class Tablero;
class CuatroEnLinea;
class Interfaz;
template <class T> class Celda;
template <class T> class ListaSimple;
template <class T> class Lista;
template <class T> class Nodo;


typedef struct{
  size_t x;
  size_t y;
  size_t z;
} Dimension;

typedef struct{
	int x;
	int y;
	int z;
} Corrimiento;

typedef Dimension Coordenada;

typedef struct {
  RGBApixel colorRGBA;
  std::string colorTerminal;
} Color;

#endif /* _DECLARACIONES_H_ */
