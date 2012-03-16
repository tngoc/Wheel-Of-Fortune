#ifndef H_KEYBOARD_H
#define H_KEYBOARD_H

#include "Engine/Advanced2D.h"
#include "button.h"

class Keyboard {
private:
	int status;
	Button* letter[26];
public :
	enum K_STATUS {AVAILABLE=50,UNAVAILABLE};
	Keyboard();
	~Keyboard();
	int getStatus() const {return status;}
	void setStatus(int pstatus) {status = pstatus;}
	string chose();
	void update();
	void reset();
	void setPosition(double x,double y);
	void draw();
	void addEntity();
	void resetPosition();
};


#endif