#pragma once

#include "Menu.h"
#include "Engine/Advanced2D.h"

ostringstream heee;

namespace Scene {
	Menu* menu = new Menu();
	Sprite* background = new Sprite();
	Texture* background_image = new Texture();
	bool scene1_start=false;
	bool scene2_start=false;
	bool scene3_start=false;
	bool scene4_start=false;
	bool scene1_on = false;
	bool scene2_on = false;
	bool scene3_on = false;
	bool scene4_on = false;

	void scene1();
	void scene2();
	void scene3();
	void scene4();

	void update();
	void release();
}

void scene1_to_scene4() {
	Scene::scene1_start = false;
	Scene::scene1_on = false;
	Scene::scene4_start = true;
}

void scene4_to_scene1() {
	Scene::scene4_start = false;
	Scene::scene4_on = false;
	Scene::scene1_start = true;
}

void exit() {
	g_engine->Close();
}

void Scene::scene1() {
	if(scene1_on == true)
		return;
	if((scene1_start == true) && (scene1_on == false)) {
		menu->close();
		background_image->Release();
		delete menu;
		background_image->Load("scene1.png");
		menu = new Menu("Scene1","play_button","exit_button",NULL);
		menu->addFunction("play_button",scene1_to_scene4);
		//menu->addFunction("exit_button",exit);
		menu->setPosition(100,100);
		scene1_on = true;
	}
}

void Scene::scene2() {

	scene1_start = false;
	menu->close();
	menu = new Menu("Scene2","about_button","exit_button",NULL);
	menu->setPosition(100,100);
}

void Scene::scene3() {

	scene2_start = false;
	menu->close();
	menu = new Menu("Scene3","about_button","Highscore_button",NULL);
	menu->setPosition(100,100);
}

void Scene::scene4() {
	if(scene4_on == true)
		return;
	if((scene4_start == true) && (scene4_on == false)) {
		menu->close();
		background_image->Release();
		delete menu;
		background_image->Load("scene4.jpg");
		menu = new Menu("Scene4","play_button","Highscore_button","about_button","exit_button",NULL);
		menu->addFunction("exit_button",exit);
		menu->addFunction("play_button",scene4_to_scene1);
		menu->setPosition(200,100);
		scene4_on = true;
	}
}

void Scene::update() {
	Scene::background->setImage(Scene::background_image);
	scene1();
	scene4();
	Scene::menu->update();
}

void Scene::release() {
	delete menu;
	delete background;
	delete background_image;
}