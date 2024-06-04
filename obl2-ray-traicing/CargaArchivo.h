#pragma once

#include "nlohmann/json.hpp"
#include "Triangulo.h"
#include "LuzPuntual.h"
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct Plano
{
	int ancho;
	int largo;
	int altura;
	int r;
	int g;
	int b;
	int atConst;
	int	atLineal;
	int	atCuadr;
	int	esxpReflecEspec;
	int	fracReflecEspec;
	int colorReflecEspec;
	int sesibilidad;
};

struct Rectangulo
{
	int ancho;
	int largo;
	int altura;
	int x;
	int y;
	int z;
	int r;
	int g;
	int b;
	int Transparencia;
	int Refleccion;
	int Refraccion;
	int atConst;
	int	atLineal;
	int	atCuadr;
	int	esxpReflecEspec;
	int	fracReflecEspec;
	int colorReflecEspec;
	int sesibilidad;
};

struct Sphear
{
	int radio;
	int x;
	int y;
	int z;
	int r;
	int g;
	int b;
	int Transparencia;
	int Refleccion;
	int Refraccion;
	int atConst;
	int	atLineal;
	int	atCuadr;
	int	esxpReflecEspec;
	int	fracReflecEspec;
	int colorReflecEspec;
	int sesibilidad;
};

struct Cilinder
{
	int radio;
	int altura;
	int x;
	int y;
	int z;
	int r;
	int g;
	int b;
	int Transparencia;
	int Refleccion;
	int Refraccion;

	int atConst;
	int	atLineal;
	int	atCuadr;
	int	esxpReflecEspec;
	int	fracReflecEspec;
	int colorReflecEspec;
	int sesibilidad;
};


class CargaArchivo
{
	private:

		json data;
		std::vector<Plano> cuarto;
		std::vector<Rectangulo> rects;
		std::vector<Sphear> sphears;
		std::vector<Cilinder> cilins;
		std::vector<float> dirACam, dirPVCam, ubCam;
		std::vector<float> luzAmb;
		std::vector<LuzPuntual> luces;
		int resolucion;

	public:

		CargaArchivo(std::string file);

		std::vector<float> getDirACam();

		std::vector<float> getUbCam();

		std::vector<float> getDirPVCam();

		int getRes();

		std::vector<Sphear> getEsferas();

		std::vector<Triangulo> getPlanos();

		std::vector<Rectangulo> getPrismas();

		std::vector<LuzPuntual> getLuces();

		std::vector<float> getLuzAmb();
};

