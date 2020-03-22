#ifndef _CELDA_H_
#define _CELDA_H_

#ifndef NULL
#define NULL 0
#endif /*NULL*/

template <class T> class Celda {

private:

  Celda<T>* siguiente;
  Celda<T>* anterior;

  T dato;

public:

  /*Pre:
   *Post:crea la celda con el dato y sin una celda siguiente
   */
  Celda(T datoIngresado);

  /*Pre:
   *Post:devuelve el dato contenido en la celda
   */
  T obtenerDato();

  /*Pre:
   *Post:Devuelve la celda siguiente o null si esta no existe
   */
   Celda<T>* obtenerSiguiente();

   /*Pre:
    *Post:Devuelve la celda anterior o null si esta no existe
    */
   Celda<T>* obtenerAnterior();

   /*Pre:
    *Post:cambia el dato dentro de la celda por el nuevoDato
    */
    void cambiarDato(T nuevoDato);

   /*Pre:
    *Post:cambia la siguiente celda por nuevoSiguiente
    */
    void cambiarSiguiente(Celda<T>* nuevoSiguiente);

    /*Pre:
     *Post:cambia la anterior celda por nuevoAnterior
     */
    void cambiarAnterior(Celda<T>* nuevoAnterior);

};

template <class T>
Celda<T>::Celda(T datoIngresado){
  this->dato = datoIngresado;
  this->siguiente = NULL;
  this->anterior = NULL;
}

template <class T>
T Celda<T>::obtenerDato(){
  return this->dato;
}

template <class T>
Celda<T>* Celda<T>::obtenerSiguiente(){
  return this->siguiente;
}

template <class T>
Celda<T>* Celda<T>::obtenerAnterior(){
  return this->anterior;
}

template <class T>
void Celda<T>::cambiarDato(T nuevoDato){
  this->dato = nuevoDato;
}

template <class T>
void Celda<T>::cambiarSiguiente(Celda<T>* nuevoSiguiente){
  this->siguiente = nuevoSiguiente;
}

template <class T>
void Celda<T>::cambiarAnterior(Celda<T>* nuevoAnterior){
  this->anterior = nuevoAnterior;
}


#endif /*_CELDA_H_ */
