 
#include <direct.h> 
#include <iostream>
#include "Freeimage.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES  // for C
#endif 
#include <math.h>

#ifndef UTILS
#define UTILS

#define EPSILON 1e-8
#define PROFUNDIDAD_MAX 3


std::string getCurrentDateTime();

FIBITMAP* crearImagenVacia(int width, int height);

float gradosToRadianes(float grados);


void guardarImagen(FIBITMAP* bitmap, std::string time,  std::string sufix_nombre);// , std::string dateTime1);


// Retora unicamente raices positivas (utilizado para las intersepciones mas cercanas, pero positivas)
// En caso de no haber raices con esas caracteristicas retorna -1
float obtenerMenorRaizPositivaBhaskara(float a, float b, float c);

#endif // !UTILS