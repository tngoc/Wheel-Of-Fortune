#ifndef H_MENU_H
#define H_MENU_H

#include "Engine/Advanced2D.h"
#include "button.h"

using namespace std;
class Menu {
private:
	int ID;
	int status;
	string name;
	std::list<Button*> menu;
public:
	enum status {OFF,ON};
	Menu();
	Menu(string ...);
	~Menu();

	string getName() const {return name;}
	void setName(string pname) {name = pname;}
	int getStatus() const {return status;}
	void setStatus(int pstatus) {status =pstatus;}

	void addButton(string );
	void addButton(Button*);
	void setPosition(double,double);

	void update();
	void reset();
	void updateMouseButton();
	void updateMouseMove();
	void close();
	void addFunction(string,void(*function)());
};

#endif