#include "Color.h"

Color corregirColorMaximos(Color c) {
	if (c.b > 255.f) {
		c.b = 255.f;
	}

	if (c.g > 255.f) {
		c.g = 255.f;
	}

	if (c.r > 255.f) {
		c.r = 255.f;
	}

	return c;
}