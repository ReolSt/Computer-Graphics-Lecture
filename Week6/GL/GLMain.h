#pragma once

#include <string>
#include <unordered_map>
#include <functional>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include "core/Singleton.h"
#include "GLScene.h"
#include "GLWindow.h"
#include "GLKeyMapper.h"

class GLCallback
{
public:
	GLCallback(int id, std::function<void()> func)
		: id(id), func(func) { }

	void operator()()
	{
		this->func();
	}

	int id = 0;

	std::function<void()> func;
};

class GLTimeoutCallback : public GLCallback
{
public:
	GLTimeoutCallback(int id, std::function<void()> func, int timeout_msec)
		: GLCallback(id, func), timeout_msec(timeout_msec) { }

	int timeout_msec = 0;
};

class GLIntervalCallback : public GLCallback
{
public:
	GLIntervalCallback(int id, std::function<void()> func, int interval_msec)
		: GLCallback(id, func), interval_msec(interval_msec) { }

	int interval_msec = 0;
	bool interval_finished = false;
};

class GLMain : public Singleton<GLMain>
{
public:
	GLMain();

	GLMain(const std::shared_ptr<GLWindow>& window);

	virtual ~GLMain() { };

	void RegisterCallbackManager();

	virtual void OnDraw();
	virtual void OnIdle();
	virtual void OnReshape(int w, int h);
	virtual void OnKeyboard(unsigned char key, int x, int y);
	virtual void OnKeyboardUp(unsigned char key, int x, int y);
	virtual void OnSpecial(int key, int x, int y);
	virtual void OnSpecialUp(int key, int x, int y);
	virtual void OnMouse(int button, int state, int x, int y);
	virtual void OnMouseWheel(int wheel, int direction, int x, int y);
	virtual void OnMotion(int x, int y);
	virtual void OnPassiveMotion(int x, int y);
	virtual void OnEntry(int state);

	int SetTimeout(int msec, std::function<void()> callback);

	int SetInterval(int msec, std::function<void()> callback);
	GLboolean ClearInterval(int id);

	std::shared_ptr<GLCallback> GetCallback(int id);

	void DeleteCallback(int id);

	std::shared_ptr<GLWindow> window;
	std::shared_ptr<GLScene> scene;

	GLKeyMapper key_mapper;
private:
	std::unordered_map<int, std::shared_ptr<GLCallback>> callbacks;
	int unique_id_provider = 1;

	int mouse_button = -1;
	int mouse_x = 0;
	int mouse_y = 0;
};

std::shared_ptr<GLScene>& GLCurrentScene()
{
	return GLMain::GetInstance()->scene;
}

void GLLoadScene(const std::shared_ptr<GLScene>& scene)
{
	auto instance = GLMain::GetInstance();

	instance->scene = scene;
}

void __GLMainOnDraw();
void __GLMainOnIdle();
void __GLMainOnReshape(int w, int h);
void __GLMainOnKeyboard(unsigned char key, int x, int y);
void __GLMainOnKeyboardUp(unsigned char key, int x, int y);
void __GLMainOnSpecial(int key, int x, int y);
void __GLMainOnSpecialUp(int key, int x, int y);
void __GLMainOnMouse(int button, int state, int x, int y);
void __GLMainOnMouseWheel(int wheel, int direction, int x, int y);
void __GLMainOnMotion(int x, int y);
void __GLMainOnPassiveMotion(int x, int y);
void __GLMainOnEntry(int state);

void __GLMainTimeoutCallbackRunner(int id);
void __GLMainIntervalCallbackRunner(int id);

void __GLUpdateScene()
{
	static GLfloat old_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

	GLfloat current_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	GLfloat delta_time = current_time - old_time;

	old_time = current_time;

	auto& scene = GLCurrentScene();

	glClearColor(scene->background.r, scene->background.g, scene->background.b, scene->background.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene->root->Update(delta_time);
	if (scene->active_camera != nullptr)
	{
		scene->root->Render(scene->active_camera->ProjectionMatrix() * scene->active_camera->ViewMatrix());
	}

	glutSwapBuffers();

	GLfloat finish_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	GLfloat elapsed_time = finish_time - current_time;
	std::this_thread::sleep_for(std::chrono::milliseconds((int)glm::max(0.0f, 1000 / 60 - elapsed_time)));
}

GLMain::GLMain()
{
	this->RegisterCallbackManager();
}


GLMain::GLMain(const std::shared_ptr<GLWindow>& window)
{
	this->RegisterCallbackManager();

	this->window = window;
}

void GLMain::RegisterCallbackManager()
{
	glutDisplayFunc(__GLMainOnDraw);
	glutIdleFunc(__GLMainOnIdle);
	glutReshapeFunc(__GLMainOnReshape);
	glutKeyboardFunc(__GLMainOnKeyboard);
	glutKeyboardUpFunc(__GLMainOnKeyboardUp);
	glutSpecialFunc(__GLMainOnSpecial);
	glutSpecialUpFunc(__GLMainOnSpecialUp);
	glutMouseFunc(__GLMainOnMouse);
	glutMouseWheelFunc(__GLMainOnMouseWheel);
	glutMotionFunc(__GLMainOnMotion);
	glutPassiveMotionFunc(__GLMainOnPassiveMotion);
	glutEntryFunc(__GLMainOnEntry);
}

void GLMain::OnDraw()
{
	__GLUpdateScene();
}

void GLMain::OnIdle()
{
	glutPostRedisplay();
}

void GLMain::OnReshape(int w, int h)
{
	if (this->window)
	{
		this->window->SetSize(w, h);
		this->scene->active_camera->window_width = w;
		this->scene->active_camera->window_height = h;
	}
}

void GLMain::OnKeyboard(unsigned char key, int x, int y)
{
	if (this->scene)
	{
		this->scene->root->OnKeyDown(this->key_mapper[key], x, y);
	}
}

void GLMain::OnKeyboardUp(unsigned char key, int x, int y)
{
	if (this->scene)
	{
		this->scene->root->OnKeyUp(this->key_mapper[key], x, y);
	}
}

void GLMain::OnSpecial(int key, int x, int y)
{
	if (this->scene)
	{
		this->scene->root->OnKeyDown(this->key_mapper[key + 128], x, y);
	}
}

void GLMain::OnSpecialUp(int key, int x, int y)
{
	if (this->scene)
	{
		this->scene->root->OnKeyUp(this->key_mapper[key + 128], x, y);
	}
}

void GLMain::OnMouse(int button, int state, int x, int y)
{
	this->mouse_x = x;
	this->mouse_y = y;

	if (this->scene)
	{
		if (state == GLUT_DOWN)
		{
			this->mouse_button = button;
			this->scene->root->OnMouseDown(button, x, y);
		}
		else if (state == GLUT_UP)
		{
			this->mouse_button = -1;
			this->scene->root->OnMouseUp(button, x, y);
		}
	}
}

void GLMain::OnMouseWheel(int wheel, int direction, int x, int y)
{
	this->mouse_x = x;
	this->mouse_y = y;

	if (this->scene)
	{
		this->scene->root->OnMouseWheel(wheel, direction, x, y);
	}
}

void GLMain::OnMotion(int x, int y)
{
	this->mouse_x = x;
	this->mouse_y = y;

	if (this->scene)
	{
		this->scene->root->OnMouseMove(this->mouse_button, x, y);
	}
}

void GLMain::OnPassiveMotion(int x, int y)
{
	this->mouse_x = x;
	this->mouse_y = y;

	if (this->scene)
	{
		this->scene->root->OnMouseMove(-1, x, y);
	}
}

void GLMain::OnEntry(int state)
{
	if (this->scene)
	{
		if (state == GLUT_LEFT)
		{
			this->scene->root->OnMouseLeave();
		}
		else if (state == GLUT_ENTERED)
		{
			this->scene->root->OnMouseEnter();
		}
	}
}

int GLMain::SetTimeout(int msec, std::function<void()> func)
{
	std::shared_ptr<GLTimeoutCallback> callback = std::make_shared<GLTimeoutCallback>(this->unique_id_provider++, func, msec);
	this->callbacks[callback->id] = callback;

	glutTimerFunc(callback->timeout_msec, __GLMainIntervalCallbackRunner, callback->id);

	return callback->id;
}

int GLMain::SetInterval(int msec, std::function<void()> func)
{
	std::shared_ptr<GLIntervalCallback> callback = std::make_shared<GLIntervalCallback>(this->unique_id_provider++, func, msec);
	this->callbacks[callback->id] = callback;

	glutTimerFunc(callback->interval_msec, __GLMainIntervalCallbackRunner, callback->id);

	return callback->id;
}

GLboolean GLMain::ClearInterval(int id)
{
	if (this->callbacks.find(id) != this->callbacks.end())
	{
		auto callback = std::static_pointer_cast<GLIntervalCallback>(this->callbacks[id]);
	    callback->interval_finished = true;
		return true;
	}

	return false;
}

std::shared_ptr<GLCallback> GLMain::GetCallback(int id)
{
	auto callback_info = this->callbacks.find(id);
	if (callback_info != this->callbacks.end())
	{
		return callback_info->second;
	}

	return nullptr;
}

void GLMain::DeleteCallback(int id)
{
	auto callback = this->callbacks.find(id);
	if (callback != this->callbacks.end())
	{
		this->callbacks.erase(callback);
	}
}

void __GLMainOnDraw()
{
	GLMain::GetInstance()->OnDraw();
}

void __GLMainOnIdle()
{
	GLMain::GetInstance()->OnIdle();
}

void __GLMainOnReshape(int w, int h)
{
	GLMain::GetInstance()->OnReshape(w, h);
}

void __GLMainOnKeyboard(unsigned char key, int x, int y)
{
	GLMain::GetInstance()->OnKeyboard(key, x, y);
}

void __GLMainOnKeyboardUp(unsigned char key, int x, int y)
{
	GLMain::GetInstance()->OnKeyboardUp(key, x, y);
}

void __GLMainOnSpecial(int key, int x, int y)
{
	GLMain::GetInstance()->OnSpecial(key, x, y);
}

void __GLMainOnSpecialUp(int key, int x, int y)
{
	GLMain::GetInstance()->OnSpecialUp(key, x, y);
}

void __GLMainOnMouse(int button, int state, int x, int y)
{
	GLMain::GetInstance()->OnMouse(button, state, x, y);
}

void __GLMainOnMouseWheel(int wheel, int direction, int x, int y)
{
	GLMain::GetInstance()->OnMouseWheel(wheel, direction, x, y);
}

void __GLMainOnMotion(int x, int y)
{
	GLMain::GetInstance()->OnMotion(x, y);
}

void __GLMainOnPassiveMotion(int x, int y)
{
	GLMain::GetInstance()->OnPassiveMotion(x, y);
}

void __GLMainOnEntry(int state)
{
	GLMain::GetInstance()->OnEntry(state);
}

void __GLMainTimeoutCallbackRunner(int id)
{
	auto callback = GLMain::GetInstance()->GetCallback(id);

	if (callback == nullptr)
	{
		return;
	}

	(*callback)();

	GLMain::GetInstance()->DeleteCallback(callback->id);
}

void __GLMainIntervalCallbackRunner(int id)
{
	std::shared_ptr<GLIntervalCallback> callback = std::static_pointer_cast<GLIntervalCallback>(GLMain::GetInstance()->GetCallback(id));

	if (callback == nullptr)
	{
		return;
	}

	(*callback)();

	if (callback->interval_finished)
	{
		GLMain::GetInstance()->DeleteCallback(callback->id);
		return;
	}

	glutTimerFunc(callback->interval_msec, __GLMainIntervalCallbackRunner, id);
}

