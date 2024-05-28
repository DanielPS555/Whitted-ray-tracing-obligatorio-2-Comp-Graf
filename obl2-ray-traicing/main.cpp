#include <iostream>
#include <cmath>
#include <FreeImage.h>
#include "ejemplo.h"
#include <ctime>
#include "Utils.h"
#include "ObjetosEscena.h"
#include "Camara.h"
#include "Esfera.h"
#include "../Objeto.h"


// Main function
int main() {
    ObjetosEscena::getInstancia()->resolucionX = 1000.f;
    ObjetosEscena::getInstancia()->resolucionY =  500.f;


    // Camara superior diagonal para el ejemplo
    //Camara* camaraPtr = new Camara({ 0.0f, 1.0f, 1.0f }, { 0.0f, -1.0f, 1.0f }, { 200.0f, 500.0f, 600.0f });
    Camara* camaraPtr = new Camara({ 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f});

    FIBITMAP* bitmap = crearImagenVacia(ObjetosEscena::getInstancia()->resolucionX,
                                        ObjetosEscena::getInstancia()->resolucionY);


    /* ESTE CODIGO ES DE PRUEBA, NO ABUSAR EN PONER COSAS EN EL*/

    int w = (int)ObjetosEscena::getInstancia()->resolucionX;
    int h = (int)ObjetosEscena::getInstancia()->resolucionY;

    Esfera* eferaPrueba = new Esfera({ 200,200,600 }, 150.0f, {(BYTE)100, (BYTE)2, (BYTE)15});
    Esfera* eferaPrueba2 = new Esfera({ -100,200,1200 }, 350.0f, { (BYTE)200, (BYTE)20, (BYTE)150 });

    Objeto** elementos = new Objeto * [2];
    elementos[0] = eferaPrueba;
    elementos[1] = eferaPrueba2;

    ObjetosEscena::getInstancia()->setElementos(2, elementos);


    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {

            Rayo r = camaraPtr->getRayo(x, y);


            RGBQUAD rgbColor = ObjetosEscena::getInstancia()->getPixelPorRayo(r);
            

            FreeImage_SetPixelColor(bitmap, x, y, &rgbColor);
        }
    }

    /* --------------------------------------- */

    guardarImagen(bitmap);

    return 0;
}
