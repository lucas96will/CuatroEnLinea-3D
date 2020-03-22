#ifndef _LISTASIMPLE_H_
#define _LISTASIMPLE_H_

#include <iostream>
#include "Nodo.h"
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
template <class T> class ListaSimple {

  private:

    unsigned int tamanio;
    Nodo<T>* primero;
    Nodo<T>* cursor;

  public:

    /*
    *Pre:
    *Post: Se crea una lista simple vacia
    */
    ListaSimple();

    /*
    *Pre:
    *Post: Lista que tiene los mismos elementos que otraLista
    *      La instancia resulta en una copia de otraLista
    */
    ListaSimple(ListaSimple<T>& otraLista);

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
    void agregar(ListaSimple<T>& otraLista);

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
    *Pre: El cursor fue posicionado sobre un elemento de la lista
    *     (fue invocado el metodo avanzarCursor() y devolvio true)
    *Post: Devuelve el elemento en la posicion del cursor
    */
    T obtenerCursor();

    /*
    *Pre:
    *Post: Libera todos los recursos asociados a la Lista.
    */
    ~ListaSimple();

    void invertir();

  private:

    /*
    *Pre: Posicion pertenece al intervalo: [1, contarElementos()]
    *Post: Devuelve el nodo en la posicion indicada
    */
    Nodo<T>* obtenerNodo(unsigned int posicion);




};


template <class T>
ListaSimple<T>::ListaSimple(){
    this->tamanio = 0;
    this->primero = NULL;
    this->cursor = NULL;
}

template <class T>
ListaSimple<T>::ListaSimple(ListaSimple<T>& otraLista){
  this->tamanio = 0;
  this->primero = NULL;
  this->cursor = NULL;

  /*Copia los elementos de otraLista*/
  this->agregar(otraLista);

}

template <class T>
bool ListaSimple<T>::estaVacia(){
  return (this->tamanio == 0);
}

template <class T>
unsigned int ListaSimple<T>::contarElementos(){
  return this->tamanio;
}

template <class T>
void ListaSimple<T>::agregar(T elemento){

  this->agregar(elemento, this->tamanio + 1);
}

template <class T>
void ListaSimple<T>::agregar(T elemento, unsigned int posicion){

  if(posicion > 0 && posicion <= this->tamanio + 1){
    Nodo<T>* nuevoNodo = new Nodo<T>(elemento);

    if(posicion == 1){
      nuevoNodo->cambiarSiguiente(this->primero);
      this->primero = nuevoNodo;
    } else {

      Nodo<T>* anteriorNodo = this->obtenerNodo(posicion - 1);
      nuevoNodo->cambiarSiguiente(anteriorNodo->obtenerSiguiente());
      anteriorNodo->cambiarSiguiente(nuevoNodo);

    }

    this->tamanio++;

    /* cualquier recorrido actual queda invalidado */
    this->iniciarCursor();

  } else {
      throw ExcepcionError(posicion);
  }
}

template <class T>
void ListaSimple<T>::agregar(ListaSimple<T>& otraLista){

  otraLista.iniciarCursor();

  while(otraLista.avanzarCursor()){
    this->agregar(otraLista.obtenerCursor());
  }
}

template <class T>
T ListaSimple<T>::obtener(unsigned int posicion){

  T elemento;

  if(posicion > 0 && posicion <= this->tamanio){

    elemento = this->obtenerNodo(posicion)->obtenerDato();

  } else {
    throw ExcepcionError(posicion);
  }

  return elemento;
}

template <class T>
void ListaSimple<T>::asignar(T elemento, unsigned int posicion){

  if(posicion > 0 && posicion <= this->contarElementos() + 1){

    this->obtenerNodo(posicion)->cambiarDato(elemento);

  } else {

    throw ExcepcionError(posicion);

  }
}

template <class T>
void ListaSimple<T>::remover(unsigned int posicion){

  if(posicion > 0 && posicion <= this->contarElementos()){

    Nodo<T>* nodoRemovido;

    if(posicion == 1){
      nodoRemovido = this->primero;
      this->primero = nodoRemovido->obtenerSiguiente();

    }
    else {
      Nodo<T>* nodoAnterior = this->obtenerNodo(posicion - 1);
      nodoRemovido = nodoAnterior->obtenerSiguiente();
      nodoAnterior->cambiarSiguiente(nodoRemovido->obtenerSiguiente());
    }

    delete nodoRemovido;
    this->tamanio--;

    /* cualquier recorrido actual queda invalidado */
    this->iniciarCursor();

  } else {

    throw ExcepcionError(posicion);
  }

}

template <class T>
void ListaSimple<T>::iniciarCursor(){

  this->cursor = NULL;

}

template <class T>
bool ListaSimple<T>::avanzarCursor(){

  if(this->cursor == NULL){
    this->cursor = this->primero;
  } else {
    this->cursor = this->cursor->obtenerSiguiente();
  }

  /* pudo avanzar si el cursor apunta a un nodo */

  return(this->cursor != NULL);
}

template <class T>
T ListaSimple<T>::obtenerCursor(){

  T elemento;

  if(this->cursor != NULL){
    elemento = this->cursor->obtenerDato();
  } else {
    throw ExcepcionError(0);
  }

  return elemento;
}

template <class T>
Nodo<T>* ListaSimple<T>::obtenerNodo(unsigned int posicion){

  Nodo<T>* nodoActual = this->primero;

  for(unsigned int i = 1 ; i < posicion ; i++){
    nodoActual = nodoActual->obtenerSiguiente();
  }

  return nodoActual;
}

template <class T>
ListaSimple<T>::~ListaSimple(){

  while(this->primero != NULL){
    Nodo<T>* nodoBorrado = this->primero;
    this->primero = nodoBorrado->obtenerSiguiente();
    delete nodoBorrado;
  }

}

template<class T>
void ListaSimple<T>::invertir(){
    ListaSimple<T>* listaInvertida;
    listaInvertida = new ListaSimple<T>();
    this->iniciarCursor();

    while(this->avanzarCursor()){
        listaInvertida->agregar(this->obtenerCursor(), 1);
    }

    this->iniciarCursor();
    listaInvertida->iniciarCursor();

    while(this->avanzarCursor() && listaInvertida->avanzarCursor()){
    	this->cursor->cambiarDato(listaInvertida->cursor->obtenerDato());
    }


    delete listaInvertida;
}


#endif /*_LISTASIMPLE_H_ */
