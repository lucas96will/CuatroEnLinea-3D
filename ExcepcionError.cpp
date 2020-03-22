#include "ExcepcionError.h"

ExcepcionError::ExcepcionError(unsigned int posicion){
	this->posicion = posicion;
	this->descripcion = "Se intento acceder a una posicion no valida dentro de una lista (unsigned int)";

}

ExcepcionError::ExcepcionError(std::string error){
	this->posicion = 0;
	this->descripcion = error;

}

unsigned int ExcepcionError::obtenerPosicionInvalida(){
	return this->posicion;
}

std::string ExcepcionError::obtenerDescripcion(){
	return this->descripcion;
}

ExcepcionError::~ExcepcionError() {
}

