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
	glPointSize((GLfloat)lifetime*3);
	color[3] = (GLfloat)std::clamp(lifetime / 3, 0.0, 0.5) * 255;
	glColor4fv(color);

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

void ParticleTrail::update(double delta_time) {
	lifetime -= delta_time;
	if (lifetime <= 0) {
		destroy();
		return;
	}
	//хотим сопротивление воздуха - чем быстрее летит тем быстрее замедляется частица

	dx = dx - dx * delta_time * 1.91f;
	dy = dy - dy * delta_time * 1.91f + 25 * delta_time;
	//
	x = x + dx * delta_time;
	y = y + dy * delta_time;

	if (points.size() == 0 || abs(x - points[points.size() - 2]) >= 5 || abs(y - points.back()) >= 5) {
		points.push_back((GLfloat)x);
		points.push_back((GLfloat)y);
	}
};

void ParticleTrail::draw() {
	color[3] = (GLfloat)std::clamp(lifetime / 1, 0.0, 0.5);
	glColor4fv(color);

	//point
	glPointSize((GLfloat)lifetime * 3);

	glBegin(GL_POINTS);
	glVertex2d(x, y);
	glEnd();


	//Trail


	/*glEnableClientState(GL_VERTEX_ARRAY);

	//GLint vertexes[][2] = { {x0, y0}, {x0, y1}, {x1, y1}, {x1, y0} };
	glVertexPointer(2, GL_FLOAT, sizeof(GLfloat[2]), points.data());

	GLuint lineList[][2] = { {0,1},{1,2} };
	glDrawElements(GL_LINE_STRIP, 2 * 3, GL_UNSIGNED_INT, lineList);
	glDisableClientState(GL_VERTEX_ARRAY);*/



	if (!points.empty())
	{
		glLineWidth(3);
		glBegin(GL_LINE_STRIP);

		glVertex2f((GLfloat)x, (GLfloat)y);
		for (int i = points.size() - 2; i >= 0; i -= 2)
		{
			color[3] = color[3] - decay_speed;
			glColor4fv(color);
			if (color[3] <= 0) break;
			glVertex2f(points[i], points[i + 1]);
			//glVertex2f(points[i], points[i + 1]);
		}
		//glVertex2f(points[0], points[1]);

		glEnd();
	}

};