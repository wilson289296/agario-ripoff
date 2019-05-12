#ifndef Ai_hpp
#define Ai_hpp

#include "AppComponent.h"
#include "Player.h""


class Ai: public AppComponent, public Player{
	public:
		Ai(float = 0, float = 0, float = 0.01, float = 1, float = 1, float = 1, float = 0, float = 0);
		void moveUp();
		void moveDown();
		void moveRight();
		void moveLeft();
		void move();
		void draw() const;
};


#endif