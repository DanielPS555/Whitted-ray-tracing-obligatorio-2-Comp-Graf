#include "../Objeto.h"

class Esfera: public Objeto{
private:
	float radio;
	MathVector centro;


public:

	Esfera(MathVector centro, float radio, Color color);

	MathVector getNormal(MathVector punto);
	float intersepcion(Rayo rayo);
};

