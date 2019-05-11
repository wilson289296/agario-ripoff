#include <iostream>
#include "Player.h"

Player::Player(float x, float y, float rad, float r, float g, float b, float xVelo, float yVelo, bool isDead):
	user(new Circle(x, y, rad, r, g, b)), xVelo(xVelo), yVelo(yVelo), isDead(isDead) {
}

void Player::setXVelo(float xv) 
{
	xVelo = xv;
}
void Player::setYVelo(float yv)
{
	yVelo = yv;
}

float Player::getXVelo()
{
	return xVelo;
}
float Player::getYVelo()
{
	return yVelo;
}

Circle* Player::getCircle()
{
	return user;
}

void Player::draw() const {
    user->draw();
}

void Player::moveUp()
{
	if(yVelo >= -0.000002f) 
		yVelo += 0.000001f;
	else 
		yVelo += 0.000002f;
}
void Player::moveDown()
{
	if(yVelo <= 0.000002f) 
		yVelo -= 0.000001f;
	else 
		yVelo -= 0.000002f;
}
void Player::moveRight()
{
	if(xVelo >= -0.000002f) 
		xVelo += 0.000001f;
	else 
		xVelo += 0.000002f;
}
void Player::moveLeft()
{
	if(xVelo <= -0.000002f) 
		xVelo -= 0.000001f;
	else 
		xVelo -= 0.000002f;
}

void Player::playerMove() {
	if(user->getX() > 1.5 || user->getX() < -1.5){
		xVelo = -xVelo * 0.5;
		if(user->getX() > 1.5) user->setX(1.49);
		else user->setX(-1.49);
	}
	else user->setX(user->getX() + xVelo);
	
	if(user->getY() > 1 || user->getY() < -1){
		yVelo = -yVelo * 0.5;
		if(user->getY() > 1) user->setY(0.99);
		else user->setY(-0.99);
	}
	else user->setY(user->getY() + yVelo);
}