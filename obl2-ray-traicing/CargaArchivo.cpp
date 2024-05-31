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
		this->cuarto.push_back(p);
		std::cout << p.altura;
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
		this->sphears.push_back(esfe);
	}

	for (int c = 0; c < data["cilindros"].size(); c++) {
		Cilindro cilin;
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
		this->cilins.push_back(cilin);
	}

	this->xCam = data["camara"][0]["x"];
	this->yCam = data["camara"][0]["y"];
	this->zCam = data["camara"][0]["z"];
	this->resolucion = data["camara"][0]["Resolucion"];

}
