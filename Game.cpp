#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <time.h>
#include <cstdlib>

#include "Game.h"

Game *singleton;

Game::Game(){
    srand(time(NULL));
	test = new Circle(0.0f, 0.0f, 0.01f, 1.0f, 0.0f, 0.0f);
	orbs = new std::vector<Circle*>;
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
	
    glutTimerFunc(500, timer, id);
}

void Game::action(){
	//circleMove(xVelo, yVelo);
	/*
	std::vector<Circle*>::iterator it = orbs->begin();
	try {
		while(it != orbs->end())
		{
			if((*it)->contains(test)) {
				test->setRad(test->getRad() + ((*it)->getRad()/2));
				it = orbs->erase(it);
				break;
			}
			else {
				++it;
			}
		}
	}
	catch (int e) {
		std::cout << e << std::endl;
	}
	*/
	for(std::vector<Circle*>::iterator it = orbs->begin(); it != orbs->end(); ++it) {
		if((*it)->contains(test)) {
			std::cout << "we insidie" << std::endl;
			test->setRad(test->getRad() + (*it)->getRad());
			//delete orbs->at(*it);
			//orbs->erase(it);
		}
	}
}

void Game::draw() const {
	for(std::vector<Circle*>::iterator it = orbs->begin(); it != orbs->end(); ++it) {
		(*it)->draw();
	}
}

void Game::handleKeyDown(unsigned char key, float x, float y){
    if (key == ' '){
		timer(0);
    }
    else if (key == 'w'){
        yVelo = 0.0005f;
    }
    else if (key == 's'){
        yVelo = -0.0005f;
    }
	else if (key == 'd'){
        xVelo = 0.0005f;
    }
    else if (key == 'a'){
        xVelo = -0.0005f;
    }
}

void Game::createOrbs() {
	try{
		//if(orbs->size() < 2)
		//{
			float randX = (((float)rand() / (float) RAND_MAX) * 4.0) - 2;
			float randY = (((float)rand() / (float) RAND_MAX) * 2.0) - 1;
			std::cout << "Orb created at (" << randX << ", " << randY << ")." << std::endl;
			Circle *temp = new Circle(randX, randY);
			orbs->push_back(temp);
		//}
	}
	catch(int e) {
		std::cout << e << std::endl;
	}	
}

Game::~Game(){
	delete test;
    stop();
}
