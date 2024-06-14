#include "Plano.h"

Plano::Plano(MathVector puntoDeAnclaje, MathVector vectorU, MathVector vectorV, Color color)
: Objeto(){
	
	this->puntoDeAnclaje = puntoDeAnclaje;
	this->u = vectorU;
	this->v = vectorV;

	this->normalCalculada = normalizar(productoVectorial(u, v));

	setColorBase(color);
}

void Plano::intersepcion(Rayo rayo, int& idObjetoInterseptado, float& t_int)
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


	MathVector r = rayo.dirrecion;
	MathVector rc = rayo.puntoAnclaje;
	MathVector c = puntoDeAnclaje;


	float detA = - u.x * v.y * r.z	-   u.y * v.z * r.x   -   u.z * v.x * r.y
		         + r.x * v.y * u.z	+	r.y * v.z * u.x   +   r.z * v.x * u.y;

	if (detA != 0) {

		float f_x = -c.x + rc.x;
		float f_y = -c.y + rc.y;
		float f_z = -c.z + rc.z;

		float det_z = + u.x * v.y * f_z   +	u.y * v.z * f_x	  +   u.z * v.x * f_y
					  - f_x * v.y * u.z  -	f_y * v.z * u.x	  -	  f_z * v.x * u.y;

		float t = det_z / detA;

		if (t > 0) {
			t_int = t;
			idObjetoInterseptado = this->getId();
			return;
		}
		else {
			t_int = -1;
			idObjetoInterseptado = -1;
			return;
		}
	}
	else {
		t_int = -1;
		idObjetoInterseptado = -1;
		return;
	}

	
}

MathVector Plano::getNormal(MathVector punto)
{
	return normalCalculada;
}

std::vector<Objeto*> Plano::getObjetosInternos() {
	std::vector<Objeto*> objetosInternos;
	objetosInternos.push_back(this);
	return objetosInternos;
}
