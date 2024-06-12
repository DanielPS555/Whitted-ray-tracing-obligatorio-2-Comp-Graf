#include "Plano.h"

Plano::Plano(MathVector puntoBase, float D, Color color)
{
	this->puntoBase = puntoBase;
	this->D = D;
	setColorBase(color);
}

float Plano::intersepcion(Rayo rayo)
{
	/*
	La ecuacion del plano es asi:
		Ax + By + Cz + D = 0

		Utilizando  x = x_0 + t*v_x (notar que x_0 es la posicion del pixel en el frame)
					y = y_0 + t*v_y
					z = z_0 + t*v_z

		Queda de la forma:

		A*(x_0 + t*v_x) + B*(y_0 + t*v_y) + C*(z_0 + t*v_z) + D = 0

		Formando un polinomio de 1º grado queda de la forma:

		  t= -(A*x_0+B*y_0+C*z_0+D)/(A*v_x+B*v_y+C*v_z)

	*/
	float t = -((puntoBase.x * rayo.puntoAnclaje.x) + (puntoBase.y * rayo.puntoAnclaje.y) + (puntoBase.z * rayo.puntoAnclaje.z) + D) / ((puntoBase.x * rayo.dirrecion.x) + (puntoBase.y * rayo.dirrecion.y) + (puntoBase.z * rayo.dirrecion.z));

	if (t > 0) {
		return t;
	}
	else {
		return -1.0;
	}
}

MathVector Plano::getNormal(MathVector punto)
{
	return puntoBase;
}
