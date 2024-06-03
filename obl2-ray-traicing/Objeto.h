#include "MathVector.h"
#include "Rayo.h"
#include <FreeImage.h>
#include "Color.h"

#ifndef OBJETO_CLASS
#define OBJETO_CLASS

#define SENSIBILIDAD_LUZ_AMBIENTE_POR_DEFECTO 1.0f
#define SENSIBILIDAD_LUZ_DIFUSA_POR_DEFECTO 0.9f
#define SENSIBLIDAD_LUZ_ESPECULAR_POR_DEFECTO 0.0f
#define SENSIBILIDAD_TRANSPARENCIA 0.0f

#define ATENUACION_CONSTANTE_DEFECTO 1.0f
#define ATENUACION_LINEAL_DEFECTO 0.0f
#define ATENUACION_CUADRATICA_DEFECTO 0.0f 

#define EXPONENTE_REFELXION_ESPECULAR_DEFECTO 3;
#define FRACION_LUZ_REFLEJADA_ESPECULAR_DEFECTO 0.45f



class Objeto{

protected: 
	Color colorBase;
	float sensibilidad_luz_ambiente = SENSIBILIDAD_LUZ_AMBIENTE_POR_DEFECTO;

	float atenuacion_constante = ATENUACION_CONSTANTE_DEFECTO;
	float antenuacion_lineal = ATENUACION_LINEAL_DEFECTO;
	float atenuacion_cuadratica = ATENUACION_CUADRATICA_DEFECTO;

	int exponenteReflexionEspecular = EXPONENTE_REFELXION_ESPECULAR_DEFECTO; 
	float fracionLuzReflejadaEspecular = FRACION_LUZ_REFLEJADA_ESPECULAR_DEFECTO;
	Color colorEspecular = { 255.f, 255.f, 255.f };

public:
	float coeficienteReflexion = SENSIBLIDAD_LUZ_ESPECULAR_POR_DEFECTO; // ks
	float coeficienteTransparencia = SENSIBILIDAD_TRANSPARENCIA; // kt
	float sensibilidad_luz_difusa = SENSIBILIDAD_LUZ_DIFUSA_POR_DEFECTO;
	virtual float intersepcion(Rayo rayo) = 0;
	
	Color getColor(Rayo rayo, float t, int profundidad);

	virtual MathVector getNormal(MathVector punto) = 0;

	void setAtenuacion(float atenuacionConstante, float atenuacionLineal, float atenuacionCuadratica) {
		this->atenuacion_constante = atenuacionConstante;
		this->antenuacion_lineal = atenuacionLineal;
		this->atenuacion_cuadratica = atenuacionCuadratica;		
	}

	void setParametrosEspeculares(int exponenteRefrexionEspecular, float fracionLuzReflejadaEspecular, Color colorEspecular) {
		this->exponenteReflexionEspecular = exponenteRefrexionEspecular;
		this->fracionLuzReflejadaEspecular = fracionLuzReflejadaEspecular;
		this->colorEspecular = colorEspecular;
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