#include "MathVector.h"
#include "Rayo.h"
#include "../Objeto.h"
#include <FreeImage.h>

#ifndef OBJECTO_ESCENA_CLASS
#define OBJECTO_ESCENA_CLASS


class ObjetosEscena
{
private:

	Objeto** elementos;
	unsigned int numeroElementos;

	RGBQUAD bgColor;

	ObjetosEscena() {
		resolucionX = 0.0f;
		resolucionY = 0.0f;

		bgColor.rgbRed  = (BYTE)(1 * 255);
		bgColor.rgbGreen = (BYTE)(1 * 255);
		bgColor.rgbBlue = (BYTE)(1 * 255);
		

	}

public:
	unsigned resolucionX;
	unsigned resolucionY;


	ObjetosEscena(const ObjetosEscena& obj) = delete;
	static ObjetosEscena* getInstancia() {
		static ObjetosEscena* const inst = new ObjetosEscena{};

		return inst;
	}

	// La collecion de "elementos" debe estar creado y se va a utilizar de igual forma
	void setElementos(unsigned numeroElementos, Objeto** elementos);

	RGBQUAD getPixelPorRayo(Rayo rayo);

};

#endif // !OBJECTO_ESCENA_CLASS