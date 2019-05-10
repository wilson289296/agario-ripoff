#include <iostream>
#include "Circle.h"

//--------------------Constructor--------------------//
Circle::Circle(float x, float y, float rad, float r, float g, float b): x(x), y(y), rad(rad), r(r), g(g), b(b){
    
}

//--------------------Getters--------------------//
float Circle::getX() const{
	return x;
}
float Circle::getY() const{
	return y;
}
float Circle::getRad() const {
	return rad;
}

//--------------------Setters--------------------//
void Circle::setX(float x) {
	this->x = x;
}
void Circle::setY(float y) {
	this->y = y;
}
void Circle::setRad(float rad) {
	this->rad = rad;
}

//--------------------Contains--------------------//
bool Circle::contains(Circle *other) const {
	float distance = sqrt( (float)pow(( (float)x - other->getX() ), 2) + (float)pow(( (float)y - other->getY() ), 2)); 
    return distance < other->getRad();
}
//--------------------Draws--------------------//
void Circle::draw() const {
    glColor3f(r, g, b);
    
    glBegin(GL_POLYGON);
    
    float theta = 0;
			
	float thetaInc = M_PI/100;
	
	glBegin(GL_LINES);
	
	for (theta; theta < 2*M_PI; theta+=thetaInc) {
		glVertex2f(rad * cos(theta) + x, rad * sin(theta) + y);
	}
			
    
    glEnd();
}

void Circle::redrawScene(){
    glutPostRedisplay();
}

//--------------------Deconstructor--------------------//
Circle::~Circle(){
    
}
