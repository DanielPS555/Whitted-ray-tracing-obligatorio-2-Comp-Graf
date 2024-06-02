#include "mathVector.h"

#include <iostream>

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES  // for C
#endif 
#include <math.h>



void print(MathVector vector) {
	std::cout << vector.x << "|" << vector.y << "|" << vector.z << std::endl;
}

MathVector sumar(MathVector vec1, MathVector vec2) {
	return {
		vec1.x + vec2.x,
		vec1.y + vec2.y,
		vec1.z + vec2.z
	};
}

MathVector multiplicar(MathVector vec1, MathVector vec2) {
	return {
		vec1.x * vec2.x,
		vec1.y * vec2.y,
		vec1.z * vec2.z
	};
}


MathVector restar(MathVector vec1, MathVector vec2) {
	return {
		vec1.x - vec2.x,
		vec1.y - vec2.y,
		vec1.z - vec2.z
	};
}

MathVector multiplicarPorEscalar(MathVector vec1, float escalar) {
	return {
		vec1.x * escalar,
		vec1.y * escalar,
		vec1.z * escalar
	};
}

float productoEscalar(MathVector vec1, MathVector vec2) {
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

MathVector productoVectorial(MathVector vec1, MathVector vec2) {
	return {
		vec1.y * vec2.z - vec1.z * vec2.y,
		vec1.z * vec2.x - vec1.x * vec2.z,
		vec1.x * vec2.y - vec1.y * vec2.x
	};
}

float angulo(MathVector vec1, MathVector vec2) {
	float normaA = norma(vec1);
	float normaB = norma(vec2);
	float proEsc = productoEscalar(vec1, vec2);
	return (float)acos(proEsc / (normaA * normaB));
}

float norma(MathVector vec1) {
	return sqrt(productoEscalar(vec1, vec1));
}

MathVector normalizar(MathVector vec) {
	float invertidoNorma = 1 / norma(vec);
	return multiplicarPorEscalar(vec, invertidoNorma);
}

bool isNulo(MathVector vec) {
	return vec.x == 0 && vec.y == 0 && vec.z == 0;
}

MathVector rotar(MathVector vec, float anguloEnGrado) {
	float rad = (anguloEnGrado * M_PI) / 180.0f;
	return {
		cos(rad) * vec.x - sin(rad) * vec.y,
		sin(rad) * vec.x + cos(rad) * vec.y,
		vec.z
	};
}

MathVector interpolarVectores(MathVector inicio, MathVector fin, float t) {
	float x_inter = (1 - t) * inicio.x + t * fin.x;
	float y_inter = (1 - t) * inicio.y + t * fin.y;
	float z_inter = (1 - t) * inicio.z + t * fin.z;
	return { x_inter, y_inter, z_inter };
}

MathVector simetrico(MathVector ejeSimetria, MathVector vectorAInvetir) {
	MathVector normasEspejo = normalizar(ejeSimetria);
	float c = productoEscalar(ejeSimetria, vectorAInvetir);
	MathVector vec1 = multiplicarPorEscalar(normasEspejo, 2 * c);
	return restar(vec1, vectorAInvetir);
}
