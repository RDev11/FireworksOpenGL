#include "App.h"

#include <string>


App::App()
	: rootWidget(0, 0, 0, 0, .0f, .0f, 1.0f, 1.0f)
	, fireworks(this->objects)
{
	rootWidget.colorRGBA[3] = .0f;

	auto windowClose = std::make_shared<Widget>(
		-100, -50,
		100, 50,
		0.5f, 0.5f,//align=center
		0.5f, 0.5f
	);
	{
		windowClose->colorRGBA[0] = 0.5f;
		windowClose->colorRGBA[1] = 0.5f;
		windowClose->colorRGBA[2] = 0.5f;
		windowClose->colorRGBA[3] = 0.9f;
		//windowClose->texture = LoadTexture("media/box_green.png");
		auto txtWClose_msg = std::make_shared<WText>(
			"Quit the game?",
			0, -30,
			0, -30,
			0.5f, 0.5f,
			0.5f, 0.5f
			);
		auto btnWClose_confirm = std::make_shared<WButton>(
			"Quit",
			[]()
			{
				exit(0);
			},
			-90, 10,
			-10, 30,
			0.5f, 0.5f,
			0.5f, 0.5f
			);
		auto btnWClose_cancel = std::make_shared<WButton>(
			"Cancel",
			[wwp = std::weak_ptr<Widget>(windowClose)]()
			{
				if (auto w = wwp.lock(); w)
					w->visible = 0;
			},
			10, 10,
			90, 30,
			0.5f, 0.5f,
			0.5f, 0.5f
			);
		windowClose->addChild(txtWClose_msg);
		windowClose->addChild(btnWClose_confirm);
		windowClose->addChild(btnWClose_cancel);
		
		windowClose->visible = false;
		rootWidget.addChild(windowClose);
	}


	auto buttonClose = std::make_shared<WButton>(
		"",
		[wwp = std::weak_ptr<Widget>(windowClose)]() 
	    {
		if (auto w = wwp.lock(); w)
			w->visible = !w->visible;
		}, 
		16     , -16 - 48,
		16 + 48, -16,
		0.0f, 1.0f, 
		0.0f, 1.0f
	);
	buttonClose->texture = LoadTexture("media/exit.png");

	rootWidget.addChild(buttonClose);


	/// ///////////
	auto sliderSpeed = std::make_shared<WSlider>(
		"Velocity:",
		[&](double val)
	    {
			fireworks.particles_init_speed = val;
		}, 
		15.0, 1000.0, fireworks.particles_init_speed,

		-90, -16 - 16,
		-10, -16,
		1.0f, 1.0f, 
		1.0f, 1.0f
	); 
	sliderSpeed->colorRGBA[1] = 255;
	rootWidget.addChild(sliderSpeed);
	//
	auto sliderDelay = std::make_shared<WSlider>(
		"Delay:",
		[&](double val)
		{
			fireworks.wait_def = val;
		},
		0.0, 7.5, fireworks.wait_def,

			-90, -32 - 16,
			-10, -32,
			1.0f, 1.0f,
			1.0f, 1.0f
			);
	sliderDelay->colorRGBA[1] = 255;
	rootWidget.addChild(sliderDelay);
	//
	auto sliderFreq = std::make_shared<WSlider>(
		"Density:",
		[&](double val)
		{
			fireworks.particleContM = val;
		},
		0.0, 4.0, fireworks.particleContM,

			-90, -48 - 16,
			-10, -48,
			1.0f, 1.0f,
			1.0f, 1.0f
			);
	sliderFreq->colorRGBA[1] = 255;
	rootWidget.addChild(sliderFreq);
}
App::~App()
{ }
/**
**/
void App::display() {
	//сначала вся логика 
	int miliseconds_since_start = glutGet(GLUT_ELAPSED_TIME);
	double time_since_last_frame = miliseconds_since_start * 0.001 - time_now;
	time_now = float(miliseconds_since_start * 0.001);

	fps_t += time_since_last_frame;
	fps_i++;
	if (fps_t > 0.5f) {
		fps = int(fps_i / 0.5f);
		fps_i = 0;
		fps_t -= 0.5f;
	}

	//if (!pause)
	{
		fireworks.update(time_since_last_frame);

		for (auto&& o : objects) {
			o->update(time_since_last_frame);
		}

		objects.remove_if([](const std::shared_ptr<GameObject>& o) { return o->isDestroed(); });
	}

	//========================================================
	//теперь отрисовка

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//очищаем буфер


	glEnable(GL_POINT_SMOOTH);
	for (auto&& o : objects) {
		o->draw();
	}

	rootWidget.draw();

	
	//glColor3f(1.0f, 0.0f, 0.0f);//задаем цвет рисования
	//glLineWidth(3);//задаем толщину линии
	//glBegin(GL_LINES);//говорим что будем рисовать линию
	//glVertex2d(10, 10);//координата начала отрезка в формате (x,y)
	//glVertex2d(30, 30);//координата конца отрезка
	//glEnd();//говорим что закончили рисовать линию

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glPointSize(6);
	//glColor3f(1.0f, 1.0f, 1.0f);
	//glBegin(GL_POINTS);//рисуем черную точку
	//glVertex2f(100, 100);
	//glEnd();

	//glLineWidth(3);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glBegin(GL_LINES);//рисуем красную линию
	//glVertex2d(-50, 150);
	//glVertex2d(50, 50);
	//glEnd();


	//glLineWidth(3);
	//glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
	//glBegin(GL_LINES);//рисуем красную линию
	//glVertex2d(-50, 145);
	//glVertex2d(50, 45);
	//glEnd();

	//glLineWidth(3);
	//glColor4f(1.0f, 0.0f, 0.0f, 0.2f);
	//glBegin(GL_LINES);//рисуем красную линию
	//glVertex2d(-50,140);
	//glVertex2d(50, 40);
	//glEnd();

	glColor3ub(0, 192, 0);
	printText(0, glutGet(GLUT_WINDOW_HEIGHT), "Fps: " + std::to_string(fps) 
		+ "\n#Particles: " + std::to_string(objects.size())
		+ "\n#Fireworks: " + std::to_string(fireworks.fwCount));
	

	glutSwapBuffers();//прорисовываем буфер на экран
}
void App::keyboard(unsigned char key, int mousePositionX, int mousePositionY) {
	//
	//switch (key)
	//{
	////case 27://escape
	////	exit(0);
	//
	////	case 'P':
	////		mm.Load("c:\\"); 
	////		break;
	//default:
	//	break;
	//}
	////keys[key] = 1;
}

void App::reshape(int w, int h)
{
	glLoadIdentity();
	
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//GLfloat aspect = (GLfloat)win.width / (win.height>0 ? win.height : 0);
	//gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);   
	//if (w > h)
	{

		glOrtho(0, w, h, 0, -1, 1);
	}
	glMatrixMode(GL_MODELVIEW);

	rootWidget.reshape();
}

void App::keyboardUp(unsigned char key, int mousePositionX, int mousePositionY) {
	//keys[key] = 0;
}


void App::mouseButton(int but, int state, int x, int y) {
	mouse_x = x;
	mouse_y = y;
	//std::cout << "mouseEvent("<<but<<", "<< state << ", " << x << ", " << y << ")" << std::endl;
	bool handled = rootWidget.mouseButton(but, state, x, y);
	if (!handled && but == GLUT_LEFT_BUTTON && state == GLUT_DOWN)	{
		fireworks.fwExplode(x, y);
	}
}

void App::mouseMoved(int x, int y) {
	//cout << ".";
	bool handled = rootWidget.mouseButton(-1, -2, x, y);
}

void App::mouseMovedPressed(int x, int y) {
	mouse_x = x;
	mouse_y = y;
	bool handled = rootWidget.mouseButton(-1, -1, x, y);
}

void App::printText(int x, int y, std::string_view text)
{
	int font_size = 18;
	/*
	 * Prepare the OpenGL state
	 */
	//glDisable(GL_LIGHTING);
	//glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	/*
	 * Have an orthogonal projection matrix set
	 */
	glOrtho(0, glutGet(GLUT_WINDOW_WIDTH),
		0, glutGet(GLUT_WINDOW_HEIGHT),
		-1, +1
	);

	/*
	 * Now the matrix mode
	 */
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	/*
	 * Now the main text
	 */
	//glColor3ub(0, 0, 0);
	int lines = 1;
	glRasterPos2i(x, y - (lines * font_size));

	for (auto p = text.begin(); p!=text.end(); ++p)
	{
		if (*p == '\n')
		{
			lines++;
			glRasterPos2i(x, y - (lines * font_size));
		}
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
	}

	/*
	 * Revert to the old matrix modes
	 */

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	/*
	 * Restore the old OpenGL states
	 */
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
}

