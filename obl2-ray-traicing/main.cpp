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

int render();

int SDL_main(int argc, char* argv[]) {
    // Tu c�digo SDL aqu�

    SDL_Init(SDL_INIT_VIDEO);

    // Ejemplo: Crear una ventana
    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

    // Bucle principal
    bool quit = false;
    SDL_Event e;

    render();


    // Liberar recursos
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800


Camara* ejemploObj() {
    ObjetosEscena::getInstancia()->resolucionX = 500;
    ObjetosEscena::getInstancia()->resolucionY = 500;

    Camara* camaraPtr = new Camara({ 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 100.0f , -700.0f });

    std::vector<unsigned short> indices;
    std::vector<glm::vec3> verticess;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    //loadAssImp("Horse.obj", indices, verticess, uvs, normals);
    loadAssImp("m.obj", indices, verticess, uvs, normals);

    int cantTriangulos = verticess.size() / 3;

    float escalar = 80;


    std::vector<Objeto*> elementos;

    for (int i = 0; i < cantTriangulos; i++) {

        MathVector v1 = { verticess[i * 3].x * escalar      , verticess[i * 3].y * escalar    , verticess[i * 3].z * escalar };
        MathVector v2 = { verticess[i * 3 + 1].x * escalar  , verticess[i * 3 + 1].y * escalar, verticess[i * 3 + 1].z * escalar };
        MathVector v3 = { verticess[i * 3 + 2].x * escalar  , verticess[i * 3 + 2].y * escalar, verticess[i * 3 + 2].z * escalar };

        MathVector n_v1 = { normals[i * 3].x    , normals[i * 3].y     , normals[i * 3].z };
        MathVector n_v2 = { normals[i * 3 + 1].x, normals[i * 3 + 1].y , normals[i * 3 + 1].z };
        MathVector n_v3 = { normals[i * 3 + 2].x, normals[i * 3 + 2].y , normals[i * 3 + 2].z };


        elementos.push_back(new Triangulo(v1, v2, v3, n_v1, n_v2, n_v3, { 255,255,255 }));
    }

    ObjetosEscena::getInstancia()->setElementos(elementos);
    ObjetosEscena::getInstancia()->luzAmbiente = { 100.0f,100.0f,100.0f };

    LuzPuntual* luces = new LuzPuntual[1];
    luces[0] = { {255.f,    255.f,  255.f}, {0.f   ,0.f,   300.f} };
    ObjetosEscena::getInstancia()->lucesDifusas = luces;
    ObjetosEscena::getInstancia()->numeroLucesDifusas = 1;

    return camaraPtr;
}

Camara* ejemploObligatorio() {

    ObjetosEscena::getInstancia()->resolucionX = 1000;
    ObjetosEscena::getInstancia()->resolucionY = 1000;

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

    std::vector<unsigned short> indices;
    std::vector<glm::vec3> verticess;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    loadAssImp("m.obj", indices, verticess, uvs, normals);

    int cantTriangulos = verticess.size() / 3;

    float escalar = 85;
    MathVector trasladar = { 0.f, -300.f, 350.f };

    for (int i = 0; i < cantTriangulos; i++) {

        MathVector v1 = { verticess[i * 3].x * escalar + trasladar.x , verticess[i * 3].y * escalar + trasladar.y   , verticess[i * 3].z * escalar + trasladar.z };
        MathVector v2 = { verticess[i * 3 + 1].x * escalar + trasladar.x , verticess[i * 3 + 1].y * escalar + trasladar.y   , verticess[i * 3 + 1].z * escalar + trasladar.z };
        MathVector v3 = { verticess[i * 3 + 2].x * escalar + trasladar.x , verticess[i * 3 + 2].y * escalar + trasladar.y   , verticess[i * 3 + 2].z * escalar + trasladar.z };

        MathVector n_v1 = { normals[i * 3].x    , normals[i * 3].y     , normals[i * 3].z };
        MathVector n_v2 = { normals[i * 3 + 1].x, normals[i * 3 + 1].y , normals[i * 3 + 1].z };
        MathVector n_v3 = { normals[i * 3 + 2].x, normals[i * 3 + 2].y , normals[i * 3 + 2].z };


        elementos.push_back(new Triangulo(v1, v2, v3, n_v1, n_v2, n_v3, { 255,255,255 }));
    }

    ObjetosEscena::getInstancia()->setElementos(elementos);
    ObjetosEscena::getInstancia()->luzAmbiente = { 80.0f,80.0f,80.0f };

    LuzPuntual* luces = new LuzPuntual[2];
    luces[0] = { {255.f,  255.f,  255.f}, {0.f  , 300.f,   200.f} };

    luces[1] = { {255.f,  255.f,  255.f}, {0.f  , 300.f,   500.f} };

    ObjetosEscena::getInstancia()->lucesDifusas = luces;
    ObjetosEscena::getInstancia()->numeroLucesDifusas = 2;


    return camaraPtr;
}

using namespace std;

// Main function
int render() {


    /*if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Bomberman - Obligatorio 1 - Comp Graf ",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    */


    Camara* camaraEj = ejemploObligatorio();

    FIBITMAP* bitmap = crearImagenVacia(ObjetosEscena::getInstancia()->resolucionX,
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

    int w = (int)ObjetosEscena::getInstancia()->resolucionX;
    int h = (int)ObjetosEscena::getInstancia()->resolucionY;





    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {

            //printf("%.2f\n", (float)(y * w + x) / (float)(w * h));
             //Implementacion de  anti-aliasing


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


            for (int y_s = 0; y_s <= 1; y_s++) {
                for (int x_s = 0; x_s <= 1; x_s++) {

                    float x_delta = ((float)x_s - 0.5f) * 0.5f;
                    float y_delta = ((float)y_s - 0.5f) * 0.5f;

                    Rayo r = camaraEj->getRayo(x + x_delta, y + y_delta);

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
                }
            }

            RGBQUAD rgbColor = { (BYTE)(b_c / 4), (BYTE)(g_c / 4), (BYTE)(r_c / 4) };

            RGBQUAD rgbColorTransp = { (BYTE)(b_t / 4), (BYTE)(g_t / 4), (BYTE)(r_t / 4) };
            RGBQUAD rgbColorReflec = { (BYTE)(b_r / 4), (BYTE)(g_r / 4), (BYTE)(r_r / 4) };
            RGBQUAD rgbColorAmbient = { (BYTE)(b_a / 4), (BYTE)(g_a / 4), (BYTE)(r_a / 4) };
            RGBQUAD rgbColorEspec = { (BYTE)(b_e / 4), (BYTE)(g_e / 4), (BYTE)(r_e / 4) };
            RGBQUAD rgbColorDifus = { (BYTE)(b_d / 4), (BYTE)(g_d / 4), (BYTE)(r_d / 4) };

            FreeImage_SetPixelColor(bitmap, x, y, &rgbColor);

            FreeImage_SetPixelColor(bitmapTrans, x, y, &rgbColorTransp);
            FreeImage_SetPixelColor(bitmapRef, x, y, &rgbColorReflec);
            FreeImage_SetPixelColor(bitmapAmb, x, y, &rgbColorAmbient);
            FreeImage_SetPixelColor(bitmapEspec, x, y, &rgbColorEspec);
            FreeImage_SetPixelColor(bitmapDif, x, y, &rgbColorDifus);
        }
    }

    /* --------------------------------------- */
    std::string dt = getCurrentDateTime();


    guardarImagen(bitmap, dt, "Base");// , dt);
    guardarImagen(bitmapTrans, dt, "Transp");//, dt);
    guardarImagen(bitmapRef, dt, "Reflec");//, dt);
    guardarImagen(bitmapAmb, dt, "Amb");//, dt);
    guardarImagen(bitmapEspec, dt, "Espec");//, dt);
    guardarImagen(bitmapDif, dt, "Difus");//, dt);

    return 0;
}
