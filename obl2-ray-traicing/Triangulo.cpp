#include "Triangulo.h"
#include <cmath>

Triangulo::Triangulo(MathVector v0, MathVector v1, MathVector v2, RGBQUAD color) {
    Triangulo::v0 = v0;
    Triangulo::v1 = v1;
    Triangulo::v2 = v2;
    setColorBase(color);
}

float Triangulo::intersepcion(Rayo rayo) {
    const float EPSILON = 1e-8;

    MathVector edge1 = restar(v1,v0);
    MathVector edge2 = restar(v2,v0);
    MathVector h = productoVectorial(rayo.dirrecion, edge2);
    float a = productoEscalar(edge1,h);

    if (fabs(a) < EPSILON) {
        return -1; 
    }

    float f = 1.0f / a;
    MathVector s = restar(rayo.puntoAnclaje, v0);
    float u = f * productoEscalar(s,h);
    if (u < 0.0f || u > 1.0f) {
        return -1; 
    }

    MathVector q = productoVectorial(s,edge1);
    float v = f * productoEscalar(rayo.dirrecion,q);
    if (v < 0.0f || u + v > 1.0f) {
        return -1; 
    }

    float t = f * productoEscalar(edge2,q);
    if (t > EPSILON) {
        return t; 
    }
    else {
        return -1; 
    }
}
