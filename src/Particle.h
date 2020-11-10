#pragma once
#include "GameObject.h"

class Particle : public GameObject {

public:
	Particle(double x, double y, double dx=0, double dy=0, double lifetime=5)
		: GameObject()
		, x(x)
		, y(y) 
		, dx(dx)
		, dy(dy)
		, lifetime(lifetime)
	{	}
	~Particle() {
		
	}
	double x, y;
	double dx, dy;//speed
	double lifetime;//seconds before particle is destroed

	void update(double delta_time) override;
	void draw() override;
};