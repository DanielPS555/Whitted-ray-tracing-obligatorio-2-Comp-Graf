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

Color ObjetosEscena::getPixelPorRayo(Rayo rayo, int profundidad) {

	int indiceObjetoMasCercano = -1;
	float t_min = -1;

	getIntersepcionMasCercana(rayo, indiceObjetoMasCercano, t_min);

	if (indiceObjetoMasCercano == -1) {
		return bgColor;
	}
	else {
		return elementos[indiceObjetoMasCercano]->getColor(rayo, t_min,profundidad);
	}
	
}