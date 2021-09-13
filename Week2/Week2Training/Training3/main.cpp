#include <iostream>
#include <memory>
#include <random>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include "../GL/GLMain.h"
#include "../GL/GLColor.h"
#include "../GL/GLHelpers.h"
#include "../GL/GLWindow.h"
#include "../GL/GLVector.h"

class GLMainTraining3 : public GLMain
{
public:
	GLMainTraining3(std::shared_ptr<GLWindow> window, GLColor background_color, GLColor rectangle_color)
		: _window(window), _background_color(background_color), _rectangle_color(rectangle_color),
		  _rectangle_position(-0.2f, 0.2f), _rectangle_size(0.4f, 0.4f)
	{ }

	GLVector2<GLfloat> ScreenToWorldPoint(int x, int y)
	{
		auto window_size = this->_window->Size();

		x -= window_size.x / 2;
		y -= window_size.y / 2; 

		return GLVector2<GLfloat>(x, -y) * 2 / GLVector2<GLfloat>(window_size.x, window_size.y);
	}

	GLVector2<int> WorldToScreenPoint(GLfloat x, GLfloat y)
	{
		x += 1.0f;
		y += 1.0f;
		y = -y;

		auto window_size = this->_window->Size();

		return GLVector2<int>(x * window_size.x, y * window_size.y);
	}

	GLvoid OnDraw() override;
	GLvoid OnReshape(int w, int h) override;
	GLvoid OnMouse(int button, int state, int x, int y) override;
	GLvoid OnMotion(int x, int y) override;
	GLvoid OnPassiveMotion(int x, int y);

private:
	GLColor _background_color;
	GLColor _rectangle_color;

	GLVector2<GLfloat> _rectangle_position;
	GLVector2<GLfloat> _rectangle_size;

	GLVector2<int> _mouse_position;

	std::shared_ptr<GLWindow> _window;
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	auto window = std::make_shared<GLWindow>(0, 0, 800, 600, "Training3");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "GLEW Initialized" << std::endl;
	}

	GLMain::SetInstance(std::make_shared<GLMainTraining3>(window, GLColor(0.1f, 0.1f, 0.1f), GLColor(0.0f, 1.0f, 0.0f)));

	glutMainLoop();
}

GLvoid GLMainTraining3::OnDraw()
{
	GLClearColor(this->_background_color);
	glClear(GL_COLOR_BUFFER_BIT);

	GLColor4f(this->_rectangle_color);
	GLRectf(this->_rectangle_position, this->_rectangle_size);

	glutSwapBuffers();
}


GLvoid GLMainTraining3::OnReshape(int w, int h)
{
	this->_window->SetSize(w, h);
}

GLvoid GLMainTraining3::OnMouse(int button, int state, int x, int y)
{
	if (button == 0)
	{
		if (state == 1)
		{
			return;
		}

		auto world_coordinate = this->ScreenToWorldPoint(x, y);
		GLfloat x = world_coordinate.x;
		GLfloat y = world_coordinate.y;

		GLfloat left = this->_rectangle_position.x;
		GLfloat right = left + this->_rectangle_size.x;

		GLfloat top = this->_rectangle_position.y;
		GLfloat bottom = top - this->_rectangle_size.y;

		if (x >= left && x <= right && y >= bottom && y <= top)
		{
			this->_rectangle_color.Rand3f();
		}
	}
}

GLvoid GLMainTraining3::OnMotion(int x, int y)
{
	GLVector2<int> mousePosition(x, y);

	GLVector2<GLfloat> mousePositionDeltaWorld = this->ScreenToWorldPoint(x, y) - this->ScreenToWorldPoint(this->_mouse_position.x, this->_mouse_position.y);

	this->_rectangle_position.x += mousePositionDeltaWorld.x;
	this->_rectangle_position.y += mousePositionDeltaWorld.y;

	this->_mouse_position.x = x;
	this->_mouse_position.y = y;

	glutPostRedisplay();
}

GLvoid GLMainTraining3::OnPassiveMotion(int x, int y)
{
	this->_mouse_position.x = x;
	this->_mouse_position.y = y;
}