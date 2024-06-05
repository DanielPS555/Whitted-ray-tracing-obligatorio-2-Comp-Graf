#pragma once

#include "../Objeto.h"
#include "LuzPuntual.h"
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

#ifndef CARGA_CLASS 
#define CARGA_CLASS 

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
	float atLineal;
	float atCuadr;
	float esxpReflecEspec;
	float fracReflecEspec;
	float colorReflecEspecR;
	float colorReflecEspecG;
	float colorReflecEspecB;
	float sesibilidad;
};


struct Triangle {
	float xV1;
	float yV1;
	float zV1;
	float xV2;
	float yV2;
	float zV2;
	float xV3;
	float yV3;
	float zV3;
	float r;
	float g;
	float b;
	float Transparencia;
	float Refleccion;
	float Refraccion;

	float atConst;
	float atLineal;
	float atCuadr;
	float esxpReflecEspec;
	float fracReflecEspec;
	float colorReflecEspecR;
	float colorReflecEspecG;
	float colorReflecEspecB;
	float sesibilidad;
};

class CargaArchivo
{
	private:

		json data;
		std::vector<Objeto*> paredes;
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

		std::vector<Objeto*> getPlanos();

		std::vector<Rectangulo> getPrismas();

		LuzPuntual* getLuces();
		int getCantLuces();

		MathVector getLuzAmb();

		std::vector<Cilinder> getCilindros();
};

#endif
