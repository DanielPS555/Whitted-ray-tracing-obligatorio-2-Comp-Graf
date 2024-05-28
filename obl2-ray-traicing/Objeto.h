#include "MathVector.h"
#include "Rayo.h"
#include <FreeImage.h>

#ifndef OBJETO_CLASS
#define OBJETO_CLASS

#pragma once
class Objeto{

private: 
	RGBQUAD colorBase;
public:
	virtual float intersepcion(Rayo rayo) = 0;
	void setColorBase(RGBQUAD color) {
		colorBase = color;
	}
	RGBQUAD getColorBase() {
		return colorBase;
	}
};

#endif // !OBJETO_CLASS