#ifndef EXCEPCIONERROR_H_
#define EXCEPCIONERROR_H_

#include "Declaraciones.h"

class ExcepcionError {

private:
	unsigned int posicion;
	std::string descripcion;

public:
	ExcepcionError(unsigned int posicion);

	ExcepcionError(std::string error);

	unsigned int obtenerPosicionInvalida();

	std::string obtenerDescripcion();

	~ExcepcionError();
};

#endif /* EXCEPCIONERROR_H_ */
