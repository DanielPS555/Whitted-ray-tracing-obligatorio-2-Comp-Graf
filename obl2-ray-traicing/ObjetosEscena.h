#include "MathVector.h"


#ifndef OBJECTO_ESCENA_CLASS
#define OBJECTO_ESCENA_CLASS


class ObjetosEscena
{
private:
	ObjetosEscena() {
		resolucionX = 0.0f;
		resolucionY = 0.0f;

		bgColor = { 255.f, 255.f, 255.f };
		

	}

public:
	unsigned resolucionX;
	unsigned resolucionY;

	
	MathVector bgColor;



	ObjetosEscena(const ObjetosEscena& obj) = delete;
	static ObjetosEscena* getInstancia() {
		static ObjetosEscena* const inst = new ObjetosEscena{};

		return inst;
	}
};

#endif // !OBJECTO_ESCENA_CLASS