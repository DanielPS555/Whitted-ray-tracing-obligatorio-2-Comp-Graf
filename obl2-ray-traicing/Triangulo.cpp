#include "Triangulo.h"
#include <cmath>
#include "ObjetosEscena.h"

Triangulo::Triangulo(MathVector v0, MathVector v1, MathVector v2, Color color) : Objeto()
{
    Triangulo::v0 = v0;
    Triangulo::v1 = v1;
    Triangulo::v2 = v2;
    setColorBase(color);

    MathVector t1 = restar(v1, v0);
    MathVector t2 = restar(v2, v0);

    vectorNormalV0 = normalizar(productoVectorial(t1, t2));
    vectorNormalV1 = vectorNormalV0;
    vectorNormalV2 = vectorNormalV0;    

    this->t_v0 = { 0,0,0 };
    this->t_v1 = { 0,0,0 };
    this->t_v2 = { 0,0,0 };
}

Triangulo::Triangulo(MathVector v0, MathVector v1, MathVector v2,
                        MathVector vectorNormalV0, MathVector vectorNormalV1, MathVector vectorNormalV2,
                        Color color): Objeto() {
    Triangulo::v0 = v0;
    Triangulo::v1 = v1;
    Triangulo::v2 = v2;
    setColorBase(color);

    this->vectorNormalV0 = vectorNormalV0;
    this->vectorNormalV1 = vectorNormalV1;
    this->vectorNormalV2 = vectorNormalV2;   

    this->t_v0 = {0,0,0};
    this->t_v1 = { 0,0,0 };
    this->t_v2 = { 0,0,0 };
}

Triangulo::Triangulo(MathVector v0, MathVector v1, MathVector v2,
    MathVector n_v0, MathVector n_v1, MathVector n_v2,
    MathVector t_v0, MathVector t_v1, MathVector t_v2, FIBITMAP* bitmap, Color color) {

    Triangulo::v0 = v0;
    Triangulo::v1 = v1;
    Triangulo::v2 = v2;
    setColorBase(color);

    this->vectorNormalV0 = n_v0;
    this->vectorNormalV1 = n_v1;
    this->vectorNormalV2 = n_v2;

    this->t_v0 = t_v0;
    this->t_v1 = t_v1;
    this->t_v2 = t_v2;

    this->bitmap = bitmap;
    this->widthBitmap = FreeImage_GetWidth(bitmap);
    this->heightBitmap = FreeImage_GetHeight(bitmap);
}




// este metodo esta basado en el algoritmo Moller-trumbore.
// para entenderlo completamente visitar https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm#Rust_implementation
void Triangulo::intersepcion(Rayo rayo, int& idObjetoInterseptado, float& t_int) {
    //calculos los vectores de las aristas del triangulo.
    MathVector edge1 = restar(v1,v0);
    MathVector edge2 = restar(v2,v0);

    // h representa el vector perpendicular a la dirección del rayo y la arista 2.
    MathVector h = productoVectorial(rayo.dirrecion, edge2);

    // Verificación de si el rayo es paralelo al triángulo
    float a = productoEscalar(edge1,h);

    if (fabs(a) < EPSILON) {
        idObjetoInterseptado = -1;
        t_int = -1;
        return;
    }

    // f es el factor inverso del determinante.
    // s es el vector desde el origen del rayo hasta v0.
    // u es la coordenada baricentrica.

    float f = 1.0f / a;
    MathVector s = restar(rayo.puntoAnclaje, v0);
    float u = f * productoEscalar(s,h);
    if (u < 0.0f || u > 1.0f) {
        idObjetoInterseptado = -1;
        t_int = -1;
        return;
    }

    // q es el vector perpendicular a s y edge1.
    // v es coordenada baricentrica.

    MathVector q = productoVectorial(s,edge1);
    float v = f * productoEscalar(rayo.dirrecion,q);
    if (v < 0.0f || u + v > 1.0f) {
        idObjetoInterseptado = -1;
        t_int = -1;
        return;
    }

    // t es la distancia del origen del rayo hata el punto de intersección.
    float t = f * productoEscalar(edge2,q);
    if (t > EPSILON) { 
        idObjetoInterseptado = this->getId();
        t_int = t;
        return;
    }
    else {
        idObjetoInterseptado = -1;
        t_int = -1;
        return;
    }

}

Color Triangulo::getColor(Rayo rayo, float t,int profundidad){

    LuzAmbiente luzAmbiente = ObjetosEscena::getInstancia()->luzAmbiente;

    Color colorConLuzAmbiente = getLuzAmbientePorObjeto(luzAmbiente, colorBase, sensibilidad_luz_ambiente);

    return colorConLuzAmbiente;
}

void Triangulo::corrBarisentricas(MathVector punto, float& l_0, float& l_1, float& l_2) {
    MathVector u0 = restar(v1, v0);
    MathVector u1 = restar(v2, v0);
    MathVector u2 = restar(punto, v0);

    float dot00 = productoEscalar(u0, u0);
    float dot01 = productoEscalar(u0, u1);
    float dot11 = productoEscalar(u1, u1);
    float dot02 = productoEscalar(u0, u2);
    float dot12 = productoEscalar(u1, u2);

    double invD = 1.0 / (dot00 * dot11 - dot01 * dot01);

    l_2 = (dot00 * dot12 - dot01 * dot02) * invD;
    l_1 = (dot11 * dot02 - dot01 * dot12) * invD;
    l_0 = 1.0f - l_1 - l_2;
}

MathVector Triangulo::getNormal(MathVector punto) {
    float lambdav0;
    float lambdav1;
    float lambdav2;
    corrBarisentricas(punto, lambdav0, lambdav1, lambdav2);

    MathVector n0_b = multiplicarPorEscalar(vectorNormalV0, lambdav0);
    MathVector n1_b = multiplicarPorEscalar(vectorNormalV1, lambdav1);
    MathVector n2_b = multiplicarPorEscalar(vectorNormalV2, lambdav2);

    return sumar(n0_b, sumar(n1_b, n2_b));
}

std::vector<Objeto*> Triangulo::getObjetosInternos() {
    std::vector<Objeto*> objetosInternos;
    objetosInternos.push_back(this);
    return objetosInternos;
}

Color Triangulo::getColorBase(MathVector punto) {

    if (bitmap == nullptr) {
        return colorBase;
    }
    else {
        float lambdav0;
        float lambdav1;
        float lambdav2;
        corrBarisentricas(punto, lambdav0, lambdav1, lambdav2);

        MathVector t_b_v0 = multiplicarPorEscalar(t_v0, lambdav0);
        MathVector t_b_v1 = multiplicarPorEscalar(t_v1, lambdav1);
        MathVector t_b_v2 = multiplicarPorEscalar(t_v2, lambdav2);

        MathVector corrCalculadas = sumar(t_b_v0, sumar(t_b_v1, t_b_v2));

        float corr_x = corrCalculadas.x * widthBitmap;
        float corr_y = corrCalculadas.y * heightBitmap;

        

        RGBQUAD color;
        FreeImage_GetPixelColor(bitmap, (int) corr_x, (int)corr_y, &color);

        return { (float)color.rgbRed, (float)color.rgbBlue , (float)color.rgbBlue };

    }
    
}