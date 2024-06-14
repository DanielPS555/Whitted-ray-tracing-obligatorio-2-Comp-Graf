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

	Malla(std::string path, MathVector traslacion, float escalar);

	float intersepcion(Rayo rayo);

	MathVector getNormal(MathVector punto);


};

#endif // !MALLA_CLASS




