#ifndef H_BUTTON_H
#define H_BUTTON_H

#include "Engine/Advanced2D.h"
using namespace Advanced2D;
using namespace std;

class Button : public Sprite {
private:
	Timer checkpress;
	string label;
	int status;
	bool checkposition;
	Texture *image_normal;
	Texture *image_pressed;
	void (*callback)();
public :
	
	enum {BUTTON_NORMAL,BUTTON_PRESSED,BUTTON=100};
	Button(string );
	~Button();
	string getLabel() const {return label;}
	int getStatus() const {return status;}
	bool isPosition() const {return checkposition;}

	void setCallback(void(*function)()) {callback = function;}
	void setCheckPosition(bool pcheckposition) {checkposition = pcheckposition;}
	void setLabel(string pLabel) {label = pLabel;}
	void setStatus(int pstatus) {status = pstatus;}
	
	void reset();
	void pressed();
	void release();
};


#endif