#ifndef H_LETTER_H
#define H_LETTER_H

#include "Engine/Advanced2D.h"

enum L_STATUS {OFF,ON};

class Letters : public Sprite {
private:
	int value;
	int status;
public :
	Letters() : Sprite() {status = OFF;}
	Letters(int v) : Sprite(),value(v) {status = OFF;}
	inline int getValue() const {return value;}
	inline int getStatus() const {return status;}

	void setStatus(int sta) {status = sta;}
};

#endif