#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <time.h>
#include <cstdlib>

#include "Game.h"

Game *singleton;

Game::Game(){
    srand(time(NULL));
	test = new Player(0.0f, 0.0f, 0.01f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	orbs = new std::vector<Circle*>;
	
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

	test->playerMove();
	
	for(std::vector<Circle*>::iterator it = orbs->begin(); it != orbs->end(); ++it) {
		if((*it)->contains(test->getCircle())) {
			//std::cout << "we insidie" << std::endl;
			test->getCircle()->setRad(test->getCircle()->getRad() + (*it)->getRad());
			//delete orbs->at(*it);
			orbs->erase(it);
			break;
		}
	}
}

void Game::draw() const {
	test->draw();
	for(std::vector<Circle*>::iterator it = orbs->begin(); it != orbs->end(); ++it) {
		(*it)->draw();
	}
}

void Game::handleKeyDown(unsigned char key, float x, float y){

    if (key == ' '){
		timer(0);
    }
    else if (key == 'w'){
		test->moveUp();
    }
    else if (key == 's'){
		test->moveDown();
    }
	else if (key == 'd'){
		test->moveRight();
    }
    else if (key == 'a'){
		test->moveLeft();
    }
}

void Game::createOrbs() {
	try{
		//if(orbs->size() < 2)
		//{
			float randX = (((float)rand() / (float) RAND_MAX) * 4.0) - 2;
			float randY = (((float)rand() / (float) RAND_MAX) * 2.0) - 1;
			//std::cout << "Orb created at (" << randX << ", " << randY << ")." << std::endl;
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
