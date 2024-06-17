#include "LuzAmbiente.h"


Color getLuzAmbientePorObjeto(LuzAmbiente luz, Color colorObjecto, float sensibilidad) {
	return {
		(luz.intensidadesRgb.r / 255.f) * sensibilidad * colorObjecto.r,
		(luz.intensidadesRgb.g / 255.f) * sensibilidad * colorObjecto.g,
		(luz.intensidadesRgb.b / 255.f )* sensibilidad * colorObjecto.b
	};
}