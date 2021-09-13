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

class GLMainTraining2 : public GLMain
{
public:
	GLMainTraining2(std::shared_ptr<GLWindow> window, GLColor background_color, GLColor rectangle_color)
		: _window(window), _background_color(background_color), _rectangle_color(rectangle_color)
	{
	}

	GLVector2<GLfloat> ScreenToWorldPoint(int x, int y)
	{
		auto window_size = this->_window->Size();

		x -= window_size.x / 2;
		y -= window_size.y / 2;

		return GLVector2<GLfloat>(x, -y) / GLVector2<GLfloat>(window_size.x / 2, window_size.y / 2);
	}

	GLVector2<int> WorldToScreenPoint(GLfloat x, GLfloat y)
	{
		x += 1.0f;
		y += 1.0f;
		y = -y;

		auto window_size = this->_window->Size();

		return GLVector2<int>((int)(x * window_size.x), (int)(y * window_size.y));
	}

	GLvoid OnDraw() override;
	GLvoid OnReshape(int w, int h) override;
	GLvoid OnMouse(int button, int state, int x, int y) override;

private:
	GLColor _background_color;
	GLColor _rectangle_color;

	std::shared_ptr<GLWindow> _window;
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	auto window = std::make_shared<GLWindow>(0, 0, 800, 600, "Training2");

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

	GLMain::SetInstance(std::make_shared<GLMainTraining2>(window, GLColor(1.0f, 0.0f, 0.0f), GLColor(0.0f, 1.0f, 0.0f)));

	glutMainLoop();
}

GLvoid GLMainTraining2::OnDraw()
{
	GLClearColor(this->_background_color);
	glClear(GL_COLOR_BUFFER_BIT);

	GLColor4f(this->_rectangle_color);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

	glutSwapBuffers();
}


GLvoid GLMainTraining2::OnReshape(int w, int h)
{
	this->_window->SetSize(w, h);
}

GLvoid GLMainTraining2::OnMouse(int button, int state, int x, int y)
{
	if (button == 0)
	{
		auto world_coordinate = this->ScreenToWorldPoint(x, y);
		GLfloat x = world_coordinate.x;
		GLfloat y = world_coordinate.y;

		if (x >=  -0.5f && x <= 0.5f && y >= -0.5f && y <= 0.5f)
		{
			this->_rectangle_color.Rand3f();
		}
		else
		{
			this->_background_color.Rand3f();
		}
	}
}