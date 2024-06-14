#include "ObjetosEscena.h"


void ObjetosEscena::setElementos( std::vector<Objeto*> elementosPrimerNivel) {
	this->objetosPrimerNivel = elementosPrimerNivel;
	
	for (Objeto* elementoPrimerNivel : elementosPrimerNivel) {
		for (Objeto* objetoInterno : elementoPrimerNivel->getObjetosInternos()) {			
			allObjetos[objetoInterno->getId()] = objetoInterno;
		}
	}

}

void ObjetosEscena::getIntersepcionMasCercana(Rayo rayo, int& idObjeto, float& t_intersepcion) {
	for (Objeto* elemento: objetosPrimerNivel) {
		float t;
		int id_choque;
		elemento->intersepcion(rayo, id_choque, t);
		if (t != -1) {
			if (t_intersepcion == -1 || t_intersepcion > t) {
				t_intersepcion = t;
				idObjeto = id_choque;
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
		return allObjetos[indiceObjetoMasCercano]->getColor(rayo, t_min,profundidad);
	}
	
}

std::vector<Objeto*> ObjetosEscena::getIntersepcionesHastaDistancia(Rayo rayo, float distanciaMaxima) {
	std::vector<Objeto*> objetosInterseptados;
	for (Objeto* elemento : objetosPrimerNivel) {

		float t;
		int id;
		elemento->intersepcion(rayo, id, t);

		if (t != -1) {
			MathVector puntoIntersepcion = getPosicion(rayo, t, 0);
			float distanciaHastaPuntoIntersepcion = norma(restar(puntoIntersepcion, rayo.puntoAnclaje));

			if (distanciaMaxima > distanciaHastaPuntoIntersepcion) {
				objetosInterseptados.push_back(allObjetos[id]);
			}
		}
	}
	
	return objetosInterseptados;
}