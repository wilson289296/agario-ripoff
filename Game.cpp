#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <time.h>
#include <cstdlib>

#include "Game.h"

Game *singleton;

void runAI(int id){
	//if(singleton->menu) {
		singleton->aiMove();
	//}
	glutTimerFunc(300, runAI, id);
}

void timer(int id){
    // This will get called every 16 milliseconds after
    // you call it once
	
    // If you want to manipulate the app in here
    // do it through the singleton pointer
	
	singleton->createOrbs();
	
	
    glutTimerFunc(500, timer, id);
}

Game::Game(){
    srand(time(NULL));
	
	players = new std::vector<Player*>;
	orbs = new std::vector<Circle*>;
	textbox1 = new TextBox("One Player", -0.25, -0.25);
	textbox2 = new TextBox("Two Player", -0.25, -0.50);
	//textbox3 = new TextBox("Temp", 0, 0);
	selector = new Circle(-0.30, -0.235, 0.015f, 0, 1, 1);
	numPlayers = 0;
	selectOne = true;
	triggered = false;
	
	reset(numPlayers);

    setRate(1);
	singleton = this;
	runAI(1);
	timer(0);
    start();
}

void Game::action(){
	
	if(numAlive == 1) {
		
		numPlayers = 0;
		reset(numPlayers);
		std::cout << "GAME OVER" << std::endl;
		return;
	}

	if(wDown){ (players->at(0))->moveUp();} else {(players->at(0))->setYVelo((players->at(0))->getYVelo() * 0.999);}
	if(aDown){ (players->at(0))->moveLeft();} else {(players->at(0))->setXVelo((players->at(0))->getXVelo() * 0.999);}
	if(sDown){ (players->at(0))->moveDown();} else {(players->at(0))->setYVelo((players->at(0))->getYVelo() * 0.999);}
	if(dDown){ (players->at(0))->moveRight();} else {(players->at(0))->setXVelo((players->at(0))->getXVelo() * 0.999);}
	if(numPlayers > 1){
		if(upDown){ (players->at(1))->moveUp();} else {(players->at(1))->setYVelo((players->at(1))->getYVelo() * 0.999);}
		if(downDown){ (players->at(1))->moveDown();} else {(players->at(1))->setYVelo((players->at(1))->getYVelo() * 0.999);}
		if(leftDown){ (players->at(1))->moveLeft();} else {(players->at(1))->setXVelo((players->at(1))->getXVelo() * 0.999);}
		if(rightDown){ (players->at(1))->moveRight();} else {(players->at(1))->setXVelo((players->at(1))->getXVelo() * 0.999);}
	}
	
	for(std::vector<Player*>::iterator it = players->begin(); it < players->end(); it++){
		(*it)->playerMove();
		for(std::vector<Player*>::iterator tit = 1 + it; tit < players->end(); tit++){
			if((*it)->getCircle()->contains((*tit)->getCircle()) && (*it)->isDead != true){
				if ((*tit)->getCircle()->getRad() > (*it)->getCircle()->getRad()){
					(*tit)->getCircle()->setRad((*tit)->getCircle()->getRad() + (*it)->getCircle()->getRad());
					(*it)->isDead = true;
					(*it)->getCircle()->setRad(0);
				} else {
					(*it)->getCircle()->setRad((*it)->getCircle()->getRad() + (*tit)->getCircle()->getRad());
					(*tit)->isDead = true;
					(*tit)->getCircle()->setRad(0);
				}
				numAlive--;
				break;
			}
		}
	}
	
	for(std::vector<Circle*>::iterator it = orbs->begin(); it < orbs->end(); ++it) {
		for(std::vector<Player*>::iterator tit = players->begin(); tit < players->end(); tit++){
			if((*it)->contains((*tit)->getCircle())){
				(*tit)->getCircle()->setRad((*tit)->getCircle()->getRad() + (*it)->getRad()/3);
				//delete *it;
				orbs->erase(it);
				goto beef;
			}
		}
	}	
	beef:;
}

void Game::draw() const {
	
	if(menu) {
		textbox1->draw();
		textbox2->draw();
		selector->draw();
	}
	
	for(std::vector<Player*>::iterator it = players->begin(); it < players->end(); it++){
		if(!(*it)->isDead){
			(*it)->draw();
		}
	}
	
	for(std::vector<Circle*>::iterator it = orbs->begin(); it < orbs->end(); ++it) {
		(*it)->draw();
	}
	
}

void Game::handleKeyDown(unsigned char key, float x, float y){

    if (key == ' '){
    }
	if(!menu){
		if (key == 'w'){
			wDown = true;
		} 
		else if (key == 'a'){
			aDown = true;
		} 
		else if (key == 's'){
			sDown = true;
		} 
		else if (key == 'd'){
			dDown = true;
		} 
	}
	else if(menu){
		if (key == 13) {
			if(selectOne) {
				numPlayers = 1;
				reset(numPlayers);
				menu = false;
			}
			else {
				numPlayers = 2;
				reset(numPlayers);
				menu = false;
			}
			
			return;
		}
	}
}

void Game::handleSpecialKeyDown(int key, float x, float y) {
	if(numPlayers >= 2 && !menu){
		
		if (key == GLUT_KEY_UP){
			upDown = true;
		} else if (key == GLUT_KEY_DOWN){
			downDown = true;
		} else if (key == GLUT_KEY_RIGHT){
			rightDown = true;
		} else if (key == GLUT_KEY_LEFT){
			leftDown = true;
		}
	}
	else if(menu) {
		if (key == GLUT_KEY_DOWN){
			if(selectOne) {
				selector->setY(selector->getY() - 0.25);
				selectOne = false;
			}
			return;
		}
		if (key == GLUT_KEY_UP){
			if(!selectOne) {
				selector->setY(selector->getY() + 0.25);
				selectOne = true;			
			}
			return;
		}
	}
	
}

void Game::aiMove() {
	for(int i = players->size() - 1; i >= numPlayers; i--)
	{
		if(!players->at(i)->isDead)
			(players->at(i))->moveUp();
	}
}

void Game::handleSpecialKeyUp(int key, float x, float y) {
	if (key == GLUT_KEY_UP){
		upDown = false;
	} else if (key == GLUT_KEY_DOWN){
		downDown = false;
	} else if (key == GLUT_KEY_RIGHT){
		rightDown = false;
	} else if (key == GLUT_KEY_LEFT){
		leftDown = false;
	}
}

void Game::handleKeyUp(unsigned char key, float x, float y){
	//std::cout << "called" << std::endl;
	if (key == 'w'){
		wDown = false;
	} else if (key == 'a'){
		aDown = false;
	} else if (key == 's'){
		sDown = false;
	} else if (key == 'd'){
		dDown = false;
	} 
}

void Game::createOrbs() {
	float randX = (((float)rand() / (float) RAND_MAX) * 3.5) - 2;
	float randY = (((float)rand() / (float) RAND_MAX) * 2.0) - 1;
	//std::cout << "Orb created at (" << randX << ", " << randY << ")." << std::endl;
	orbs->push_back(new Circle(randX, randY));
}

void Game::deleteVectors() {
	for(std::vector<Player*>::iterator it = players->begin(); it < players->end(); it++){
		delete (*it);
	}
	
	for(std::vector<Circle*>::iterator it = orbs->begin(); it < orbs->end(); ++it) {
		delete (*it);
	}
}

void Game::reset(int numPlayers) {
	deleteVectors();
	players->clear();
	orbs->clear();
	
	wDown = false;
	aDown = false;
	sDown = false;
	dDown = false;
	upDown = false;
	downDown = false;
	leftDown = false;
	rightDown = false;
	
	numAlive = 4;
	menu = true;
	
	xStart = 1.25;
	yStart = 0.75;
	
	for(int i = 0; i < numPlayers; i++){
	}
	for(int i= 0; i < numPlayers; i++){
		if(i == 0){
			players->push_back(new Player(-xStart, yStart, 0.01f, 1, 0, 0, 0, 0));
		}
		if(i == 1){
			players->push_back(new Player(xStart, yStart, 0.01f, 0, 1, 0, 0, 0));
		}
		if(i == 2){
			players->push_back(new Player(-xStart, -yStart, 0.01f, 0, 0, 1, 0, 0));
		}
		if(i == 3){
			players->push_back(new Player(xStart, -yStart, 0.01f, 1, 1, 0, 0, 0));
		}
	}
	for(int i = 0; i < 4 - numPlayers; i++){
		if(i == 3){
			players->push_back(new Ai(xStart, -yStart, 0.01f, 1, 0, 0, 0, 0));
		}
		if(i == 2){
			players->push_back(new Ai(-xStart, -yStart, 0.01f, 0, 1, 0, 0, 0));
		}
		if(i == 1){
			players->push_back(new Ai(xStart, yStart, 0.01f, 0, 0, 1, 0, 0));
		}
		if(i == 0){
			players->push_back(new Ai(-xStart, yStart, 0.01f, 1, 1, 0, 0, 0));
		}
	}
}

Game::~Game(){
	deleteVectors();
	delete orbs;
	delete players;
	delete textbox1;
	delete textbox2;
	delete selector;
    stop();
}
