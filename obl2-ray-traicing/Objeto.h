#include "MathVector.h"
#include "Rayo.h"
#include <FreeImage.h>
#include "Color.h"

#ifndef OBJETO_CLASS
#define OBJETO_CLASS

#define SENSIBILIDAD_LUZ_AMBIENTE_POR_DEFECTO 1.0f
#define SENSIBILIDAD_LUZ_DIFUSA_POR_DEFECTO 1.0f

#define ATENUACION_CONSTANTE_DEFECTO 1.0f
#define ATENUACION_LINEAL_DEFECTO 0.0f
#define ATENUACION_CUADRATICA_DEFECTO 0.0f 

class Objeto{

protected: 
	Color colorBase;
	float sensibilidad_luz_ambiente = SENSIBILIDAD_LUZ_AMBIENTE_POR_DEFECTO;
	float sensibilidad_luz_difusa = SENSIBILIDAD_LUZ_DIFUSA_POR_DEFECTO;

	float atenuacion_constante = ATENUACION_CONSTANTE_DEFECTO;
	float antenuacion_lineal = ATENUACION_LINEAL_DEFECTO;
	float atenuacion_cuadratica = ATENUACION_CUADRATICA_DEFECTO;

public:
	virtual float intersepcion(Rayo rayo) = 0;
	
	Color getColor(Rayo rayo, float t);

	virtual MathVector getNormal(MathVector punto) = 0;


	void setAtenuacion(float atenuacionConstante, float atenuacionLineal, float atenuacionCuadratica) {
		this->atenuacion_constante = atenuacionConstante;
		this->antenuacion_lineal = atenuacionLineal;
		this->atenuacion_cuadratica = atenuacionCuadratica;		
	}

	void setColorBase(Color color) {
		colorBase = color;
	}

	void setSensibilidadLuzAmbiente(float sensibilidad) {
		sensibilidad_luz_ambiente = sensibilidad;
	}

	Color getColorBase() {
		return colorBase;
	}
};

#endif // !OBJETO_CLASS