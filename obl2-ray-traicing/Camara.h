#include "MathVector.h"
#include "Rayo.h"
#include "../ObjetosEscena.h"

#ifndef CAMARA_CLASS
#define CAMARA_CLASS


#define ANGULO_VISION_CAMARA_DEFECTO 45.0f

class Camara{
private:
	// Parametros por constructor
	MathVector dirrecionArriba;
	MathVector dirrecionPuntoVista;
	MathVector ubicacionPuntoVista;

	float anguloVisionCamara;

	// Valores calculados
	MathVector ubicacionCamara;



public:

	Camara(MathVector up, MathVector lookupDirrecion, MathVector lookUpPosition);

	Rayo getRayo(int x, int y);


};
#endif // !CAMARA_CLASS
