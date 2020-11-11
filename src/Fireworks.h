#pragma once
#include "utls.h"
#include "Particle.h"
//#include "App.h"

/**
	eqw
**/
class Fireworks {
	//decltype(App::objects) *objects;
	std::list<std::shared_ptr<GameObject>> &objs;
public:
	int fwCount = 0;
	Fireworks(std::list<std::shared_ptr<GameObject>>& objects_)
		:objs (objects_) 
	{
		
		
	};

	double particles_init_speed = 250;
	GLfloat r=0.0f, g=0.5f, b=1;
	double particleContM = 1;
	int fwType = 0;

	void fwExplode(GLint x, GLint y) {
		fwCount++;
		for (double i = 0; i < 2 * M_PI; i += 0.02 / particleContM)
		{
			double speed = random(0, 1);
			speed = particles_init_speed * (1.05f - speed * speed);
			switch (fwType) {
			case 0:
			default:
				objs.emplace_back(
					std::make_shared<ParticleTrail>(
						x, y,
						speed * cos(i), speed * sin(i),
						3,
						r, g, b
						)
				);
				break;
			case 1:
				objs.emplace_back(
					std::make_shared<ParticleTrail>(
						x, y,
						speed * cos(i), speed * sin(i),
						3,
						r * (float)random(0.6, 1.5), g * (float)random(0.6, 1.5), b * (float)random(0.6, 1.5)
						)
				);
				break;
			case 2:
				objs.emplace_back(
					std::make_shared<Particle>(
						x, y,
						speed * cos(i), speed * sin(i),
						3,
						r, g, b
						)
				);
				break;
			}
		}
	}


	int strip_def = 3, strip = strip_def;
	double wait_def = 2.5, wait = 0.5;

	void update(double delta_time) {
		wait -= delta_time;
		if (wait < 0)
		{
			auto h = glutGet(GLUT_WINDOW_HEIGHT);
			auto w = glutGet(GLUT_WINDOW_WIDTH);

			fwExplode((GLint)random(0, w-200)+100, (GLint)random(0, h / 2) + h / 4 - h/16);

			strip--;
			if (strip <= 0) {
				strip = strip_def;
				wait = wait_def;

				do {
					r = (GLfloat)random();
					g = (GLfloat)random();
					b = (GLfloat)random();
				} while (r + g + b < 1.3f);
				fwType = (int)random(0, 3 - 0.001);
			}
			else
			{
				wait = 0.12;
			}
		}
	}
};