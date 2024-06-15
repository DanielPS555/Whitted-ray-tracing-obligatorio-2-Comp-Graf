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


Camara* ejemploObj() {
    ObjetosEscena::getInstancia()->resolucionX = 1920;
    ObjetosEscena::getInstancia()->resolucionY = 1080;

    Camara* camaraPtr = new Camara({ 0.0f, 1.0f, 0.0f }, { -1.0f, -1.0f, -1.0f }, { 1200.0f, 1200.0f , 1200.0f });

 
    std::vector<Objeto*> elementos;

    MallaClass* m = new MallaClass("Horse.obj", { -100.f, 0.f, 0.f }, 4.f, "horsetexture.png");
    MallaClass* m3 = new MallaClass("Horse.obj", { 300.f, 0.f, 400.f }, 4.f, "horsetexture.png");


    Esfera* esferaEspejo = new Esfera({ 500,200,0 }, 200.0f, { 255,255,255 });
    esferaEspejo->coeficienteTransparencia = 0.0f;
    esferaEspejo->coeficienteReflexion = 0.8f;
    esferaEspejo->setParametrosEspeculares(23, 0.7, { 255,255,255 });

    elementos.push_back(m); 
    elementos.push_back(m3);
    elementos.push_back(esferaEspejo);


    Plano* pared_piso = new Plano({ 0.0f, 0.0f, 0.0f }, { 0, 0, 1 }, { 1, 0, 0 }, { 150, 0, 150});
    elementos.push_back(pared_piso);

    Plano* pared_techo = new Plano({ 0.0f, 2000.0f, 0.0f }, { 0, 0, 1 }, { 1, 0, 0 }, { 150, 0, 0 });
    elementos.push_back(pared_techo);

    ObjetosEscena::getInstancia()->setElementos(elementos);
    ObjetosEscena::getInstancia()->luzAmbiente = { 100.0f,100.0f,100.0f };

    LuzPuntual* luces = new LuzPuntual[2];
    luces[0] = { {255.f,    255.f,  255.f},{400.f   ,500.f,    0.f} };
    luces[1] = { {255.f,    0.f,  255.f}, { 300.f   ,700.f,   700.f} };

    ObjetosEscena::getInstancia()->lucesDifusas = luces;
    ObjetosEscena::getInstancia()->numeroLucesDifusas = 2;

    return camaraPtr;
}

Camara* ejemploObligatorio() {

    ObjetosEscena::getInstancia()->resolucionX = 800;
    ObjetosEscena::getInstancia()->resolucionY = 800;

    Camara* camaraPtr = new Camara({ 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, -1000.0f });

    Cilindro* cilindro = new Cilindro({ -40,-220,400 }, { 0,1,0 }, 80, 180, { 0,255,0 });

    Plano* pared_piso = new Plano({ 0.0f, -350.0f, 0.0f }, { 0, 0, 1 }, { 1, 0, 0 }, { 255, 255, 255 });
    Plano* pared_techo = new Plano({ 0.0f,  350.0f, 0.0f }, { 1, 0, 0 }, { 0, 0, 1 }, { 100, 100, 100 });
    Plano* pared_derecha = new Plano({ 350.0f, 0.0f, 0.0f }, { 0, -1, 0 }, { 0, 0, 1 }, { 0, 100, 0 });
    Plano* pared_isquierda = new Plano({ -350.0f, 0.0f, 0.0f }, { 0, 1, 0 }, { 0, 0, 1 }, { 100, 0, 0 });
    Plano* fondo = new Plano({ 00.0f, 0.0f, 800.0f }, { 0,1, 0 }, { 1, 0, 0 }, { 255, 255, 255 });
    Plano* frente = new Plano({ 00.0f, 0.0f, -1050.0f }, { 0,1, 0 }, { -1, 0, 0 }, { 0, 0, 0 });

    Esfera* esferaEspejo = new Esfera({ 140,-150,400 }, 70.0f, { 255,255,255 });
    esferaEspejo->coeficienteTransparencia = 0.0f;
    esferaEspejo->coeficienteReflexion = 1.0f;

    Esfera* esferaTransparente = new Esfera({ -120,-100,400 }, 120.0f, { 255,198,198 });
    esferaTransparente->coeficienteTransparencia = .60f;
    esferaTransparente->coeficienteReflexion = 0.0f;
    esferaTransparente->setParametrosEspeculares(23, 0.8, { 255,255,255 });

    std::vector<Objeto*> elementos;


    elementos.push_back(pared_piso);
    elementos.push_back(pared_techo);
    elementos.push_back(pared_derecha);
    elementos.push_back(pared_isquierda);
    elementos.push_back(fondo);
    elementos.push_back(frente);
    elementos.push_back(esferaEspejo);
    elementos.push_back(esferaTransparente);
    elementos.push_back(cilindro);


    MallaClass* mesa = new MallaClass("m.obj", { 0.f, -300.f, 350.f }, 85.f, nullptr);

    elementos.push_back(mesa);

    ObjetosEscena::getInstancia()->setElementos(elementos);
    ObjetosEscena::getInstancia()->luzAmbiente = { 80.0f,80.0f,80.0f };

    LuzPuntual* luces = new LuzPuntual[2];
    luces[0] = { {255.f,  255.f,  255.f}, {0.f  , 300.f,   200.f} };

    luces[1] = { {255.f,  255.f,  255.f}, {0.f  , 300.f,   500.f} };

    ObjetosEscena::getInstancia()->lucesDifusas = luces;
    ObjetosEscena::getInstancia()->numeroLucesDifusas = 2;


    return camaraPtr;
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

    Camara* camaraEj = ejemploObj();

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







