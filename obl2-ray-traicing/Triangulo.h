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

	MathVector t_v0; //Posicion textura del v0, no se usa la corrdenada z
	MathVector t_v1;
	MathVector t_v2;

	MathVector vectorNormalV0, vectorNormalV1, vectorNormalV2;

	int widthBitmap, heightBitmap;

	FIBITMAP* bitmap;

	void corrBarisentricas(MathVector punto, float& l_0, float& l_1, float& l_2);

public:

	Triangulo(MathVector v0, MathVector v1, MathVector v2, Color color);

	Triangulo(MathVector v0, MathVector v1, MathVector v2, MathVector vectorNormalV0, MathVector vectorNormalV1, MathVector vectorNormalV2, Color color);

	Triangulo(MathVector v0, MathVector v1, MathVector v2, MathVector n_v0, MathVector n_v1, MathVector n_v2, MathVector t_v0, MathVector t_v1, MathVector t_v2, FIBITMAP* bitmap, Color color);

	MathVector getNormal(MathVector punto);

	void intersepcion(Rayo rayo, int& idObjetoInterseptado, float& t);

	std::vector<Objeto*> getObjetosInternos();

	Color getColor(Rayo rayo, float t, int profunidad);

	Color getColorBase(MathVector punto);
};

#endif // !TRIANGULO_CLASS

