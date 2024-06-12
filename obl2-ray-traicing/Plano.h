#pragma once
#include "../Objeto.h"

class Plano : public Objeto
{
private:
	MathVector puntoBase;
	float D;

public:

	Plano(MathVector puntoBase, float D, Color color);

	float intersepcion(Rayo rayo);

	MathVector getNormal(MathVector punto);
};

