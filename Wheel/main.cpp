/*
  Name: Spinning Wheel Test
  Date: 02/2012
  Description:Spinning Wheel Test
*/

#include "Engine/Advanced2D.h"
#include "Keyboard.h"
#include "wheel.h"
#include "Quiz.h"
#include <math.h>

using namespace Advanced2D;
using namespace std;

Texture* cursor_image;

Wheel* wheel;
Keyboard* keyboard;
Quiz* quiz;

Sprite* cursor;
Sprite* arrow;

Font* system12;
float delta_x,delta_y;

string chose;

enum {CURSOR,WHEEL_POS};
bool game_preload() 
{
	g_engine->setAppTitle("TEST WHEEL");
	g_engine->setScreenWidth(1000);
	g_engine->setScreenHeight(513);
	g_engine->setColorDepth(32);
	g_engine->setFullscreen(false);
	ShowCursor(FALSE);
	return true;
}

bool game_init(HWND) 
{
	Sprite* background = new Sprite();
	background->loadImage("background.png");
	background->setCollidable(false);
	g_engine->addEntity(background);
	g_engine->setMaximizeProcessor(true);
	
	cursor_image = new Texture();
	if(!cursor_image->Load("Cursor_564.png"))
		return false;

	cursor = new Sprite();
	cursor->setImage(cursor_image);
	cursor->setScale(0.5);
	cursor->setCollisionMethod(COLLISION_DIST);
	cursor->setObjectType(CURSOR);
	g_engine->addEntity(cursor);
	
	wheel = new Wheel();
	wheel->loadImage("wheel.png");
	wheel->setPosition(0,300);
	wheel->setOR(wheel->getX() + wheel->getWidth()/2,wheel->getY() + wheel->getHeight()/2,(wheel->getHeight()/2));
	wheel->setObjectType(WHEEL_POS);
	g_engine->addEntity(wheel);
	wheel->setStatus(false);

	arrow = new Sprite();
	arrow->loadImage("arrow.png");
	arrow->setRotation(g_engine->math->toRadians(90));
	arrow->setPosition(220,230);
	arrow->setCollidable(false);

	system12 = new Font();
	if (!system12->loadImage("system12.tga")) {
		g_engine->message("Error loading system12.tga");
		return false;
	}
	system12->setColumns(16);
	system12->setCharSize(14,16);

	if (!system12->loadWidthData("system12.dat")) {
		g_engine->message("Error loading system12.dat");
		return false;
	}

	quiz = new Quiz();
	quiz->loadImage("quiz_background.png",D3DCOLOR_XRGB(255,255,255));
	quiz->setPosition(0,0);
	quiz->setAnswer("a b c fdasaskdjasd asdasdasd asdjasdas");

	quiz->arrangeLetter();
	quiz->setQuizPos(27,39,quiz->getX(),quiz->getY(),quiz->getX() + quiz->getWidth(),quiz->getY() + quiz->getHeight());
	quiz->addQuizEntity();
	//quiz->reset();
	quiz->setAnswer("Cho meo lon ga chim co buom ca");
	quiz->update();
	//ostringstream ss;
	//ss << quiz->getAnswer();

	keyboard = new Keyboard();
	keyboard->setPosition(640.0f,513-80);
	keyboard->addEntity();


	return true;
}



void game_update() 
{
	
	
}

void game_render2d()
{	
	wheel->setHolding(false);	
	ostringstream result;
	if(wheel->spin() == Wheel::STOP) {
		keyboard->setStatus(Keyboard::AVAILABLE);
		result << wheel->getTossUp();
	}
	system12->Print(10,250, result.str(),D3DCOLOR_XRGB(40,255,255));
	system12->Print(0,0,chose,D3DCOLOR_XRGB(255,255,100));
	quiz->draw();
	arrow->draw();
	cursor->draw();
	quiz->drawQuiz();
	
}

void game_end() 
{
	delete cursor_image;
	delete cursor;
	delete keyboard;
	delete wheel;
	delete arrow;
}

void game_keyPress(int key) 
{ 
}

void game_keyRelease(int key) 
{ 
	switch (key) {
		case DIK_ESCAPE:
			g_engine->Close();
			break;
		case DIK_SPACE:
			keyboard->reset();
			break;
	}
}

void game_render3d()
{
    g_engine->ClearScene(D3DCOLOR_XRGB(0,0,80));
	g_engine->SetIdentity();
	wheel->update();
	keyboard->setStatus(Keyboard::UNAVAILABLE);
}

void game_mouseButton(int button) {
	switch(button) {
	case 0 :	
				wheel->updateMouseButton();
				chose = keyboard->chose();
				break;
	}
}

void game_mouseMotion(int x,int y) {
	delta_x = (float)x;
	delta_y = (float)y;
	wheel->updateDirection(delta_x,delta_y,cursor);
}

void game_mouseMove(int x,int y) {
	keyboard->resetPosition();
	double fx= (float)x;
	double fy = (float)y;
	wheel->updateMouseMove(delta_x,delta_y,fx,fy);
	cursor->setPosition(fx,fy);
}

void game_mouseWheel(int wheel) {}
void game_entityRender(Advanced2D::Entity* entity) { }
void game_entityUpdate(Advanced2D::Entity* entity) { }
void game_entityCollision(Advanced2D::Entity* entity1,Advanced2D::Entity* entity2) {
	if(entity1->getObjectType() == CURSOR) {
		if(entity2->getObjectType() == Button::BUTTON) {
			Button* temp = (Button*)entity2;
			temp->setCheckPosition(true);
		}
		if(entity2->getObjectType() == WHEEL_POS) {
			wheel->updateMousePosition(cursor);
		}
	}
}		
