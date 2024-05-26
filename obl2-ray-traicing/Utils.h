#include <iostream>
#include "Freeimage.h"

#ifndef UTILS
#define UTILS


std::string getCurrentDateTime();
FIBITMAP* cargarParametrosImagen(int width, int height);
void guardarImagen(FIBITMAP* bitmap);


#endif // !UTILS