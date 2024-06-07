#include "CargaArchivo.h"
#include <fstream>
#include <iostream>
#include "Triangulo.h"

CargaArchivo::CargaArchivo(std::string file)
{
	std::ifstream f(file);
	json data = json::parse(f);

	for (int i = 0; i < data["planos"].size(); i++) {
		if (data["planos"][i]["name"] != "ign") {
			Plano p;
			p.altura = data["planos"][i]["altura"];
			p.ancho = data["planos"][i]["ancho"];
			p.largo = data["planos"][i]["largo"];
			p.x = data["planos"][i]["x"];
			p.y = data["planos"][i]["y"];
			p.z = data["planos"][i]["z"];
			p.r = data["planos"][i]["r"];
			p.g = data["planos"][i]["g"];
			p.b = data["planos"][i]["b"];
			p.atConst = data["planos"][i]["atConst"];
			p.atLineal = data["planos"][i]["atLineal"];
			p.atCuadr = data["planos"][i]["atCuadr"];
			p.esxpReflecEspec = data["planos"][i]["esxpReflecEspec"];
			p.fracReflecEspec = data["planos"][i]["fracReflecEspec"];
			p.colorReflecEspecR = data["planos"][i]["colorReflecEspecR"];
			p.colorReflecEspecG = data["planos"][i]["colorReflecEspecG"];
			p.colorReflecEspecB = data["planos"][i]["colorReflecEspecB"];
			p.sesibilidad = data["planos"][i]["sensibilidad"];
			this->cuarto.push_back(p);
		}
	}

	for (int r = 0; r < data["rectangulos"].size(); r++) {
		if (data["rectangulos"][r]["name"] != "ign") {
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
			rect.atConst = data["rectangulos"][r]["atConst"];
			rect.atLineal = data["rectangulos"][r]["atLineal"];
			rect.atCuadr = data["rectangulos"][r]["atCuadr"];
			rect.esxpReflecEspec = data["rectangulos"][r]["esxpReflecEspec"];
			rect.fracReflecEspec = data["rectangulos"][r]["fracReflecEspec"];
			rect.colorReflecEspecR = data["rectangulos"][r]["colorReflecEspecR"];
			rect.colorReflecEspecG = data["rectangulos"][r]["colorReflecEspecG"];
			rect.colorReflecEspecB = data["rectangulos"][r]["colorReflecEspecB"];
			rect.sesibilidad = data["rectangulos"][r]["sensibilidad"];
			this->rects.push_back(rect);
		}
	}

	for (int e = 0; e < data["esferas"].size(); e++) {
		if (data["esferas"][e]["name"] != "ign") {
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
			esfe.atConst = data["esferas"][e]["atConst"];
			esfe.atLineal = data["esferas"][e]["atLineal"];
			esfe.atCuadr = data["esferas"][e]["atCuadr"];
			esfe.esxpReflecEspec = data["esferas"][e]["esxpReflecEspec"];
			esfe.fracReflecEspec = data["esferas"][e]["fracReflecEspec"];
			esfe.colorReflecEspecR = data["esferas"][e]["colorReflecEspecR"];
			esfe.colorReflecEspecG = data["esferas"][e]["colorReflecEspecG"];
			esfe.colorReflecEspecB = data["esferas"][e]["colorReflecEspecB"];
			esfe.sesibilidad = data["esferas"][e]["sensibilidad"];
			this->sphears.push_back(esfe);
		}
	}

	for (int c = 0; c < data["cilindros"].size(); c++) {
		if (data["cilindros"][c]["name"] != "ign") {
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
			cilin.colorReflecEspecR = data["cilindros"][c]["colorReflecEspecR"];
			cilin.colorReflecEspecG = data["cilindros"][c]["colorReflecEspecG"];
			cilin.colorReflecEspecB = data["cilindros"][c]["colorReflecEspecB"];
			cilin.sesibilidad = data["cilindros"][c]["sensibilidad"];
			this->cilins.push_back(cilin);
		}
	}

	for (int tr = 0; tr < data["triangulos"].size(); tr++) {
		if (data["triangulos"][tr]["name"] != "ign") {
			Triangle tri;
			tri.V1 = { data["triangulos"][tr]["xV1"], data["triangulos"][tr]["yV1"], data["triangulos"][tr]["zV1"] };
			tri.V2 = { data["triangulos"][tr]["xV2"], data["triangulos"][tr]["yV2"], data["triangulos"][tr]["zV2"] };
			tri.V3 = { data["triangulos"][tr]["xV3"], data["triangulos"][tr]["yV3"], data["triangulos"][tr]["zV3"] };
			tri.r = data["triangulos"][tr]["r"];
			tri.g = data["triangulos"][tr]["g"];
			tri.b = data["triangulos"][tr]["b"];
			tri.atConst = data["triangulos"][tr]["atConst"];
			tri.atLineal = data["triangulos"][tr]["atLineal"];
			tri.atCuadr = data["triangulos"][tr]["atCuadr"];
			tri.esxpReflecEspec = data["triangulos"][tr]["esxpReflecEspec"];
			tri.fracReflecEspec = data["triangulos"][tr]["fracReflecEspec"];
			tri.colorReflecEspecR = data["triangulos"][tr]["colorReflecEspecR"]; 
			tri.colorReflecEspecG = data["triangulos"][tr]["colorReflecEspecG"];
			tri.colorReflecEspecB = data["triangulos"][tr]["colorReflecEspecB"];
			tri.Refleccion = data["triangulos"][tr]["Refleccion"];
			//data["triangulos"][tr]["Refraccion"];
			tri.Transparencia = data["triangulos"][tr]["Transparencia"];
			//data["triangulos"][tr]["sensibilidad"];
			this->paredes.push_back(tri);
		}
	}

	this->ubCam = { data["camara"][0]["x"], data["camara"][0]["y"], data["camara"][0]["z"] };
	this->dirACam = {data["camara"][0]["dirAx"], data["camara"][0]["dirAy"], data["camara"][0]["dirAz"]};
	this->dirPVCam = { data["camara"][0]["dirPVx"], data["camara"][0]["dirPVy"], data["camara"][0]["dirPVz"] };
	this->resolucion = data["camara"][0]["Resolucion"];

	this->luzAmb.push_back(data["luzAmbiente"][0]["intr"]);
	this->luzAmb.push_back(data["luzAmbiente"][0]["intg"]);
	this->luzAmb.push_back(data["luzAmbiente"][0]["intb"]);

	for (int l = 0; l < data["lucesPuntuales"].size(); l++) {
		LuzPunt lp;
		lp.r = data["lucesPuntuales"][l]["intr"]; 
		lp.g = data["lucesPuntuales"][l]["intg"]; 
		lp.b = data["lucesPuntuales"][l]["intb"];
		lp.pos = { data["lucesPuntuales"][l]["posX"], data["lucesPuntuales"][l]["posY"], data["lucesPuntuales"][l]["posZ"]};
		this->luces.push_back(lp);
	}

}

MathVector CargaArchivo::getDirACam()
{
	return this->dirACam;
}

MathVector CargaArchivo::getUbCam()
{
	return this->ubCam;
}

MathVector CargaArchivo::getDirPVCam()
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

std::vector<Triangle> CargaArchivo::getPlanos()
{
	for (int t = 0; t < this->cuarto.size(); t++) {
		MathVector v0, v1, v2, v3;
		v0 = {this->cuarto[t].x, this->cuarto[t].y, this->cuarto[t].z};
		if (this->cuarto[t].altura == 0) {
			v1 = { this->cuarto[t].x + this->cuarto[t].largo, this->cuarto[t].y, this->cuarto[t].z };
			v2 = { this->cuarto[t].x, this->cuarto[t].y + this->cuarto[t].ancho, this->cuarto[t].z };
			v3 = { this->cuarto[t].x + this->cuarto[t].largo, this->cuarto[t].y + this->cuarto[t].ancho, this->cuarto[t].z };
		}
		if (this->cuarto[t].ancho == 0) {
			v1 = { this->cuarto[t].x + this->cuarto[t].largo, this->cuarto[t].y, this->cuarto[t].z };
			v2 = { this->cuarto[t].x, this->cuarto[t].y, this->cuarto[t].z + this->cuarto[t].altura};
			v3 = { this->cuarto[t].x + this->cuarto[t].largo, this->cuarto[t].y, this->cuarto[t].z + this->cuarto[t].altura};
		}
		if (this->cuarto[t].largo == 0) {
			v1 = { this->cuarto[t].x, this->cuarto[t].y, this->cuarto[t].z + this->cuarto[t].altura};
			v2 = { this->cuarto[t].x, this->cuarto[t].y + this->cuarto[t].ancho, this->cuarto[t].z};
			v3 = { this->cuarto[t].x, this->cuarto[t].y + this->cuarto[t].ancho, this->cuarto[t].z + this->cuarto[t].altura};
		}
		Triangle t1, t2;
		t1.V1 = v0; 
		t1.V2 = v1; 
		t1.V3 = v2; 
		t2.V1 = v3; 
		t2.V2 = v1; 
		t2.V3 = v2; 
		t1.r = this->cuarto[t].r; 
		t1.g = this->cuarto[t].g; 
		t1.b = this->cuarto[t].b;
		t2.r = this->cuarto[t].r; 
		t2.g = this->cuarto[t].g; 
		t2.b = this->cuarto[t].b; 
		t1.atConst = this->cuarto[t].atConst; 
		t1.atLineal = this->cuarto[t].atLineal; 
		t1.atCuadr = this->cuarto[t].atCuadr;
		t2.atConst = this->cuarto[t].atConst;
		t2.atLineal = this->cuarto[t].atLineal;
		t2.atCuadr = this->cuarto[t].atCuadr;
		t1.esxpReflecEspec = this->cuarto[t].esxpReflecEspec; 
		t1.fracReflecEspec = this->cuarto[t].fracReflecEspec;
		t1.colorReflecEspecR = this->cuarto[t].colorReflecEspecR; 
		t1.colorReflecEspecG = this->cuarto[t].colorReflecEspecG; 
		t1.colorReflecEspecB = this->cuarto[t].colorReflecEspecB;
		t2.esxpReflecEspec = this->cuarto[t].esxpReflecEspec;
		t2.fracReflecEspec = this->cuarto[t].fracReflecEspec;
		t2.colorReflecEspecR = this->cuarto[t].colorReflecEspecR;
		t2.colorReflecEspecG = this->cuarto[t].colorReflecEspecG;
		t2.colorReflecEspecB = this->cuarto[t].colorReflecEspecB;
		this->paredes.push_back(t1);
		this->paredes.push_back(t2);
	}
	return this->paredes;
}

std::vector<Rectangulo> CargaArchivo::getPrismas()
{
	return this->rects;
}

std::vector<LuzPunt> CargaArchivo::getLuces()
{	
	return this->luces;
}

int CargaArchivo::getCantLuces()
{
	return this->luces.size();
}

MathVector CargaArchivo::getLuzAmb()
{
	return { this->luzAmb[0] , this->luzAmb[1] , this->luzAmb[2] };
}

std::vector<Cilinder> CargaArchivo::getCilindros()
{
	return this->cilins;
}
