#include "../Objeto.h"
#include "MathVector.h"
#include "Triangulo.h"
#include "vector"

#ifndef MALLA_CLASS
#define MALLA_CLASS

class Malla : public Objeto{

protected:
	
	MathVector traslacion;
	float escalar;
	std::vector<Triangulo*> triangulos;

public:

	Malla(const char* path, MathVector traslacion, float escalar);

	float intersepcion(Rayo rayo);

	MathVector getNormal(MathVector punto);

	std::vector<Objeto*> getObjetosInternos();


};

#endif // !MALLA_CLASS




