#pragma once

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
};

struct Cilindro
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
};


class CargaArchivo
{
	private:

		json data;
		std::vector<Plano> cuarto;
		std::vector<Rectangulo> rects;
		std::vector<Sphear> sphears;
		std::vector<Cilindro> cilins;
		int xCam, yCam, zCam, resolucion;

	public:

		CargaArchivo();
};

