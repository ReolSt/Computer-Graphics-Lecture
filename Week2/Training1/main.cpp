#include <iostream>
#include <memory>
#include <functional>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include "GLMain.h"
#include "GLColor.h"
#include "GLHelpers.h"

#include <random>
#include <unordered_map>

class GLMainTraining1 : public GLMain
{
public:
	GLMainTraining1()
		: _background_color(GLColor()) { }

	GLMainTraining1(GLColor background_color)
		: _background_color(background_color) { }

	GLvoid SetBackgroundColor(const GLColor& color)
	{
		this->_background_color = color;
	}

	GLvoid SetRandomBackgroundColor3f()
	{
		this->_background_color.Rand3f();
	}

	GLvoid SetRandomBackgroundColor4f()
	{
		this->_background_color.Rand4f();
	}

	GLvoid OnDraw() override;
	GLvoid OnReshape(int w, int h) override;
	GLvoid OnKeyboard(unsigned char key, int x, int y) override;

private:
	GLColor _background_color;

	int _color_interval = -1;
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Training1");

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

	GLMain::SetInstance(std::make_shared<GLMainTraining1>(GLColor(1.0f, 1.0f, 1.0f)));

	glutMainLoop();
}

GLvoid GLMainTraining1::OnDraw()
{
	GLClearColor(this->_background_color);
	glClear(GL_COLOR_BUFFER_BIT);

	glutSwapBuffers();
}

GLvoid GLMainTraining1::OnReshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid GLMainTraining1::OnKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r':
		this->SetBackgroundColor(GLColor(1.0f, 0.0f, 0.0f));
		break;
	case 'g':
		this->SetBackgroundColor(GLColor(0.0f, 1.0f, 0.0f));
		break;
	case 'b':
		this->SetBackgroundColor(GLColor(0.0f, 0.0f, 1.0f));
		break;
	case 'w':
		this->SetBackgroundColor(GLColor(1.0f, 1.0f, 1.0f));
		break;
	case 'k':
		this->SetBackgroundColor(GLColor(0.0f, 0.0f, 0.0f));
		break;
	case 'a':
		this->SetRandomBackgroundColor3f();
		break;
	case 't':
		if (this->_color_interval == -1)
		{
			this->_color_interval = this->SetInterval(500, []() -> GLvoid
			{
				auto glMain = std::dynamic_pointer_cast<GLMainTraining1>(GLMain::GetInstance());
				glMain->SetRandomBackgroundColor3f();

				glutPostRedisplay();
			});
		}
		break;
	case 's':
		if (this->_color_interval != -1)
		{
			this->ClearInterval(this->_color_interval);
			this->_color_interval = -1;
		}
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}

	glutPostRedisplay();
}