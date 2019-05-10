#include <iostream>
#include "Player.h"

Player::Player(float x, float y, float rad, float r, float g, float b, float xVelo, float yVelo):
	user(new Circle(x, y, rad, r, g, b)), xVelo(xVelo), yVelo(yVelo) {
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

void Player::draw() const {
    user->draw();
}

void Player::playerMove(float x, float y) {
	user->setX(user->getX() + xVelo);
	user->setY(user->getY() + yVelo);
}