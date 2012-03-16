#include "button.h"


Button::Button(string plabel) : Sprite() {
	label = plabel;
	status = BUTTON_NORMAL;
	checkposition = false;
	setScale(1.0f);
	setCollisionMethod(COLLISION_RECT);
	setObjectType(BUTTON);

	ostringstream ss1,ss2;
	image_normal = new Texture();
	ss1 << "button/" << label << "" <<".png";
	image_normal->Load(ss1.str());
	
	image_pressed = new	Texture();
	ss2 << "button/"<< label << "'" <<".png";
	image_pressed->Load(ss2.str());
	callback = NULL;
	reset();
}

Button::~Button() {
	Sprite::~Sprite();
	if(image_normal!=NULL)
		image_normal->Release();
	if(image_pressed!=NULL)
		image_pressed->Release();
}

void Button::reset() {
	setImage(image_normal);
	status = BUTTON_NORMAL;
}

void Button::pressed() {
	if(status==BUTTON_NORMAL) {
		setImage(image_pressed);
		status = BUTTON_PRESSED;
		if(callback!=NULL)
			callback();
		checkpress.sleep(10);
	}
}

void Button::release() {
	Sprite::~Sprite();
	if(image_normal!=NULL)
		image_normal->Release();
	if(image_pressed!=NULL)
		image_pressed->Release();
	setAlive(false);
}