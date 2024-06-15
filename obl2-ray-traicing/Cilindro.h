#pragma once
#include "../Objeto.h"

class Cilindro : public Objeto {
private:
	float radio, altura;
	MathVector centro;
	MathVector direccion;


public:

	Cilindro(MathVector centro, MathVector direccion, float radio, float altura, Color color);

	void intersepcion(Rayo rayo, int& idObjetoInterseptado, float& t);

	MathVector getNormal(MathVector punto);

	std::vector<Objeto*> getObjetosInternos();

	Color getColorBase(MathVector punto);

	Color getColor(Rayo rayo, float t_int);
};