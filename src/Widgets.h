#pragma once
#include "utls.h"
#include <iterator> 

class Widget : public std::enable_shared_from_this<Widget> {
protected:
	GLint x0,x1,y0,y1;
	//"�����" anchor_x0 - ���� == 0, �� ��������� � ����� ������� ������; ���� ==1 �� � ������
	std::weak_ptr<Widget> parent;
	GLint   offset_x0, offset_y0, offset_x1, offset_y1;
	GLfloat anchor_x0, anchor_y0, anchor_x1, anchor_y1;
	std::vector<std::shared_ptr<Widget>>children;

public:
	GLuint texture;
	GLfloat colorRGBA[4];
	bool visible = true;

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

protected:
	/** 
	������ ��������� ��� ������ ������������� x0,y0,x1,y1 
	**/
	void drawQuad() {
		
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
	/**
	* ������� �����, ������������ ������������ anchor_x0. 
	* \param x_ : ���������� ����������
	* \param y_ : ���������� ����������
	* \param font_align_x : ���������� x_ ����� ��������������� 0-������ ����, 1-�������, 0.5 - ������ ������.
	**/
	void drawText(std::string_view text, int x_, int y_, float font_align_x = 0.0f) {
		auto font = GLUT_BITMAP_9_BY_15;
		int font_h = 15;
		int font_w = 9;

		int lines = 1;
		int lineWidth = (int)std::distance(text.begin(), std::find(text.begin(), text.end(), '\n'));
		glRasterPos2i(x_ - (GLint)(lineWidth * font_w * font_align_x), y_ + (lines * font_h));

		for (auto p = text.begin(); p != text.end(); ++p)
		{
			if (*p == '\n')
			{
				lineWidth = (int)std::distance(p+1, std::find(p+1, text.end(), '\n'));
				lines++;
				glRasterPos2i(x_ - (GLint)(lineWidth * font_w * font_align_x), y_ + (lines * font_h));
			}else
				glutBitmapCharacter(font, *p);
		}
	}
public:
	virtual void draw() {
		if (!visible) return;

		glColor4fv(colorRGBA);
		drawQuad();

		for (auto&& child : children)
			child->draw();
	}

	void addChild(std::shared_ptr<Widget> child) {
		children.push_back(child);
		child->parent = weak_from_this();
	}

	bool mouseButton(int but, int state, int x, int y) {
		bool handled = false;
		if (!visible) return handled;
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
		/* ��������, ��� mouse_x, y ������ � bbox widget'� */
		bool handled = false;
		return handled;
	}
}; 

class WButton: public Widget{
	std::function<void()>  onMouseDown;
public:
	std::string text;
	WButton(std::string text_,
			std::function<void()> && onMouseDown_,
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
		text = std::move(text_);
	}

	void draw() override {
		if (!visible) return;
		glColor4fv(colorRGBA);
		drawQuad();
		if (!text.empty()) {
			glColor3ub(0, 0, 0);
			drawText(text, (x0 + x1) / 2, (y0 + y1) / 2 - 11, 0.5f);
		}
		for (auto&& child : children)
			child->draw();
	}
	bool mouseButtonImpl(int but, int state, int x, int y) override {
		/* ��������, ��� mouse_x, y ������ � bbox widget'� */
		bool handled = false;
		if (but == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			onMouseDown();
			handled = true;
		}
		return handled;
	}
};

class WText : public Widget {
public:
	std::string text;
public:
	WText(std::string text_,
		GLint offset_x0_, GLint offset_y0_,
		GLint offset_x1_, GLint offset_y1_,
		GLfloat	anchor_x0_ = .0f, GLfloat anchor_y0_ = .0f,
		GLfloat anchor_x1_ = .0f, GLfloat anchor_y1_ = .0f)
		:Widget(
			offset_x0_, offset_y0_,
			offset_x1_, offset_y1_,
			anchor_x0_, anchor_y0_,
			anchor_x1_, anchor_y1_)
	{
		text = std::move(text_);
	}

	void draw() override {
		if (!visible) return;

		glColor4fv(colorRGBA);
		drawText(text, x0, y1, anchor_x0);

		for (auto&& child : children)
			child->draw();
	}
};
class WSlider : public Widget {
	std::function<void(double)>  onChange;
public:
	std::string text; 
	double value_min; 
	double value_max; 
	double value;
	WSlider(std::string text_,
		std::function<void(double)>&& onChange_,
		double value_min_, double value_max_, double value_init_,
		GLint offset_x0_, GLint offset_y0_,
		GLint offset_x1_, GLint offset_y1_,
		GLfloat	anchor_x0_ , GLfloat anchor_y0_,
		GLfloat anchor_x1_ , GLfloat anchor_y1_)
		:Widget(
			offset_x0_, offset_y0_,
			offset_x1_, offset_y1_,
			anchor_x0_, anchor_y0_,
			anchor_x1_, anchor_y1_)
		, onChange(onChange_)
		, value_min(value_min_)
		, value_max(value_max_)
		, value(value_init_)
	{
		text = std::move(text_);
	}

	void draw() override {
		if (!visible) return;
		glColor4fv(colorRGBA);		
	//----
		{//line...
			glColor4f(colorRGBA[0] * 0.5f, colorRGBA[1] * 0.5f, colorRGBA[2] * 0.5f, colorRGBA[3]);
			glEnableClientState(GL_VERTEX_ARRAY);
			GLint vertexes[][2] = { {x0, (y0 + y1) / 2 - 2}
								  , {x0, (y0 + y1) / 2 + 2}
								  , {x1, (y0 + y1) / 2 + 2}
							      , {x1, (y0 + y1) / 2 - 2} };
			glVertexPointer(2, GL_INT, sizeof(GLint[2]), vertexes);
			GLuint triangleList[][3] = { {0,1,3},{1,2,3} };
			glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, triangleList);
			glDisableClientState(GL_VERTEX_ARRAY);
		}
		{//slider
			glColor4fv(colorRGBA);
			glEnableClientState(GL_VERTEX_ARRAY);
			GLint x_ = GLint(x0 + (x1 - x0) * (value - value_min) / (value_max - value_min));
			GLint vertexes[][2] = { {x_ - 4, y0}
								  , {x_ - 4, y1}
								  , {x_ + 4, y1}
								  , {x_ + 4, y0} };
			glVertexPointer(2, GL_INT, sizeof(GLint[2]), vertexes);

			if (texture) {
				GLfloat texCoords[][2] = { {0, 0}, {0, 1}, {1, 1}, {1, 0} };
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(2, GL_FLOAT, sizeof(GLfloat[2]), texCoords);

				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture);
			}
			GLuint triangleList[][3] = { {0,1,3},{1,2,3} };
			glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, triangleList);
			glDisable(GL_TEXTURE_2D);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
	//------
		if (!text.empty()) {
			glColor3ub(255, 255, 255);
			drawText(text, x0, (y0 + y1) / 2 - 11, 1.0f);
		}
		for (auto&& child : children)
			child->draw();
	}
	bool mouseButtonImpl(int but, int state, int x, int y) override {
		/* ��������, ��� mouse_x, y ������ � bbox widget'� */
		bool handled = false;
		if ((but == GLUT_LEFT_BUTTON && state == GLUT_DOWN) ||
			(but == -1 && state == -1)
			) {
			//begin_drag(...) //todo...
			if (x1 - x0 != 0) {
				value = (x - x0) / (double)(x1 - x0) * (value_max - value_min);
				onChange(value);
				handled = true;
			}
		}
		return handled;
	}
};