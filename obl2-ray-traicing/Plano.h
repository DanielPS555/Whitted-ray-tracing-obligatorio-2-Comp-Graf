#pragma once
#include "../Objeto.h"

class Plano : public Objeto
{
private:
	MathVector puntoDeAnclaje;
	MathVector u;
	MathVector v;


	MathVector normalCalculada;

public:

	Plano(MathVector puntoDeAnclaje, MathVector vectorU, MathVector vectorV, Color color);

	float intersepcion(Rayo rayo);

	MathVector getNormal(MathVector punto);
};

