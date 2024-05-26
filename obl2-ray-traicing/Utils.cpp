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

FIBITMAP* cargarParametrosImagen(int width,int height) {
    // cargar free_image para guardar la imagen.
    FreeImage_Initialise();
    FIBITMAP* bitmap = FreeImage_Allocate(width, height, 24);
    if (!bitmap) {
        std::cerr << "Could not allocate memory for image!" << std::endl;
    }
    return bitmap;
}

void guardarImagen(FIBITMAP* bitmap) {
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