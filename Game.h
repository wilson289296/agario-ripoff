#ifndef Game_hpp
#define Game_hpp

#include "AppComponent.h"
#include "AnimatedRect.h"
#include "Timer.h"
#include "Player.h"
#include "Circle.h"
#include "Ai.h"
#include <vector>

class Game: public AppComponent, private Timer{

public:
	
	std::vector<Circle*> *orbs;
	std::vector<Player*> *players;
	int numPlayers;
	
	//WASD states
	bool wDown;
	bool aDown;
	bool sDown;
	bool dDown;
	
	//arrow key states
	bool downDown;
	bool upDown;
	bool leftDown;
	bool rightDown;
	
	/*
	Player *test;
	Player *player2;
	Ai *bitch;
	*/

	

    Game();
    
    void draw() const ;
    void handleKeyDown(unsigned char, float, float);
	void handleKeyUp(unsigned char, float, float);
	void handleSpecialKeyDown(int, float, float);
	
	//void handleKeyUp(unsigned char, float, float);
	void createOrbs();
    
    void action();
	
	friend void timer(int);

    ~Game();

};

#endif 
