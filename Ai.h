#ifndef Ai_hpp
#define Ai_hpp

#include "AppComponent.h"
#include "Player.h""


class Ai: public AppComponent, public Player{
	public:
		Ai(float, float, float, float, float, float, float, float);
		void moveUp();
		void moveDown();
		void moveRight();
		void moveLeft();
		void move();
		void draw() const;
};


#endif