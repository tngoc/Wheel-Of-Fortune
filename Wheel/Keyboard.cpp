#include "Keyboard.h"


Keyboard::Keyboard() {
	string ss;
	char i;
	char temp;
	for(i=0;i<26;i++) {
		temp = i+65;
		ss = temp;
		letter[i] = new Button(ss);
		letter[i]->reset();
	}
}

Keyboard::~Keyboard() {
	int i;
	for(i=0;i<26;i++) {
		if(letter[i])
			delete letter[i];
	}
}

void Keyboard::setPosition(double x,double y) {
	int i;
	double fx,fy;
	for(i=0;i<26;i++) {
		fx = i%13;
		fy = (int)i/13;
		letter[i]->setPosition(x+ letter[i]->getWidth()*fx,y + letter[i]->getHeight()*fy);
	}
}

void Keyboard::draw() {
	int i;
	for(i=0;i<26;i++)
		letter[i]->draw();
}

void Keyboard::reset() {
	int i;
	for(i=0;i<26;i++) {
		letter[i]->reset();
	}
}

void Keyboard::resetPosition() {
	int i;
	for(i=0;i<26;i++) {
		letter[i]->setCheckPosition(false);
	}
}

string Keyboard::chose() {
	int i;
	string temp;
	if(status == AVAILABLE) {
		for(i=0;i<26;i++) {
			if(letter[i]->isPosition()==true) {
				letter[i]->pressed();
				status = UNAVAILABLE;
				return letter[i]->getLabel();
			}
		}
	}
	return "MISS";
}

void Keyboard::addEntity() {
	int i;
	for(i=0;i<26;i++) {
		if(letter[i])
			g_engine->addEntity(letter[i]);
	}
}
