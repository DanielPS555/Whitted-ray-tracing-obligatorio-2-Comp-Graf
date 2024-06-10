#include "Utils.h"
#include "Freeimage.h"

std::string getCurrentDateTime() {
    std::time_t now = std::time(nullptr);
    struct tm timeInfo;
    localtime_s(&timeInfo, &now);  // Usar localtime_s en lugar de localtime
    char buf[80];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", &timeInfo);
    return std::string(buf);
}

FIBITMAP* crearImagenVacia(int width,int height) {
    // cargar free_image para guardar la imagen.
    FreeImage_Initialise();
    FIBITMAP* bitmap = FreeImage_Allocate(width, height, 24);
    if (!bitmap) {
        std::cerr << "Could not allocate memory for image!" << std::endl;
    }
    return bitmap;
}

void guardarImagen(FIBITMAP* bitmap, std::string sufix_nombre) {
    //-----GUARDAR IMAGEN GENERADA-----
    std::string filename = "generadas/" + getCurrentDateTime() + ".png";
    if (FreeImage_Save(FIF_PNG, bitmap, filename.c_str(), 0)) {
        std::cout << "Image saved successfully!" << std::endl;
    }
    else {
        std::cerr << "Failed to save image!" << std::endl;
    }

    FreeImage_Unload(bitmap);
    FreeImage_DeInitialise();
}

float gradosToRadianes(float grados) {
    return (grados * M_PI) / 180.0f;
}

float obtenerMenorRaizPositivaBhaskara(float a, float b, float c) {

    float discriminante = b * b - 4 * a * c;

    if (discriminante < 0.0f) {
        return -1;
    }
    else if (discriminante == 0.0f) {

        float resultado = (-b + sqrt(discriminante)) / (2 * a);
        return resultado < 0 ? -1 : resultado;

    }
    else {
        float resultado1 = (-b + sqrt(discriminante)) / (2 * a);
        float resultado2 = (-b - sqrt(discriminante)) / (2 * a);

        if (resultado1 > 0 && resultado2 > 0) {
            return std::min(resultado1, resultado2);
        }
        else if (resultado1 > 0) {
            return resultado1;
        }
        else if (resultado2 > 0) {
            return resultado2;
        }
        else {
            return -1;
        }
    }

}