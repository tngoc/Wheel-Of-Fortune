#include "wheel.h"
#include "math.h"

Wheel::Wheel() : Sprite() {
	speed = 0;
	friction = 0.0002;
	angle = 0;
	s=0;
	direction = NONE;
	teng = "";
	start_spin  = false;
	
}

Wheel::Wheel(double sp,double fric) : Sprite() {
	speed = sp;
	friction = fric;
	angle = 0;
	s = 0;
	direction = NONE;
	teng = "";
	start_spin = false;
	
}

int Wheel::spin() {
	if (start_spin  == false) goto fin;

	double speed_temp;
	speed_temp =speed;
	speed = speed - friction;
	if(speed > 0) 
		s = (speed_temp*speed_temp - speed*speed)/(2*friction);
	if(speed <= 0)
		start_spin = false;

	if(start_spin == true) {
		if(direction == LEFT) 
			angle -= s;
		else if(direction == RIGHT) {
			angle += s;
		}
	}
	fin:
	this->setRotation(this->getAngle());
	if (isSlices15() == true) {
		if(teng!= "")
			g_engine->audio->Play(teng);
	}

	if(speed > 0) {
		status = SPINNING;
		return SPINNING;
	}
	else {
		status = STOP;
		return STOP;
	}
}

bool Wheel::isSlices15() {
	double angle_in_degree = 7.5 + g_engine->math->toDegrees(this->getAngle());
	int times = (int)(angle_in_degree/15);
	return (fabs(angle_in_degree - times*15) < fabs(g_engine->math->toDegrees(s)));
}

int Wheel::getTossUp() {
	double angle_in_degree = g_engine->math->toDegrees(this->getAngle());
	angle_redundance = ((angle_in_degree +7.5) - ((int)((angle_in_degree +7.5)/360))*360);
	double slices = angle_redundance/15;
	int position = (int)(std::floor(slices));
	if (position < 0) position = 24 + position;
	return (Wheel::TossUp = position);
}

void Wheel::setOR(double x, double y, double r) {
	ox = x;
	oy = y;
	or = r;
}

void Wheel::update() {
	if(this->isHolding() ==false) {
		if (this->getSpeed() > 0) {
			if (this->getStatus() == false) 
				this->setStatus(true);
		}
	}
}

void Wheel::updateDirection(double delta_x,double delta_y,Sprite* cursor) {
	if(this->isHolding()==true) {
		double a = delta_x*(cursor->getY() - delta_y - this->getOY()) - delta_y*(cursor->getX() - delta_x - this->getOX());
		if (a > 0) this->setDirection(Wheel::LEFT);
		else if ( a < 0) this->setDirection(Wheel::RIGHT);
		else this->setDirection(Wheel::NONE);
	}
}

void Wheel::updateMouseButton() {
	if(this->isCheckPosition() == true && this->getStatus() == false) {
		this->setHolding(true);
	}
	else this->setHolding(false);
}

void Wheel::updateMouseMove(double delta_x,double delta_y,double fx,double fy) {
	
	float d = (float)sqrt(pow((fx - this->getOX()),2) + pow((fy - this->getOY()),2));
	if (d > this->getR()) {
		this->setHolding(false);
	}
	if (this->isHolding() == true) {
		double x = (delta_x * (delta_y + this->getOY() - fy) + delta_y * (delta_x + this->getOX() - fx)*(-1))/
			(sqrt(delta_x * delta_x + delta_y * delta_y)*sqrt(pow((delta_x + this->getOX() - fx),2) + pow((delta_y + this->getOY() - fy),2)));
		x = x*sqrt(delta_x * delta_x + delta_y * delta_y);
		x = x/sqrt(pow((fx - delta_x - this->getOX()),2) + pow((fy - delta_y - this->getOY()),2));
		this->setS(fabs(atan(x)));
		if (delta_x < 0)
			this->setAngle(this->getAngle() - fabs(atan(x)));
		else
			this->setAngle(this->getAngle() + fabs(atan(x)));
		this->setSpeed(this->getS()*10/Utils::timecount());
	}
}

void Wheel::updateMousePosition(Sprite* cursor) {
	float d = (float)sqrt(pow((cursor->getX() - this->getOX()),2) + pow((cursor->getY() - this->getOY()),2));
	if (d <= this->getR()) {
		this->setCheckPosition(true);
	}
	else this->setCheckPosition(false);
}