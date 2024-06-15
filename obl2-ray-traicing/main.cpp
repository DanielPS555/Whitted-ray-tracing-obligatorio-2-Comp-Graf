#include <iostream>
#include <cmath>
#include <FreeImage.h>
#include <ctime>
#include "Utils.h"
#include "ObjetosEscena.h"
#include "Camara.h"
#include "Plano.h"
#include "Esfera.h"
#include "Objeto.h"
#include "Color.h"
#include "CargaArchivo.h"
#include "Cilindro.h"
#include "Triangulo.h"
#include "objloader.h"
#include "SDL.h"
#include "Malla.h"

#include "omp.h"

#include "chrono"


#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 700


using namespace std;

using Clock = std::chrono::steady_clock;
using chrono::time_point;
using chrono::duration_cast;
using chrono::milliseconds;
using chrono::seconds;


Camara* cargarArchivoMetaData() {


    CargaArchivo* carga = new CargaArchivo("MetaDatas.json");

    ObjetosEscena::getInstancia()->resolucionX = carga->getResX();
    ObjetosEscena::getInstancia()->resolucionY = carga->getResY();

    Camara* camaraPtr2 = new Camara(carga->getDirACam(), carga->getDirPVCam(), carga->getUbCam());

    std::vector<Sphear> esferas = carga->getEsferas();
    std::vector<Triangle> tris = carga->getCaras();
    std::vector<Cilinder> cilins = carga->getCilindros();
    std::vector<LuzPunt> lucesPunt = carga->getLuces();
    std::vector<Plane> plans = carga->getPlanos();
    std::vector<Malla> mallas = carga->getMallas();


    std::vector<Objeto*> elementos;

    for (int t = 0; t < tris.size(); t++) {
        Triangulo * tri;
        tri = new Triangulo(tris[t].V1, tris[t].V2, tris[t].V3, { tris[t].r, tris[t].g, tris[t].b });
        tri->setAtenuacion(tris[t].atConst, tris[t].atLineal, tris[t].atCuadr);
        tri->setParametrosEspeculares(tris[t].esxpReflecEspec, tris[t].fracReflecEspec, { tris[t].colorReflecEspecR, tris[t].colorReflecEspecG, tris[t].colorReflecEspecB });
        tri->coeficienteReflexion = tris[t].Refleccion;
        tri->coeficienteTransparencia = tris[t].Transparencia;
        elementos.push_back(tri);
    }

    for (int e = 0; e < esferas.size(); e++) {
        Esfera* esf;
        esf = new Esfera({ esferas[e].x, esferas[e].y, esferas[e].z }, esferas[e].radio, { esferas[e].r, esferas[e].g, esferas[e].b });
        esf->setAtenuacion(esferas[e].atConst, esferas[e].atLineal, esferas[e].atCuadr);
        esf->setParametrosEspeculares(esferas[e].esxpReflecEspec, esferas[e].fracReflecEspec, { esferas[e].colorReflecEspecR, esferas[e].colorReflecEspecG, esferas[e].colorReflecEspecB });
        esf->coeficienteReflexion = esferas[e].Refleccion;
        esf->coeficienteTransparencia = esferas[e].Transparencia;
        elementos.push_back(esf);
    }

    for (int c = 0; c < cilins.size(); c++) {
        Cilindro* cili;
        cili = new Cilindro({ cilins[c].x, cilins[c].y, cilins[c].z }, { cilins[c].direccion_x,cilins[c].direccion_y,cilins[c].direccion_z }, cilins[c].radio, cilins[c].altura, { cilins[c].r, cilins[c].g, cilins[c].b });
        cili->setAtenuacion(cilins[c].atConst, cilins[c].atLineal, cilins[c].atCuadr);
        cili->setParametrosEspeculares(cilins[c].esxpReflecEspec, cilins[c].fracReflecEspec, { cilins[c].colorReflecEspecR, cilins[c].colorReflecEspecG, cilins[c].colorReflecEspecB });
        cili->coeficienteReflexion = cilins[c].Refleccion;
        cili->coeficienteTransparencia = cilins[c].Transparencia;
        elementos.push_back(cili);
    }

    for (int p = 0; p < plans.size(); p++) {
        Plano* plan;
        
        plan = new Plano(plans[p].puntoBase,plans[p].VectorU,plans[p].VectorV, { plans[p].r, plans[p].g, plans[p].b });
        //plan->setAtenuacion(plans[p].atConst, plans[p].atLineal, plans[p].atCuadr);
        //plan->setParametrosEspeculares(plans[p].esxpReflecEspec, plans[p].fracReflecEspec, { plans[p].colorReflecEspecR, plans[p].colorReflecEspecG, plans[p].colorReflecEspecB });
        //plan->coeficienteReflexion = plans[p].Refleccion;
        //plan->coeficienteTransparencia = plans[p].Transparencia;
        elementos.push_back(plan);
    }

    for (int m = 0; m < mallas.size(); m++) {
        MallaClass* mall;
        MathVector traslacion = { mallas[m].trasladar_x,mallas[m].trasladar_y,mallas[m].trasladar_z };
        mall = new MallaClass(mallas[m].obj_url.c_str(), traslacion, mallas[m].escalamiento, mallas[m].png_url.c_str());
        elementos.push_back(mall);
    }

    ObjetosEscena::getInstancia()->setElementos(elementos);
    ObjetosEscena::getInstancia()->luzAmbiente = { carga->getLuzAmb().x, carga->getLuzAmb().y , carga->getLuzAmb().z };

    LuzPuntual* luces2 = new LuzPuntual[lucesPunt.size()];
    for (int l = 0; l < lucesPunt.size(); l++) {
        luces2[l] = { {lucesPunt[l].r, lucesPunt[l].g, lucesPunt[l].b}, lucesPunt[l].pos };
    }

    ObjetosEscena::getInstancia()->lucesDifusas = luces2;
    ObjetosEscena::getInstancia()->numeroLucesDifusas = carga->getCantLuces();


    return camaraPtr2;
}

void render(int x_p, int y_p, Camara* cam, FIBITMAP* bitmap, FIBITMAP* bitmapTrans, FIBITMAP* bitmapRef,
    FIBITMAP* bitmapAmb, FIBITMAP* bitmapEspec, FIBITMAP* bitmapDif, FIBITMAP* bitmapPriRecTrans, FIBITMAP* bitmapPriRecRefle, FIBITMAP* preview) {

    int r_c = 0;
    int g_c = 0;
    int b_c = 0;

    int r_t = 0;
    int g_t = 0;
    int b_t = 0;

    int r_r = 0;
    int g_r = 0;
    int b_r = 0;

    int r_e = 0;
    int g_e = 0;
    int b_e = 0;

    int r_a = 0;
    int g_a = 0;
    int b_a = 0;


    int r_d = 0;
    int g_d = 0;
    int b_d = 0;

    int r_pr = 0;
    int g_pr = 0;
    int b_pr = 0;

    int r_pt = 0;
    int g_pt = 0;
    int b_pt = 0;


    for (int y_s = 0; y_s <= 1; y_s++) {
        for (int x_s = 0; x_s <= 1; x_s++) {

            float x_delta = ((float)x_s - 0.5f) * 0.5f;
            float y_delta = ((float)y_s - 0.5f) * 0.5f;

            Rayo r = cam->getRayo(x_p + x_delta, y_p + y_delta);

            ColorCoef color = ObjetosEscena::getInstancia()->getPixelPorRayo(r, 1);

            if (color.base.r > 255) {
                color.base.r = 255.0f;
            }

            if (color.base.g > 255) {
                color.base.g = 255.0f;
            }

            if (color.base.b > 255) {
                color.base.b = 255.0f;
            }

            r_c += color.base.r;
            g_c += color.base.g;
            b_c += color.base.b;

            if (color.transp.r > 255) {
                color.transp.r = 255.0f;
            }


            if (color.transp.g > 255) {
                color.transp.g = 255.0f;
            }


            if (color.transp.b > 255) {
                color.transp.b = 255.0f;
            }

            r_t += color.transp.r;
            g_t += color.transp.g;
            b_t += color.transp.b;

            if (color.reflecc.r > 255) {
                color.reflecc.r = 255.0f;
            }


            if (color.reflecc.g > 255) {
                color.reflecc.g = 255.0f;
            }


            if (color.reflecc.b > 255) {
                color.reflecc.b = 255.0f;
            }

            r_r += color.reflecc.r;
            g_r += color.reflecc.g;
            b_r += color.reflecc.b;


            if (color.espec.r > 255) {
                color.espec.r = 255.0f;
            }


            //Implementacion de  anti-aliasing

            if (color.espec.g > 255) {
                color.espec.g = 255.0f;
            }

            if (color.espec.b > 255) {
                color.espec.b = 255.0f;
            }

            r_e += color.espec.r;
            g_e += color.espec.g;
            b_e += color.espec.b;

            if (color.ambient.r > 255) {
                color.ambient.r = 255.0f;
            }

            if (color.ambient.g > 255) {
                color.ambient.g = 255.0f;
            }

            if (color.ambient.b > 255) {
                color.ambient.b = 255.0f;
            }

            r_a += color.ambient.r;
            g_a += color.ambient.g;
            b_a += color.ambient.b;

            if (color.difus.r > 255) {
                color.difus.r = 255.0f;
            }

            if (color.difus.g > 255) {
                color.difus.g = 255.0f;
            }

            if (color.difus.b > 255) {
                color.difus.b = 255.0f;
            }

            r_d += color.difus.r;
            g_d += color.difus.g;
            b_d += color.difus.b;

            if (color.primRecReflex.r > 255) {
                color.primRecReflex.r = 255.0f;
            }

            if (color.primRecReflex.g > 255) {
                color.primRecReflex.g = 255.0f;
            }

            if (color.primRecReflex.b > 255) {
                color.primRecReflex.b = 255.0f;
            }

            r_pr += color.primRecReflex.r;
            g_pr += color.primRecReflex.g;
            b_pr += color.primRecReflex.b;

            if (color.primRecTrans.r > 255) {
                color.primRecTrans.r = 255.0f;
            }

            if (color.primRecTrans.g > 255) {
                color.primRecTrans.g = 255.0f;
            }

            if (color.primRecTrans.b > 255) {
                color.primRecTrans.b = 255.0f;
            }

            r_pt += color.primRecTrans.r;
            g_pt += color.primRecTrans.g;
            b_pt += color.primRecTrans.b;
        }
    }

    RGBQUAD rgbColor = { (BYTE)(b_c / 4), (BYTE)(g_c / 4), (BYTE)(r_c / 4) };

    RGBQUAD rgbColorTransp = { (BYTE)(b_t / 4), (BYTE)(g_t / 4), (BYTE)(r_t / 4) };
    RGBQUAD rgbColorReflec = { (BYTE)(b_r / 4), (BYTE)(g_r / 4), (BYTE)(r_r / 4) };
    RGBQUAD rgbColorAmbient = { (BYTE)(b_a / 4), (BYTE)(g_a / 4), (BYTE)(r_a / 4) };
    RGBQUAD rgbColorEspec = { (BYTE)(b_e / 4), (BYTE)(g_e / 4), (BYTE)(r_e / 4) };
    RGBQUAD rgbColorDifus = { (BYTE)(b_d / 4), (BYTE)(g_d / 4), (BYTE)(r_d / 4) };
    RGBQUAD rgbColorPrimRecTrans = { (BYTE)(b_pt / 4), (BYTE)(g_pt / 4), (BYTE)(r_pt / 4) };
    RGBQUAD rgbColorPrimRecReflex = { (BYTE)(b_pr / 4), (BYTE)(g_pr / 4), (BYTE)(r_pr / 4) };

    int y_inv = ObjetosEscena::getInstancia()->resolucionY - y_p - 1;
    
    #pragma omp critical
    FreeImage_SetPixelColor(bitmap, x_p, y_p, &rgbColor);

    #pragma omp critical
    FreeImage_SetPixelColor(preview, x_p, y_inv, &rgbColor);

    #pragma omp critical
    FreeImage_SetPixelColor(bitmapTrans, x_p, y_p, &rgbColorTransp);

    #pragma omp critical    
    FreeImage_SetPixelColor(bitmapRef, x_p, y_p, &rgbColorReflec);

    #pragma omp critical
    FreeImage_SetPixelColor(bitmapAmb, x_p, y_p, &rgbColorAmbient);

    #pragma omp critical
    FreeImage_SetPixelColor(bitmapEspec, x_p, y_p, &rgbColorEspec);

    #pragma omp critical
    FreeImage_SetPixelColor(bitmapDif, x_p, y_p, &rgbColorDifus);

    #pragma omp critical
    FreeImage_SetPixelColor(bitmapPriRecTrans, x_p, y_p, &rgbColorPrimRecTrans);

    #pragma omp critical
    FreeImage_SetPixelColor(bitmapPriRecRefle, x_p, y_p, &rgbColorPrimRecReflex);
}

int SDL_main(int argc, char* argv[]) {

    // Tu c�digo SDL aqu�

    SDL_Init(SDL_INIT_VIDEO);

    // Ejemplo: Crear una ventana
    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Camara* camaraEj = cargarArchivoMetaData();

    FIBITMAP* bitmap = crearImagenVacia(ObjetosEscena::getInstancia()->resolucionX,
        ObjetosEscena::getInstancia()->resolucionY);

    FIBITMAP* bitmapPreview = crearImagenVacia(ObjetosEscena::getInstancia()->resolucionX,
        ObjetosEscena::getInstancia()->resolucionY);

    FIBITMAP* bitmapTrans = crearImagenVacia(ObjetosEscena::getInstancia()->resolucionX,
        ObjetosEscena::getInstancia()->resolucionY);

    FIBITMAP* bitmapRef = crearImagenVacia(ObjetosEscena::getInstancia()->resolucionX,
        ObjetosEscena::getInstancia()->resolucionY);

    FIBITMAP* bitmapAmb = crearImagenVacia(ObjetosEscena::getInstancia()->resolucionX,
        ObjetosEscena::getInstancia()->resolucionY);

    FIBITMAP* bitmapEspec = crearImagenVacia(ObjetosEscena::getInstancia()->resolucionX,
        ObjetosEscena::getInstancia()->resolucionY);

    FIBITMAP* bitmapDif = crearImagenVacia(ObjetosEscena::getInstancia()->resolucionX,
        ObjetosEscena::getInstancia()->resolucionY);

    FIBITMAP* bitmapPriRecTrans = crearImagenVacia(ObjetosEscena::getInstancia()->resolucionX,
        ObjetosEscena::getInstancia()->resolucionY);

    FIBITMAP* bitmapPriRecRefle = crearImagenVacia(ObjetosEscena::getInstancia()->resolucionX,
        ObjetosEscena::getInstancia()->resolucionY);

    int w = (int)ObjetosEscena::getInstancia()->resolucionX;
    int h = (int)ObjetosEscena::getInstancia()->resolucionY;

    bool quit = false;
    SDL_Event evento;

    int inicio = 0;
    int cant_a_procesar_por_refesh = 5000;
    bool primeraVezFin = false;


    time_point<Clock> inicioTiempo = Clock::now();

    while (!quit) {

        int cant_pross = min(w * h - inicio, cant_a_procesar_por_refesh);

        if (cant_pross > 0) {
#pragma omp parallel for num_threads (6)  schedule(dynamic,100)

            for (int h = 0; h < cant_pross; h++) {

                int id = omp_get_thread_num();

                int p = inicio + h;

                int y = p / w;
                int x = p % w;

                render(x, y, camaraEj, bitmap, bitmapTrans, bitmapRef, bitmapAmb, bitmapEspec, bitmapDif, bitmapPriRecTrans, bitmapPriRecRefle, bitmapPreview);
            }

            if (inicio < w * h) {
                void* datos = FreeImage_GetBits(bitmapPreview);

                SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(datos, w, h, 24, 3 * w, 0x00ff0000, 0x0000ff00, 0x000000ff, 0);

                SDL_Texture* image = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);

                SDL_Rect imageRect = { 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT };
                //SDL_QueryTexture(image, NULL, NULL, &imageRect.w, &imageRect.h);
                SDL_RenderCopy(renderer, image, NULL, &imageRect);

                SDL_RenderPresent(renderer);
            }

            inicio += cant_pross;

            if (inicio == w * h && !primeraVezFin) {
                primeraVezFin = true;
                std::string dt = getCurrentDateTime();

                std::time_t tf = std::time(0);

                milliseconds miliseconds = duration_cast<milliseconds>(Clock::now() - inicioTiempo);

                guardarImagen(bitmap, dt, "Base");
                guardarImagen(bitmapTrans, dt, "Transp");
                guardarImagen(bitmapRef, dt, "Reflec");
                guardarImagen(bitmapAmb, dt, "Amb");
                guardarImagen(bitmapEspec, dt, "Espec");
                guardarImagen(bitmapDif, dt, "Difus");
                guardarImagen(bitmapPriRecTrans, dt, "TranspPrimRecursion");
                guardarImagen(bitmapPriRecRefle, dt, "ReflexPrimRecursion");

                printf("----- Tiempo transcurido = %.2f seg \n", (float)miliseconds.count() / 1000.f);

            }
        }       

        while (SDL_PollEvent(&evento)) {
            switch (evento.type) {
            case SDL_QUIT:
                quit = true;
                break;
            }
        }

    }
    


    // Liberar recursos
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}







