#include "CargaArchivo.h"
#include "Esfera.h"
#include "Objeto.h"
#include <fstream>
#include <iostream>

CargaArchivo::CargaArchivo()
{
	std::ifstream f("Especificaciones.json");
	json data = json::parse(f);

	for (int i = 0; i < 4; i++) {
		Plano p;
		p.altura = data["planos"][i]["altura"];
		p.ancho = data["planos"][i]["ancho"];
		p.largo = data["planos"][i]["largo"];
		p.r = data["planos"][i]["r"];
		p.g = data["planos"][i]["g"];
		p.b = data["planos"][i]["b"];
		p.atConst = data["cilindros"][i]["atConst"];
		p.atLineal = data["cilindros"][i]["atLineal"];
		p.atCuadr = data["cilindros"][i]["atCuadr"];
		p.esxpReflecEspec = data["cilindros"][i]["esxpReflecEspec"];
		p.fracReflecEspec = data["cilindros"][i]["fracReflecEspec"];
		p.colorReflecEspec = data["cilindros"][i]["colorReflecEspec"];
		p.sesibilidad = data["cilindros"][i]["sesibilidad"];
		this->cuarto.push_back(p);
	}

	for (int r = 0; r < data["rectangulos"].size(); r++) {
		Rectangulo rect;
		rect.altura = data["rectangulos"][r]["altura"];
		rect.ancho = data["rectangulos"][r]["ancho"];
		rect.largo = data["rectangulos"][r]["largo"];
		rect.r = data["rectangulos"][r]["r"];
		rect.g = data["rectangulos"][r]["g"];
		rect.b = data["rectangulos"][r]["b"];
		rect.Refleccion = data["rectangulos"][r]["Refleccion"];
		rect.Refraccion = data["rectangulos"][r]["Refraccion"];
		rect.Transparencia = data["rectangulos"][r]["Transparencia"];
		rect.x = data["rectangulos"][r]["x"];
		rect.y = data["rectangulos"][r]["y"];
		rect.z = data["rectangulos"][r]["z"];
		rect.atConst = data["cilindros"][r]["atConst"];
		rect.atLineal = data["cilindros"][r]["atLineal"];
		rect.atCuadr = data["cilindros"][r]["atCuadr"];
		rect.esxpReflecEspec = data["cilindros"][r]["esxpReflecEspec"];
		rect.fracReflecEspec = data["cilindros"][r]["fracReflecEspec"];
		rect.colorReflecEspec = data["cilindros"][r]["colorReflecEspec"];
		rect.sesibilidad = data["cilindros"][r]["sesibilidad"];
		this->rects.push_back(rect);
	}

	for (int e = 0; e < data["esferas"].size(); e++) {
		Sphear esfe;
		esfe.radio = data["esferas"][e]["radio"];
		esfe.r = data["esferas"][e]["r"];
		esfe.g = data["esferas"][e]["g"];
		esfe.b = data["esferas"][e]["b"];
		esfe.Refleccion = data["esferas"][e]["Refleccion"];
		esfe.Refraccion = data["esferas"][e]["Refraccion"];
		esfe.Transparencia = data["esferas"][e]["Transparencia"];
		esfe.x = data["esferas"][e]["x"];
		esfe.y = data["esferas"][e]["y"];
		esfe.z = data["esferas"][e]["z"];
		esfe.atConst = data["cilindros"][e]["atConst"];
		esfe.atLineal = data["cilindros"][e]["atLineal"];
		esfe.atCuadr = data["cilindros"][e]["atCuadr"];
		esfe.esxpReflecEspec = data["cilindros"][e]["esxpReflecEspec"];
		esfe.fracReflecEspec = data["cilindros"][e]["fracReflecEspec"];
		esfe.colorReflecEspec = data["cilindros"][e]["colorReflecEspec"];
		esfe.sesibilidad = data["cilindros"][e]["sesibilidad"];
		this->sphears.push_back(esfe);
	}

	for (int c = 0; c < data["cilindros"].size(); c++) {
		Cilinder cilin;
		cilin.radio = data["cilindros"][c]["radio"];
		cilin.altura = data["cilindros"][c]["altura"];
		cilin.r = data["cilindros"][c]["r"];
		cilin.g = data["cilindros"][c]["g"];
		cilin.b = data["cilindros"][c]["b"];
		cilin.Refleccion = data["cilindros"][c]["Refleccion"];
		cilin.Refraccion = data["cilindros"][c]["Refraccion"];
		cilin.Transparencia = data["cilindros"][c]["Transparencia"];
		cilin.x = data["cilindros"][c]["x"];
		cilin.y = data["cilindros"][c]["y"];
		cilin.z = data["cilindros"][c]["z"];
		cilin.atConst = data["cilindros"][c]["atConst"];
		cilin.atLineal = data["cilindros"][c]["atLineal"];
		cilin.atCuadr = data["cilindros"][c]["atCuadr"];
		cilin.esxpReflecEspec = data["cilindros"][c]["esxpReflecEspec"];
		cilin.fracReflecEspec = data["cilindros"][c]["fracReflecEspec"];
		cilin.colorReflecEspec = data["cilindros"][c]["colorReflecEspec"];
		cilin.sesibilidad = data["cilindros"][c]["sesibilidad"];
		this->cilins.push_back(cilin);
	}

	this->ubCam.push_back(data["camara"][0]["x"]);
	this->ubCam.push_back(data["camara"][0]["y"]);
	this->ubCam.push_back(data["camara"][0]["z"]);
	this->dirACam.push_back(data["camara"][0]["dirAx"]);
	this->dirACam.push_back(data["camara"][0]["dirAy"]);
	this->dirACam.push_back(data["camara"][0]["dirAz"]);
	this->dirPVCam.push_back(data["camara"][0]["dirPVx"]);
	this->dirPVCam.push_back(data["camara"][0]["dirPVx"]);
	this->dirPVCam.push_back(data["camara"][0]["dirPVx"]);
	this->resolucion = data["camara"][0]["Resolucion"];

}

std::vector<float> CargaArchivo::getDirACam()
{
	return this->dirACam;
}

std::vector<float> CargaArchivo::getUbCam()
{
	return this->ubCam;
}

std::vector<float> CargaArchivo::getDirPVCam()
{
	return this->dirPVCam;
}

int CargaArchivo::getRes()
{
	return this->resolucion;
}

std::vector<Sphear> CargaArchivo::getEsferas()
{
	return this->sphears;
}

std::vector<Triangulo> CargaArchivo::getPlanos()
{
	return std::vector<Triangulo>();
}

std::vector<Rectangulo> CargaArchivo::getPrismas()
{
	return this->rects;
}
