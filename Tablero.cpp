#include "Tablero.h"

using namespace std;

Tablero::Tablero(Dimension dimensionIngresada){
    this->tamanio.x = dimensionIngresada.x;
    this->tamanio.y = dimensionIngresada.y;
    this->tamanio.z = dimensionIngresada.z;
    if(!this->tamanioValido()){
      throw ExcepcionError("Al menos 2 de las dimensiones del tablero tienen que ser mayor o igual a 4");
    }
    this->armarTablero();
    this->inicializarCorrimientosPosibles();
    this->ultimoEnJugar = NULL;
}

void Tablero::armarTablero(){

  this->tablero = new Base;
  for (size_t i = 1; i <= this->tamanio.x; i++){
    Fila* filaActual = new Fila;

    for(size_t j = 1; j <= this->tamanio.y ; j++){
      Columna* columnaActual = new Columna;
      filaActual->agregar(columnaActual);
    }

    this->tablero->agregar(filaActual);
  }
}

void Tablero::inicializarCorrimientosPosibles(){
    this->corrimientosPosibles = new ListaSimple<Corrimiento>();
    this->agregarCorrimiento( 1, 0, 0); /* (-1, 0, 0) */ //hacer
    this->agregarCorrimiento( 0, 1, 0);
    this->agregarCorrimiento( 0, 0, 1);
    this->agregarCorrimiento( 1, 1, 0);
    this->agregarCorrimiento( 1, 0, 1);
    this->agregarCorrimiento( 0, 1, 1);
    this->agregarCorrimiento( 1, 1, 1);
    this->agregarCorrimiento( 1,-1, 0);
    this->agregarCorrimiento( 1, 0,-1);
    this->agregarCorrimiento( 0, 1,-1);
    this->agregarCorrimiento( 1, 1,-1);
    this->agregarCorrimiento( 1,-1, 1);
    this->agregarCorrimiento( 1,-1,-1);
}

void Tablero::agregarCorrimiento(int x, int y, int z){
    Corrimiento corrimiento;
    corrimiento.x = x;
    corrimiento.y = y;
    corrimiento.z = z;
    this->corrimientosPosibles->agregar(corrimiento);
}

bool Tablero::tamanioValido(){
  return ((this->tamanio.z >= 1 && this->tamanio.x >= TAMANIO_MINIMO && this->tamanio.y >= TAMANIO_MINIMO) ||
          (this->tamanio.y >= 1 && this->tamanio.x >= TAMANIO_MINIMO && this->tamanio.z >= TAMANIO_MINIMO) ||
          (this->tamanio.x >= 1 && this->tamanio.z >= TAMANIO_MINIMO && this->tamanio.y >= TAMANIO_MINIMO) );
}

unsigned Tablero::obtenerCantidadDeCeldas(){
  return ((unsigned)((this->tamanio.x)*(this->tamanio.y)*(this->tamanio.z)));
}

Dimension Tablero::consultarDimensiones(){
  return this->tamanio;
}

Jugador* Tablero::obtenerFichaEnCelda(Coordenada posicionFicha){

  if(!esValidaLa(posicionFicha)){
    throw ExcepcionError("Error al tratar de obtener una ficha en una coordenada no valida");
  }

  Jugador* jugadorActual;

  Columna* columnaActual = this->obtenerColumnaEn(posicionFicha);

  if(columnaActual->contarElementos() < posicionFicha.z){
    jugadorActual = NULL;
  } else {
    jugadorActual = columnaActual->obtener((unsigned)posicionFicha.z);
  }

  return jugadorActual;
}

void Tablero::agregarFichaEnCelda(Coordenada posicionIngresada, Jugador* jugador){

  if(!esValidaLa(posicionIngresada)){
    throw ExcepcionError("Error al tratar de obtener una ficha en una coordenada no valida");
  }

  Columna* columnaActual = this->obtenerColumnaEn(posicionIngresada);

  if(columnaActual->contarElementos() >= this->tamanio.z){
    throw ExcepcionError("Error al tratar de ingresar una ficha en una columna llena");
  }

  columnaActual->agregar(jugador);
  this->ultimoEnJugar = jugador;
}

void Tablero:: cambiarColorEnCeldaEn(Coordenada posicion, Jugador* jugador ){
	if(!esValidaLa(posicion)){
	    throw ExcepcionError("Error al tratar de obtener una ficha en una coordenada no valida");
	  }

	  Columna* columnaActual = this->obtenerColumnaEn(posicion);
	  columnaActual->asignar(jugador,(unsigned)posicion.z);

}

Columna* Tablero::obtenerColumnaEn(Coordenada posicion){

  if(!this->esValidaLa(posicion)){
    throw ExcepcionError("Error al tratar de obtener una ficha en una coordenada no valida");
  }

  Fila* filaActual = this->tablero->obtener((unsigned)posicion.x);
  Columna* columnaActual = filaActual->obtener((unsigned)posicion.y);

  return columnaActual;

}

void Tablero::eliminarFicha(Coordenada posicion){
  if(!this->esValidaLa(posicion)){
    throw ExcepcionError("Error al tratar de obtener una ficha en una coordenada no valida");
  }

  Columna* columnaActual = this->obtenerColumnaEn(posicion);
  columnaActual->remover((unsigned)posicion.z);

}

string Tablero::obtenerColorFichaEnCelda(Coordenada posicionFicha){
	Jugador* ficha = this->obtenerFichaEnCelda(posicionFicha);

	string colorFicha("");
	if(ficha != NULL){
		colorFicha = ficha->consultarColor();
	}
	return colorFicha;
}

bool Tablero::esValidaLa(Coordenada posicionIngresada){
  return(posicionIngresada.x <= this->tamanio.x &&
         posicionIngresada.y <= this->tamanio.y &&
         posicionIngresada.z <= this->tamanio.z &&
         this->posicionMayorACero(posicionIngresada));
}

bool Tablero::posicionMayorACero(Dimension posicionIngresada){
  return(posicionIngresada.x > 0 &&
         posicionIngresada.y > 0 &&
         posicionIngresada.z > 0);
}

bool Tablero::hayCuatroEnLinea(Coordenada posicionIngresada, Jugador* elegido){
  if(!this->esValidaLa(posicionIngresada)){
    throw ExcepcionError("Error al tratar de hallar cuatro en linea desde una posicion fuera del tablero");
  }
  unsigned contadorDeFichasIguales;
  bool hayCuatroEnLinea = false;
  this->corrimientosPosibles->iniciarCursor();

  while(this->corrimientosPosibles->avanzarCursor() && !hayCuatroEnLinea){
    contadorDeFichasIguales = 1;
    Corrimiento corrimientoActual = this->corrimientosPosibles->obtenerCursor();
    hayCuatroEnLinea = tieneCuatroEnLineaEn(posicionIngresada, corrimientoActual, contadorDeFichasIguales, elegido);
    if(!hayCuatroEnLinea){
        Corrimiento corrimientoContrario = this->ContrarioDe(corrimientoActual);
        hayCuatroEnLinea = tieneCuatroEnLineaEn(posicionIngresada, corrimientoContrario, contadorDeFichasIguales, elegido);
    }
  }
  return hayCuatroEnLinea;
}

unsigned int Tablero::obtenerFichasMaximasEnLinea(Coordenada posicionIngresada){
  if(!this->esValidaLa(posicionIngresada)){
    throw ExcepcionError("Error al tratar de contar fichas en linea desde una posicion fuera del tablero");
  }


  Jugador* fichaEnPosicion = this->obtenerFichaEnCelda(posicionIngresada);
  unsigned contadorDeFichasIguales;
  unsigned maximoDeFichasEnLinea = 0;
  bool hayCuatroEnLinea = false;
  this->corrimientosPosibles->iniciarCursor();

  while(this->corrimientosPosibles->avanzarCursor() && !hayCuatroEnLinea){
    contadorDeFichasIguales = 1;
    Corrimiento corrimientoActual = this->corrimientosPosibles->obtenerCursor();
    hayCuatroEnLinea = tieneCuatroEnLineaEn(posicionIngresada, corrimientoActual, contadorDeFichasIguales, fichaEnPosicion);
    Corrimiento corrimientoContrario = this->ContrarioDe(corrimientoActual);
    hayCuatroEnLinea = tieneCuatroEnLineaEn(posicionIngresada, corrimientoContrario, contadorDeFichasIguales, fichaEnPosicion);
    maximoDeFichasEnLinea = devolverElMayorEntre(contadorDeFichasIguales, maximoDeFichasEnLinea);
    }

  return maximoDeFichasEnLinea;
}

unsigned int Tablero::devolverElMayorEntre(unsigned contadorUno, unsigned contadorDos){
  unsigned maximoNumero;
  if(contadorUno > contadorDos){
    maximoNumero = contadorUno;
  } else {
    maximoNumero = contadorDos;
  }
  return maximoNumero;
}

bool Tablero::esLateralEl(Coordenada casillero){
  return (casillero.x == 1 || casillero.x == this->tamanio.x ||
          casillero.y == 1 || casillero.y == this->tamanio.x ||
          casillero.z == 1 || casillero.z == this->tamanio.x);
}

unsigned Tablero::distanciaEntre(Coordenada posicionUno, Coordenada posicionDos){
	unsigned distancia = 0;
	Coordenada diferencia;
	diferencia.x = unsigned(abs(int(posicionUno.x)- int(posicionDos.x)));
	diferencia.y = unsigned(abs(int(posicionUno.y)- int(posicionDos.y)));
	diferencia.z = unsigned(abs(int(posicionUno.z)- int(posicionDos.z)));
	distancia = (unsigned)max(max(diferencia.x,diferencia.y), max(diferencia.x, diferencia.z));
	return distancia;
}


bool Tablero::sonIguales(Coordenada posicionUno, Coordenada posicionDos){
  return(posicionUno.x == posicionDos.x &&
         posicionUno.y == posicionDos.y &&
         posicionUno.z == posicionDos.z);
}




size_t Tablero::obtenerAlturaDeLa(Coordenada posicion){
	if(!this->esValidaLa(posicion)){
		throw ExcepcionError("No se puede obtener la altura de una columna fuera de rango del tablero");
	}
	return this->obtenerColumnaEn(posicion)->contarElementos();
}

bool Tablero::tieneCuatroEnLineaEn(Coordenada estaPosicion,
                                   Corrimiento haciaEstaDireccion,
                                   unsigned &contadorDeFichasIguales,
								   Jugador* fichaInicial){
  Coordenada posicionFichaVecina = this->suma(estaPosicion, haciaEstaDireccion);
  Jugador* fichaVecina = this->buscarFichaVecina(posicionFichaVecina);
  if((fichaVecina != fichaInicial) || (!fichaVecina) ||
     (++contadorDeFichasIguales >= FICHAS_MINIMAS_PARA_GANAR)){
    return (fichaVecina == fichaInicial);
  }
  else{
    return this->tieneCuatroEnLineaEn(posicionFichaVecina, haciaEstaDireccion, contadorDeFichasIguales, fichaInicial);
  }
}

Coordenada Tablero::suma(Coordenada posicionIngresada, Corrimiento corrimiento){
    Coordenada suma;
    suma.x = (unsigned)((int)posicionIngresada.x + corrimiento.x);
    suma.y = (unsigned)((int)posicionIngresada.y + corrimiento.y);
    suma.z = (unsigned)((int)posicionIngresada.z + corrimiento.z);
    return suma;
}

Corrimiento Tablero::ContrarioDe(Corrimiento corrimientoActual){
    Corrimiento contrario;
    contrario.x = (-corrimientoActual.x);
    contrario.y = (-corrimientoActual.y);
    contrario.z = (-corrimientoActual.z);
    return contrario;
}

Jugador* Tablero::buscarFichaVecina(Coordenada posicionFichaVecina){
    Jugador* fichaVecina = NULL;
    if(this->esValidaLa(posicionFichaVecina)){
      fichaVecina = (this->obtenerFichaEnCelda(posicionFichaVecina));
    }
    return fichaVecina;
}

Jugador* Tablero::obtenerUltimoEnIngresarFicha(){
	return this->ultimoEnJugar;
}

Tablero::~Tablero(){
  this->desarmarTablero();
  delete this->corrimientosPosibles;
}

void Tablero::desarmarTablero(){
  this->tablero->iniciarCursor();
  while(this->tablero->avanzarCursor()){
    Fila* filas = this->tablero->obtenerCursor();

    filas->iniciarCursor();
    while(filas->avanzarCursor()){
      Columna* columna = filas->obtenerCursor();
      delete columna;
    }
    delete filas;
  }
  delete this->tablero;
}
