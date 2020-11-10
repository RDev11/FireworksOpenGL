#include "App.h"

#include <string>
#include <iostream>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>
#ifndef M_PI //is _USE_MATH_DEFINES compiler specific?
	constexpr double M_PI = 3.14159265358979323846;
#endif




void App::display() {

	int miliseconds_since_start = glutGet(GLUT_ELAPSED_TIME);
	double time_since_last_frame = miliseconds_since_start * 0.001f - time_now;
	time_now = miliseconds_since_start * 0.001f;

	fps_t += time_since_last_frame;
	fps_i++;
	if (fps_t > 0.5f)	{
		fps = int(fps_i/0.5f);
		fps_i = 0;
		fps_t -= 0.5f;
	}

	for (auto && o : objects)	{
		o->update(time_since_last_frame);
	}

	objects.remove_if([](const std::shared_ptr<GameObject>& o) { return o->isDestroed(); });


	//========================================================
	/* ������ ��� ������ */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//������� �����


	glEnable(GL_POINT_SMOOTH);
	for (auto&& o : objects) {
		o->draw();
	}

	glColor3f(1.0f, 0.0f, 0.0f);//������ ���� ���������
	glLineWidth(3);//������ ������� �����
	glBegin(GL_LINES);//������� ��� ����� �������� �����
	glVertex2d(10, 10);//���������� ������ ������� � ������� (x,y)
	glVertex2d(30, 30);//���������� ����� �������
	glEnd();//������� ��� ��������� �������� �����

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPointSize(6);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);//������ ������ �����
	glVertex2f(100, 100);
	glEnd();

	glLineWidth(3);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);//������ ������� �����
	glVertex2d(-50, 150);
	glVertex2d(50, 50);
	glEnd();


	glLineWidth(3);
	glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
	glBegin(GL_LINES);//������ ������� �����
	glVertex2d(-50, 145);
	glVertex2d(50, 45);
	glEnd();

	glLineWidth(3);
	glColor4f(1.0f, 0.0f, 0.0f, 0.2f);
	glBegin(GL_LINES);//������ ������� �����
	glVertex2d(-50,140);
	glVertex2d(50, 40);
	glEnd();

	glColor3ub(0, 255, 0);
	printText(0, win.height, "Fps: " + std::to_string(fps) + "\n#Particles: " + std::to_string(objects.size()));


	glutSwapBuffers();//������������� ����� �� �����
	/*
	vec3 light(150*sin(last_frame_time*0.002),50,150*cos(last_frame_time*0.002));
	glsl_.setUniformVector4("lightPos",light);

	vec3 eye(Cam.x,Cam.y,Cam.z);
	glsl_.setUniformVector4("eyePos",eye);

	double time[4];time[0]=glutGet(GLUT_ELAPSED_TIME);
	glsl_.setUniformVector4("time",time);

	*/
	//
	//
	//	int tss = glutGet(GLUT_ELAPSED_TIME);
	//	time_since_last_frame = double(tss - last_frame_time) / 1000;
	//	last_frame_time = tss;
	//	//count fps
	//	s_time += time_since_last_frame;
	//	s_time_i++;
	//	if (s_time > 1.0)
	//	{
	//		fps = s_time_i;
	//		s_time -= 1.0;
	//		s_time_i = 0;
	//	}							//
	//	if (!keys['r'] || keys['y'])///////////////////////////////////////////////////D I S P L A Y
	//	{
	//		if (keys['w'])Cam.onW(move_speed * time_since_last_frame);
	//		if (keys['a'])Cam.strafe(-move_speed * time_since_last_frame);
	//		if (keys['s'])Cam.onW(-move_speed * time_since_last_frame);
	//		if (keys['d'])Cam.strafe(move_speed * time_since_last_frame);
	//		if (keys['q'])Cam.onA(50 * time_since_last_frame);
	//		if (keys['e'])Cam.onA(-50 * time_since_last_frame);
	//	}
	//	glDisable(GL_TEXTURE_2D);
	//
	//	// Clear Screen and Depth Buffer
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		     ///////////////D I S P L A Y
	//	glLoadIdentity();
	//	//glBitmap(32,32,1,1,0,0,img[0][0]);
	//	//glMap2f(;
	//	//glDrawPixels(32,32,4,GL_UNSIGNED_BYTE,img);
	//
	//	characterController.doyourstuff(keys, &Cam, time_since_last_frame);
	//	Cam.apply();
	//
	//
	//
	//
	//
	//
	//
	//	//if(keys['W'])
	//	//	charaterController.rigidBody_->applyCentralImpulse(btVector3(1,0,0).rotate(btVector3(0,1,0),(90+Cam.pitch)*3.1415/180)
	//
	//	characterController.update_transform_and_draw();
	//
	//
	//
	//
	//
	//	if (keys['m'])
	//		m_dynamicsWorld->stepSimulation(time_since_last_frame, 1, time_since_last_frame);
	//
	//	rootNode->draw();
	//
	//	//glRotatef(g_rotation,0,1,0);
	//	/*
	//	angle_m*=0.995;
	//	if(keys['N'])	mm.applySkelet();
	//	mm.bones[8].getWorldTransform(gun.pos,gun.ori);
	//	gun.pos+=mm.dpos;
	//	//,gun.or
	//	aa->addTime(timesinelastframe*2);
	//	aa->apply(mm,multval);
	//	//
	//	mm.bones[1].ori=mm.bones[1].ori*quat(angle_m,vec3(1,0,0));
	//	glDisable(GL_LIGHTING);
	//	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	//	map.Draw();
	//	glEnable(GL_TEXTURE_2D);
	//	*/
	//
	//	/*	glEnable(GL_POINT_SMOOTH);		glPointSize(5);
	//		glPolygonMode(GL_BACK,GL_LINE);		glFrontFace(GL_CCW);	*/
	//		//////////////////////////////////////////
	//
	//		///////////////////////////////////////////
	//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//	glLoadIdentity();
	//	glMatrixMode(GL_PROJECTION);
	//	glLoadIdentity();
	//	GLfloat aspect = (GLfloat)win.width / win.height;
	//	glOrtho(0, win.width, 0, win.height, 0, 1);
	//	glEnable(GL_TEXTURE_2D);
	//	//guiP->draw();
	////    t1=GL_ZERO;
	////	  t1=GL_ONE;
	////	  t1=GL_SRC_COLOR;
	////	  t1=GL_ONE_MINUS_SRC_COLOR;
	////	  t1=GL_SRC_ALPHA;
	////	  t1=GL_ONE_MINUS_SRC_ALPHA;
	////	  t1=GL_DST_ALPHA;
	////	  t1=GL_ONE_MINUS_DST_ALPHA;  
	////	glEnable(GL_BLEND);
	//	glBlendFunc(GL_ONE, GL_SRC_ALPHA);
	//	glBindTexture(GL_TEXTURE_2D, sceneManager.materialManager.font);
	//	sceneManager.materialManager.setptr(0, win.height);
	//	{
	//		char fps_char[50];
	//		_itoa(fps, fps_char, 10);
	//		int i;
	//		for (i = 0; fps_char[i] != '\0'; i++); fps_char[i++] = ' ';
	//		_itoa(int(cc_velocity.y() * 100), &fps_char[i], 10);
	//		for (i = 0; fps_char[i] != '\0'; i++); fps_char[i++] = ' ';
	//		_itoa(int(cc_velocity.length() * 100), &fps_char[i], 10);
	//		for (i = 0; fps_char[i] != '\0'; i++); fps_char[i++] = ' ';
	//		cc_velocity.setY(0);
	//		_itoa(int(cc_velocity.length() * 100), &fps_char[i], 10);
	//
	//		sceneManager.materialManager.Symbol(fps_char);
	//	}
	//	glDisable(GL_BLEND);
	//	glLoadIdentity();
	//	gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);
	//	glMatrixMode(GL_MODELVIEW);
	//	////////////////////////////////////////
	//	glutSwapBuffers();
}
void App::keyboard(unsigned char key, int mousePositionX, int mousePositionY) {

	switch (key)
	{
	case 27://escape
	//	closing();
		//shutdown();
		exit(0);
		//case '~':
		//case '`':
		//	APP.guiP->state= (APP.guiP->state+1)%3;
		//	if( APP.guiP->state==0)
		//	{
		//		glutWarpPointer(win.width/2,win.height/2);
		//		glutSetCursor(GLUT_CURSOR_NONE);
		//	}
		//	else
		//		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

		//	break;
		//case 'b':
		//	test_b_s=(test_b_s+1)%mm.BNUM; 
		//	break;
	//	case 'P':
	//		mm.Load("c:\\"); 
	//		break;
	default:
		break;
	}
	//keys[key] = 1;
}

void App::reshape(int w, int h)
{
	glLoadIdentity();
	win.width = w;
	win.height = h;

	glViewport(0, 0, win.width, win.height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//GLfloat aspect = (GLfloat)win.width / (win.height>0 ? win.height : 0);
	//gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);   
	//if (w > h)
	{

		glOrtho(0, w, h, 0, -1, 1);
	}
	glMatrixMode(GL_MODELVIEW);
}

void App::keyboardUp(unsigned char key, int mousePositionX, int mousePositionY) {
	//keys[key] = 0;
}


void App::mouseButton(int but, int state, int x, int y) {
	mouse_x = x;
	mouse_y = y;
	std::cout << "mouseEvent("<<but<<", "<< state << ", " << x << ", " << y << ")" << std::endl;
	if (but == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		for (double i = 0; i < 2*M_PI; i += 0.01)
		{
			double speed = random(0, 1);
			speed = 250*(1.05f - speed * speed );
			objects.emplace_back(std::make_shared<Particle>(x, y, speed*cos(i), speed*sin(i)*0.95, 3));
		}

	}
}

void App::mouseMoved(int x, int y) {

}

void App::mouseMovedPressed(int x, int y) {
	mouse_x = x;
	mouse_y = y;
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

