#include "Objeto.h"
#include "Color.h"
#include "Utils.h"

#ifndef TRIANGULO_CLASS
#define TRIANGULO_CLASS

class Triangulo : public Objeto {
private:
	MathVector v0;
	MathVector v1;
	MathVector v2;

	MathVector vectorNormalV0, vectorNormalV1, vectorNormalV2;

public:

	Triangulo(MathVector v0, MathVector v1, MathVector v2, Color color);

	Triangulo(MathVector v0, MathVector v1, MathVector v2, MathVector vectorNormalV0, MathVector vectorNormalV1, MathVector vectorNormalV2, Color color);

	MathVector getNormal(MathVector punto);

	void intersepcion(Rayo rayo, int& idObjetoInterseptado, float& t);

	std::vector<Objeto*> getObjetosInternos();

	Color getColor(Rayo rayo, float t, int profunidad);
};

#endif // !TRIANGULO_CLASS

