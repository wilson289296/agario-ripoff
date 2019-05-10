#ifndef Player_hpp
#define Player_hpp

#include "AppComponent.h"
#include "Circle.h"

class Player: public AppComponent {
	Circle *user;
	float xVelo;
	float yVelo;
public:
    Player(float=0.0, float=0.0, float rad=0.01, float r=0.0, float g=0.0, float b=0.0, float xVelo=0.0, float yVelo=0.0);
    
	void setXVelo(float);
	void setYVelo(float);
	
	float getXVelo();
	float getYVelo();
	Circle *getCircle();
	
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	
	void draw() const;
	void playerMove();
    
    virtual ~Player(){}
};

#endif
