#pragma once
#include "GameObject.h"
#include "utls.h"

class Particle : public GameObject {

public:
	Particle(double x_, double y_, double dx_ = 0, double dy_ = 0, 
				double lifetime_ = 5,
		GLfloat r_ = 1.0f, GLfloat g_ = 0.1f, GLfloat b_ = 0.1f
	  )	: GameObject()
		, x(x_)
		, y(y_)
		, dx(dx_)
		, dy(dy_)
		, lifetime(lifetime_)
		, color{ r_, g_, b_, 1.0f }
	{	}
	~Particle() {
		
	}
	double x, y;
	double dx, dy;//speed
	double lifetime;//seconds before particle is destroed
	GLfloat color[4];

	void update(double delta_time) override;
	void draw() override;
};


class ParticleTrail : public Particle {
	GLfloat decay_speed;
	std::vector<GLfloat> points;
public:

	ParticleTrail(double x_, double y_, double dx_ = 0, double dy_ = 0,
		double lifetime_ = 5,
		GLfloat r_ = 1.0f, GLfloat g_ = 0.1f, GLfloat b_ = 0.1f,
		GLfloat	decay_speed_ = 0.07f
	) : Particle(x_, y_, dx_, dy_, lifetime_, r_, g_, b_)
		, decay_speed(decay_speed_)
	{	}
	~ParticleTrail() {

	}

	void update(double delta_time) override;
	void draw() override;

};