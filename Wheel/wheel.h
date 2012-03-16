#ifndef H_WHEEL_H
#define H_WHEEL_H

#include "Engine/Advanced2D.h"
#include "utils.h"
using namespace std;
using namespace Advanced2D;

class Wheel : public Advanced2D::Sprite {
private:
	int TossUp;
	int direction;
	int status;

	double speed;
	double friction;
	double angle,angle_redundance;
	double s;
	double interval;
	double ox,oy,or;

	bool start_spin;
	bool wheel_holding;
	bool checkposition;
	string teng;

public:
	enum slices {
		G_5000=5,G_600_1,G_300_0,G_700,G_450,G_350,G_800_1,G_LOSE_TURN,G_300_1,G_400_1,
		G_600_2,G_BANKRUPT,G_900_1,G_300_2,G_500_2,G_900_2,G_300_3,G_400_2,
		G_550,G_800_2,G_500_3,G_300_4,G_500_4,G_600_3
	};
	enum DICRECTION  {LEFT,RIGHT,NONE};
	enum WHEEL_STATUS {STOP=0,SPINNING=1,WAIT};
	Wheel();
	Wheel(double,double);

	int getTossUp();
	int getDirection() const {return direction;}
	bool getStatus() const {return start_spin;}
	bool isCheckPosition() const {return checkposition;}
	bool isHolding() const {return wheel_holding;}
	double getAngle() const {return angle;}
	double getAngleRedundance() const {return angle_redundance;}
	double getS() const {return s;}
	double getOX() const {return ox;}
	double getOY() const {return oy;}
	double getR() const {return or;}
	double getInterval() const {return interval;}
	double getSpeed() const {return speed;}
	string getTeng() const {return teng;}

	void setTeng(string pteng) {teng = pteng;}
	void setCheckPosition(bool pos) {checkposition = pos;}
	void setHolding(bool hold) {wheel_holding = hold;}
	void setDirection(int dir) {direction = dir;}
	void setInterval(double i) {interval = i;}
	void setOR(double x, double y, double r);
	void setFriction(double fric) {friction = fric;}
	void setStatus(bool stat) {start_spin = stat;}
	void setSpeed(double sp) {speed = sp;}
	void setAngle(double angl) {angle = angl;}
	void setS(double epsilon) {s = epsilon;}

	void update();
	void updateDirection(double ,double ,Sprite*);
	void updateMouseButton();
	void updateMouseMove(double,double,double,double);
	void updateMousePosition(Sprite*);

	int spin();
	bool isSlices15();

};

#endif