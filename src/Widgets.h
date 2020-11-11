#pragma once
#include "utls.h"

class Widget : public std::enable_shared_from_this<Widget> {
protected:
	GLint x0,x1,y0,y1;
	//"якорь" anchor_x0 - если == 0, то цепляемся к левой границе предка; если ==1 то к правой
	std::weak_ptr<Widget> parent;
	GLint   offset_x0, offset_y0, offset_x1, offset_y1;
	GLfloat anchor_x0, anchor_y0, anchor_x1, anchor_y1;
	std::vector<std::shared_ptr<Widget>>children;

public:
	GLuint texture;
	GLfloat colorRGBA[4];

	Widget(//std::shared_ptr<Widget> parent,
		GLint offset_x0_, GLint offset_y0_,
		GLint offset_x1_, GLint offset_y1_,
		GLfloat	anchor_x0_=.0f, GLfloat anchor_y0_=.0f,
		GLfloat anchor_x1_=.0f, GLfloat anchor_y1_=.0f
	 )  : parent()
		, offset_x0(offset_x0_)
		, offset_y0(offset_y0_)
		, offset_x1(offset_x1_)
		, offset_y1(offset_y1_)
		, anchor_x0(anchor_x0_)
		, anchor_y0(anchor_y0_)
		, anchor_x1(anchor_x1_)
		, anchor_y1(anchor_y1_)
		, texture(0) 
		, colorRGBA{1.0f,1.0f,1.0f,1.0f }
	{
		reshape();
	}
	virtual ~Widget() {
	}

	/** recalc x0, y0, x1,y1; shall be called after parent reshape/move **/
	void reshape() {
		//x0 = parent.x + parent.width * anchor_x0 + dx0
		GLint px0, px1, py0, py1;
		auto parent_o = parent.lock();
		if (parent_o) {
			px0 = parent_o->x0;
			py0 = parent_o->y0;
			px1 = parent_o->x1;
			py1 = parent_o->y1;
		}
		else {
			px0 = 0;
			py0 = 0;
			px1 = glutGet(GLUT_WINDOW_WIDTH);
			py1 = glutGet(GLUT_WINDOW_HEIGHT);
		}
		x0 = px0 + (GLint)((px1 - px0) * anchor_x0) + offset_x0;
		y0 = py0 + (GLint)((py1 - py0) * anchor_y0) + offset_y0;
		x1 = px0 + (GLint)((px1 - px0) * anchor_x1) + offset_x1;
		y1 = py0 + (GLint)((py1 - py0) * anchor_y1) + offset_y1;

		for (auto&& child : children)
			child->reshape();
	}
	virtual void draw() {
		//reshape();
		{
			glColor4fv(colorRGBA);
			glEnableClientState(GL_VERTEX_ARRAY);

			GLint vertexes[][2] = { {x0, y0}, {x0, y1}, {x1, y1}, {x1, y0} };
			glVertexPointer(2, GL_INT, sizeof(GLint[2]), vertexes);
			//glVertexPointer(3, GL_FLOAT, sizeof(GLfloat[3]), vertexes);

			if (texture)
			{
				GLfloat texCoords[][2] = { {0, 0}, {0, 1}, {1, 1}, {1, 0} };
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(2, GL_FLOAT, sizeof(GLfloat[2]), texCoords);
			
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture);
			}
			//glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, indexBuffers[layer]);
			GLuint triangleList[][3] = { {0,1,3},{1,2,3} };
			glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, triangleList);
			glDisable(GL_TEXTURE_2D);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}

		for (auto&& child : children)
			child->draw();
	}

	void addChild(std::shared_ptr<Widget> child) {
		children.push_back(child);
		child->parent = weak_from_this();
	}

	bool mouseButton(int but, int state, int x, int y) {
		bool handled = false;
		if (x >= x0 && x <= x1 && y0 <= y && y <= y1)//y0>y1??
		{
			for (auto&& child : children)
				if (child->mouseButton(but, state, x, y))
				{
					handled = true;
					return handled;
				}
			//
			handled = mouseButtonImpl(but, state, x, y);
		}
		return handled;
	}
protected:
	virtual bool mouseButtonImpl(int but, int state, int x, int y) {
		/* известно, что mouse_x, y попали в bbox widget'а */
		bool handled = false;
		return handled;
	}
}; 


struct Button : public Widget {
	std::function<void()>  onMouseDown;

	Button( std::function<void()> && onMouseDown_,
			GLint offset_x0_, GLint offset_y0_,
			GLint offset_x1_, GLint offset_y1_,
			GLfloat	anchor_x0_ = .0f, GLfloat anchor_y0_ = .0f,
			GLfloat anchor_x1_ = .0f, GLfloat anchor_y1_ = .0f)
		:Widget(
			 offset_x0_,  offset_y0_,
			 offset_x1_,  offset_y1_,
			 anchor_x0_,  anchor_y0_,
			 anchor_x1_,  anchor_y1_)
		, onMouseDown(onMouseDown_)
	{
		
	}
	/*Button() {
		texture = LoadTexture("media/qwerty.png");

	}*/
	/*void draw() override {

		//GLuint vertexBuffer, * indexBuffers;
		//GLuint** triangleList;
		

	}*/
	bool mouseButtonImpl(int but, int state, int x, int y) override {
		/* известно, что mouse_x, y попали в bbox widget'а */
		bool handled = false;
		if (but == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			onMouseDown();
			handled = true;
		}
		return handled;
	}
};
