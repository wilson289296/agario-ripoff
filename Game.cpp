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
	glutTimerFunc(200, runAI, id);
}

void timer(int id){
    // This will get called every 16 milliseconds after
    // you call it once
	
    // If you want to manipulate the app in here
    // do it through the singleton pointer
	if(!singleton->win_screen){
	singleton->createOrbs();
	}
	
	
    glutTimerFunc(500, timer, id);
}

Game::Game(){
    srand(time(NULL));
	
	players = new std::vector<Player*>;
	orbs = new std::vector<Circle*>;
	sort_scoreboard = new std::vector<TextBox*>;
	ready_scoreboard = new std::vector<TextBox*>;
	textbox1 = new TextBox("One Player", -0.25, -0.25);
	textbox2 = new TextBox("Two Player", -0.25, -0.50);
	win_display = new TextBox("Temp", 0, 0);
	win_screen = false;
	selector = new Circle(-0.30, -0.235, 0.015f, 0, 1, 1);
	numPlayers = 0;
	selectOne = true;
	triggered = false;
	winner = '\0';

	sort_scoreboard->push_back(new TextBox("Red", 1.5, 0.95, GLUT_BITMAP_HELVETICA_18, 1, 0, 0));
	sort_scoreboard->push_back(new TextBox("Blue", 1.5, 0.90, GLUT_BITMAP_HELVETICA_18, 0, 0, 1));
	sort_scoreboard->push_back(new TextBox("Green", 1.5, 0.85, GLUT_BITMAP_HELVETICA_18, 0, 1, 0));
	sort_scoreboard->push_back(new TextBox("Yellow", 1.5, 0.80, GLUT_BITMAP_HELVETICA_18, 1, 1, 0));
	ready_scoreboard->push_back(new TextBox("Red", 1.5, 0.95, GLUT_BITMAP_HELVETICA_18, 1, 0, 0));
	ready_scoreboard->push_back(new TextBox("Blue", 1.5, 0.90, GLUT_BITMAP_HELVETICA_18, 0, 0, 1));
	ready_scoreboard->push_back(new TextBox("Green", 1.5, 0.85, GLUT_BITMAP_HELVETICA_18, 0, 1, 0));
	ready_scoreboard->push_back(new TextBox("Yellow", 1.5, 0.80, GLUT_BITMAP_HELVETICA_18, 1, 1, 0));
	selector = new Circle(-0.30, -0.235, 0.015f, 0, 1, 1);
	numPlayers = 0;
	selectOne = true;
	updating = false;
	
	reset(numPlayers); 

    setRate(1);
	singleton = this;
	runAI(1);
	timer(0);
    start();
}

void Game::action(){
	
	if(!resetting) {
		if(numAlive == 1) {
			win_screen = true;
			numPlayers = 0;
			for(int tit = 0; tit < 4; tit++){
				if(!(players->at(tit))->isDead){
					if(tit == 0){
						winner = 'r';
						win_display->setR(1);
						win_display->setG(0);
						win_display->setB(0);
						win_display->setText("Red wins!");
					} else if (tit == 1){
						winner = 'g';
						win_display->setR(0);
						win_display->setG(1);
						win_display->setB(0);
						win_display->setText("Green wins!");
					} else if (tit == 2){
						winner = 'b';
						win_display->setR(0);
						win_display->setG(0);
						win_display->setB(1);
						win_display->setText("Blue wins!");
					} else if (tit == 3){
						winner = 'y';
						win_display->setR(1);
						win_display->setG(1);
						win_display->setB(0);
						win_display->setText("Yellow wins!");
					}
				}
			}
			//if(!win_screen) reset(numPlayers);
			//std::cout << "GAME OVER" << std::endl;
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
	scoreboardSort();
	}
}

void Game::draw() const {
	
	if(win_screen){
		win_display->draw();
	}
	
	if(!win_screen){
		if(menu) {
			textbox1->draw();
			textbox2->draw();
			selector->draw();
		}
	}
	
	
	if(!menu && !updating){
		for(int i = 0; i < ready_scoreboard->size(); i++) {
			(ready_scoreboard->at(i))->setY(0.95 - (0.05 * i));
			(ready_scoreboard->at(i))->draw();
		}
	}
	
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
		if(win_screen){
			win_screen = false;
			reset(0);
		}
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

void Game::scoreboardSort()
{
	if(!singleton->menu) {
		std::vector<float> *playerRad = new std::vector<float>;
		for(int i = 0; i < singleton->players->size(); i++)
			playerRad->push_back(((singleton->players->at(i))->getCircle())->getRad());
		
		// We use insertion sort, because the players vector is size 4, and is small
		// And we heard insertion sort is good for small n's
		
		for(int i = 0; i < singleton->players->size(); i++)
		{
			std::cout << "sort!\n";
			float curRad = (playerRad->at(i));
			TextBox *curBoard = sort_scoreboard->at(i);
			int j = i - 1;
			while(j >= 0 && (playerRad->at(j) < curRad))
			{
				//sort_scoreboard->at(j+1) = (sort_scoreboard->at(j));
				playerRad->at(j+1) = playerRad->at(j);
				j--;
			}
			if(playerRad->at(j+1) != curRad) {
				updating = true;
				TextBox* temp = ready_scoreboard->at(j+1);
				ready_scoreboard->at(j+1) = curBoard;
				ready_scoreboard->at(i) = temp;
				playerRad->at(j+1) = curRad;
				updating = false;
			}
			
		}
		delete playerRad;/*
		
		for(int i = 0; i < 4; i++){
			ready_scoreboard->at(i) = sort_scoreboard->at(i);
		}
		*/
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
	resetting = true;
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
	
	int playersSpawned = numPlayers;
	
	for(int i= 0; i < 4; i++){
		float xSpawn, ySpawn;
		if(i%2 == 0)
			xSpawn = -xStart;
		else
			xSpawn = xStart;
		if(i < 2)
			ySpawn = yStart;
		else
			ySpawn = -yStart;
		if(playersSpawned > 0)
		{
			players->push_back(new Player(xSpawn, ySpawn, 0.01f, 1, 0, 0, 0, 0, false));
			playersSpawned--;
		}
		else
		{
			players->push_back(new Ai(xSpawn, ySpawn, 0.01f, 1, 0, 1, 0, 0));
		}
	}
	resetting = false;
}

Game::~Game(){
	deleteVectors();
	delete orbs;
	delete players;
	delete textbox1;
	delete textbox2;
	delete win_display;
	delete selector;
    stop();
}
