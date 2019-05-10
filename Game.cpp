#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <time.h>
#include <cstdlib>

#include "Game.h"

Game *singleton;

Game::Game(){
    
	test = new Circle(0.0f, 0.0f, 0.01f, 1.0f, 0.0f, 0.0f);
	orbs = new std::list<Circle*>;
	xVelo = 0.0f;
	yVelo = 0.0f;
	
    setRate(1);
	singleton = this;
    start();
}

void timer(int id){
    // This will get called every 16 milliseconds after
    // you call it once
	
    // If you want to manipulate the app in here
    // do it through the singleton pointer
	
	singleton->createOrbs();
	
    glutTimerFunc(100, timer, id);
}

void Game::action(){
	circleMove(xVelo, yVelo);
	std::list<Circle*>::iterator it = orbs->begin();
	while(it != orbs->end())
	{
		if((*it)->contains(test)) {
			test->setRad(test->getRad() + (*it)->getRad());
			delete *it;
			orbs->erase(it);
			break;
		}
		else
			it++;
	}
	/*
	for(std::list<Circle*>::iterator it = orbs->begin(); it != orbs->end(); ++it) {
		if((*it)->contains(test)) {
			std::cout << "we insidie" << std::endl;
			test->setRad(test->getRad() + (*it)->getRad());
			//delete orbs->at(*it);
			//orbs->erase(it);
		}
	}*/
}

void Game::draw() const {
    test->draw();
	for(std::list<Circle*>::iterator it = orbs->begin(); it != orbs->end(); ++it) {
		(*it)->draw();
	}
}

void Game::handleKeyDown(unsigned char key, float x, float y){

    if (key == ' '){
		timer(0);
    }
    else if (key == 'w'){
		if(yVelo >= 0) yVelo += 0.0001f;
		else yVelo += 0.0002f;
    }
    else if (key == 's'){
		if(yVelo <= 0) yVelo += -0.0001f;
		else yVelo += -0.0002f;
    }
	else if (key == 'd'){
		if(yVelo >= 0) xVelo += 0.0001f;
		else xVelo += 0.0002f;
    }
    else if (key == 'a'){
		if(yVelo <= 0) xVelo += -0.0001f;
		else xVelo += -0.0002f;
    }
}

void Game::circleMove(float x, float y) {
	if(test->getX() > 1.5 || test->getX() < -1.5){
		xVelo = 0;
		if(test->getX() > 1.5) test->setX(1.5);
		else test->setX(-1.5);
	}
	else test->setX(test->getX() + xVelo);
	
	if(test->getY() > 1 || test->getY() < -1){
		yVelo = 0;
		if(test->getY() > 1) test->setY(1);
		else test->setY(-1);
	}
	else test->setY(test->getY() + yVelo);
}

void Game::createOrbs() {
	if(orbs->size() < 10)
	{
		srand(time(NULL));
		float randX = (((float)rand() / (float) RAND_MAX) * 2) - 1;
		float randY = (((float)rand() / (float) RAND_MAX) * 2) - 1;
		//std::cout << "Orb created at (" << randX << ", " << randY << ")." << std::endl;
		Circle *temp = new Circle(randX, randY);
		orbs->push_back(temp);
	}
}

Game::~Game(){
	delete test;
    stop();
}
