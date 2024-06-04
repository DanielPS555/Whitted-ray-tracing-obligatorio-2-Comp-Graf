#include "../Objeto.h"
#include "Color.h"
#include "Utils.h"

#ifndef TRIANGULO_CLASS
#define TRIANGULO_CLASS

class Triangulo : public Objeto {
private:
	MathVector v0;
	MathVector v1;
	MathVector v2;

	MathVector vectorNormal;

public:

	Triangulo(MathVector v0, MathVector v1, MathVector v2, Color color);

	MathVector getNormal(MathVector punto);

	float intersepcion(Rayo rayo);
	Color getColor(Rayo rayo, float t);
};

#endif // !TRIANGULO_CLASS