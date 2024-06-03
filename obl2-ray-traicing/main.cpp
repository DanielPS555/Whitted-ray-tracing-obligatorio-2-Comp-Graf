#include <iostream>
#include <cmath>
#include <FreeImage.h>
#include "ejemplo.h"
#include <ctime>
#include "Utils.h"
#include "ObjetosEscena.h"
#include "Camara.h"
#include "Esfera.h"
#include "Triangulo.h"
#include "../Objeto.h"
#include "Color.h"
#include "CargaArchivo.h"
#include "Cilindro.h"


Camara* ejemplo1() {
    Camara* camaraPtr = new Camara({ 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });

    Esfera* eferaPrueba1 = new Esfera({ 250,250,500 }, 200.0f, { 90,180,15 });
    Esfera* eferaPrueba2 = new Esfera({ 250,-250,500 }, 200.0f, { 232,158,15 });
    Esfera* eferaPrueba3 = new Esfera({ -250,-250,500 }, 200.0f, { 5,2,200 });
    Esfera* eferaPrueba4 = new Esfera({ -250,250,500 }, 200.0f, { 10,250,123 });


    Objeto** elementos = new Objeto * [4];
    elementos[0] = eferaPrueba1;
    elementos[1] = eferaPrueba2;
    elementos[2] = eferaPrueba3;
    elementos[3] = eferaPrueba4;

    ObjetosEscena::getInstancia()->setElementos(4, elementos);
    ObjetosEscena::getInstancia()->luzAmbiente = { 100.0f,100.0f,100.0f };

    LuzPuntual* luces = new LuzPuntual[3];
    luces[0] = { {255.f,    255.f,  255.f}, {0.f   ,0.f,   500.f} };
    luces[1] = { {255.f,    0.f,  0.f} ,    {700.f ,0.f,   400.f} };
    luces[2] = { {255.f,    0.f,  255.f},  {-700.f ,0.f,   400.f} };
    ObjetosEscena::getInstancia()->lucesDifusas = luces;
    ObjetosEscena::getInstancia()->numeroLucesDifusas = 3;


    return camaraPtr;
}


Camara* ejemplo2() {
    Camara* camaraPtr = new Camara({ 0.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, -1.0f }, { 100.0f, 0.0f, 100.0f });

    Esfera* eferaPrueba1 = new Esfera({ 0,0,0}, 40.0f, { 90,180,15 });
    eferaPrueba1->setAtenuacion(0, 0.001, 0.00001f);
    eferaPrueba1->setParametrosEspeculares(29, 0.9, {255.f, 0.f, 0.f});

    Triangulo* triangulo2 = new Triangulo({ -500,-500,-100 }, { 500,-500,-100 }, { 0,500,-100 }, { 0,200,150 });
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

Camara* ejemplo3() {
    CargaArchivo* carga = new CargaArchivo("EscenaEjemplo.json");

    Camara* camaraPtr = new Camara(carga->getDirACam(), carga->getDirPVCam(), carga->getUbCam());

    std::vector<Sphear> esferas = carga->getEsferas();
    std::vector<Triangulo*> tris = carga->getPlanos();
    std::vector<Cilinder> cilins = carga->getCilindros();
    LuzPuntual* luces = carga->getLuces();
    

    Objeto** elementos = new Objeto * [esferas.size() + tris.size() + cilins.size()];

    for (int t = 0; t < tris.size(); t++) {
        elementos[t] = tris[t];
    }

    for (int e = 0; e < esferas.size(); e++) {
        elementos[e] = new Esfera({ esferas[e].x, esferas[e].y, esferas[e].z }, esferas[e].radio, { esferas[e].r, esferas[e].g, esferas[e].b });
        elementos[e]->setAtenuacion(esferas[e].atConst, esferas[e].atLineal, esferas[e].atCuadr);
        elementos[e]->setParametrosEspeculares(esferas[e].esxpReflecEspec, esferas[e].fracReflecEspec, { esferas[e].colorReflecEspecR, esferas[e].colorReflecEspecG, esferas[e] .colorReflecEspecB});
    }

    for (int c = 0; c < cilins.size(); c++) {
        elementos[c] = new Cilindro({ cilins[c].x, cilins[c].y, cilins[c].z }, cilins[c].radio, cilins[c].altura, { cilins[c].r, cilins[c].g, cilins[c].b });
        elementos[c]->setAtenuacion(cilins[c].atConst, cilins[c].atLineal, cilins[c].atCuadr);
        elementos[c]->setParametrosEspeculares(cilins[c].esxpReflecEspec, cilins[c].fracReflecEspec, { cilins[c].colorReflecEspecR, cilins[c].colorReflecEspecG, cilins[c].colorReflecEspecB });
    }

    ObjetosEscena::getInstancia()->setElementos(esferas.size() + tris.size() + cilins.size(), elementos);
    ObjetosEscena::getInstancia()->luzAmbiente = { carga->getLuzAmb()[0], carga->getLuzAmb()[1], carga->getLuzAmb()[2] };

    ObjetosEscena::getInstancia()->lucesDifusas = luces;
    ObjetosEscena::getInstancia()->numeroLucesDifusas = carga->getCantLuces();

    return camaraPtr;
}

// Main function
int main() {
    ObjetosEscena::getInstancia()->resolucionX = 1000.f;
    ObjetosEscena::getInstancia()->resolucionY =  500.f;

    FIBITMAP* bitmap = crearImagenVacia(ObjetosEscena::getInstancia()->resolucionX,
        ObjetosEscena::getInstancia()->resolucionY);

    int w = (int)ObjetosEscena::getInstancia()->resolucionX;
    int h = (int)ObjetosEscena::getInstancia()->resolucionY;

    Camara* camaraEj = ejemplo3();
   

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {

            Rayo r = camaraEj->getRayo(x, y);


            Color color = ObjetosEscena::getInstancia()->getPixelPorRayo(r);
            
            if (color.r > 255) {
                color.r = 255.0f;
            }

            if (color.g > 255) {
                color.g = 255.0f;
            }

            if (color.b > 255) {
                color.b = 255.0f;
            }


            RGBQUAD rgbColor = { (BYTE)color.b, (BYTE)color.g, (BYTE)color.r };

            FreeImage_SetPixelColor(bitmap, x, y, &rgbColor);
        }
    }

    /* --------------------------------------- */

    guardarImagen(bitmap);

    return 0;
}
