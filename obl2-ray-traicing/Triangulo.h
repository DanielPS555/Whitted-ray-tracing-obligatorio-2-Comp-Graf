#include "../Objeto.h"

class Triangulo : public Objeto {
private:
	MathVector v0;
	MathVector v1;
	MathVector v2;


public:

	Triangulo(MathVector v0, MathVector v1, MathVector v2, RGBQUAD color);

	float intersepcion(Rayo rayo);
};