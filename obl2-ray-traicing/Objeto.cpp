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

	
	// Calculo luz difuza y especular

	MathVector normal = normalizar(getNormal(posicionIntersepcion));

	for (int i = 0; i < numeroLuces; i++) {
		LuzPuntual ld = ObjetosEscena::getInstancia()->lucesDifusas[i];
		MathVector posicionLuzSegunPixel = normalizar(restar(ld.posicion, posicionIntersepcion));

		float coeficiente_luz_por_obstruccion = coeficienteDeIntersepcion[i];

		MathVector vectorALaLuz = restar(posicionIntersepcion, ld.posicion);

		float distanciaConLuz = norma(vectorALaLuz);

		float atenuacion = fmin(1.0f, 1 / (atenuacion_constante + antenuacion_lineal * distanciaConLuz + atenuacion_cuadratica * powf(distanciaConLuz, 2)));

		float coeficienteDifusa = productoEscalar(posicionLuzSegunPixel, normal);
		coeficienteDifusa = fmax(coeficienteDifusa, 0.f);

		MathVector vectorRefraxion = normalizar(simetrico(normal, normalizar(vectorALaLuz)));

		float coeficienteEspecular = powf(productoEscalar(normalizar(rayo.dirrecion), vectorRefraxion), exponenteReflexionEspecular);
		
		coeficienteEspecular = fmax(coeficienteEspecular, 0.f);




		Color luzDifusaYEspecular = {
						(coeficiente_luz_por_obstruccion * atenuacion * (ld.intensidad.r / 255.f)) * (colorBase.r * coeficienteDifusa * sensibilidad_luz_difusa + coeficienteEspecular * fracionLuzReflejadaEspecular * colorEspecular.r),
						(coeficiente_luz_por_obstruccion * atenuacion * (ld.intensidad.g / 255.f)) * (colorBase.g * coeficienteDifusa * sensibilidad_luz_difusa + coeficienteEspecular * fracionLuzReflejadaEspecular * colorEspecular.g),
						(coeficiente_luz_por_obstruccion * atenuacion * (ld.intensidad.b / 255.f)) * (colorBase.b * coeficienteDifusa * sensibilidad_luz_difusa + coeficienteEspecular * fracionLuzReflejadaEspecular * colorEspecular.b),
		};

		colorTotal.r += luzDifusaYEspecular.r;
		colorTotal.g += luzDifusaYEspecular.g;
		colorTotal.b += luzDifusaYEspecular.b;
	}


	return colorTotal;
}
