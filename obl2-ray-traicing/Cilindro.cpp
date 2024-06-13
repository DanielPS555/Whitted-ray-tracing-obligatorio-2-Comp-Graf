#include "Cilindro.h"
#include <cmath>
#include "MathVector.h"
#include "Utils.h"

Cilindro::Cilindro(MathVector centro, MathVector direccion, float radio, float altura, Color color) {
    this->altura = altura;
    this->centro = centro;
    this->radio = radio;
    this->direccion = normalizar(direccion);
    setColorBase(color);
}

float Cilindro::intersepcion(Rayo rayo) {

    /*
    el rayo es P(t)= O + t.D 
    el cilindro son los puntos P que satisfacen (P-C).D = 0 siendo C centro cilindro y D la direccion.
    => interseccion rayo cilindro es (O + t⋅D − C)⋅D = 0
    donde:
    a=D⋅D−(D⋅v)^2
    b= 2[(O−C)⋅D−(D⋅v)(O−C)⋅v]
    c=(O−C)⋅(O−C)−(O−C)⋅v^2−R^2
    */

    MathVector oc = restar(rayo.puntoAnclaje, centro);

    float d_dot_d = productoEscalar(rayo.dirrecion, rayo.dirrecion);
    float d_dot_v = productoEscalar(rayo.dirrecion, direccion);
    float oc_dot_d = productoEscalar(oc, rayo.dirrecion);
    float oc_dot_v = productoEscalar(oc, direccion);
    float oc_dot_oc = productoEscalar(oc, oc);

    float a = d_dot_d - d_dot_v * d_dot_v;
    float b = 2 * (oc_dot_d - d_dot_v * oc_dot_v);
    float c = oc_dot_oc - oc_dot_v * oc_dot_v - radio * radio;

    float discriminante = b * b - 4 * a * c;
    if (discriminante < 0) {
        return -1.0f;  //sin interseccion
    }

    float sqrtDiscriminante = sqrtf(discriminante);
    float t1 = (-b - sqrtDiscriminante) / (2 * a);
    float t2 = (-b + sqrtDiscriminante) / (2 * a);

    float t = -1.0f;

    if (t1 >= 0) {
        MathVector punto1 = sumar(rayo.puntoAnclaje, multiplicarPorEscalar(rayo.dirrecion, t1));
        float alturaRelativa1 = productoEscalar(restar(punto1, centro), direccion);
        if (alturaRelativa1 >= 0 && alturaRelativa1 <= altura) {
            t = t1;
        }
    }

    if (t2 >= 0) {
        MathVector punto2 = sumar(rayo.puntoAnclaje, multiplicarPorEscalar(rayo.dirrecion, t2));
        float alturaRelativa2 = productoEscalar(restar(punto2, centro), direccion);
        if (alturaRelativa2 >= 0 && alturaRelativa2 <= altura) {
            if (t == -1 || t2 < t) {
                t = t2;
            }
        }
    }


    /* interseccion base cilindro
     punto de interseccion = rayo.puntoAnclaje + t⋅rayo.dirrecion, buscamos el t que choque.
     ademas el plano se define como P = centro + s . direccionPerperndicular
     tenemos que igualar estas dos cosas.
     t_inferior = productoEscalar(direccion, rayo.dirrecion) / ( productoEscalar(direccion, centro)−productoEscalar(direccion, rayo.puntoAnclaje)
    ​*/

    //Luego de ver donde interseca con el plano hay que corroborar que el punto este efectivamente en el cilindro.

    

    float t_inferior = (productoEscalar(direccion, centro) - productoEscalar(direccion, rayo.puntoAnclaje)) / productoEscalar(direccion, rayo.dirrecion);
    MathVector punto_interseccion_inferior = sumar(rayo.puntoAnclaje, multiplicarPorEscalar(rayo.dirrecion, t_inferior));
    if (t_inferior >= 0) {
        MathVector delta = restar(punto_interseccion_inferior, centro);
        //float distancia_cuadrada = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
        //if (productoEscalar(delta, direccion) >= 0 && productoEscalar(delta, direccion) <= altura && distancia_cuadrada <= radio * radio) {
        float distancia_cuadradada = norma(delta);
        if(distancia_cuadradada <= radio){
            if (t == -1 || t_inferior < t) {
                t = t_inferior;
            }
        }
    }

    

    
    // interseccion tapa del cilindro
    MathVector topCenter = sumar(centro, multiplicarPorEscalar(direccion, altura));
    float t_superior = (productoEscalar(direccion, topCenter) - productoEscalar(direccion, rayo.puntoAnclaje)) / productoEscalar(direccion, rayo.dirrecion);
    MathVector punto_interseccion_superior = sumar(rayo.puntoAnclaje, multiplicarPorEscalar(rayo.dirrecion, t_superior));
    if (t_superior >= 0) {
        MathVector delta = restar(punto_interseccion_superior, topCenter);
        float distancia_cuadradada = norma(delta);
        if (distancia_cuadradada <= radio) {
            if (t == -1 || t_superior < t){
                t = t_superior;
            }
        }
    }
    
    return t;
}

MathVector Cilindro::getNormal(MathVector punto) {
    MathVector topCenter = sumar(centro, multiplicarPorEscalar(direccion, altura));
    // si el punto esta en la tapa.
    if (productoEscalar(restar(punto,topCenter),restar(centro,topCenter)) <= 0.1) {
        return direccion;
    }
    // si el punto esta en la base.
    else  if (productoEscalar(restar(punto, centro), restar(topCenter, centro)) <= 0.1) {
        return multiplicarPorEscalar(direccion, -1.0f);
    }
    // si el punto esta en la cara lateral.
    else {
        //la gracia aqui es que la norma de direccion es 1.
        MathVector projection = sumar(centro, multiplicarPorEscalar(direccion, productoEscalar(restar(punto, centro), direccion)));
        return normalizar(restar(punto, projection));
    }
}
