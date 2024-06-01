#include "Rayo.h"



MathVector getPosicion(Rayo r, float t, float tolerancia) {
	return sumar(r.puntoAnclaje, multiplicarPorEscalar(r.dirrecion, t- tolerancia));
}