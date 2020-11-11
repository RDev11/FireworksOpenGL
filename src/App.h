#pragma once

#include "utls.h"
#include "GL/freeglut.h"
#include "GameObject.h"
#include "Particle.h"
#include "Widgets.h"
////
#include <list>
#include "Fireworks.h"


class App {
private:
	std::list<std::shared_ptr<GameObject>> objects;
	Widget rootWidget;
	Fireworks fireworks;

	int mouse_x, mouse_y;
public:
	static App* instance() {
		static App app={};
		return &app;
	}
private:
	App();
	~App();
public:
	//[seconds] since start
	float time_now = 0;
	int fps;
	int fps_i;
	double fps_t;


	//bool keys[256];
	void firstframe()
	{
		//glutWarpPointer(win.width / 2, win.height / 2);
	}
	void display();
	void reshape(int w, int h);
	void keyboard(unsigned char key, int mousePositionX, int mousePositionY);
	void keyboardUp(unsigned char key, int mousePositionX, int mousePositionY);
	void mouseButton(int but, int state, int x, int y);
	void mouseMoved(int x, int y);
	void mouseMovedPressed(int x, int y);


	void printText(int x, int y, std::string_view text);
};