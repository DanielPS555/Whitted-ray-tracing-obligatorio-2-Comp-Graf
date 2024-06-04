#include "Objeto.h"
#include "Utils.h"
#include "ObjetosEscena.h"
#include "LuzAmbiente.h"

Color Objeto::getColor(Rayo rayo, float t, int profundidad) {

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
				coeficiente_luz_por_obstruccion = 0.0f;
			}
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

		MathVector vectorEspecular = normalizar(simetrico(normal, normalizar(vectorALaLuz)));

		float coeficienteEspecular = powf(productoEscalar(normalizar(rayo.dirrecion), vectorEspecular), exponenteReflexionEspecular);
		
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

	if (profundidad < PROFUNDIDAD_MAX) {
		if (coeficienteReflexion > 0) {
			//vectorRefraxion = multiplicarPorEscalar(vectorRefraxion, -1);
			//R = 2(L⋅N)N−L

			MathVector vectorReflexion = normalizar(simetrico(normal, multiplicarPorEscalar(normalizar(rayo.dirrecion), -1)));
			Rayo aux = { posicionIntersepcion, vectorReflexion };
			MathVector puntoAnclajeAux = getPosicion(aux, 1.0f, 0);
			Rayo r = { puntoAnclajeAux , vectorReflexion };

			Color color_r = ObjetosEscena::getInstancia()->getPixelPorRayo(r, profundidad + 1);

			colorTotal.r += color_r.r * coeficienteReflexion;
			colorTotal.g += color_r.g * coeficienteReflexion;
			colorTotal.b += color_r.b * coeficienteReflexion;
		}

		//ley de snell dice que n1 sin01 = n2 sin02
		//se usa el cos porque es la información que podemos obtener a través del producto escalar.
		// por mas información del procedimiento consultar wikipedia ley de snell en lenguaje ingles.


		if (coeficienteTransparencia > 0) {
			float n1 = 1.0f; //transp del aire
			float n2 = indiceTransparencia;

			MathVector I = normalizar(rayo.dirrecion);
			MathVector N = normalizar(normal);

			float cosi = fmax(-1.0f, fmin(1.0f, productoEscalar(I, N)));
			if (cosi < 0) {
				cosi = -cosi;
			}
			else {
				std::swap(n1, n2);
				N = multiplicarPorEscalar(N, -1);
			}

			float eta = n1 / n2;
			float k = 1 - eta * eta * (1 - cosi * cosi);

			if (k >= 0) {
				MathVector refractada = sumar(multiplicarPorEscalar(I, eta), multiplicarPorEscalar(N, (eta * cosi - sqrtf(k))));

				Rayo aux2 = { posicionIntersepcion, refractada };
				MathVector puntoAnclajeAux = getPosicion(aux2, 1.0f, 0);
				Rayo r = { puntoAnclajeAux , refractada };

				Color color_t = ObjetosEscena::getInstancia()->getPixelPorRayo(r, profundidad + 1);

				colorTotal.r += color_t.r * coeficienteTransparencia;
				colorTotal.g += color_t.g * coeficienteTransparencia;
				colorTotal.b += color_t.b * coeficienteTransparencia;
			}
		}
	}


	return colorTotal;
}
