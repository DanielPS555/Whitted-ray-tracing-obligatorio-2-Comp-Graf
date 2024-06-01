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

	// Calculo luz difuza 

	MathVector normal = getNormal(posicionIntersepcion);

	for (int i = 0; i < ObjetosEscena::getInstancia()->numeroLucesDifusas; i++) {
		LuzDifusa ld = ObjetosEscena::getInstancia()->lucesDifusas[i];
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

		float coeficiente = productoEscalar(posicionLuzSegunPixel, normal);
		coeficiente = fmax(coeficiente, 0.f);
		Color luzDifusa = {
						(ld.intensidad.r / 255.f) * sensibilidad_luz_difusa* colorBase.r * coeficiente * coeficiente_luz_por_obstruccion, //ToDO sensibilidad_luz_ambiente cambiar
						(ld.intensidad.g / 255.f) * sensibilidad_luz_difusa* colorBase.g * coeficiente * coeficiente_luz_por_obstruccion,
						(ld.intensidad.b / 255.f) * sensibilidad_luz_difusa* colorBase.b * coeficiente * coeficiente_luz_por_obstruccion
		};



		colorTotal.r += luzDifusa.r;
		colorTotal.g += luzDifusa.g;
		colorTotal.b += luzDifusa.b;
	}

	return colorTotal;
}
