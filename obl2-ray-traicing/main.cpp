#include <iostream>
#include <cmath>
#include <FreeImage.h>
#include "ejemplo.h"
#include <ctime>
#include "Utils.h"
#include "ObjetosEscena.h"
#include "Camara.h"
#include "Esfera.h"


// Main function
int main() {
    ObjetosEscena::getInstancia()->resolucionX = 1000.f;
    ObjetosEscena::getInstancia()->resolucionY =  500.f;

    Camara* camaraPtr = new Camara({ 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });


    FIBITMAP* bitmap = crearImagenVacia(ObjetosEscena::getInstancia()->resolucionX,
                                        ObjetosEscena::getInstancia()->resolucionY);


    /* ESTE CODIGO ES DE PRUEBA, NO ABUSAR EN PONER COSAS EN EL*/

    int w = (int)ObjetosEscena::getInstancia()->resolucionX;
    int h = (int)ObjetosEscena::getInstancia()->resolucionY;

    Esfera* eferaPrueba = new Esfera({ 200,200,1000 }, 150.0f);


    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {

            Rayo r = camaraPtr->getRayo(x, y);


            RGBQUAD rgbColor;
            if (eferaPrueba->intersepcion(r) == -1) {
                rgbColor.rgbRed = (BYTE)(1 * 255);
                rgbColor.rgbGreen = (BYTE)(1 * 255);
                rgbColor.rgbBlue = (BYTE)(1 * 255);
            }
            else {
                rgbColor.rgbRed = (BYTE)(0 * 255);
                rgbColor.rgbGreen = (BYTE)(0 * 255);
                rgbColor.rgbBlue = (BYTE)(0 * 255);
            }

            FreeImage_SetPixelColor(bitmap, x, h - y - 1, &rgbColor);
        }
    }

    /* --------------------------------------- */

    guardarImagen(bitmap);

    return 0;
}
