#include <iostream>
#include <cmath>
#include <FreeImage.h>
#include "ejemplo.h"
#include <ctime>
#include "Utils.h"
#include "ObjetosEscena.h"
#include "Camara.h"
#include "Esfera.h"
#include "Objeto.h"
#include "Color.h"
#include "CargaArchivo.h"
#include "Cilindro.h"
#include "Triangulo.h"

Camara* ejemplo1() {
    Camara* camaraPtr = new Camara({ 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, -1000.0f });

    Esfera* eferaPrueba1 = new Esfera({ 250,250,500 }, 200.0f, { 90,180,15 });
    Esfera* eferaPrueba2 = new Esfera({ 250,-250,500 }, 200.0f, { 232,158,15 });
    Esfera* eferaPrueba3 = new Esfera({ -250,-250,500 }, 200.0f, { 5,2,200 });
    Esfera* eferaPrueba4 = new Esfera({ -250,250,500 }, 200.0f, { 10,250,123 });
    Esfera* eferaPrueba5 = new Esfera({ 0,0,1000 }, 200.0f, { 100,100,100 });
    Esfera* eferaPrueba6 = new Esfera({ 0,0,-2000 }, 400.0f, { 255,0,0 });
    Triangulo * triangulo2 = new Triangulo({ -10000,-10000,-2000 }, { 10000,-10000,-2000 }, { 0,10000,-2000 }, { 255,0,0 });
   
    //eferaPrueba5->sensibilidad_luz_difusa = 0;


    Objeto** elementos = new Objeto * [5];
    elementos[0] = eferaPrueba1;
    elementos[1] = eferaPrueba2;
    elementos[2] = eferaPrueba3;
    elementos[3] = eferaPrueba4;
    elementos[4] = eferaPrueba5;
    elementos[5] = triangulo2;

    ObjetosEscena::getInstancia()->setElementos(6, elementos);
    ObjetosEscena::getInstancia()->luzAmbiente = { 100.0f,100.0f,100.0f };

    LuzPuntual* luces = new LuzPuntual[3];
    luces[0] = { {255.f,    255.f,  255.f}, {0.f   ,0.f,   100.f} };
    luces[1] = { {255.f,    0.f,  0.f} ,    {700.f ,0.f,   400.f} };
    luces[2] = { {255.f,    0.f,  255.f},  {-700.f ,0.f,   400.f} };
    ObjetosEscena::getInstancia()->lucesDifusas = luces;
    ObjetosEscena::getInstancia()->numeroLucesDifusas = 1;


    return camaraPtr;
}


Camara* ejemplo2() {
    Camara* camaraPtr = new Camara({ 0.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, -1.0f }, { 100.0f, 0.0f, 100.0f });

    Esfera* eferaPrueba1 = new Esfera({ 0,0,0}, 40.0f, { 90,180,15 });
    eferaPrueba1->setAtenuacion(0, 0.001, 0.00001f);
    eferaPrueba1->setParametrosEspeculares(29, 0.9, {255.f, 0.f, 0.f});
    eferaPrueba1->coeficienteReflexion = 0.2;
    eferaPrueba1->coeficienteTransparencia = 0.9;

    Triangulo* triangulo2 = new Triangulo({ -500,-500,-100 }, { 500,-500,-100 }, { 0,500,-100 }, { 255,0,0 });
    triangulo2->setAtenuacion(0, 0.001, 0.00001f);
    triangulo2->setParametrosEspeculares(29, 0.9, { 255.f, 0.f, 0.f });


    Objeto** elementos = new Objeto * [2];
    elementos[0] = eferaPrueba1;
    elementos[1] = triangulo2;

    ObjetosEscena::getInstancia()->setElementos(2, elementos);
    ObjetosEscena::getInstancia()->luzAmbiente = { 100.0f,100.0f,100.0f };

    LuzPuntual* luces = new LuzPuntual[1];
    luces[0] = { {200.f,  200.f,  200.f}, {0.f   ,0.f,   200.f} };

    ObjetosEscena::getInstancia()->lucesDifusas = luces;
    ObjetosEscena::getInstancia()->numeroLucesDifusas = 1;


    return camaraPtr;
}

Camara* ejemplo4() {
    Camara* camaraPtr = new Camara({ 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, -1000.0f });


    Triangulo* triangulo10 = new Triangulo({100,0,100}, {300,0,100}, {200,240,100}, {255,0,0});
    triangulo10->setAtenuacion(0, 0.001, 0.00001f);
    triangulo10->setParametrosEspeculares(29, 0.9, { 255.f, 0.f, 0.f });

    Esfera* eferaPrueba1 = new Esfera({ 270,120,500 }, 50.0f, { 90,180,15 });
    eferaPrueba1->setAtenuacion(0, 0.001, 0.00001f);
    eferaPrueba1->setParametrosEspeculares(29, 0.9, { 255.f, 0.f, 0.f });
    eferaPrueba1->coeficienteReflexion = 0.0f;
    eferaPrueba1->coeficienteTransparencia = 0.f;

    Esfera* eferaPrueba2 = new Esfera({ 200,120,100 }, 100.0f, { 255.f,255.f,255.f});
    eferaPrueba1->setAtenuacion(0, 0.001, 0.00001f);
    eferaPrueba1->setParametrosEspeculares(29, 0.9, { 255.f, 0.f, 0.f });
    eferaPrueba2->coeficienteReflexion = 0.0f;
    eferaPrueba2->coeficienteTransparencia =0.8f;


    MathVector v1 = { 800, 0, 0 };
    MathVector v2 = { -800, 0, 0 };
    MathVector v3 = { -800, 100, 400 };
    MathVector v4 = { 800, 100, 400 };

    Triangulo* triangulo1 = new Triangulo(v1, v2, v3, { 0,200,150 });
    triangulo1->setAtenuacion(0, 0.001, 0.00001f);
    triangulo1->setParametrosEspeculares(29, 0.9, { 255.f, 0.f, 0.f });

    Triangulo* triangulo2 = new Triangulo(v1, v3, v4, { 0,200,150 });
    triangulo2->setAtenuacion(0, 0.001, 0.00001f);
    triangulo2->setParametrosEspeculares(29, 0.9, { 255.f, 0.f, 0.f });

    //eferaPrueba5->sensibilidad_luz_difusa = 0;


    Objeto** elementos = new Objeto * [5];
    elementos[0] = eferaPrueba1;
    elementos[1] = eferaPrueba2;
    elementos[2] = triangulo1;
    elementos[3] = triangulo2;
    elementos[4] = triangulo10;

    ObjetosEscena::getInstancia()->setElementos(5, elementos);
    ObjetosEscena::getInstancia()->luzAmbiente = { 100.0f,100.0f,100.0f };

    LuzPuntual* luces = new LuzPuntual[3];
    luces[0] = { {255.f,    255.f,  255.f}, {0.f   ,500.f,  100.f} };
    ObjetosEscena::getInstancia()->lucesDifusas = luces;
    ObjetosEscena::getInstancia()->numeroLucesDifusas = 1;


    return camaraPtr;
}

Camara* ejemplo3() {
   
    CargaArchivo* carga = new CargaArchivo("EscenaEjemplo.json");

    Camara* camaraPtr2 = new Camara(carga->getDirACam(), carga->getDirPVCam(), carga->getUbCam());

    std::vector<Sphear> esferas = carga->getEsferas();
    std::vector<Objeto*> tris = carga->getPlanos();
    std::vector<Cilinder> cilins = carga->getCilindros();
    LuzPuntual* luces2 = carga->getLuces();
    

    Objeto** elementos = new Objeto * [esferas.size() + tris.size() + cilins.size()];

    for (int t = 0; t < tris.size(); t++) { 
        elementos[t] = tris[t]; 
    } 

    for (int e = 0; e < esferas.size(); e++) { 
        elementos[e + tris.size()] = new Esfera({ esferas[e].x, esferas[e].y, esferas[e].z }, esferas[e].radio, { esferas[e].r, esferas[e].g, esferas[e].b });
        elementos[e + tris.size()]->setAtenuacion(esferas[e].atConst, esferas[e].atLineal, esferas[e].atCuadr); 
        elementos[e + tris.size()]->setParametrosEspeculares(esferas[e].esxpReflecEspec, esferas[e].fracReflecEspec, { esferas[e].colorReflecEspecR, esferas[e].colorReflecEspecG, esferas[e] .colorReflecEspecB});
    }
    
    for (int c = 0; c < cilins.size(); c++) {
        elementos[c + esferas.size() + tris.size()] = new Cilindro({ cilins[c].x, cilins[c].y, cilins[c].z }, cilins[c].radio, cilins[c].altura, { cilins[c].r, cilins[c].g, cilins[c].b });
        elementos[c + esferas.size() + tris.size()]->setAtenuacion(cilins[c].atConst, cilins[c].atLineal, cilins[c].atCuadr);
        elementos[c + esferas.size() + tris.size()]->setParametrosEspeculares(cilins[c].esxpReflecEspec, cilins[c].fracReflecEspec, { cilins[c].colorReflecEspecR, cilins[c].colorReflecEspecG, cilins[c].colorReflecEspecB });
    }

    ObjetosEscena::getInstancia()->setElementos(esferas.size() + tris.size() + cilins.size(), elementos);
    ObjetosEscena::getInstancia()->luzAmbiente = { carga->getLuzAmb()[0], carga->getLuzAmb()[1], carga->getLuzAmb()[2] };

    ObjetosEscena::getInstancia()->lucesDifusas = luces2;
    ObjetosEscena::getInstancia()->numeroLucesDifusas = carga->getCantLuces();


    return camaraPtr2;
}


    //CargaArchivo carga = CargaArchivo("Especificaciones.json");



// Main function
int main() {
    ObjetosEscena::getInstancia()->resolucionX = 1000.f;
    ObjetosEscena::getInstancia()->resolucionY =  600.f;

    FIBITMAP* bitmap = crearImagenVacia(ObjetosEscena::getInstancia()->resolucionX,
        ObjetosEscena::getInstancia()->resolucionY);

    int w = (int)ObjetosEscena::getInstancia()->resolucionX;
    int h = (int)ObjetosEscena::getInstancia()->resolucionY;


    Camara* camaraEj = ejemplo4();


    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {

            //Implementacion de  anti-aliasing


            int r_c = 0;
            int g_c = 0;
            int b_c = 0;

            for (int y_s = 0; y_s <= 1; y_s++){
                for (int x_s = 0; x_s <= 1; x_s++) {

                    float x_delta = ((float)x_s - 0.5f)*0.5f;
                    float y_delta = ((float)y_s - 0.5f)*0.5f;

                    Rayo r = camaraEj->getRayo(x + x_delta, y + y_delta);

                    Color color = ObjetosEscena::getInstancia()->getPixelPorRayo(r, 1);

                    if (color.r > 255) {
                        color.r = 255.0f;
                    }

                    if (color.g > 255) {
                        color.g = 255.0f;
                    }

                    if (color.b > 255) {
                        color.b = 255.0f;
                    }

                    r_c += color.r;
                    g_c += color.g;
                    b_c += color.b;
                }
            }

            RGBQUAD rgbColor = { (BYTE)(b_c / 4), (BYTE)(g_c / 4), (BYTE)(r_c / 4) };

            FreeImage_SetPixelColor(bitmap, x, y, &rgbColor);
        }
    }

    /* --------------------------------------- */

    guardarImagen(bitmap);

    return 0;
}
