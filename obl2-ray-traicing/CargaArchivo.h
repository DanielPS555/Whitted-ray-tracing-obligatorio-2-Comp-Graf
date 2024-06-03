#pragma once

#include "nlohmann/json.hpp"
#include "Objeto.h"
#include "Triangulo.h"
#include "LuzPuntual.h"
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct Plano
{
	float ancho;
	float largo;
	float altura;
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	float atConst;
	float	atLineal;
	float	atCuadr;
	float	esxpReflecEspec;
	float	fracReflecEspec;
	float colorReflecEspecR;
	float colorReflecEspecG;
	float colorReflecEspecB;
	float sesibilidad;
};

struct Rectangulo
{
	float ancho;
	float largo;
	float altura;
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	float Transparencia;
	float Refleccion;
	float Refraccion;
	float atConst;
	float	atLineal;
	float	atCuadr;
	float	esxpReflecEspec;
	float	fracReflecEspec;
	float colorReflecEspecR;
	float colorReflecEspecG;
	float colorReflecEspecB;
	float sesibilidad;
};

struct Sphear
{
	float radio;
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	float Transparencia;
	float Refleccion;
	float Refraccion;
	float atConst;
	float	atLineal;
	float	atCuadr;
	float	esxpReflecEspec;
	float	fracReflecEspec;
	float colorReflecEspecR;
	float colorReflecEspecG;
	float colorReflecEspecB;
	float sesibilidad;
};

struct Cilinder
{
	float radio;
	float altura;
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	float Transparencia;
	float Refleccion;
	float Refraccion;

	float atConst;
	float	atLineal;
	float	atCuadr;
	float	esxpReflecEspec;
	float	fracReflecEspec;
	float colorReflecEspecR;
	float colorReflecEspecG;
	float colorReflecEspecB;
	float sesibilidad;
};


class CargaArchivo
{
	private:

		json data;
		std::vector<Plano> cuarto;
		std::vector<Rectangulo> rects;
		std::vector<Sphear> sphears;
		std::vector<Cilinder> cilins;
		MathVector dirACam, dirPVCam, ubCam;
		std::vector<float> luzAmb;
		std::vector<LuzPuntual> luces;
		int resolucion;

	public:

		CargaArchivo(std::string file);

		MathVector getDirACam();

		MathVector getUbCam();

		MathVector getDirPVCam();

		int getRes();

		std::vector<Sphear> getEsferas();

		std::vector<Triangulo*> getPlanos();

		std::vector<Rectangulo> getPrismas();

		LuzPuntual* getLuces();
		int getCantLuces();

		std::vector<float> getLuzAmb();

		std::vector<Cilinder> getCilindros();
};

