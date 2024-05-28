#include "ObjetosEscena.h"


void ObjetosEscena::setElementos(unsigned numeroElementos, Objeto** elementos) {
	this->elementos = elementos;
	this->numeroElementos = numeroElementos;
}

RGBQUAD ObjetosEscena::getPixelPorRayo(Rayo rayo) {
	float minT = -1;
	RGBQUAD color = bgColor;

	for (int i = 0; i < numeroElementos; i++) {
		float t = elementos[i]->intersepcion(rayo);
		if (t != -1) {
			if (minT == -1 || minT > t) {
				minT = t;
				color = elementos[i]->getColorBase();
			}
		}
	}

	return color;
}