#pragma once

class GameObject {
	bool destroed = false;
public:
	virtual void update(double delta_time) {};
	virtual void draw() {};
	virtual ~GameObject() { };
	virtual void destroy() { destroed = true; };
	bool isDestroed() {	return destroed; };
};