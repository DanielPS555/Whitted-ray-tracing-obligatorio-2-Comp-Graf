#include "ObjetosEscena.h"


void ObjetosEscena::setElementos(unsigned numeroElementos, Objeto** elementos) {
	this->elementos = elementos;
	this->numeroElementos = numeroElementos;
}

void ObjetosEscena::getIntersepcionMasCercana(Rayo rayo, int& indiceObjeto, float& t_intersepcion) {
	for (int i = 0; i < numeroElementos; i++) {
		float t = elementos[i]->intersepcion(rayo);
		if (t != -1) {
			if (t_intersepcion == -1 || t_intersepcion > t) {
				t_intersepcion = t;
				indiceObjeto = i;
			}
		}
	}

}

ColorCoef ObjetosEscena::getPixelPorRayo(Rayo rayo, int profundidad) {

	int indiceObjetoMasCercano = -1;
	float t_min = -1;
	ColorCoef bgf;
	bgf.base = bgColor;
	bgf.difus = bgColor;
	bgf.reflecc = bgColor;
	bgf.espec = bgColor;
	bgf.ambient = bgColor;
	bgf.transp = bgColor;
	getIntersepcionMasCercana(rayo, indiceObjetoMasCercano, t_min);

	if (indiceObjetoMasCercano == -1) {
		return bgf;
	}
	else {
		return elementos[indiceObjetoMasCercano]->getColor(rayo, t_min,profundidad);
	}
	
}

std::vector<Objeto*> ObjetosEscena::getIntersepcionesHastaDistancia(Rayo rayo, float distanciaMaxima) {
	std::vector<Objeto*> objetosInterseptados;
	for (int i = 0; i < numeroElementos; i++) {
		float t = elementos[i]->intersepcion(rayo);
		if (t != -1) {
			MathVector puntoIntersepcion = getPosicion(rayo, t, 0);
			float distanciaHastaPuntoIntersepcion = norma(restar(puntoIntersepcion, rayo.puntoAnclaje));

			if (distanciaMaxima > distanciaHastaPuntoIntersepcion) {
				objetosInterseptados.push_back(elementos[i]);
			}
		}
	}
	
	return objetosInterseptados;
}