#ifndef _Lista_H_
#define _Lista_H_

#include <iostream>
#include "Celda.h"
#include "ExcepcionError.h"



#ifndef NULL
#define NULL 0
#endif /*NULL*/

/*
*Una lista es una coleccion dinamica de elementos dispuestos en una secuencia
*
*Define operaciones para agregar, remover, acceder y cambiar elementos en
*cualquier posicion.
*
*Tiene un cursor que permite recorrer todos los elementos secuencialmente
*/
template <class T> class Lista {

  private:

    unsigned int tamanio;
    Celda<T>* primero;
    Celda<T>* ultimo;
    Celda<T>* cursor;

  public:

    /*
    *Pre:
    *Post: Se crea una lista simple vacia
    */
    Lista();

    /*
    *Pre:
    *Post: Lista que tiene los mismos elementos que otraLista
    *      La instancia resulta en una copia de otraLista
    */
    Lista(Lista<T>& otraLista);

    /*
    *Pre:
    *Post: Indica si la lista tiene algun elemento
    */
    bool estaVacia();

    /*
    *Pre:
    *Post: devuelve la cantidad de elementos que contiene la lista
    */
    unsigned int contarElementos();

    /*
    *Pre:
    *Post: Agrega el elemento al final de la lista, en la posicion:
    *      contarElementos() + 1.
    */
    void agregar(T elemento);

    /*
    *Pre: Posicion pertenece al intervalo [1 , contarElementos() + 1]
    *Post:  agregar el elemento en la posicion dada
    */
    void agregar(T elemento, unsigned int posicion);

    /*
    *Pre:
    *Post: Agrega los elementos de otraLista
    *      a partir de la posicion contarElementos()+1
    */
    void agregar(Lista<T>& otraLista);

    /*
    *Pre: Posicion pertenece al intervalo [1 , contarElementos()]
    *Post: devuelve el dato en la posicion dada
    */
    T obtener(unsigned int posicion);

    /*
    *Pre: Posicion pertenece al intervalo [1 , contarElementos()]
    *Post: cambia el elemento en la posicion indiciada
    *      por el elemento dado
    */
    void asignar(T elemento, unsigned int posicion);

    /*
    *Pre: Posicion pertenece al intervalo [1 , contarElementos()]
    *Post: remueve el elemento de la lista en la posicion dada
    */
    void remover(unsigned int posicion);

    /*
    *Pre:
    *Post: Deja el cursor de la lista preparado para hacer un nuevo
    *      recorrido sobre sus elementos
    */
    void iniciarCursor();

    /*
    *Pre: Se ha iniciado un recorrido (invocando el metodo iniciarCursor())
    *     y desde entonces no se han agregado o removido elementos de la lista
    *Post: Mueve el cursor y lo posiciona en el siguiente elemento del recorrrido
    *      El valor de retorno indica si el cursos quedo posicionado sobre un
    *      elemento o no (en caso de que la Lista este vacia o no existan mas
    *      elementos por recorrer)
    */
    bool avanzarCursor();

    /*
    *Pre: Se ha iniciado un recorrido (invocando el metodo iniciarCursor())
    *     y desde entonces no se han agregado o removido elementos de la lista
    *Post: Mueve el cursor y lo posiciona en el elemento anterior del recorrrido
    *      El valor de retorno indica si el cursos quedo posicionado sobre un
    *      elemento o no (en caso de que la Lista este vacia o no existan mas
    *      elementos por recorrer)
    */
    bool retrocederCursor();


    /*
    *Pre: El cursor fue posicionado sobre un elemento de la lista
    *     (fue invocado el metodo avanzarCursor() y devolvio true)
    *Post: Devuelve el elemento en la posicion del cursor
    */
    T obtenerCursor();

    /*
     *  Pos: Devuelve si la posicion pertenece
     *       al intervalo [1 , contarElementos()+1]
     */
    bool esValidaLa(unsigned int posicion);
    /*
    *Pre:
    *Post: Libera todos los recursos asociados a la Lista.
    */
    ~Lista();

  private:

    /*
    *Pre: Posicion pertenece al intervalo: [1, contarElementos()]
    *Post: Devuelve el Celda en la posicion indicada
    */
    Celda<T>* obtenerCelda(unsigned int posicion);




};


class ExcepcionElementoInexistente {

  private:

    unsigned int posicion;

  public:

    /*
    *Pre:
    *Post: excepcion creada a partir de la posicion invalida a
    *      la que se intento acceder
    */
    ExcepcionElementoInexistente(unsigned int posicion){

      this->posicion = posicion;
    }

    /*
    *Pre:
    *Post: Devuelve la posicion invalida a la que se intento acceder
    */
    unsigned int obtenerPosicionInvalida(){

      return this->posicion;
    }

};

template <class T>
Lista<T>::Lista(){
    this->tamanio = 0;
    this->primero = NULL;
    this->ultimo = NULL;
    this->cursor = NULL;
}

template <class T>
Lista<T>::Lista(Lista<T>& otraLista){
  this->tamanio = 0;
  this->primero = NULL;
  this->ultimo = NULL;
  this->cursor = NULL;

  /*Copia los elementos de otraLista*/
  this->agregar(otraLista);

}

template <class T>
bool Lista<T>::estaVacia(){
  return (this->tamanio == 0);
}

template <class T>
unsigned int Lista<T>::contarElementos(){
  return this->tamanio;
}

template <class T>
void Lista<T>::agregar(T elemento){

  this->agregar(elemento, this->tamanio + 1);
}

template <class T>
void Lista<T>::agregar(T elemento, unsigned int posicion){

  if(!this->esValidaLa(posicion)){
    throw ExcepcionElementoInexistente(posicion);
  }

  Celda<T>* nuevaCelda = new Celda<T>(elemento);
  if(posicion == 1){
    nuevaCelda->cambiarSiguiente(this->primero);
    if(this->primero != NULL){
      this->primero->cambiarAnterior(nuevaCelda);
    }
    this->primero = nuevaCelda;

    if(!this->ultimo){
      this->ultimo = nuevaCelda;
    }

  } else {

    Celda<T>* celdaAnterior = this->obtenerCelda(posicion - 1);
    nuevaCelda->cambiarSiguiente(celdaAnterior->obtenerSiguiente());
    nuevaCelda->cambiarAnterior(celdaAnterior);
    if(posicion == this->contarElementos() + 1){
      this->ultimo = nuevaCelda;
    } else {
      celdaAnterior->obtenerSiguiente()->cambiarAnterior(nuevaCelda);
    }
    celdaAnterior->cambiarSiguiente(nuevaCelda);
  }

  this->tamanio++;

  /* cualquier recorrido actual queda invalidado */
  this->iniciarCursor();

}

template <class T>
void Lista<T>::agregar(Lista<T>& otraLista){

  otraLista.iniciarCursor();

  while(otraLista.avanzarCursor()){
    this->agregar(otraLista.obtenerCursor());
  }
}

template <class T>
T Lista<T>::obtener(unsigned int posicion){

  T elemento;

  if(posicion > 0 && posicion <= this->tamanio){

    elemento = this->obtenerCelda(posicion)->obtenerDato();

  } else {
    throw ExcepcionElementoInexistente(posicion);
  }

  return elemento;
}

template <class T>
void Lista<T>::asignar(T elemento, unsigned int posicion){

  if(this->esValidaLa(posicion)){

    this->obtenerCelda(posicion)->cambiarDato(elemento);

  } else {

    throw ExcepcionElementoInexistente(posicion);

  }
}

template <class T>
void Lista<T>::remover(unsigned int posicion){


    Celda<T>* celdaRemovida;

    if(!this->esValidaLa(posicion)){
    	throw ExcepcionElementoInexistente(posicion);
    }

	if(posicion == 1){
		celdaRemovida = this->primero;
		this->primero = celdaRemovida->obtenerSiguiente();
    if(this->contarElementos() != posicion){
		  this->primero->cambiarAnterior(celdaRemovida->obtenerAnterior());
    }
	}
	else if(posicion < this->contarElementos()){

		Celda<T>* celdaAnterior = this->obtenerCelda(posicion - 1);
		celdaRemovida = celdaAnterior->obtenerSiguiente();
		Celda<T>* celdaSiguiente = celdaRemovida->obtenerSiguiente();
		celdaAnterior->cambiarSiguiente(celdaSiguiente);
		celdaSiguiente->cambiarAnterior(celdaAnterior);

	} else {
			celdaRemovida = this->ultimo;
      this->ultimo = celdaRemovida->obtenerAnterior();
      this->ultimo->cambiarSiguiente(celdaRemovida->obtenerSiguiente());
	}
    this->tamanio--;
    delete celdaRemovida;
}

template <class T>
void Lista<T>::iniciarCursor(){

  this->cursor = NULL;

}

template <class T>
bool Lista<T>::avanzarCursor(){

  if(this->cursor == NULL){
    this->cursor = this->primero;
  } else {
    this->cursor = this->cursor->obtenerSiguiente();
  }

  /* pudo avanzar si el cursor apunta a un Celda */

  return(this->cursor != NULL);
}

template <class T>
bool Lista<T>::retrocederCursor(){

  if(this->cursor == NULL){
    this->cursor = this->ultimo;
  } else {
    this->cursor = this->cursor->obtenerAnterior();
  }

  /* pudo avanzar si el cursor apunta a un Celda */

  return(this->cursor != NULL);
}

template <class T>
T Lista<T>::obtenerCursor(){

  T elemento;

  if(this->cursor != NULL){
    elemento = this->cursor->obtenerDato();
  } else {
    throw ExcepcionElementoInexistente(0);
  }

  return elemento;
}

template <class T>
Celda<T>* Lista<T>::obtenerCelda(unsigned int posicion){

  if(!this->esValidaLa(posicion)){
    throw ExcepcionElementoInexistente(posicion);
  }
  Celda<T>* CeldaActual = this->primero;

  for(unsigned int i = 1 ; i < posicion ; i++){
    CeldaActual = CeldaActual->obtenerSiguiente();
  }

  return CeldaActual;
}

template <class T>
bool Lista<T>::esValidaLa(unsigned int posicion){
  return ((posicion > 0) && (posicion <= this->contarElementos()+1));
}

template <class T>
Lista<T>::~Lista(){

  while(this->primero != NULL){
    Celda<T>* CeldaBorrado = this->primero;
    this->primero = CeldaBorrado->obtenerSiguiente();

    delete CeldaBorrado;
  }

}


#endif /*_Lista_H_ */
