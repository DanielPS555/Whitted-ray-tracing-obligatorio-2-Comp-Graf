#include "MathVector.h"
#include "Rayo.h"

#ifndef OBJETO_CLASS
#define OBJETO_CLASS

#pragma once
class Objeto{
	virtual float intersepcion(Rayo rayo) = 0;
};

#endif // !OBJETO_CLASS