#include <iostream>
#include <cmath>
#include <FreeImage.h>
#include "ejemplo.h"
#include <ctime>
#include "Utils.h"

// Main function
int main() {
    int width = 800;
    int height = 600;

    FIBITMAP* bitmap = cargarParametrosImagen(width, height);

    dibujar(width, height, bitmap);

    guardarImagen(bitmap);

    return 0;
}
