#include "../Objeto.h"

class Esfera: public Objeto{
private:
	float radio;
	MathVector centro;


public:

	Esfera(MathVector centro, float radio, Color color);

	MathVector getNormal(MathVector punto);

	std::vector<Objeto*> getObjetosInternos();

	Color getColorBase(MathVector punto);

	void intersepcion(Rayo rayo, int& idObjetoInterseptado, float& t);
};

