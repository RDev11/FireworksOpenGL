#include "Particle.h"
#include "GL/freeglut.h" 
#include <algorithm>
void Particle::update(double delta_time) {
	lifetime -= delta_time;
	if (lifetime <= 0)	{
		destroy();
		return;
	}
	//хотим сопротивление воздуха - чем быстрее летит тем быстрее замедляется частица

	dx = dx - dx * delta_time * 1.91f;
	dy = dy - dy * delta_time * 1.91f + 25 * delta_time;
	//
	x = x + dx * delta_time;
	y = y + dy * delta_time;
};

void Particle::draw() {
	glPointSize(lifetime*3);
	glColor4ub(255, 25, 25, std::clamp(lifetime / 3, 0.0, 0.5)*255);

	glBegin(GL_POINTS);
	glVertex2d(x, y);
	glEnd();
	/*
	glPointSize(lifetime);
	glColor4f(1.0f, 0.7f, 0.6f, (float)std::clamp(lifetime / 3, 0.0, 0.8));
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	glEnd();*/
};