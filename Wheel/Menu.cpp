#include "Menu.h"


Menu::Menu() {
	ID = 1000;
	status = Menu::ON;
}

Menu::Menu(string pname ...) {
	ID = 1000;
	status = Menu::ON;
	menu.clear();
	va_list ap;
	va_start (ap,pname);
	for(;;) {
		char *p = va_arg(ap,char*);
		if((p==0)||(p==NULL))
			break;
		addButton(p);
	}
	va_end(ap);
	return;
}

void Menu::addButton(string plabel) {
	Button* button = new Button(plabel);
	menu.push_front(button);
	g_engine->addEntity(button);
	button->setID(ID);
	ID++;
}

void Menu::addButton(Button* pbutton) {
	menu.push_front(pbutton);
	g_engine->addEntity(pbutton);
	pbutton->setID(ID);
	ID++;
}

void Menu::setPosition(double fx,double fy) {
	std::list<Button*>::iterator iter;
	Button* button;
	iter = menu.begin();
	while (iter != menu.end())
	{
		button = *iter;
		button->setPosition(fx,fy + (button->getID()-1000)*(button->getHeight()+30));
		++iter;
	}
}

Menu::~Menu() {
	std::list<Button*>::iterator iter;
	iter = menu.begin();
	while (iter != menu.end())
	{
		delete(*iter);
		iter = menu.erase(iter);
	}
	menu.clear();
}
void Menu::updateMouseButton() {
	std::list<Button*>::iterator iter;
	Button* button;
	iter = menu.begin();
	while (iter != menu.end())
	{
		button = *iter;
		if(button->isPosition()==true) {
			button->pressed();
			break;
		}
		++iter;
	}

}

void Menu::updateMouseMove() {
	std::list<Button*>::iterator iter;
	Button* button;
	iter = menu.begin();
	while (iter != menu.end())
	{
		button = *iter;
		button->setCheckPosition(false);
		++iter;
	}
}

void Menu::update() {
	std::list<Button*>::iterator iter;
	Button* button;
	iter = menu.begin();
	while (iter != menu.end())
	{
		button = *iter;
		button->reset();
		++iter;
	}
}

void Menu::close() {
	std::list<Button*>::iterator iter;
	Button* button;
	iter = menu.begin();
	while (iter != menu.end())
	{
		button = *iter;
		button->release();
		iter = menu.erase(iter);
	}
	menu.clear();
	ID = 1000;
	status = OFF;
}

void Menu::addFunction(string label,void(*pfunction)()) {
	std::list<Button*>::iterator iter;
	Button* button;
	iter = menu.begin();
	while (iter != menu.end())
	{
		button = *iter;
		if(button->getLabel() == label) {
			button->setCallback(pfunction);
			break;
		}
		++iter;
	}
	status = OFF;
}