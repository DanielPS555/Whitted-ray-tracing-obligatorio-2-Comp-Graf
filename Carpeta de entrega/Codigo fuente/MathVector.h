#ifndef MATH_VECTOR
#define MATH_VECTOR

struct MathVector {
	float x;
	float y;
	float z;

};




MathVector sumar(MathVector, MathVector);
MathVector multiplicar(MathVector, MathVector);
MathVector restar(MathVector, MathVector);
MathVector multiplicarPorEscalar(MathVector, float);

float productoEscalar(MathVector, MathVector);

MathVector productoVectorial(MathVector, MathVector);
float angulo(MathVector, MathVector);

float norma(MathVector);

MathVector normalizar(MathVector);

bool isNulo(MathVector);

void print(MathVector);

MathVector rotar(MathVector, float anguloEnGrado);

// El grado de interpolacion entre el inicio de inicio y fin lo `marca t`, donde 0 es el inicio y 1 es el final
MathVector interpolarVectores(MathVector inicio, MathVector fin, float t);
MathVector simetrico(MathVector ejeSimetria, MathVector vectorAInvetir);
MathVector calcularMagnitudCuadrada(MathVector v);
#endif 


