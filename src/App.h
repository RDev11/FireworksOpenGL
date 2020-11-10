#pragma once

#include "utls.h"
#include <iostream>
#include "GL/freeglut.h"
#include "GameObject.h"
#include "Particle.h"
////
#include <list>

class Widget {
public:
	GLuint texture;
	Widget() {}
	virtual ~Widget(){}
	virtual void draw() {}
};
struct Button : public Widget{
	Button() {
		texture = LoadTexture("qwerty.png");
		assert(texture);
	}
};

class App {
	std::list<std::shared_ptr<GameObject>> objects;
	std::list<std::shared_ptr<Widget>> widgets;

	struct  glutWindow {
		int width;
		int height;
		int hwnd;
		char* title;

		float field_of_view_angle;
		float z_near;
		float z_far;
	};
	glutWindow win;

	int mouse_x, mouse_y;
public:
	static App* instance() {
		static App app={};
		return &app;
	}
private:
	App() {
		std::cout << "App();";
		widgets.emplace_back(std::make_shared<Button>());
	}
	~App() {
		std::cout << "~App();";
	}
public:
	//[seconds] since start
	float time_now = 0;
	int fps;
	int fps_i;
	float fps_t;


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