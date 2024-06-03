#include "MathVector.h"
#include "Rayo.h"
#include "../Objeto.h"
#include "Color.h"
#include "LuzAmbiente.h"
#include "LuzPuntual.h"

#ifndef OBJECTO_ESCENA_CLASS
#define OBJECTO_ESCENA_CLASS


class ObjetosEscena
{
private:

	Objeto** elementos;
	unsigned int numeroElementos;
	

	Color bgColor;

	

	ObjetosEscena() {
		resolucionX = 0.0f;
		resolucionY = 0.0f;

		bgColor.r = 0;
		bgColor.g = 0;
		bgColor.b = 0;
	}

public:
	unsigned resolucionX;
	unsigned resolucionY;

	LuzAmbiente luzAmbiente;
	LuzPuntual* lucesDifusas;
	int numeroLucesDifusas;

	ObjetosEscena(const ObjetosEscena& obj) = delete;
	static ObjetosEscena* getInstancia() {
		static ObjetosEscena* const inst = new ObjetosEscena{};

		return inst;
	}

	// La collecion de "elementos" debe estar creado y se va a utilizar de igual forma
	void setElementos(unsigned numeroElementos, Objeto** elementos);

	Color getPixelPorRayo(Rayo rayo,int profundidad);

	void getIntersepcionMasCercana(Rayo rayo, int& indiceObjeto, float& t_intersepcion);

};

#endif // !OBJECTO_ESCENA_CLASS