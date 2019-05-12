#include "Colors.h"

Colors::Colors(float r, float g, float b): r(r), g(g), b(b) {}
	
float Colors::getR() const {
	return r;
}
float Colors::getB() const {
	return b;
}
float Colors::getG() const {
	return g;
}