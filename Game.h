#ifndef Game_hpp
#define Game_hpp

#include "AppComponent.h"
#include "AnimatedRect.h"
#include "Timer.h"
#include "Player.h"
#include "Circle.h"
#include "Ai.h"
#include "Textbox.h"
#include <vector>

class Game: public AppComponent, private Timer{

public:
	TextBox* textbox1;
	TextBox* textbox2;
	TextBox* win_display;
	Circle* selector;
	std::vector<Circle*> *orbs;
	std::vector<Player*> *players;
	int numPlayers;
	int numAlive;
	float xStart;
	float yStart;
	bool menu;
	bool win_screen;
	bool selectOne;
	bool triggered;
	char winner;
	
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

	//constructor
    Game();
    
    void draw() const ;
    void handleKeyDown(unsigned char, float, float);
	void handleKeyUp(unsigned char, float, float);
	void handleSpecialKeyDown(int, float, float);
	void handleSpecialKeyUp(int, float, float);
	
	//void handleKeyUp(unsigned char, float, float);
	void createOrbs();
    void aiMove();
    void action();
	void reset(int numPlayers);
	void deleteVectors();
	
	friend void timer(int);
	friend void runAI(int);

    ~Game();

};

#endif 
