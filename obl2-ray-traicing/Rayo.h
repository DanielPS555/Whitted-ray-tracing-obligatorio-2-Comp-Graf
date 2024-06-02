#include "MathVector.h"

#ifndef RAYO_STRUCT
#define RAYO_STRUCT

struct Rayo {
	MathVector puntoAnclaje;
	MathVector dirrecion;
};

// Devuelve la posicion siguiendo el rayo, durante t. Resta una pequeña tolerancia para disernir el caso de chocar de forma intera o externa con la esfera o cilindo
MathVector getPosicion(Rayo r, float t,  float tolerancia);


#endif // !RAYO_STRUCT


