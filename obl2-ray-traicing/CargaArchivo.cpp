#include "CargaArchivo.h"
#include "Esfera.h"
#include "Objeto.h"
#include <fstream>

CargaArchivo::CargaArchivo()
{
	std::ifstream f("Especificaciones.json");
	json data = json::parse(f);
	
	for (auto jit = data.begin(); jit != data.end(); jit++) {
		
	}
}
