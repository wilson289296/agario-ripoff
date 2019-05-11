#include "Ai.h"

Ai::Ai(float x, float y, float rad, float r, float g, float b, float xVelo, float yVelo):Player(x, y, rad, r, g, b, xVelo, yVelo) {
	
}
	

void Ai::moveUp(){
	move();
}

void Ai::moveDown(){
	move();
}


void Ai::moveRight(){
	move();
}


void Ai::moveLeft(){
	move();
}

void Ai::draw() const{
	Player::draw();
}

void Ai::move(){
	//float amount = 0.0001 * ((rand() % 10) + 1);
	if(rand() % 10 > 5) setYVelo(getYVelo() + 0.0001);
	else setYVelo(getYVelo() - 0.0001);
	if(rand() % 10 > 5) setXVelo(getXVelo() + 0.0001);
	else setXVelo(getXVelo() - 0.0001);
}



