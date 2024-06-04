#include "Cilindro.h"

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
	La ecuacion de la esfera es asi:
		(x - c_x)^2 + (y - c_y)^2 = r^2, con altura > z > centro.z

		Utilizando  x = x_0 + t*v_x (notar que x_0 es la posicion del pixel en el frame)
					y = y_0 + t*v_y
					z = z_0 + t*v_z

		Queda de la forma:

		(x_0 + t*v_x - c_x)^2 + (y_0 + t*v_y - c_y)^2 = r^2, con altura > z_0 + t*v_z > centro.z

		Formando un polinomio de 2º grado queda de la forma:

		  (v_x^2 + v_y^2 + v_z^2) *  t^2
		+ 2(v_x(x_0 - c_x) + v_y(y_0 - c_y) + v_z(z_0 - c_z) ) * t
		+ (x_0 - c_x)^2 + (y_0 - c_y)^2 + (z_0 - c_z)^2

	*/
	return 0.0f;
}

MathVector Cilindro::getNormal(MathVector punto)
{
	return MathVector();
}

Color Cilindro::getColor(Rayo rayo, float t)
{
	return Color();
}
