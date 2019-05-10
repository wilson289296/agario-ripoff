#ifndef Game_hpp
#define Game_hpp

#include "AppComponent.h"
#include "AnimatedRect.h"
#include "Timer.h"
#include "Circle.h"
#include <vector>

class Game: public AppComponent, private Timer{

public:
	
	std::vector<Circle*> *orbs;
	Circle *test;
	float xVelo;
	float yVelo;
	int eaten;

    Game();
    
    void draw() const ;
    void handleKeyDown(unsigned char, float, float);
    
    void action();
	void createOrbs();
	
	friend void timer(int);

    ~Game();

};

#endif 
