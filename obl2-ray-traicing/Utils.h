#include <iostream>
#include "Freeimage.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES  // for C
#endif 
#include <math.h>

#ifndef UTILS
#define UTILS

#define EPSILON 1e-8


std::string getCurrentDateTime();

FIBITMAP* crearImagenVacia(int width, int height);

float gradosToRadianes(float grados);


void guardarImagen(FIBITMAP* bitmap);


// Retora unicamente raices positivas (utilizado para las intersepciones mas cercanas, pero positivas)
// En caso de no haber raices con esas caracteristicas retorna -1
float obtenerMenorRaizPositivaBhaskara(float a, float b, float c);

#endif // !UTILS