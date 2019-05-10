#ifndef Circle_h
#define Circle_h

#include "Shape.h"
#include <cmath>

class Circle: public Shape{
protected:
    float x;
    float y;
    float rad;
    
    float r;
    float g;
    float b;
    
public:
    Circle(float=0.0f, float=0.0f, float=0.005f, float=1.0f, float=1.0f, float=1.0f);
    
	//Getters
	float getX() const;
	float getY() const;
	float getRad() const;
	
	//Setters
	void setX(float);
	void setY(float);
	void setRad(float);
	
    bool contains(Circle *) const;

    void redrawScene();
    
    virtual void draw() const;
    
    virtual ~Circle();
};

#endif
