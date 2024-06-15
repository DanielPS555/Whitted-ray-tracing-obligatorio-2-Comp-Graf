#include "../Objeto.h"
#include "MathVector.h"
#include "Triangulo.h"
#include "vector"

#ifndef MALLA_CLASS_A
#define MALLA_CLASS_A

class MallaClass : public Objeto{
protected:	
	std::vector<Triangulo*> triangulos;
	std::vector<Triangulo*> volumenAcotante;

public:
	MallaClass(const char* path, MathVector traslacion, float escalar);
	void intersepcion(Rayo rayo, int& idObjetoInterseptado, float& t_int);
	MathVector getNormal(MathVector punto);
	std::vector<Objeto*> getObjetosInternos();

	

};

#endif // !MALLA_CLASS




