#pragma once
#include "../Objeto.h"

class Cilindro : public Objeto {
private:
	float radio, altura;
	MathVector centro;
	MathVector direccion;


public:

	Cilindro(MathVector centro, MathVector direccion, float radio, float altura, Color color);

	float intersepcion(Rayo rayo);

	MathVector getNormal(MathVector punto);
	Color getColor(Rayo rayo, float t);
};