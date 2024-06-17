#include "Objeto.h"
#include "MathVector.h"
#include "Triangulo.h"
#include "vector"
#include "Freeimage/FreeImage.h"
#include "Utils.h"

#ifndef MALLA_CLASS_A
#define MALLA_CLASS_A

class MallaClass : public Objeto{
protected:	
	std::vector<Triangulo*> triangulos;
	std::vector<Triangulo*> volumenAcotante;

public:
	//Enviar nomArchivoTextura = nullptr cuando no haya textura que cargar
	MallaClass(const char* path, MathVector traslacion, float escalar, const char* nomArchivoTextura);

	void intersepcion(Rayo rayo, int& idObjetoInterseptado, float& t_int);
	MathVector getNormal(MathVector punto);
	std::vector<Objeto*> getObjetosInternos();
	Color getColorBase(MathVector punto);
	

};

#endif // !MALLA_CLASS




