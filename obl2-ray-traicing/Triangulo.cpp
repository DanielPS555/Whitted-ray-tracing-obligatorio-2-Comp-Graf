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

    vectorNormalV0 = normalizar(productoVectorial(t1, t2));
    vectorNormalV1 = vectorNormalV0;
    vectorNormalV2 = vectorNormalV0;
}

Triangulo::Triangulo(MathVector v0, MathVector v1, MathVector v2,
                        MathVector vectorNormalV0, MathVector vectorNormalV1, MathVector vectorNormalV2,
                        Color color) {
    Triangulo::v0 = v0;
    Triangulo::v1 = v1;
    Triangulo::v2 = v2;
    setColorBase(color);

    this->vectorNormalV0 = vectorNormalV0;
    this->vectorNormalV1 = vectorNormalV1;
    this->vectorNormalV2 = vectorNormalV2;
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

    MathVector u0 = restar(v1, v0);
    MathVector u1 = restar(v2, v0);
    MathVector u2 = restar(punto, v0);

    float dot00 = productoEscalar(u0, u0);
    float dot01 = productoEscalar(u0, u1);
    float dot11 = productoEscalar(u1, u1);
    float dot02 = productoEscalar(u0, u2);
    float dot12 = productoEscalar(u1, u2);

    double invD = 1.0 / (dot00 * dot11 - dot01 * dot01);

    float lambdav2 = (dot00 * dot12 - dot01 * dot02) * invD;
    float lambdav1 = (dot11 * dot02 - dot01 * dot12) * invD;
    float lambdav0 = 1.0f - lambdav1 - lambdav2;

    MathVector n0_b = multiplicarPorEscalar(vectorNormalV0, lambdav0);
    MathVector n1_b = multiplicarPorEscalar(vectorNormalV1, lambdav1);
    MathVector n2_b = multiplicarPorEscalar(vectorNormalV2, lambdav2);

    return sumar(n0_b, sumar(n1_b, n2_b));
}