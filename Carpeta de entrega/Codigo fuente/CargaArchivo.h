#pragma once

#include "Objeto.h"
#include "LuzPuntual.h"
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

#ifndef CARGA_CLASS 
#define CARGA_CLASS 

struct Cara
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
	
	float direccion_x;
	float direccion_y;
	float direccion_z;

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
	MathVector V1;
	MathVector V2;
	MathVector V3;
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

struct LuzPunt {
	MathVector pos;
	float r;
	float g;
	float b;
};


struct Plane {
	MathVector puntoBase;
	MathVector VectorU;
	MathVector VectorV;
	float D;
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

struct Malla {
	float trasladar_x;
	float trasladar_y;
	float trasladar_z;

	float escalamiento;
	std::string obj_url;
	std::string png_url;

};

class CargaArchivo
{
	private:

		json data;
		std::vector<Triangle> paredes;
		std::vector<Cara> cuarto;
		std::vector<Malla> mallas;
		std::vector<Sphear> sphears;
		std::vector<Cilinder> cilins;
		MathVector dirACam, dirPVCam, ubCam;
		std::vector<float> luzAmb;
		std::vector<LuzPunt> luces;
		std::vector<Plane> planos;
		int resolucionX;
		int resolucionY;

	public:

		CargaArchivo(std::string file);

		MathVector getDirACam();

		MathVector getUbCam();

		MathVector getDirPVCam();

		int getResX();
		int getResY();

		std::vector<Plane> getPlanos();

		std::vector<Sphear> getEsferas();

		std::vector<Triangle> getCaras();

		std::vector<Malla> getMallas();

		std::vector<LuzPunt> getLuces();
		int getCantLuces();

		MathVector getLuzAmb();

		std::vector<Cilinder> getCilindros();

};

#endif
