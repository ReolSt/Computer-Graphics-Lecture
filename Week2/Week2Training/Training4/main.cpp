#include <iostream>
#include <memory>
#include <functional>
#include <random>
#include <chrono>
#include <ctime>
#include <sstream>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>


#include "../GL/GLMain.h"
#include "../GL/GLColor.h"
#include "../GL/GLHelpers.h"
#include "../GL/GLWindow.h"
#include "../GL/GLVector.h"

struct GLRectangle
{
	GLVector2<GLfloat> position;
	GLVector2<GLfloat> size;
	GLColor color;
};

class GLMainTraining4 : public GLMain
{
public:
	GLMainTraining4(std::shared_ptr<GLWindow> window, GLColor background_color)
		: _window(window), _background_color(background_color) { }

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

	GLfloat Randf(GLfloat min, GLfloat max)
	{
		static std::default_random_engine engine(time(0));

		std::uniform_real_distribution<GLfloat> distribution(min, max);
		return distribution(engine);
	}

	template <typename T>
	GLVector2<T> RandVector2(T min, T max)
	{
		return GLVector2<T>(Randf(min, max), Randf(min, max));
	}

	GLVector2<GLfloat> RandDirection(GLfloat velocity)
	{
		GLVector2<GLboolean> directionSelector = RandVector2<GLboolean>(false, true);

		return GLVector2<GLfloat>(
			directionSelector.x ? velocity : -velocity,
			directionSelector.y ? velocity : -velocity
		);
	}

	GLRectangle RandRect(GLfloat x, GLfloat y, GLfloat min, GLfloat max)
	{
		GLRectangle rectangle;
		rectangle.position.x = x;
		rectangle.position.y = y;
		rectangle.size.x = Randf(min, max);
		rectangle.size.y = Randf(min, max);
		rectangle.color.Rand3f();

		return rectangle;
	}

	GLvoid OnIdle() override;
	GLvoid OnDraw() override;
	GLvoid OnReshape(int w, int h) override;
	GLvoid OnMouse(int button, int state, int x, int y) override;
	GLvoid OnMotion(int x, int y) override;
	GLvoid OnPassiveMotion(int x, int y);
	GLvoid OnKeyboard(unsigned char key, int x, int y);

private:
	std::shared_ptr<GLWindow> _window;

	GLColor _background_color;
	std::vector<GLVector2<GLfloat>> _rect_origins;
	std::vector<GLRectangle> _rectangles;
	std::vector<GLVector2<GLfloat>> _move_velocities;
	std::vector<GLVector2<GLfloat>> _size_velocities;

	GLboolean _moveToggle = false;
	GLboolean _sizeToggle = false;
};


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	auto window = std::make_shared<GLWindow>(0, 0, 800, 600, "Training4");

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

	GLMain::SetInstance(std::make_shared<GLMainTraining4>(window, GLColor(0.1f, 0.1f, 0.1f)));

	glutMainLoop();
}

GLvoid GLMainTraining4::OnIdle()
{
	if (this->_moveToggle)
	{
		for (auto i = 0; i < this->_rectangles.size(); ++i)
		{
			this->_rectangles[i].position += _move_velocities[i];

			if (this->_rectangles[i].position.x < -1.0f || this->_rectangles[i].position.x + this->_rectangles[i].size.x > 1.0f)
			{
				this->_move_velocities[i].x = -this->_move_velocities[i].x;
			}
			if (this->_rectangles[i].position.y - this->_rectangles[i].size.y < -1.0f || this->_rectangles[i].position.y > 1.0f)
			{
				this->_move_velocities[i].y = -this->_move_velocities[i].y;
			}
		}
	}

	if (this->_sizeToggle)
	{
		for (auto i = 0; i < this->_rectangles.size(); ++i)
		{
			this->_rectangles[i].size += _size_velocities[i];

			if (this->_rectangles[i].size.x < 0.1f || this->_rectangles[i].size.x > 0.6f)
			{
				this->_size_velocities[i].x = -this->_size_velocities[i].x;
			}
			if (this->_rectangles[i].size.y < 0.1f || this->_rectangles[i].size.y > 0.6f)
			{
				this->_size_velocities[i].y = -this->_size_velocities[i].y;
			}
		}
	}

	glutPostRedisplay();
}

GLvoid GLMainTraining4::OnDraw()
{
	GLClearColor(this->_background_color);
	glClear(GL_COLOR_BUFFER_BIT);	

	for (const auto& rectangle : this->_rectangles)
	{
		GLColor3f(rectangle.color);
		GLRectf(rectangle.position, rectangle.size);
	}

	glutSwapBuffers();
}

GLvoid GLMainTraining4::OnReshape(int w, int h)
{
	this->_window->SetSize(w, h);
}

GLvoid GLMainTraining4::OnMouse(int button, int state, int x, int y)
{
	if (button == 0)
	{
		if (state == 0)
		{
			if (this->_rectangles.size() < 5)
			{
				GLVector2<GLfloat> mousePositionWorld = this->ScreenToWorldPoint(x, y);

				GLRectangle rectangle = this->RandRect(
					mousePositionWorld.x, mousePositionWorld.y, 0.1f, 0.4f);
				rectangle.position.x -= rectangle.size.x / 2;
				rectangle.position.y += rectangle.size.y / 2;

				GLVector2<GLfloat> move_velocity = this->RandDirection(0.001f);
				GLVector2<GLfloat> size_velocity = this->RandDirection(0.001f);

				this->_rect_origins.push_back(rectangle.position);
				this->_rectangles.push_back(rectangle);
				this->_move_velocities.push_back(move_velocity);
				this->_size_velocities.push_back(size_velocity);
			}
		}
	}
}

GLvoid GLMainTraining4::OnMotion(int x, int y)
{

}

GLvoid GLMainTraining4::OnPassiveMotion(int x, int y)
{

}

GLvoid GLMainTraining4::OnKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		this->_moveToggle = true;
		break;
	case 'c':
		this->_sizeToggle = !this->_sizeToggle;
		break;
	case 's':
		this->_moveToggle = false;
		break;
	case 'm':
		for (auto i = 0; i < this->_rectangles.size(); ++i)
		{
			this->_rectangles[i].position = this->_rect_origins[i];
		}
		break;
	case 'r':
		this->_rectangles.clear();
		this->_move_velocities.clear();
		this->_size_velocities.clear();
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}
}
