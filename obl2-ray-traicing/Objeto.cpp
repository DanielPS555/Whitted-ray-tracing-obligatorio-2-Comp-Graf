#include "Objeto.h"
#include "Utils.h"
#include "ObjetosEscena.h"
#include "LuzAmbiente.h"

Color Objeto::getColor(Rayo rayo, float t) {

	Color colorTotal = { 0.0f,0.f,0.f };

	MathVector posicionIntersepcion = getPosicion(rayo, t, EPSILON);

	// Calculo luz ambiente

	LuzAmbiente luzAmbiente = ObjetosEscena::getInstancia()->luzAmbiente;

	Color colorConLuzAmbiente = getLuzAmbientePorObjeto(luzAmbiente, colorBase, sensibilidad_luz_ambiente);


	colorTotal.r = colorConLuzAmbiente.r;
	colorTotal.g = colorConLuzAmbiente.g;
	colorTotal.b = colorConLuzAmbiente.b;

	// Calculo de intersepciones con las luces

	int numeroLuces = ObjetosEscena::getInstancia()->numeroLucesDifusas;

	float* coeficienteDeIntersepcion = new float[numeroLuces];
	
	for (int i = 0; i < numeroLuces; i++) {
		LuzPuntual ld = ObjetosEscena::getInstancia()->lucesDifusas[i];
		MathVector posicionLuzSegunPixel = normalizar(restar(ld.posicion, posicionIntersepcion));

		float coeficiente_luz_por_obstruccion = 1.0f;

		Rayo rayoAuxiliar = { posicionIntersepcion , posicionLuzSegunPixel };
		MathVector puntoDeAnclajeSeparadoDeFigura = getPosicion(rayoAuxiliar, 1.0f, 0);
		Rayo rayoIntersepcion = { puntoDeAnclajeSeparadoDeFigura , posicionLuzSegunPixel };

		int numero_objeto_mas_cercano_interseptado = -1;
		float t_minimo = -1;

		ObjetosEscena::getInstancia()->getIntersepcionMasCercana(rayoIntersepcion, numero_objeto_mas_cercano_interseptado, t_minimo);

		if (numero_objeto_mas_cercano_interseptado != -1) {
			MathVector posicionIntersepcionMasCercana = getPosicion(rayoIntersepcion, t_minimo, 0);
			float distanciaObjetoMasCercano = norma(restar(posicionIntersepcion, posicionIntersepcionMasCercana));
			float distanciaConLuz = norma(restar(posicionIntersepcion, ld.posicion));

			if (distanciaConLuz > distanciaObjetoMasCercano) {

			}
			coeficiente_luz_por_obstruccion = 0.0f;
		}

		coeficienteDeIntersepcion[i] = coeficiente_luz_por_obstruccion;
	}

	
	// Calculo luz difuza 

	MathVector normal = getNormal(posicionIntersepcion);

	for (int i = 0; i < numeroLuces; i++) {
		LuzPuntual ld = ObjetosEscena::getInstancia()->lucesDifusas[i];
		MathVector posicionLuzSegunPixel = normalizar(restar(ld.posicion, posicionIntersepcion));

		float coeficiente_luz_por_obstruccion = coeficienteDeIntersepcion[i];

		float distanciaConLuz = norma(restar(posicionIntersepcion, ld.posicion));

		float atenuacion = fmin(1.0f, 1 / (atenuacion_constante + antenuacion_lineal * distanciaConLuz + atenuacion_cuadratica * powf(distanciaConLuz, 2)));

		float coeficiente = productoEscalar(posicionLuzSegunPixel, normal);
		coeficiente = fmax(coeficiente, 0.f);

		float atenuadoresConvinados = coeficiente * atenuacion * sensibilidad_luz_difusa * coeficiente_luz_por_obstruccion;

		Color luzDifusa = {
						(ld.intensidad.r / 255.f) * colorBase.r * atenuadoresConvinados, //ToDO sensibilidad_luz_ambiente cambiar
						(ld.intensidad.g / 255.f) * colorBase.g * atenuadoresConvinados,
						(ld.intensidad.b / 255.f) * colorBase.b * atenuadoresConvinados
		};

		colorTotal.r += luzDifusa.r;
		colorTotal.g += luzDifusa.g;
		colorTotal.b += luzDifusa.b;
	}


	//Calculo de luz especular

	return colorTotal;
}
