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
#include "objloader.h"
#include "glm/glm.hpp"



Camara* ejemplo1() {

    std::vector<unsigned short> indices;
    std::vector<glm::vec3> verticess;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    loadAssImp("assets/b.obj", indices, verticess, uvs, normals);

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
    ObjetosEscena::getInstancia()->numeroLucesDifusas = 3;


    return camaraPtr;
}


Camara* ejemplo2() {
    Camara* camaraPtr = new Camara({ 0.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, -1.0f }, { 1000.0f, 0.0f, 1000.0f });

    Esfera* eferaPrueba1 = new Esfera({ 0,0,0}, 40.0f, { 90,180,15 });
    eferaPrueba1->setAtenuacion(0, 0.001, 0.00001f);
    eferaPrueba1->setParametrosEspeculares(29, 0.9, {255.f, 0.f, 0.f});
    eferaPrueba1->coeficienteReflexion = 0.0;
    eferaPrueba1->coeficienteTransparencia = 0.0;

    Triangulo* triangulo2 = new Triangulo({ -500,-500,-100 }, { 500,-500,-100 }, { 0,500,-100 }, { 255,0,0 });
    triangulo2->setAtenuacion(0, 0.001, 0.00001f);
    triangulo2->setParametrosEspeculares(29, 0.9, { 255.f, 0.f, 0.f });


    Objeto** elementos = new Objeto * [2];
    elementos[0] = eferaPrueba1;
    elementos[1] = triangulo2;

    ObjetosEscena::getInstancia()->setElementos(2, elementos);
    ObjetosEscena::getInstancia()->luzAmbiente = { 100.0f,100.0f,100.0f };

    LuzPuntual* luces = new LuzPuntual[1];
    luces[0] = { {200.f,  200.f,  200.f}, {200.f   ,200.f,   200.f} };

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
   
    CargaArchivo* carga = new CargaArchivo("MetaDatas.json");

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
        elementos[e + tris.size()]->coeficienteReflexion = esferas[e].Refleccion;
        elementos[e + tris.size()]->coeficienteTransparencia = esferas[e].Transparencia;
    }
    
    for (int c = 0; c < cilins.size(); c++) {
        elementos[c + esferas.size() + tris.size()] = new Cilindro({ cilins[c].x, cilins[c].y, cilins[c].z }, cilins[c].radio, cilins[c].altura, { cilins[c].r, cilins[c].g, cilins[c].b });
        elementos[c + esferas.size() + tris.size()]->setAtenuacion(cilins[c].atConst, cilins[c].atLineal, cilins[c].atCuadr);
        elementos[c + esferas.size() + tris.size()]->setParametrosEspeculares(cilins[c].esxpReflecEspec, cilins[c].fracReflecEspec, { cilins[c].colorReflecEspecR, cilins[c].colorReflecEspecG, cilins[c].colorReflecEspecB });
    }

    ObjetosEscena::getInstancia()->setElementos(esferas.size() + tris.size() + cilins.size(), elementos);
    ObjetosEscena::getInstancia()->luzAmbiente = { carga->getLuzAmb().x, carga->getLuzAmb().y , carga->getLuzAmb().z };

    ObjetosEscena::getInstancia()->lucesDifusas = luces2;
    ObjetosEscena::getInstancia()->numeroLucesDifusas = carga->getCantLuces();


    return camaraPtr2;
}


Camara* blancoyNegroTransp() {

    CargaArchivo* cargaBNT = new CargaArchivo("MetaDatas.json");

    Camara* camaraPtrBNT = new Camara(cargaBNT->getDirACam(), cargaBNT->getDirPVCam(), cargaBNT->getUbCam());

    std::vector<Sphear> esferasBNT = cargaBNT->getEsferas();
    std::vector<Objeto*> trisBNT = cargaBNT->getPlanos();
    std::vector<Cilinder> cilinsBNT = cargaBNT->getCilindros();
    LuzPuntual* lucesBNT = cargaBNT->getLuces();


    Objeto** elementosBNT = new Objeto * [esferasBNT.size() + trisBNT.size() + cilinsBNT.size()];

    for (int t = 0; t < trisBNT.size(); t++) {
        elementosBNT[t] = trisBNT[t];
        elementosBNT[t]->setColorBase({ (trisBNT[t]->indiceTransparencia * 255), (trisBNT[t]->indiceTransparencia * 255), (trisBNT[t]->indiceTransparencia * 255) });
    }

    for (int e = 0; e < esferasBNT.size(); e++) {
        elementosBNT[e + trisBNT.size()] = new Esfera({ esferasBNT[e].x, esferasBNT[e].y, esferasBNT[e].z }, esferasBNT[e].radio, { (esferasBNT[e].Transparencia * 255), (esferasBNT[e].Transparencia * 255), (esferasBNT[e].Transparencia * 255) });
        //elementosBNT[e + trisBNT.size()]->setAtenuacion(esferasBNT[e].atConst, esferasBNT[e].atLineal, esferasBNT[e].atCuadr);
        //elementosBNT[e + trisBNT.size()]->setParametrosEspeculares(esferasBNT[e].esxpReflecEspec, esferasBNT[e].fracReflecEspec, { esferasBNT[e].colorReflecEspecR, esferasBNT[e].colorReflecEspecG, esferasBNT[e].colorReflecEspecB });
        //elementosBNT[e + trisBNT.size()]->coeficienteReflexion = esferasBNT[e].Refleccion;
        //elementosBNT[e + trisBNT.size()]->coeficienteTransparencia = esferasBNT[e].Transparencia;
    }

    for (int c = 0; c < cilinsBNT.size(); c++) {
        elementosBNT[c + esferasBNT.size() + trisBNT.size()] = new Cilindro({ cilinsBNT[c].x, cilinsBNT[c].y, cilinsBNT[c].z }, cilinsBNT[c].radio, cilinsBNT[c].altura, { (cilinsBNT[c].Transparencia * 255), (cilinsBNT[c].Transparencia * 255), (cilinsBNT[c].Transparencia * 255) });
        elementosBNT[c + esferasBNT.size() + trisBNT.size()]->setAtenuacion(cilinsBNT[c].atConst, cilinsBNT[c].atLineal, cilinsBNT[c].atCuadr);
        elementosBNT[c + esferasBNT.size() + trisBNT.size()]->setParametrosEspeculares(cilinsBNT[c].esxpReflecEspec, cilinsBNT[c].fracReflecEspec, { cilinsBNT[c].colorReflecEspecR, cilinsBNT[c].colorReflecEspecG, cilinsBNT[c].colorReflecEspecB });
    }

    ObjetosEscena::getInstancia()->setElementos(esferasBNT.size() + trisBNT.size() + cilinsBNT.size(), elementosBNT);
    ObjetosEscena::getInstancia()->luzAmbiente = { cargaBNT->getLuzAmb().x, cargaBNT->getLuzAmb().y , cargaBNT->getLuzAmb().z };

    ObjetosEscena::getInstancia()->lucesDifusas = lucesBNT;
    ObjetosEscena::getInstancia()->numeroLucesDifusas = cargaBNT->getCantLuces();


    return camaraPtrBNT;

}

Camara* blancoyNegroRef() {

    CargaArchivo* cargaBNR = new CargaArchivo("MetaDatas.json");

    Camara* camaraPtrBNR = new Camara(cargaBNR->getDirACam(), cargaBNR->getDirPVCam(), cargaBNR->getUbCam());

    std::vector<Sphear> esferasBNR = cargaBNR->getEsferas();
    std::vector<Objeto*> trisBNR = cargaBNR->getPlanos();
    std::vector<Cilinder> cilinsBNR = cargaBNR->getCilindros();
    LuzPuntual* lucesBNR = cargaBNR->getLuces();


    Objeto** elementosBNR = new Objeto * [esferasBNR.size() + trisBNR.size() + cilinsBNR.size()];

    for (int t = 0; t < trisBNR.size(); t++) {
        elementosBNR[t] = trisBNR[t];
        elementosBNR[t]->setColorBase({ trisBNR[t]->indiceTransparencia * 255, trisBNR[t]->indiceTransparencia * 255 , trisBNR[t]->indiceTransparencia * 255 });
    }

    for (int e = 0; e < esferasBNR.size(); e++) {
        elementosBNR[e + trisBNR.size()] = new Esfera({ esferasBNR[e].x, esferasBNR[e].y, esferasBNR[e].z }, esferasBNR[e].radio, { esferasBNR[e].Transparencia * 255, esferasBNR[e].Transparencia * 255, esferasBNR[e].Transparencia * 255 });
        elementosBNR[e + trisBNR.size()]->setAtenuacion(esferasBNR[e].atConst, esferasBNR[e].atLineal, esferasBNR[e].atCuadr);
        elementosBNR[e + trisBNR.size()]->setParametrosEspeculares(esferasBNR[e].esxpReflecEspec, esferasBNR[e].fracReflecEspec, { esferasBNR[e].colorReflecEspecR, esferasBNR[e].colorReflecEspecG, esferasBNR[e].colorReflecEspecB });
        elementosBNR[e + trisBNR.size()]->coeficienteReflexion = esferasBNR[e].Refleccion;
        elementosBNR[e + trisBNR.size()]->coeficienteTransparencia = esferasBNR[e].Transparencia;
    }

    for (int c = 0; c < cilinsBNR.size(); c++) {
        elementosBNR[c + esferasBNR.size() + trisBNR.size()] = new Cilindro({ cilinsBNR[c].x, cilinsBNR[c].y, cilinsBNR[c].z }, cilinsBNR[c].radio, cilinsBNR[c].altura, { cilinsBNR[c].Transparencia * 255, cilinsBNR[c].Transparencia * 255, cilinsBNR[c].Transparencia * 255 });
        elementosBNR[c + esferasBNR.size() + trisBNR.size()]->setAtenuacion(cilinsBNR[c].atConst, cilinsBNR[c].atLineal, cilinsBNR[c].atCuadr);
        elementosBNR[c + esferasBNR.size() + trisBNR.size()]->setParametrosEspeculares(cilinsBNR[c].esxpReflecEspec, cilinsBNR[c].fracReflecEspec, { cilinsBNR[c].colorReflecEspecR, cilinsBNR[c].colorReflecEspecG, cilinsBNR[c].colorReflecEspecB });
    }

    ObjetosEscena::getInstancia()->setElementos(esferasBNR.size() + trisBNR.size() + cilinsBNR.size(), elementosBNR);
    ObjetosEscena::getInstancia()->luzAmbiente = { cargaBNR->getLuzAmb().x, cargaBNR->getLuzAmb().y , cargaBNR->getLuzAmb().z };

    ObjetosEscena::getInstancia()->lucesDifusas = lucesBNR;
    ObjetosEscena::getInstancia()->numeroLucesDifusas = cargaBNR->getCantLuces();


    return camaraPtrBNR;

}



// Main function
int main() {
    ObjetosEscena::getInstancia()->resolucionX = 1000.f;
    ObjetosEscena::getInstancia()->resolucionY =  600.f;

    FIBITMAP* bitmap = crearImagenVacia(ObjetosEscena::getInstancia()->resolucionX,
        ObjetosEscena::getInstancia()->resolucionY);

    int w = (int)ObjetosEscena::getInstancia()->resolucionX;
    int h = (int)ObjetosEscena::getInstancia()->resolucionY;


    Camara* camaraEj = blancoyNegroTransp();


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
