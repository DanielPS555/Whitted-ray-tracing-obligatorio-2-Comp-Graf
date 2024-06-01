#include "Esfera.h"
#include "cmath"
#include "Utils.h"

#include "ObjetosEscena.h"
#include "LuzAmbiente.h"

Esfera::Esfera(MathVector centro, float radio, Color color) {
	this->centro = centro;
	this->radio = radio;
	setColorBase(color);
}

float Esfera::intersepcion(Rayo ra) {

	/* 
	La ecuacion de la esfera es asi:
		(x - c_x)^2 + (y - c_y)^2 + (z - c_z)^2 = r^2

		Utilizando  x = x_0 + t*v_x (notar que x_0 es la posicion del pixel en el frame)
					y = y_0 + t*v_y
					z = z_0 + t*v_z

		Queda de la forma:

		(x_0 + t*v_x - c_x)^2 + (y_0 + t*v_y - c_y)^2 + (z_0 + t*v_z - c_z)^2 = r^2

		Formando un polinomio de 2º grado queda de la forma:

		  (v_x^2 + v_y^2 + v_z^2) *  t^2
		+ 2(v_x(x_0 - c_x) + v_y(y_0 - c_y) + v_z(z_0 - c_z) ) * t
		+ (x_0 - c_x)^2 + (y_0 - c_y)^2 + (z_0 - c_z)^2

	*/

	float a = powf(ra.dirrecion.x, 2) +
			  powf(ra.dirrecion.y, 2) +
			  powf(ra.dirrecion.z, 2);

	float b = 2 * (
					ra.dirrecion.x * (ra.puntoAnclaje.x - centro.x) +
					ra.dirrecion.y * (ra.puntoAnclaje.y - centro.y) +
					ra.dirrecion.z * (ra.puntoAnclaje.z - centro.z)
			);

	float c = powf(ra.puntoAnclaje.x - centro.x, 2)
				+ powf(ra.puntoAnclaje.y - centro.y, 2)
				+ powf(ra.puntoAnclaje.z - centro.z, 2)
				- powf(radio, 2);

	return obtenerMenorRaizPositivaBhaskara(a, b, c);

}


MathVector Esfera::getNormal(MathVector punto) {
	return normalizar(restar(punto, centro));
}

