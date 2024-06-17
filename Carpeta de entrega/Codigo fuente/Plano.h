#pragma once
#include "Objeto.h"

class Plano : public Objeto
{
private:
	MathVector puntoDeAnclaje;
	MathVector u;
	MathVector v;


	MathVector normalCalculada;

public:

	Plano(MathVector puntoDeAnclaje, MathVector vectorU, MathVector vectorV, Color color);

	void intersepcion(Rayo rayo, int& idObjetoInterseptado, float& t);

	std::vector<Objeto*> getObjetosInternos();

	MathVector getNormal(MathVector punto);

	Color getColorBase(MathVector punto);
};

