#include "CargaArchivo.h"
#include <fstream>
#include <iostream>
#include "Triangulo.h"
#include "Malla.h"

CargaArchivo::CargaArchivo(std::string file)
{
	std::ifstream f(file);
	json data = json::parse(f);

	for (int i = 0; i < data["caras"].size(); i++) {
		if (data["caras"][i]["name"] != "ign") {
			Cara p;
			p.altura = data["caras"][i]["altura"];
			p.ancho = data["caras"][i]["ancho"];
			p.largo = data["caras"][i]["largo"];
			p.x = data["caras"][i]["x"];
			p.y = data["caras"][i]["y"];
			p.z = data["caras"][i]["z"];
			p.r = data["caras"][i]["r"];
			p.g = data["caras"][i]["g"];
			p.b = data["caras"][i]["b"];
			p.atConst = data["caras"][i]["atConst"];
			p.atLineal = data["caras"][i]["atLineal"];
			p.atCuadr = data["caras"][i]["atCuadr"];
			p.esxpReflecEspec = data["caras"][i]["esxpReflecEspec"];
			p.fracReflecEspec = data["caras"][i]["fracReflecEspec"];
			p.colorReflecEspecR = data["caras"][i]["colorReflecEspecR"];
			p.colorReflecEspecG = data["caras"][i]["colorReflecEspecG"];
			p.colorReflecEspecB = data["caras"][i]["colorReflecEspecB"];
			p.sesibilidad = data["caras"][i]["sensibilidad"];
			this->cuarto.push_back(p);
		}
	}

	for (int p = 0; p < data["planos"].size(); p++) {
		if (data["planos"][p]["name"] != "ign") {
			Plane pla;
			pla.D = data["planos"][p]["D"];
			pla.puntoBase.x = data["planos"][p]["x"];
			pla.puntoBase.y = data["planos"][p]["y"];
			pla.puntoBase.z = data["planos"][p]["z"];

			pla.VectorU.x = data["planos"][p]["vectorU_x"];
			pla.VectorU.y = data["planos"][p]["vectorU_y"];
			pla.VectorU.z = data["planos"][p]["vectorU_z"];

			pla.VectorV.x = data["planos"][p]["vectorV_x"];
			pla.VectorV.y = data["planos"][p]["vectorV_y"];
			pla.VectorV.z = data["planos"][p]["vectorV_z"];

			pla.r = data["planos"][p]["r"];
			pla.g = data["planos"][p]["g"];
			pla.b = data["planos"][p]["b"];
			pla.atConst = data["planos"][p]["atConst"];
			pla.atLineal = data["planos"][p]["atLineal"];
			pla.atCuadr = data["planos"][p]["atCuadr"];
			pla.esxpReflecEspec = data["planos"][p]["esxpReflecEspec"];
			pla.fracReflecEspec = data["planos"][p]["fracReflecEspec"];
			pla.colorReflecEspecR = data["planos"][p]["colorReflecEspecR"];
			pla.colorReflecEspecG = data["planos"][p]["colorReflecEspecG"];
			pla.colorReflecEspecB = data["planos"][p]["colorReflecEspecB"];
			pla.sesibilidad = data["planos"][p]["sensibilidad"];
			this->planos.push_back(pla);
		}
	}

	for (int r = 0; r < data["mallas"].size(); r++) {
		if (data["mallas"][r]["name"] != "ign") {
			Malla malla;
			malla.trasladar_x = data["mallas"][r]["trasladar_x"];
			malla.trasladar_y = data["mallas"][r]["trasladar_y"];
			malla.trasladar_z = data["mallas"][r]["trasladar_z"];
			malla.escalamiento = data["mallas"][r]["escalamiento"];
			malla.obj_url = data["mallas"][r]["obj_url"];
			malla.png_url = data["mallas"][r]["png_url"];
			this->mallas.push_back(malla);
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

			cilin.direccion_x = data["cilindros"][c]["direccion_x"];
			cilin.direccion_y = data["cilindros"][c]["direccion_y"];
			cilin.direccion_z = data["cilindros"][c]["direccion_z"];

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
	this->resolucionX = data["camara"][0]["ResolucionX"];
	this->resolucionY = data["camara"][0]["ResolucionY"];

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

int CargaArchivo::getResX()
{
	return this->resolucionX;
}

int CargaArchivo::getResY()
{
	return this->resolucionY;
}

std::vector<Plane> CargaArchivo::getPlanos()
{
	return this->planos;
}

std::vector<Sphear> CargaArchivo::getEsferas()
{
	return this->sphears;
}

std::vector<Triangle> CargaArchivo::getCaras()
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
		t1.r = this->cuarto[t].r; 
		t1.g = this->cuarto[t].g; 
		t1.b = this->cuarto[t].b;
		t1.atConst = this->cuarto[t].atConst; 
		t1.atLineal = this->cuarto[t].atLineal; 
		t1.atCuadr = this->cuarto[t].atCuadr;
		t1.esxpReflecEspec = this->cuarto[t].esxpReflecEspec; 
		t1.fracReflecEspec = this->cuarto[t].fracReflecEspec;
		t1.colorReflecEspecR = this->cuarto[t].colorReflecEspecR; 
		t1.colorReflecEspecG = this->cuarto[t].colorReflecEspecG; 
		t1.colorReflecEspecB = this->cuarto[t].colorReflecEspecB;
		
		t2.V1 = v3;
		t2.V2 = v1;
		t2.V3 = v2;
		t2.r = this->cuarto[t].r;
		t2.g = this->cuarto[t].g;
		t2.b = this->cuarto[t].b;
		t2.atConst = this->cuarto[t].atConst;
		t2.atLineal = this->cuarto[t].atLineal;
		t2.atCuadr = this->cuarto[t].atCuadr;
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

std::vector<Malla> CargaArchivo::getMallas()
{
	return this->mallas;
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
