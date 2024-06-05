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
			MathVector	vA = { data["triangulos"][tr]["xV1"], data["triangulos"][tr]["yV1"], data["triangulos"][tr]["zV1"] };
			MathVector  vC = { data["triangulos"][tr]["xV2"], data["triangulos"][tr]["yV2"], data["triangulos"][tr]["zV2"] };
			MathVector  vB = { data["triangulos"][tr]["xV3"], data["triangulos"][tr]["yV3"], data["triangulos"][tr]["zV3"] };
			Color col = { data["triangulos"][tr]["r"], data["triangulos"][tr]["g"], data["triangulos"][tr]["b"] };
			Triangulo* tri = new Triangulo(vA, vB, vC, col);
			tri->setAtenuacion(data["triangulos"][tr]["atConst"], data["triangulos"][tr]["atLineal"], data["triangulos"][tr]["atCuadr"]);
			tri->setParametrosEspeculares(data["triangulos"][tr]["esxpReflecEspec"], data["triangulos"][tr]["fracReflecEspec"], { data["triangulos"][tr]["colorReflecEspecR"], data["triangulos"][tr]["colorReflecEspecG"], data["triangulos"][tr]["colorReflecEspecB"] });

			/*data["triangulos"][tr]["Refleccion"];
			data["triangulos"][tr]["Refraccion"];
			data["triangulos"][tr]["Transparencia"];
			data["triangulos"][tr]["sensibilidad"];*/
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
		LuzPuntual lp;
		lp.intensidad = { data["lucesPuntuales"][l]["intr"], data["lucesPuntuales"][l]["intg"], data["lucesPuntuales"][l]["intb"]};
		lp.posicion = { data["lucesPuntuales"][l]["posX"], data["lucesPuntuales"][l]["posY"], data["lucesPuntuales"][l]["posZ"]};
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

std::vector<Objeto*> CargaArchivo::getPlanos()
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
		Color c = { this->cuarto[t].r, this->cuarto[t].g, this->cuarto[t].b };
		Triangulo* t1 = new Triangulo(v0, v1, v2, c);
		Triangulo* t2 = new Triangulo(v3, v1, v2, c);
		t1->setAtenuacion(this->cuarto[t].atConst, this->cuarto[t].atLineal, this->cuarto[t].atCuadr);
		t1->setParametrosEspeculares(this->cuarto[t].esxpReflecEspec, this->cuarto[t].fracReflecEspec, {this->cuarto[t].colorReflecEspecR, this->cuarto[t].colorReflecEspecG, this->cuarto[t].colorReflecEspecB });
		t2->setAtenuacion(this->cuarto[t].atConst, this->cuarto[t].atLineal, this->cuarto[t].atCuadr);
		t2->setParametrosEspeculares(this->cuarto[t].esxpReflecEspec, this->cuarto[t].fracReflecEspec, { this->cuarto[t].colorReflecEspecR, this->cuarto[t].colorReflecEspecG, this->cuarto[t].colorReflecEspecB });
		this->paredes.push_back(t1);
		this->paredes.push_back(t2);
	}
	return this->paredes;
}

std::vector<Rectangulo> CargaArchivo::getPrismas()
{
	return this->rects;
}

LuzPuntual* CargaArchivo::getLuces()
{	
	LuzPuntual* lucesPunt = new LuzPuntual[luces.size()];
	for (int l = 0; l < luces.size(); l++) {
		lucesPunt[l] = this->luces[l];
	}
	return lucesPunt;
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
