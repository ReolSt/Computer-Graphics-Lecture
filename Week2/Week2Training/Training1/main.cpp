#include <iostream>
#include <memory>
#include <functional>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include "../GL/GLMain.h"
#include "../GL/GLColor.h"
#include "../GL/GLHelpers.h"
#include "../GL/GLWindow.h"

#include <random>
#include <unordered_map>

class GLMainTraining1 : public GLMain
{
public:
	GLMainTraining1(GLColor background_color)
		: _background_color(background_color) { }

	GLvoid OnDraw() override;
	GLvoid OnReshape(int w, int h) override;
	GLvoid OnKeyboard(unsigned char key, int x, int y) override;

private:
	GLColor _background_color;

	GLint _color_interval = -1;
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	auto window = std::make_shared<GLWindow>(0, 0, 800, 600, "Training1");

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
		this->_background_color.Set(GLColor(1.0f, 0.0f, 0.0f));
		break;
	case 'g':
		this->_background_color.Set(GLColor(0.0f, 1.0f, 0.0f));
		break;
	case 'b':
		this->_background_color.Set(GLColor(0.0f, 0.0f, 1.0f));
		break;
	case 'w':
		this->_background_color.Set(GLColor(1.0f, 1.0f, 1.0f));
		break;
	case 'k':
		this->_background_color.Set(GLColor(0.0f, 0.0f, 0.0f));
		break;
	case 'a':
		this->_background_color.Rand3f();
		break;
	case 't':
		if (this->_color_interval == -1)
		{
			this->_color_interval = this->SetInterval(500, [&]() -> GLvoid
			{
				this->_background_color.Rand3f();

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