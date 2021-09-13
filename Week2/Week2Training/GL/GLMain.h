#pragma once

#include "Singleton.h"

#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include <string>
#include <unordered_map>
#include <functional>

class GLCallback
{
public:
	GLCallback(GLint id, std::function<GLvoid()> func)
		: id(id), func(func) { }

	GLvoid operator()()
	{
		this->func();
	}

	GLint id = 0;

	std::function<GLvoid()> func;
};

class GLTimeoutCallback : public GLCallback
{
public:
	GLTimeoutCallback(GLint id, std::function<GLvoid()> func, int timeout_msec)
		: GLCallback(id, func), timeout_msec(timeout_msec) { }

	int timeout_msec = 0;
};

class GLIntervalCallback : public GLCallback
{
public:
	GLIntervalCallback(GLint id, std::function<GLvoid()> func, int interval_msec)
		: GLCallback(id, func), interval_msec(interval_msec) { }

	int interval_msec = 0;
	bool interval_finished = false;
};

class GLMain : public Singleton<GLMain>
{
public:
	GLMain();

	virtual ~GLMain() { };

	virtual GLvoid OnDraw() { };
	virtual GLvoid OnIdle() { };
	virtual GLvoid OnReshape(int w, int h) { };
	virtual GLvoid OnKeyboard(unsigned char key, int x, int y) { };
	virtual GLvoid OnKeyboardUp(unsigned char key, int x, int y) { };
	virtual GLvoid OnSpecial(int key, int x, int y) { };
	virtual GLvoid OnSpecialUp(int key, int x, int y) { };
	virtual GLvoid OnMouse(int button, int state, int x, int y) { };
	virtual GLvoid OnMotion(int x, int y) { };
	virtual GLvoid OnPassiveMotion(int x, int y) { };
	virtual GLvoid OnEntry(int state) { };

	GLint SetTimeout(int msec, std::function<GLvoid()> callback);

	GLint SetInterval(int msec, std::function<GLvoid()> callback);
	GLboolean ClearInterval(GLint id);

	std::shared_ptr<GLCallback> GetCallback(GLint id);

	GLvoid DeleteCallback(GLint id);

private:
	std::unordered_map<GLint, std::shared_ptr<GLCallback>> _callbacks;
	GLint _unique_id_provider = 1;
};

GLvoid __GLMainOnDraw();
GLvoid __GLMainOnIdle();
GLvoid __GLMainOnReshape(int w, int h);
GLvoid __GLMainOnKeyboard(unsigned char key, int x, int y);
GLvoid __GLMainOnKeyboardUp(unsigned char key, int x, int y);
GLvoid __GLMainOnSpecial(int key, int x, int y);
GLvoid __GLMainOnSpecialUp(int key, int x, int y);
GLvoid __GLMainOnMouse(int button, int state, int x, int y);
GLvoid __GLMainOnMotion(int x, int y);
GLvoid __GLMainOnPassiveMotion(int x, int y);
GLvoid __GLMainOnEntry(int state);

GLvoid __GLMainTimeoutCallbackRunner(int id);
GLvoid __GLMainIntervalCallbackRunner(int id);


GLMain::GLMain()
{
	glutDisplayFunc(__GLMainOnDraw);
	glutIdleFunc(__GLMainOnIdle);
	glutReshapeFunc(__GLMainOnReshape);
	glutKeyboardFunc(__GLMainOnKeyboard);
	glutKeyboardUpFunc(__GLMainOnKeyboardUp);
	glutSpecialFunc(__GLMainOnSpecial);
	glutSpecialUpFunc(__GLMainOnSpecialUp);
	glutMouseFunc(__GLMainOnMouse);
	glutMotionFunc(__GLMainOnMotion);
	glutPassiveMotionFunc(__GLMainOnPassiveMotion);
	glutEntryFunc(__GLMainOnEntry);
}

GLint GLMain::SetTimeout(int msec, std::function<GLvoid()> func)
{
	std::shared_ptr<GLTimeoutCallback> callback = std::make_shared<GLTimeoutCallback>(this->_unique_id_provider++, func, msec);
	this->_callbacks[callback->id] = callback;

	glutTimerFunc(callback->timeout_msec, __GLMainIntervalCallbackRunner, callback->id);

	return callback->id;
}

GLint GLMain::SetInterval(int msec, std::function<GLvoid()> func)
{
	std::shared_ptr<GLIntervalCallback> callback = std::make_shared<GLIntervalCallback>(this->_unique_id_provider++, func, msec);
	this->_callbacks[callback->id] = callback;

	glutTimerFunc(callback->interval_msec, __GLMainIntervalCallbackRunner, callback->id);

	return callback->id;
}

GLboolean GLMain::ClearInterval(GLint id)
{
	if (this->_callbacks.find(id) != this->_callbacks.end())
	{
		auto callback = std::static_pointer_cast<GLIntervalCallback>(this->_callbacks[id]);
	    callback->interval_finished = true;
		return true;
	}

	return false;
}

std::shared_ptr<GLCallback> GLMain::GetCallback(GLint id)
{
	auto callback_info = this->_callbacks.find(id);
	if (callback_info != this->_callbacks.end())
	{
		return callback_info->second;
	}

	return nullptr;
}

GLvoid GLMain::DeleteCallback(GLint id)
{
	auto callback = this->_callbacks.find(id);
	if (callback != this->_callbacks.end())
	{
		this->_callbacks.erase(callback);
	}
}

GLvoid __GLMainOnDraw()
{
	GLMain::GetInstance()->OnDraw();
}

GLvoid __GLMainOnIdle()
{
	GLMain::GetInstance()->OnIdle();
}

GLvoid __GLMainOnReshape(int w, int h)
{
	GLMain::GetInstance()->OnReshape(w, h);
}

GLvoid __GLMainOnKeyboard(unsigned char key, int x, int y)
{
	GLMain::GetInstance()->OnKeyboard(key, x, y);
}

GLvoid __GLMainOnKeyboardUp(unsigned char key, int x, int y)
{
	GLMain::GetInstance()->OnKeyboardUp(key, x, y);
}

GLvoid __GLMainOnSpecial(int key, int x, int y)
{
	GLMain::GetInstance()->OnSpecial(key, x, y);
}

GLvoid __GLMainOnSpecialUp(int key, int x, int y)
{
	GLMain::GetInstance()->OnSpecialUp(key, x, y);
}

GLvoid __GLMainOnMouse(int button, int state, int x, int y)
{
	GLMain::GetInstance()->OnMouse(button, state, x, y);
}

GLvoid __GLMainOnMotion(int x, int y)
{
	GLMain::GetInstance()->OnMotion(x, y);
}

GLvoid __GLMainOnPassiveMotion(int x, int y)
{
	GLMain::GetInstance()->OnPassiveMotion(x, y);
}

GLvoid __GLMainOnEntry(int state)
{
	GLMain::GetInstance()->OnEntry(state);
}

GLvoid __GLMainTimeoutCallbackRunner(int id)
{
	auto callback = GLMain::GetInstance()->GetCallback(id);

	if (callback == nullptr)
	{
		return;
	}

	(*callback)();

	GLMain::GetInstance()->DeleteCallback(callback->id);
}

GLvoid __GLMainIntervalCallbackRunner(int id)
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

