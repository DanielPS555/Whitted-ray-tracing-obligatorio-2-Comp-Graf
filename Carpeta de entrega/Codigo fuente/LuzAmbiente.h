#include "Color.h"

#ifndef LUZ_AMBIENTE_STRUCT
#define LUZ_AMBIENTE_STRUCT

struct LuzAmbiente{
	Color intensidadesRgb;
};


Color getLuzAmbientePorObjeto(LuzAmbiente luz, Color colorObjecto, float sensibilidad);


#endif