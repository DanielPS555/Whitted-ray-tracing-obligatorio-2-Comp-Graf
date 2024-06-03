#include "Triangulo.h"
#include <cmath>
#include "ObjetosEscena.h"

Triangulo::Triangulo(MathVector v0, MathVector v1, MathVector v2, Color color) {
    Triangulo::v0 = v0;
    Triangulo::v1 = v1;
    Triangulo::v2 = v2;
    setColorBase(color);

    MathVector t1 = restar(v1, v0);
    MathVector t2 = restar(v2, v0);

    print(t1);
    print(t2);

    vectorNormal = normalizar(productoVectorial(t1, t2));
}

// este metodo esta basado en el algoritmo Moller-trumbore.
// para entenderlo completamente visitar https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm#Rust_implementation
float Triangulo::intersepcion(Rayo rayo) {
    //calculos los vectores de las aristas del triangulo.
    MathVector edge1 = restar(v1,v0);
    MathVector edge2 = restar(v2,v0);

    // h representa el vector perpendicular a la dirección del rayo y la arista 2.
    MathVector h = productoVectorial(rayo.dirrecion, edge2);

    // Verificación de si el rayo es paralelo al triángulo
    float a = productoEscalar(edge1,h);

    if (fabs(a) < EPSILON) {
        return -1; 
    }

    // f es el factor inverso del determinante.
    // s es el vector desde el origen del rayo hasta v0.
    // u es la coordenada baricentrica.

    float f = 1.0f / a;
    MathVector s = restar(rayo.puntoAnclaje, v0);
    float u = f * productoEscalar(s,h);
    if (u < 0.0f || u > 1.0f) {
        return -1; 
    }

    // q es el vector perpendicular a s y edge1.
    // v es coordenada baricentrica.

    MathVector q = productoVectorial(s,edge1);
    float v = f * productoEscalar(rayo.dirrecion,q);
    if (v < 0.0f || u + v > 1.0f) {
        return -1; 
    }

    // t es la distancia del origen del rayo hata el punto de intersección.
    float t = f * productoEscalar(edge2,q);
    if (t > EPSILON) {
        return t; 
    }
    else {
        return -1; 
    }

}

Color Triangulo::getColor(Rayo rayo, float t,int profundidad){

    LuzAmbiente luzAmbiente = ObjetosEscena::getInstancia()->luzAmbiente;

    Color colorConLuzAmbiente = getLuzAmbientePorObjeto(luzAmbiente, colorBase, sensibilidad_luz_ambiente);

    return colorConLuzAmbiente;
}

MathVector Triangulo::getNormal(MathVector punto) {
    return vectorNormal;
}