#include "Cilindro.h"
#include <corecrt_math.h>
#include "Utils.h"

Cilindro::Cilindro(MathVector centro, float radio, float altura, Color color)
{
	this->altura = altura;
	this->centro = centro;
	this->radio = radio;
	setColorBase(color);
}

float Cilindro::intersepcion(Rayo rayo)
{
	/*
	La ecuacion del cilindro es asi:
		(x - c_x)^2 + (y - c_y)^2 = r^2, con altura > z > centro.z

		Utilizando  x = x_0 + t*v_x (notar que x_0 es la posicion del pixel en el frame)
					y = y_0 + t*v_y
					z = z_0 + t*v_z

		Queda de la forma:

		(x_0 + t*v_x - c_x)^2 + (y_0 + t*v_y - c_y)^2 = r^2, con altura > z_0 + t*v_z > centro.z

		Formando un polinomio de 2º grado queda de la forma:

		  (v_x^2 + v_y^2) *  t^2
		+ 2(v_x(x_0 - c_x) + v_y(y_0 - c_y)) * t
		+ (x_0 - c_x)^2 + (y_0 - c_y)^2

	*/
	float a = powf(rayo.dirrecion.x, 2) +
		powf(rayo.dirrecion.y, 2);

	float b = 2 * (
		rayo.dirrecion.x * (rayo.puntoAnclaje.x - centro.x) +
		rayo.dirrecion.y * (rayo.puntoAnclaje.y - centro.y) 
		);

	float c = powf(rayo.puntoAnclaje.x - centro.x, 2)
		+ powf(rayo.puntoAnclaje.y - centro.y, 2)
		- powf(radio, 2);
	float t = obtenerMenorRaizPositivaBhaskara(a, b, c);
	if ((((rayo.dirrecion.z * t) + rayo.puntoAnclaje.z) <= (centro.z + altura)) && (((rayo.dirrecion.z * t) + rayo.puntoAnclaje.z) >= centro.z)) {
		return t;
	}
	else {
		return -1;
	}
	
}

MathVector Cilindro::getNormal(MathVector punto)
{	
	MathVector v1, v2;
	v2 = punto;
	if (punto.z > (centro.z + altura)) {
		v1 = { centro.x, centro.y, centro.z + altura};
		v2.z = centro.z + altura;
	}
	else {
		if (punto.z < (centro.z)) {
			v1 = { centro.x, centro.y, centro.z};
			v2.z = centro.z;
		}
		else {
			v1 = { centro.x, centro.y, punto.z };
		}
	}
	return normalizar(restar(v2, v1));
}


