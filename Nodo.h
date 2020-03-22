#ifndef _NODO_H_
#define _NODO_H_

#ifndef NULL
#define NULL 0
#endif /*NULL*/

template <class T> class Nodo {

private:

  Nodo<T>* siguiente;

  T dato;

public:

  /*Pre:
   *Post:crea el nodo con el dato y sin un nodo siguiente
   */
  Nodo(T datoIngresado);

  /*Pre:
   *Post:devuelve el dato contenido en el nodo
   */
  T obtenerDato();

  /*Pre:
   *Post:Devuelve el nodo siguiente o null si este no existe
   */
   Nodo<T>* obtenerSiguiente();

   /*Pre:
    *Post:cambia el dato dentro del nodo por el nuevoDato
    */
    void cambiarDato(T nuevoDato);

   /*Pre:
    *Post:cambia el siguiente nodo por nuevoSiguiente
    */
    void cambiarSiguiente(Nodo<T>* nuevoSiguiente);

};

template <class T>
Nodo<T>::Nodo(T datoIngresado){
  this->dato = datoIngresado;
  this->siguiente = NULL;
}

template <class T>
T Nodo<T>::obtenerDato(){
  return this->dato;
}

template <class T>
Nodo<T>* Nodo<T>::obtenerSiguiente(){
  return this->siguiente;
}

template <class T>
void Nodo<T>::cambiarDato(T nuevoDato){
  this->dato = nuevoDato;
}

template <class T>
void Nodo<T>::cambiarSiguiente(Nodo<T>* nuevoSiguiente){
  this->siguiente = nuevoSiguiente;
}


#endif /*_NODO_H_ */
