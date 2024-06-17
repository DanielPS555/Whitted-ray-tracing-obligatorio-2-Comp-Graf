#include "Objeto.h"
#include "Utils.h"
#include "ObjetosEscena.h"
#include "LuzAmbiente.h"

int Objeto::sigId = 0;

ColorCoef Objeto::getColor(Rayo rayo, float t, int profundidad){

	ColorCoef colorTotal;
	colorTotal.base = { 0.0f,0.f,0.f };
	colorTotal.transp = { 0.0f,0.f,0.f };
	colorTotal.reflecc = { 0.0f,0.f,0.f };
	colorTotal.espec = { 0.0f,0.f,0.f };
	colorTotal.ambient = { 0.0f,0.f,0.f };
	colorTotal.difus = { 0.0f,0.f,0.f };
	colorTotal.primRecTrans = { 0.0f,0.f,0.f };
	colorTotal.primRecReflex = { 0.0f,0.f,0.f };


	

	// La suma de coeficiente_difusa_especular + coeficiente_reflexion + coeficiente_transaccion debe ser 1, cada color debe aportar esto
	float coeficiente_difusa_especular_corregido;
	float coeficiente_reflexion_corregido = this->coeficienteReflexion;
	float coeficiente_transparencia_corregido = this->coeficienteTransparencia;

	if (coeficiente_reflexion_corregido + coeficiente_transparencia_corregido > 1.0) {
		coeficiente_reflexion_corregido = coeficiente_reflexion_corregido / (coeficiente_reflexion_corregido + coeficiente_transparencia_corregido);
		coeficiente_transparencia_corregido = coeficiente_transparencia_corregido / (coeficiente_reflexion_corregido + coeficiente_transparencia_corregido);
		coeficiente_difusa_especular_corregido = 0.0f;
	}
	else {
		coeficiente_difusa_especular_corregido = 1.0f - (coeficiente_reflexion_corregido + coeficiente_transparencia_corregido);
	}

	MathVector posicionIntersepcion = getPosicion(rayo, t, EPSILON);

	Color colorObjeto = getColorBase(posicionIntersepcion);

	// Calculo de intersepciones con las luces

	int numeroLuces = ObjetosEscena::getInstancia()->numeroLucesDifusas;

	Color* coloresLucesInterseptadas = new Color[numeroLuces];
	
	for (int i = 0; i < numeroLuces; i++) {
		LuzPuntual ld = ObjetosEscena::getInstancia()->lucesDifusas[i];
		MathVector posicionLuzSegunPixel = normalizar(restar(ld.posicion, posicionIntersepcion));

		float coeficiente_luz_por_obstruccion = 1.0f;

		Rayo rayoAuxiliar = { posicionIntersepcion , posicionLuzSegunPixel };
		MathVector puntoDeAnclajeSeparadoDeFigura = getPosicion(rayoAuxiliar, 1.0f, 0);


		//Primer rayo
		Rayo rayoIntersepcion = { puntoDeAnclajeSeparadoDeFigura , posicionLuzSegunPixel };

		float distanciaConLuz = norma(restar(posicionIntersepcion, ld.posicion));

		std::vector<std::pair< Objeto*, MathVector>> objetosInterseptadosHastaLuz = ObjetosEscena::getInstancia()->getIntersepcionesHastaDistancia(rayoIntersepcion, distanciaConLuz);

		float intersepcionCanalR = 1.0;
		float intersepcionCanalG = 1.0;
		float intersepcionCanalB = 1.0;

		for (auto parr : objetosInterseptadosHastaLuz) {

			float coef_difusa_otro = 1.0f - parr.first->coeficienteReflexion - parr.first->coeficienteTransparencia;
			Color colorObjetoBase = parr.first->getColorBase(parr.second);


			intersepcionCanalR *= parr.first->coeficienteTransparencia * (parr.first->coeficienteTransparencia + coef_difusa_otro * colorObjetoBase.r / 255.f);
			intersepcionCanalG *= parr.first->coeficienteTransparencia * (parr.first->coeficienteTransparencia + coef_difusa_otro * colorObjetoBase.g / 255.f);
			intersepcionCanalB *= parr.first->coeficienteTransparencia * (parr.first->coeficienteTransparencia + coef_difusa_otro * colorObjetoBase.b / 255.f);
		}

		Color c = { intersepcionCanalR , intersepcionCanalG, intersepcionCanalB };
		coloresLucesInterseptadas[i] = c;
	}
	// ----- Calculo luz ambiente -----

	Color luzColorAmbiente = { 0.0f, 0.0f, 0.0f };
	Color luzColorDifusa = { 0.0f, 0.0f, 0.0f };
	Color luzColorEspecular = { 0.0f, 0.0f, 0.0f };

	LuzAmbiente luzFuenteAmbiente = ObjetosEscena::getInstancia()->luzAmbiente;
	luzColorAmbiente = getLuzAmbientePorObjeto(luzFuenteAmbiente, colorObjeto, sensibilidad_luz_ambiente);
	
	// ----- Calculo luz difuza y especular -----

	MathVector normal = normalizar(getNormal(posicionIntersepcion));


	for (int i = 0; i < numeroLuces; i++) {
		LuzPuntual ld = ObjetosEscena::getInstancia()->lucesDifusas[i];
		MathVector posicionLuzSegunPixel = normalizar(restar(ld.posicion, posicionIntersepcion));

		MathVector vectorALaLuz = restar(posicionIntersepcion, ld.posicion);



		float distanciaConLuz = norma(vectorALaLuz);

		float atenuacion = fmin(1.0f, 1 / (atenuacion_constante + antenuacion_lineal * distanciaConLuz + atenuacion_cuadratica * powf(distanciaConLuz, 2)));

		float coeficienteDifusa = productoEscalar(posicionLuzSegunPixel, normal);
		coeficienteDifusa = fmax(coeficienteDifusa, 0.f);

		MathVector vectorEspecular = normalizar(simetrico(normal, normalizar(vectorALaLuz)));

		float coeficienteEspecular = powf(productoEscalar(normalizar(rayo.dirrecion), vectorEspecular), exponenteReflexionEspecular);
		
		coeficienteEspecular = fmax(coeficienteEspecular, 0.f);


		Color luzColorDifusaPorLuz = {
						(coloresLucesInterseptadas[i].r * atenuacion * (ld.intensidad.r / 255.f)) * (colorObjeto.r * coeficienteDifusa * sensibilidad_luz_difusa),
						(coloresLucesInterseptadas[i].g * atenuacion * (ld.intensidad.g / 255.f)) * (colorObjeto.g * coeficienteDifusa * sensibilidad_luz_difusa),
						(coloresLucesInterseptadas[i].b * atenuacion * (ld.intensidad.b / 255.f)) * (colorObjeto.b * coeficienteDifusa * sensibilidad_luz_difusa),
		};

		Color luzColorEspecularPorLuz = {
						(coloresLucesInterseptadas[i].r * atenuacion * (ld.intensidad.r / 255.f)) * (coeficienteEspecular * fracionLuzReflejadaEspecular * colorEspecular.r),
						(coloresLucesInterseptadas[i].g * atenuacion * (ld.intensidad.g / 255.f)) * (coeficienteEspecular * fracionLuzReflejadaEspecular * colorEspecular.g),
						(coloresLucesInterseptadas[i].b * atenuacion * (ld.intensidad.b / 255.f)) * (coeficienteEspecular * fracionLuzReflejadaEspecular * colorEspecular.b),
		};

		luzColorDifusa.r += luzColorDifusaPorLuz.r;
		luzColorDifusa.g += luzColorDifusaPorLuz.g;
		luzColorDifusa.b += luzColorDifusaPorLuz.b;

		luzColorEspecular.r += luzColorEspecularPorLuz.r;
		luzColorEspecular.g += luzColorEspecularPorLuz.g;
		luzColorEspecular.b += luzColorEspecularPorLuz.b;

	}

	luzColorAmbiente = corregirColorMaximos(luzColorAmbiente);
	luzColorDifusa = corregirColorMaximos(luzColorDifusa);
	luzColorEspecular = corregirColorMaximos(luzColorEspecular);

	colorTotal.base.r += luzColorAmbiente.r * coeficiente_difusa_especular_corregido;
	colorTotal.base.g += luzColorAmbiente.g * coeficiente_difusa_especular_corregido;
	colorTotal.base.b += luzColorAmbiente.b * coeficiente_difusa_especular_corregido;

	colorTotal.base.r += luzColorDifusa.r * coeficiente_difusa_especular_corregido;
	colorTotal.base.g += luzColorDifusa.g * coeficiente_difusa_especular_corregido;
	colorTotal.base.b += luzColorDifusa.b * coeficiente_difusa_especular_corregido;

	colorTotal.base.r += luzColorEspecular.r;
	colorTotal.base.g += luzColorEspecular.g;
	colorTotal.base.b += luzColorEspecular.b;

	colorTotal.ambient = luzColorAmbiente;
	colorTotal.espec = luzColorEspecular; 
	colorTotal.difus = luzColorDifusa; 

	delete coloresLucesInterseptadas;

	if (profundidad < PROFUNDIDAD_MAX) {
		if (coeficiente_reflexion_corregido > 0) {
			//vectorRefraxion = multiplicarPorEscalar(vectorRefraxion, -1);
			//R = 2(L⋅N)N−L

			MathVector vectorReflexion = normalizar(simetrico(normal, multiplicarPorEscalar(normalizar(rayo.dirrecion), -1)));
			Rayo aux = { posicionIntersepcion, vectorReflexion };
			MathVector puntoAnclajeAux = getPosicion(aux, 1.0f, 0);
			Rayo r = { puntoAnclajeAux , vectorReflexion };

			ColorCoef color_r = ObjetosEscena::getInstancia()->getPixelPorRayo(r, profundidad + 1);

			colorTotal.base.r += color_r.base.r * coeficiente_reflexion_corregido;
			colorTotal.base.g += color_r.base.g * coeficiente_reflexion_corregido;
			colorTotal.base.b += color_r.base.b * coeficiente_reflexion_corregido;

			ColorCoef color_r_pri = ObjetosEscena::getInstancia()->getPixelPorRayo(r, PROFUNDIDAD_MAX);

			colorTotal.primRecReflex.r = color_r_pri.base.r * coeficiente_reflexion_corregido;
			colorTotal.primRecReflex.g = color_r_pri.base.g * coeficiente_reflexion_corregido;
			colorTotal.primRecReflex.b = color_r_pri.base.b * coeficiente_reflexion_corregido;
		}

		//ley de snell dice que n1 sin01 = n2 sin02
		//se usa el cos porque es la información que podemos obtener a través del producto escalar.
		// por mas información del procedimiento consultar wikipedia ley de snell en lenguaje ingles.


		if (coeficienteTransparencia > 0) {
			float n1 = 1.0f; //transp del aire
			float n2 = indiceTransparencia;

			MathVector I = normalizar(rayo.dirrecion);
			MathVector N = normalizar(normal);

			// si el coseno es negativo -> el rayo viene de afuera hacia adentro del objeto.
			float cosi = productoEscalar(I, N);
			if (cosi < 0) {
				cosi = -cosi;
			} // si el coseno es positivo -> el rayo viene de adentro del objeto hacia afuera.
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

				ColorCoef color_t = ObjetosEscena::getInstancia()->getPixelPorRayo(r, profundidad + 1);

				colorTotal.base.r += color_t.base.r * coeficiente_transparencia_corregido;
				colorTotal.base.g += color_t.base.g * coeficiente_transparencia_corregido;
				colorTotal.base.b += color_t.base.b * coeficiente_transparencia_corregido;

				ColorCoef color_t_pri = ObjetosEscena::getInstancia()->getPixelPorRayo(r, PROFUNDIDAD_MAX);

				colorTotal.primRecTrans.r = color_t_pri.base.r * coeficiente_transparencia_corregido;
				colorTotal.primRecTrans.g = color_t_pri.base.g * coeficiente_transparencia_corregido;
				colorTotal.primRecTrans.b = color_t_pri.base.b * coeficiente_transparencia_corregido;
			}
		}
	}

	colorTotal.transp.r = 255 * coeficiente_transparencia_corregido;
	colorTotal.transp.g = 255 * coeficiente_transparencia_corregido;
	colorTotal.transp.b = 255 * coeficiente_transparencia_corregido;
	colorTotal.reflecc.r = 255 * coeficiente_reflexion_corregido;
	colorTotal.reflecc.g = 255 * coeficiente_reflexion_corregido;
	colorTotal.reflecc.b = 255 * coeficiente_reflexion_corregido;


	return colorTotal;
}
