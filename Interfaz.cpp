#include "Interfaz.h"
#include "EasyBMP.h"
#include "EasyBMP_SimpleArray.h"
#include "EasyBMP_Font.h"
#include "EasyBMP_Geometry.h"
#include <cstdlib>
using namespace std;
//Definiciones Externas

void mostrar(Tablero *tablero){
	system("clear");
	Dimension delTablero  = tablero->consultarDimensiones();
	unsigned largoTablero = (((unsigned)delTablero.y*5) + 1);
	imprimirSuperficieDeTablero(largoTablero);
	for(size_t altura = 1; altura <= delTablero.z; altura++){
			imprimirCartelDe((unsigned)altura, largoTablero);
			for(size_t largo = 1; largo <= delTablero.x; largo++){
					if(largo % 2 == 0){
						imprimirPorcionDeTableroIntermedia(largo, altura, delTablero, tablero);
					}
					else{
						imprimirPorcionDeTableroSuperior(largo, altura, delTablero, tablero);
					}
				}
			imprimirFondoDeTablero(largoTablero);
	}
	imprimirMiniTablero(largoTablero, (unsigned)delTablero.y);
}

void imprimirPorcionDeTableroSuperior(size_t largo, size_t altura, Dimension delTablero, Tablero *tablero){
	Coordenada posicionFicha;
	Jugador* ficha;
	cout << LATERAL_IZQUIERDO;
  	cout << repetir(BORDE_SUPERIOR, (unsigned)delTablero.y);
	cout << BORDE_LATERAL << LATERAL_DERECHO << endl;
	cout << LATERAL_IZQUIERDO;
	for(size_t ancho = 1; ancho <= delTablero.y; ancho++){
	  posicionFicha = {largo, ancho, altura};
		ficha = tablero->obtenerFichaEnCelda(posicionFicha);
		imprimirFicha(ficha, CASO_UNO);
	}
	cout << BORDE_LATERAL << LATERAL_DERECHO << endl;
	cout << LATERAL_IZQUIERDO;
  	cout << repetir(BORDE_INFERIOR, (unsigned)delTablero.y) << RELLENO_MEDIO;
	cout << LATERAL_DERECHO << endl;
}

void imprimirPorcionDeTableroIntermedia(size_t largo, size_t altura, Dimension delTablero, Tablero *tablero){
	Coordenada posicionFicha;
	Jugador* ficha;
	unsigned largoTablero = (((unsigned)delTablero.y*5) + 1);
	cout << LATERAL_IZQUIERDO;
	for(size_t ancho = 1; ancho <= delTablero.y; ancho++){
		posicionFicha = {largo, ancho, altura};
		ficha = tablero->obtenerFichaEnCelda(posicionFicha);
		imprimirFicha(ficha, CASO_DOS);
	}
	cout << BORDE_LATERAL << LATERAL_DERECHO << endl;
	cout << LATERAL_IZQUIERDO;
	for(size_t ancho = 1; ancho <= delTablero.y; ancho++){
		posicionFicha = {largo, ancho, altura};
		ficha = tablero->obtenerFichaEnCelda(posicionFicha);
		imprimirFicha(ficha, CASO_TRES);
	}
	cout << BORDE_LATERAL << LATERAL_DERECHO << endl;
	if(largo == delTablero.x){
		cout << LATERAL_IZQUIERDO << repetir(RELLENO_ALTO, largoTablero) << LATERAL_DERECHO << endl;
	}
}

void imprimirFicha(Jugador* ficha, unsigned caso){

	if(esCeldaVacia(ficha)){
		cout << BORDE_LATERAL << ESPACIO_VACIO;
	}
	else {
		string color = ficha->consultarColor();
		switch (caso) {
			case CASO_UNO:
				cout << BORDE_LATERAL << color << " " << FICHA << " " << RESET;
				break;
			case CASO_DOS:
				cout << BORDE_LATERAL << color << " " << MEDIA_FICHA_SUPERIOR << " " << RESET;
				break;
			case CASO_TRES:
				cout << BORDE_LATERAL << color << " " << MEDIA_FICHA_INFERIOR << " " << RESET;
				break;
		}
	}
}

void imprimirCartelDe(unsigned altura, unsigned largoTablero){
	string cartelNivel = " Nivel: " + to_string(altura) + ". ";
	string espacioIntermedio = LATERAL_IZQUIERDO;
	unsigned corrimiento = ((unsigned)espacioIntermedio.size() - (unsigned)cartelNivel.size() - 4);
	cout << BORDE_LATERAL << cartelNivel << BORDE_LATERAL << repetir(RELLENO, corrimiento + largoTablero) << LATERAL_DERECHO << endl;
	cout << BORDE_LATERAL << repetir(RELLENO_ALTO, (unsigned)cartelNivel.size() + 1) << repetir(RELLENO, corrimiento + largoTablero) << LATERAL_DERECHO << endl;
	cout << LATERAL_IZQUIERDO << repetir(RELLENO, largoTablero) << LATERAL_DERECHO << endl;
}

void imprimirSuperficieDeTablero(unsigned largoTablero){
		cout << BORDE_SUPERIOR_TABLERO << repetir(RELLENO_BAJO, largoTablero) << BORDE_SUPERIOR_TABLERO << endl;
}

void imprimirFondoDeTablero(unsigned largoTablero){
	cout << LATERAL_IZQUIERDO << repetir(RELLENO, largoTablero) << LATERAL_DERECHO << endl;
	cout << LATERAL_IZQUIERDO << repetir(RELLENO, largoTablero) << LATERAL_DERECHO << endl;
	cout << LATERAL_IZQUIERDO_ESQUINA << repetir(RELLENO_BAJO, largoTablero) << LATERAL_DERECHO_ESQUINA<< endl;
}

void imprimirMiniTablero(unsigned largoTablero, unsigned dimensionY){
	unsigned corrimiento = calcularCorrimiento(dimensionY);
	unsigned corrimientoIzquierdo = (dimensionY % 2 == 0) ? (corrimiento - 1) : (corrimiento);
	cout << LATERAL_IZQUIERDO << repetir(RELLENO, largoTablero) << LATERAL_DERECHO << endl;
	cout << BORDE_LATERAL << repetir(RELLENO, corrimientoIzquierdo) << "        COLUMNAS >      " << repetir(RELLENO, corrimiento) << BORDE_LATERAL << endl;
	cout << BORDE_LATERAL << repetir(RELLENO, corrimientoIzquierdo) << "    F █▀▀█▀▀█▀▀█▀▀█     " << repetir(RELLENO, corrimiento) << BORDE_LATERAL << endl;
	cout << BORDE_LATERAL << repetir(RELLENO, corrimientoIzquierdo) << "    I █▄▄█▄▄█▄▄█▄▄█     " << repetir(RELLENO, corrimiento) << BORDE_LATERAL << endl;
	cout << BORDE_LATERAL << repetir(RELLENO, corrimientoIzquierdo) << "    L █  █  █  █  █     " << repetir(RELLENO, corrimiento) << BORDE_LATERAL << endl;
	cout << BORDE_LATERAL << repetir(RELLENO, corrimientoIzquierdo) << "    A █▀▀█▀▀█▀▀█▀▀█     " << repetir(RELLENO, corrimiento) << BORDE_LATERAL << endl;
	cout << BORDE_LATERAL << repetir(RELLENO, corrimientoIzquierdo) << "    S █▄▄█▄▄█▄▄█▄▄█     " << repetir(RELLENO, corrimiento) << BORDE_LATERAL << endl;
	cout << BORDE_LATERAL << repetir(RELLENO, corrimientoIzquierdo) << "    v █  █  █  █  █     " << repetir(RELLENO, corrimiento) << BORDE_LATERAL << endl;
	cout << BORDE_LATERAL << repetir(RELLENO, corrimientoIzquierdo) << "      ▀▀▀▀▀▀▀▀▀▀▀▀▀     " << repetir(RELLENO, corrimiento) << BORDE_LATERAL << endl;
	cout << LATERAL_IZQUIERDO << repetir(RELLENO, largoTablero) << LATERAL_DERECHO << endl;
	cout << LATERAL_IZQUIERDO_ESQUINA << repetir(RELLENO_BAJO, largoTablero) << LATERAL_DERECHO_ESQUINA<< endl;

}

unsigned calcularCorrimiento(unsigned largo){
	unsigned corrimiento;
	if(largo == 1){
		corrimiento = largo;
	}
	else if (largo == 2 || largo == 3){
		corrimiento = 2*largo;
	}
	else if((largo % 4 == 0) || ((largo -1) % 4 == 0)){
		corrimiento = (2*(largo + largo/4) - 1);
	}
	else{
		corrimiento = (2*(largo + largo/4));
	}
	return corrimiento;
}

void mostrar(ListaSimple<CartaAbstracta*>* manoDeCartas){

		short int i = 1;

		cout<< "CARTAS EN MANO:" <<endl;

		manoDeCartas->iniciarCursor();
		while(manoDeCartas->avanzarCursor()){

			cout<<  " " << i << ") " << "Carta "
						<< justoIzquierda(manoDeCartas->obtenerCursor()->consultarIdentificador(),15)
						<< "   " << manoDeCartas->obtenerCursor()->consultarDescripcion()
						<<endl;

			i++;
		}
		cout<< endl;
}

void mostrar(Jugador* jugador, unsigned cantidadDeFilas){
	string color = jugador->consultarColor();
	unsigned largoTablero = ((cantidadDeFilas*5) + 1);
	unsigned suNumero = jugador->consultarNumero();
	unsigned corrimiento = calcularCorrimiento(cantidadDeFilas);
	unsigned corrimientoIzquierdo = (cantidadDeFilas % 2 == 0) ? (corrimiento - 1) : (corrimiento);
	unsigned defasePorNumero = (suNumero < 10) ? (0) : (1);
	cout << LATERAL_IZQUIERDO << repetir(RELLENO, largoTablero) << LATERAL_DERECHO << endl;
	cout << BORDE_LATERAL << repetir(RELLENO, corrimientoIzquierdo) << "  Juega el " << color << "Jugador " << suNumero << RESET << ESPACIO_VACIO
	     << repetir(RELLENO, corrimiento - defasePorNumero) << BORDE_LATERAL << endl;
	cout << LATERAL_IZQUIERDO << repetir(RELLENO, largoTablero) << LATERAL_DERECHO << endl;
	cout << LATERAL_IZQUIERDO_ESQUINA << repetir(RELLENO_BAJO, largoTablero) << LATERAL_DERECHO_ESQUINA<< endl;

}


bool esCeldaVacia(Jugador* celda){
	return celda == NULL;
}

void mostrarPresentacionJuego() {
	system("clear");
	cout<<"█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█" << endl;
	cout<<"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█" << endl;
	cout<<"█                                                                              █" << endl;
	cout<<"█                             TRABAJO PRACTICO  N°2                            █" << endl;
	cout<<"█                                                                              █" << endl;
	cout<<"█                           JUEGO: CUATRO EN LINEA 3D                          █" << endl;
	cout<<"█                                                                              █" << endl;
	cout<<"█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█" << endl;
	cout<<"█                                EQUIPO   TRON                                 █" << endl;
	cout<<"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█" << endl;
}

void mostrar(ListaSimple<Jugador*>* jugadores) {
	unsigned i = 1;

	while(i <= jugadores->contarElementos()){
		mostrarJugador(i, jugadores->obtener(i)->consultarColor());
		i++;
	}
}

void mostrarJugador(unsigned numeroJugador, string colorJugador){
	cout << colorJugador << "Jugador N°" << numeroJugador << RESET << endl;
}


void mostrarJugadoresParaRobar(ListaSimple<Jugador*>* jugadores) {

	unsigned i = 1;
	unsigned cantidadDeCartasMostradas = 0;
	unsigned cartasEnMano = 0;

	while(i <= jugadores->contarElementos()){
		Jugador* jugadorActual = jugadores->obtener(i);
		cartasEnMano = jugadorActual->consultarCantidadDeCartas();
		if(cartasEnMano >= 1 && !jugadorActual->consultarSiEsSuTurno()){
			cout << "Cartas en mano : " << jugadorActual->consultarCantidadDeCartas() << " del ";
			mostrarJugador(i, jugadorActual->consultarColor());
			cantidadDeCartasMostradas++;
		}
		i++;
	}

	if(cantidadDeCartasMostradas == 0){
		mostrarMensaje("No hay cartas a quien robarle", "");
	}

}

void mostrarResultadosFinDeJuego(int ganador){
	cout << "El jugador numero: " << ganador << " gano" << endl;
}

void mostrarCantidadFichas(int ganador){
	cout << "El jugador numero: " << ganador << " gano" << endl;
}

void mostrarCantidadCartasEnMano(int ganador){
	cout << "El jugador numero: " << ganador << " gano" << endl;
}

//Definiciones internas
Dimension pedirDimensionDelTablero(){
		Dimension dimensionIngresada;
		bool dimensionPermitida = false;
		string ingreso;
		do{
				cout << "Dimensiones Tablero" << endl;
				cout << "Ingrese el largo: ";
				cin  >> ingreso;
				dimensionIngresada.x = (unsigned)(atoi(ingreso.c_str()));
				cout << "Ingrese el ancho: ";
				cin  >> ingreso;
				dimensionIngresada.y = (unsigned)(atoi(ingreso.c_str()));
				cout << "Ingrese la altura maxima de fichas: ";
				cin  >> ingreso;
				dimensionIngresada.z = (unsigned)(atoi(ingreso.c_str()));
				dimensionPermitida = esValidaLa(dimensionIngresada);
				if(!dimensionPermitida){
						system("clear");
						cout << "Al menos dos de las dimensiones deben ser mayores o iguales a 4 (cuatro), y todas mayores a 0 (cero) ingrese nuevamente." << endl;
				}
		}while(!dimensionPermitida);
		system("clear");
		return dimensionIngresada;
}

void cartelNroDeRonda(unsigned numero, unsigned cantidadDeFilas){
	cout << "===========" << repetir('=',5*cantidadDeFilas)  << endl;
	cout << "  Ronda Nª " << numero << endl;
	cout << "===========" << repetir('=',5*cantidadDeFilas)  << endl;
}

char pedirDificultadDeJuego(){
		char dificultadIngresada;
		bool dificultadPermitida = false;
		do{
				cout << "Ingrese la dificultad deseada, (F)acil, (M)oderada o (D)ificil" << endl;
				cin >> dificultadIngresada;
				dificultadIngresada = (char)toupper(dificultadIngresada);
				dificultadPermitida = esValidaLa(dificultadIngresada);
				if(!dificultadPermitida){
						system("clear");
						cout << "El caracter ingresado no esta entre las opciones permitidas";
				}
		}while(!dificultadPermitida);
		system("clear");
		return dificultadIngresada;
}

int pedirCantidadDeJugadores(unsigned cantidadDeCeldas){
		unsigned cantidadDeJugadores;
		unsigned jugadoresMaxPorTablero = 0;
		(cantidadDeCeldas/4 > CANTIDAD_JUGADORES_MAX) ? jugadoresMaxPorTablero = CANTIDAD_JUGADORES_MAX :
																jugadoresMaxPorTablero = cantidadDeCeldas/4;

		bool cantidadPermitida = false;
		do{
				cout << "Ingrese la cantidad de jugadores deseada de "
				          << CANTIDAD_MIN_JUGADORES << " a " << jugadoresMaxPorTablero << ": ";
				cin >> cantidadDeJugadores;
				cantidadPermitida = esValidaLa(cantidadDeJugadores, jugadoresMaxPorTablero);
				if(!cantidadPermitida){
						system("clear");
						cout << "Cantidad de jugadores invalida para las dimensiones del tablero seleccionadas." << endl;
				}
		}while(!cantidadPermitida);
		system("clear");
		return cantidadDeJugadores;
}


Coordenada pedirIngresarFicha(Tablero* tablero, string color){
	Coordenada posicion;
	bool alturaValida = false;
	do{
		posicion = {0, 0, 1}; /*Predeterminado a la altura minima*/
		cout << color <<  "Por favor ingrese ficha en una fila y columna " << RESET << endl;
		cout << color << "Ingrese la columna -> " << RESET;
		cin >> posicion.y;
		cout << color << "Ingrese la fila ----> " << RESET;
		cin >> posicion.x;
		alturaValida = sePuedeIngresarFichaEn(posicion, tablero);
		imprimirSiNo(alturaValida, "No se puede ingresar fichas fuera del tablero, por favor re-ingrese su ficha");
	}while(!alturaValida);
	return posicion;
}

bool sePuedeIngresarFichaEn(Dimension &posicion, Tablero* tablero){
	bool sePuedeIngresarFicha = false;
	if(tablero->esValidaLa(posicion)){
		posicion.z = tablero->obtenerAlturaDeLa(posicion) + 1;
		sePuedeIngresarFicha = tablero->esValidaLa(posicion);
	}
	return sePuedeIngresarFicha;
}


bool esTableroMinimo(size_t dimension1, size_t dimension2, size_t dimension3){
	return (dimension1 >= 1 && dimension2 >= TAMANIO_MINIMO && dimension3 >= TAMANIO_MINIMO);
}

bool esValidaLa(Dimension dimensionIngresada){
	  return((esTableroMinimo(dimensionIngresada.x,dimensionIngresada.y,dimensionIngresada.z)) ||
			  	 (esTableroMinimo(dimensionIngresada.y,dimensionIngresada.x,dimensionIngresada.z)) ||
			  	 (esTableroMinimo(dimensionIngresada.z,dimensionIngresada.x,dimensionIngresada.y)) );
}


bool esValidaLa(char dificultadIngresada){
		return ((dificultadIngresada == DIFICULTAD_FACIL)   ||
						(dificultadIngresada == DIFICULTAD_MODERADA)||
						(dificultadIngresada == DIFICULTAD_DIFICIL));
}

bool esValidaLa(unsigned cantidadDeJugadores, unsigned jugadoresMaxPorTablero){
		return ((cantidadDeJugadores >= CANTIDAD_MIN_JUGADORES) && (cantidadDeJugadores <= jugadoresMaxPorTablero));
}

void mostrarResultados(unsigned jugadorGanador, string color){
	cout << "El " << color << "Jugador Numero "<< jugadorGanador << ". " << RESET <<"Ha Ganado, Felicitaciones!" << endl;
}

/* Jugador */

bool preguntar(string texto, char opcionVerdadero, char opcionFalsa){
		char opcion;
		do {
			cout << texto << "["<< opcionVerdadero << "/" << opcionFalsa <<"]: ";
			cin >> opcion;
		} while((opcion != opcionVerdadero) && (opcion != opcionFalsa));

		return (opcion == opcionVerdadero);
}

bool preguntaRobarCarta(){
	return preguntar("Desea Robarle la carta a un jugador?", 's', 'n');
}

bool preguntaRobarCartaJugador(){
	return preguntar("Desea Robarle la carta al jugador?", 's', 'n');
}

bool preguntaCualCartaRobarAlJugador(){
	return preguntar("Cual Carta desea Robarle al jugador?", 's', 'n');
}

unsigned obtenerCualCartaRobarAlJugador(ListaSimple<CartaAbstracta*>* manoDeCartas){
	unsigned posicionCartaElegida;
	bool posicionValidaDeLaCarta = false;
	do{
		cout<< "Elija un carta que desee robar: "<< endl;
		cin >> posicionCartaElegida;
		posicionValidaDeLaCarta = esCartaValida(manoDeCartas, posicionCartaElegida);
		imprimirSiNo(posicionValidaDeLaCarta, "Carta elegida invalida, re-ingrese porfavor");
	}while(!posicionValidaDeLaCarta);

	return posicionCartaElegida;
}

bool esCartaValida(ListaSimple<CartaAbstracta*>* manoDeCartas, unsigned posicionCarta) {
	bool cartaValida = (posicionCarta <= manoDeCartas->contarElementos() && posicionCarta > 0);
	return cartaValida;
}

Jugador* obtenerJugadorASerRobado(ListaSimple<Jugador*>* jugadores, Jugador* jugadorActual){
	unsigned posicionJugadorElegido;
	bool posicionValida = false;
	do{
		cout<< "Elija un jugador para Robar: "<< endl;
		cin >> posicionJugadorElegido;

		posicionValida = esValidoElJugadorParaRobar(jugadores, posicionJugadorElegido, jugadorActual);

		imprimirSiNo(posicionValida, "Jugador no apto para robar alguna carta, porfavor re-Ingrese");
	}while(!posicionValida);

	return jugadores->obtener(posicionJugadorElegido);
}

bool esValidoElJugadorParaRobar(ListaSimple<Jugador*>* jugadores, unsigned posicionJugador, Jugador* jugadorActual) {
	bool tieneCartas = false;
	unsigned cantidadDeCartas;
	if(jugadores->contarElementos() >= posicionJugador && posicionJugador > 0){
		Jugador* jugadorElegido = jugadores->obtener(posicionJugador);
		if(jugadorElegido != jugadorActual){
			cantidadDeCartas = jugadorElegido->consultarCantidadDeCartas();
			tieneCartas = (cantidadDeCartas > 0);
		}
	}
	return tieneCartas;
}

bool consultarJugadorJugarCarta(){
	return preguntar("Desea jugar una carta antes de ingresar ficha?", 's', 'n');
}

bool rangoPosicionValida(ListaSimple<CartaAbstracta*>* manoDeCartas, unsigned posicionCarta){
	return ((posicionCarta > 0) && (posicionCarta <= manoDeCartas->contarElementos()));
}

unsigned elegirCartaParaJugar(ListaSimple<CartaAbstracta*>* manoDeCartas){
	unsigned posicionCarta;
	string opciones;

	short int i = 1;
	manoDeCartas->iniciarCursor();
	while(manoDeCartas->avanzarCursor()){
		if(!manoDeCartas->obtenerCursor()){
			opciones += to_string(i) + ",";
		}
		i++;
	}
	opciones.resize(opciones.size());

	do{
		cout<< "Cual carta? ["<< opciones << "] Salir["<< CARTA_NULA << "] --> ";
		cin >> posicionCarta;

	}while(!rangoPosicionValida(manoDeCartas, posicionCarta) && posicionCarta != CARTA_NULA);


	return rangoPosicionValida(manoDeCartas, posicionCarta) ? posicionCarta: CARTA_NULA;
}

Coordenada pedirCoordenadaDeFicha(Tablero* tablero, string colorJugador, string descripcionPosicion){
	Coordenada posicion;
	bool coordenadaValida = false;
	do{
		posicion = pedirPosicion(tablero, descripcionPosicion, colorJugador);
		Jugador* celdaSeleccionada = tablero->obtenerFichaEnCelda(posicion);
		coordenadaValida = !esCeldaVacia(celdaSeleccionada);

		imprimirSiNo(coordenadaValida, "En la posicion no se encontro ninguna ficha, por favor re-ingrese");
		}while(!coordenadaValida);
	return (posicion);
}



Coordenada pedirPosicion(Tablero* tablero, string descripcionPosicion, string color){

  Coordenada posicion;
  bool sonCasillerosDentroDelTablero = false;
  do{
    cout << color << "Ingrese la columna" << descripcionPosicion << " ->" << RESET;
    cin >> posicion.y;
    cout << color << "Ingrese la fila" << descripcionPosicion << " ->" << RESET;
    cin >> posicion.x;
    cout << color << "Ingrese la altura" << descripcionPosicion << " ->" << RESET;
    cin >> posicion.z;
    sonCasillerosDentroDelTablero = tablero->esValidaLa(posicion);
    imprimirSiNo(sonCasillerosDentroDelTablero, "La posicion deseada esta fuera del tablero, por favor re-ingrese");
  }while(!sonCasillerosDentroDelTablero);

  return posicion;
}

void imprimirSiNo(bool dato, string texto){
	if(!dato){
		cout << texto << endl;
	}
}

void mostrarMensaje(string texto, string color){
	cout << color << texto << RESET << endl;
}

void obtenerCasillerosLaterales(Coordenada &casilleroUno, Coordenada &casilleroDos, Tablero* tablero, string color){
  bool sonCasillerosLaterales = false;
  bool sonLosMismosCasilleros = false;
  do{
    casilleroUno = pedirPosicion(tablero, " del primer casillero lateral", "");
    casilleroDos = pedirPosicion(tablero, " del segundo casillero lateral", "");
    sonLosMismosCasilleros = tablero->sonIguales(casilleroUno, casilleroDos);
    sonCasillerosLaterales = (tablero->esLateralEl(casilleroUno) && tablero->esLateralEl(casilleroDos));

    if(sonLosMismosCasilleros){
      cout << "Error, son los mismos casilleros! Re-ingrese porfavor" << endl;
    }
    if(!sonCasillerosLaterales){
      cout << "Error, alguno de los casilleros no son laterales! Re-ingrese porfavor" << endl;
    }

  }while(sonLosMismosCasilleros || !sonCasillerosLaterales);

}

string repetir(char letra, unsigned cantidadDeVeces){
	return string(cantidadDeVeces, letra);
}

string repetir(string letra, unsigned cantidadDeVeces){
	string cadena  = "";
	for(unsigned i = 0; i < cantidadDeVeces; i++){
		cadena.append(letra);
	}
	return cadena;
}

string extraerIzquierda(string texto, unsigned cantidadDePalabras){
	return texto.substr(cantidadLetras(texto) - cantidadDePalabras +1, cantidadDePalabras);
}

string extraerDerecha(string texto, unsigned cantidadDePalabras){
	return texto.substr(0 , cantidadDePalabras);
}

string extraerCentrado(string texto, unsigned cantidadDePalabras){
	unsigned extrarAdelante = (cantidadLetras(texto) - cantidadDePalabras) / 2;
	return texto.substr(extrarAdelante , cantidadDePalabras);
}


string justo(string texto, unsigned cantidadDePalabras){
	return extraerIzquierda(repetir(' ', cantidadDePalabras) + texto, cantidadDePalabras);
}

string justoCentrado(string texto, unsigned cantidadDePalabras){
	return extraerCentrado(repetir(' ',cantidadDePalabras) + texto + repetir(' ',cantidadDePalabras), cantidadDePalabras);
}

string justoIzquierda(string texto, unsigned cantidadDePalabras){
	return extraerDerecha(texto + repetir(' ', cantidadDePalabras) , cantidadDePalabras);
}

unsigned cantidadLetras(unsigned numero){
	string texto = to_string(numero);
	return cantidadLetras(texto);
}

unsigned cantidadLetras(string texto){
	return (unsigned)texto.size();
}

void crearMatriz(BMP &Sample, int filas,int columnas,int origenX, int origenY,int grosor, RGBApixel color){
  int largo = 50;//
  int ancho = 50;//
  int largoTotal = largo * filas;
  int anchoTotal = ancho * columnas;

  // lineas exteriores
  DrawLine(Sample,origenX,origenY,origenX,largoTotal+ origenY,color);//IZquierda
  DrawLine(Sample,origenX + anchoTotal,origenY,origenX + anchoTotal,largoTotal+ origenY,color);//derecha
  DrawLine(Sample,origenX,origenY + largoTotal,anchoTotal + origenX,origenY + largoTotal,color); // abajo
  DrawLine(Sample,origenX,origenY,anchoTotal + origenX,origenY,color);//arriba

  //Lineas del medio vertical
  for(int i = origenX + ancho; i < origenX + anchoTotal; i += ancho){
      DrawLine(Sample,i,origenY,i,largoTotal+ origenY,color);
  }

  //lineas del medio Horizontal
  for(int i = origenY + largo; i < origenY + largoTotal; i += largo){
      DrawLine(Sample,origenX,i,origenX + anchoTotal,i,color);
  }

  // agregando grosor a la matriz
  int medioGrosor = grosor/2;
  // lineas exteriores
  for(int i = origenX - medioGrosor;i < origenX + medioGrosor;i++){
    DrawLine(Sample,i,origenY - medioGrosor,i,largoTotal+ origenY + medioGrosor,color);//IZquierda
  }

  for(int i = origenY- medioGrosor;i < origenY + medioGrosor;i++){
    DrawLine(Sample,origenX,i,anchoTotal + origenX,i,color);//arriba
  }

  for(int i = origenX + medioGrosor;i > origenX - medioGrosor;i--){
    DrawLine(Sample,i + anchoTotal,origenY - medioGrosor,i + anchoTotal,largoTotal+ origenY + medioGrosor,color);//derecha
  }

  for(int i = origenY + medioGrosor;i > origenY - medioGrosor;i--){
    DrawLine(Sample,origenX,i + largoTotal,anchoTotal + origenX,i + largoTotal,color); // abajo
  }

  //lineas interiores


  //Lineas del medio vertical
  for(int i = origenX + ancho; i < origenX + anchoTotal; i += ancho){
    for(int j = i - medioGrosor; j < i + medioGrosor; j++){
      DrawLine(Sample,j,origenY,j,largoTotal+ origenY,color);
    }
  }
  for(int i = origenY + largo; i < origenY + largoTotal; i += largo){
    for(int j = i - medioGrosor; j < i + medioGrosor; j++){
      DrawLine(Sample,origenX,j,origenX + anchoTotal,j,color);
    }
  }
}

void crearFicha(BMP & Sample,int origenX, int origenY,RGBApixel color){

  int largoDeFicha = 20;
  int anchoDeFicha = 20;
  for(int i=origenX;i < origenX + anchoDeFicha;i++){
    for(int j =origenY;j < origenY + largoDeFicha;j++){
      Sample.SetPixel(i,j,color);
    }
  }
}




void mostrarBPM(Tablero* tablero){
	Dimension delTablero  = tablero->consultarDimensiones();
	ListaSimple<Color>* colores = new ListaSimple<Color>();
	inicializarColores(colores);
	BMP tableroDelBMP;
	RGBApixel negro = {0,0,0,0};
	int anchoDeLaImagen = (int)delTablero.y * 50 + 100 ;
	int altoDeLaImagen = ((int)delTablero.x * 50 + 50) * (int)delTablero.z + 100;
	tableroDelBMP.SetSize(anchoDeLaImagen,altoDeLaImagen);
	int cambioDeOrigenYSegunElNivel = 0;
	string nivel = "Nivel: ";
	for(size_t altura = 1; altura <= delTablero.z;altura++){
		string nivelActual = nivel + to_string(altura);
		const char * nivelBMP = nivelActual.c_str();
		int origenXDelNivel = 50;
		int origenYDelNivel = 50 + cambioDeOrigenYSegunElNivel;
		int origenXMatriz = 50;
		int origenYMatriz = 75 + cambioDeOrigenYSegunElNivel;
		Jugador * ficha;

		Dimension posicion;
		RGBApixel color;
		posicion = {0,0,altura};
		PrintString(tableroDelBMP,(char *)nivelBMP,origenXDelNivel,origenYDelNivel,10,negro);
		crearMatriz(tableroDelBMP,(int)delTablero.x,(int)delTablero.y,origenXMatriz,origenYMatriz,10,negro);
		for(int i = origenYMatriz + 15; i < origenYMatriz + (int)delTablero.x * 50; i +=50){ // 15 es el valor de desfasje para el origen de la ficha, 50 es (en el incremento de i) es la distancia siguente para el origen de otra ficha
			posicion.x++;
			for(int j = origenXMatriz + 15; j < origenXMatriz + (int)delTablero.y * 50;j +=50){ // 50 (in la comparacion de i) es el largo y ancho de los cuadrados de la matriz
				posicion.y++;
				ficha = tablero->obtenerFichaEnCelda(posicion);
				if(ficha != NULL){
					string colorJugador = ficha->consultarColor();
					color = buscarColorRGBA(colorJugador,colores);
					crearFicha(tableroDelBMP,j,i,color);
				}
			}
				posicion.y = 0;
		}
		cambioDeOrigenYSegunElNivel += ((int)delTablero.x * 50 + 50);
	}


	tableroDelBMP.WriteToFile("tablero.bmp");
}

void inicializarColores(ListaSimple<Color>* colores){
	Color negro = 	{ {0,0,0,0}, RESET};
	Color azul = 		{ {255,0,0,0}, AZUL} ;
	Color verde = 	{ {0,255,0,0}, VERDE} ;
	Color rojo = 		{ {0,0,255,0}, ROJO};
	Color amarillo ={ {0,255,255,0}, AMARILLO};
	Color blanco =	{ {255,255,255,0}, BLANCO};
	Color naranja = { {0,100,255,0}, NARANJA};
	Color rosado ={ {150,150,255,0}, ROSADO};
	Color celeste = { {255,255,0,0}, CELESTE};
	Color ocre = { {10,135,183,0}, OCRE};
	Color rosa = { {190,67,190,0}, ROSA};
	Color hoja = { {0,140,0,0}, HOJA};
	Color aquamarina = { {211,255,175,0}, AQUAMARINA};
	Color marron = { {40,40,165,0}, MARRON};
	Color purpura = { {230,50,150,0}, PURPURA};
	Color gris = { {190,190,190,0}, GRIS};
	Color bordo = { {0,0,150,0}, BORDO};
	Color marino = { {117,17,0,0}, MARINO};
	Color libre = { {255,255,255,0}, ESPACIO_LIBRE};

	colores->agregar(negro);
	colores->agregar(libre);
	colores->agregar(azul);
	colores->agregar(verde);
	colores->agregar(rojo);
	colores->agregar(amarillo);
	colores->agregar(blanco);
	colores->agregar(naranja);
	colores->agregar(rosado);
	colores->agregar(celeste);
	colores->agregar(ocre);
	colores->agregar(rosa);
	colores->agregar(hoja);
	colores->agregar(aquamarina);
	colores->agregar(marino);

}

RGBApixel buscarColorRGBA(string colorJugador, ListaSimple<Color>* colores){
	Color* colorEncontrado = NULL;
	colores->iniciarCursor();
	while(colores->avanzarCursor() && !colorEncontrado){

		Color colorActual = colores->obtenerCursor();
	//	cout << colorActual.colorTerminal << "Estoy aqui jejeje color lista" << RESET << endl;
		//cout << colorJugador << "color jugador" << RESET << endl;
		if(colorJugador.compare(colorActual.colorTerminal) == 0){
			colorEncontrado = (&colorActual);
		}
	}

	return (colorEncontrado->colorRGBA);
}
