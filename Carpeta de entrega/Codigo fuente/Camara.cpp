#include "Camara.h"
#include "Utils.h"
#include "cmath"
#include "iostream"

Camara::Camara(MathVector up, MathVector lookupDirrecion, MathVector posicionCamara) {

	this->dirrecionArriba	  = up;
	this->dirrecionPuntoVista = lookupDirrecion;
	this->ubicacionCamara   = posicionCamara;
	this->anguloVisionCamara  = ANGULO_VISION_CAMARA_DEFECTO;

	
	float w = (float) ObjetosEscena::getInstancia()->resolucionX;
	float h = (float) ObjetosEscena::getInstancia()->resolucionY;

	

	float profundidadCamara = 0.5f * sqrt(w * w + h * h) * tan( gradosToRadianes((180 - anguloVisionCamara) / 2) );

	MathVector traslacionCamara = multiplicarPorEscalar(normalizar(dirrecionPuntoVista), profundidadCamara);

	ubicacionPuntoVista = sumar(ubicacionCamara, traslacionCamara);
	
}

Rayo Camara::getRayo(float x, float y) {
	
	MathVector vectorRight = normalizar(productoVectorial(dirrecionArriba, dirrecionPuntoVista));
	MathVector vectorUp = normalizar(productoVectorial(dirrecionPuntoVista, vectorRight));

	int w = (int)ObjetosEscena::getInstancia()->resolucionX;
	int h = (int)ObjetosEscena::getInstancia()->resolucionY;

	float x_frame = x - w / 2;
	float y_frame = y - h / 2;


	MathVector lugarFrame = multiplicarPorEscalar(vectorUp, y_frame);
	lugarFrame = sumar(lugarFrame, multiplicarPorEscalar(vectorRight, x_frame));
	lugarFrame = sumar(lugarFrame, ubicacionPuntoVista);

	MathVector dirrecionCamara = restar(lugarFrame, ubicacionCamara);
	
	return { ubicacionCamara , dirrecionCamara };

}
