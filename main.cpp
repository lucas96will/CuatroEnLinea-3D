/*
 * main.cpp
 *
 */

#include <ctime>
#include <cstdlib>
#include <iostream>
#include "CuatroEnLinea.h"
#include "Interfaz.h"
#include "ExcepcionError.h"


int main (){
	srand((unsigned)time(NULL));
	CuatroEnLinea* iniciarJuego;

	try{
		iniciarJuego = new CuatroEnLinea();
	}	catch (ExcepcionError &error) {
		std::cout << error.obtenerDescripcion() << std::endl;
	}

	delete iniciarJuego;
	return 0;
}
