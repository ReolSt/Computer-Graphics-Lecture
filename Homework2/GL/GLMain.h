#pragma once

#include <string>
#include <unordered_map>
#include <functional>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include "core/Singleton.h"
#include "GLMemoryHelpers.h"
#include "GLScene.h"
#include "GLWindow.h"
#include "GLKeyMapper.h"

class GLCallback
{
public:
	GLCallback(int Id, std::function<void()> Func)
		: Id(Id), Func(Func) { }

	void operator()()
	{
		this->Func();
	}

	int Id = 0;
	std::function<void()> Func;
};

class GLTimeoutCallback : public GLCallback
{
public:
	GLTimeoutCallback(int Id, std::function<void()> Func, int TimeoutMsec)
		: GLCallback(Id, Func), TimeoutMsec(TimeoutMsec) { }

	int TimeoutMsec = 0;
};

class GLIntervalCallback : public GLCallback
{
public:
	GLIntervalCallback(int Id, std::function<void()> Func, int IntervalMsec)
		: GLCallback(Id, Func), IntervalMsec(IntervalMsec) { }

	int IntervalMsec = 0;
	bool bIntervalFinished = false;
};

class GLMain : public Singleton<GLMain>
{
public:
	GLMain();

	GLMain(const GLSharedPtr<GLWindow>& window);

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

	int SetTimeout(int Msec, std::function<void()> Callback);

	int SetInterval(int Msec, std::function<void()> Callback);
	bool ClearInterval(int id);

	GLSharedPtr<GLCallback> GetCallback(int id);

	void DeleteCallback(int id);

	void Exit();

	GLSharedPtr<GLWindow> GetWindow()
	{
		return this->window;
	}

	void SetWindow(const GLSharedPtr<GLWindow>& window)
	{
		this->window = window;
	}

	GLSharedPtr<GLScene> GetScene()
	{
		return this->scene;
	}

	void SetScene(const GLSharedPtr<GLScene>& scene)
	{
		this->scene = scene;
	}

private:
	GLSharedPtr<GLWindow> window;
	GLSharedPtr<GLScene> scene;

	GLKeyMapper keyMapper;

	std::unordered_map<int, GLSharedPtr<GLCallback>> callbacks;
	int uniqueIdProvider = 1;

	int mouseButton = -1;
	int mouseX = 0;
	int mouseY = 0;
};

GLSharedPtr<GLScene> GLGetCurrentScene()
{
	return GLMain::GetInstance()->GetScene();
}

void GLLoadScene(const GLSharedPtr<GLScene>& scene)
{
	auto instance = GLMain::GetInstance();
	instance->SetScene(scene);
}

GLSharedPtr<GLWindow> GLGetCurrentWindow()
{
	return GLMain::GetInstance()->GetWindow();
}

void GLSetWindow(const GLSharedPtr<GLWindow>& window)
{
	GLMain::GetInstance()->SetWindow(window);
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
	static float oldTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

	float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = currentTime - oldTime;

	oldTime = currentTime;

	auto window = GLGetCurrentWindow();
	auto scene = GLGetCurrentScene();

	scene->Update(deltaTime);
	scene->Render(window->GetSize());

	float finishedTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float elapsedTime = finishedTime - currentTime;
	std::this_thread::sleep_for(std::chrono::milliseconds((int)glm::max(0.0f, 1000 / 60 - elapsedTime)));
}

GLMain::GLMain()
{
	this->RegisterCallbackManager();
}


GLMain::GLMain(const GLSharedPtr<GLWindow>& Window)
{
	this->RegisterCallbackManager();

	this->window = Window;
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

void GLMain::OnReshape(int W, int H)
{
	if (this->window)
	{
		this->window->SetSize(W, H);
	}
}

void GLMain::OnKeyboard(unsigned char Key, int X, int Y)
{
	if (this->scene)
	{
		this->scene->GetRoot()->OnKeyDown(this->keyMapper[Key], X, Y);
	}
}

void GLMain::OnKeyboardUp(unsigned char Key, int X, int Y)
{
	if (this->scene)
	{
		this->scene->GetRoot()->OnKeyUp(this->keyMapper[Key], X, Y);
	}
}

void GLMain::OnSpecial(int Key, int X, int Y)
{
	if (this->scene)
	{
		this->scene->GetRoot()->OnKeyDown(this->keyMapper[Key + 128], X, Y);
	}
}

void GLMain::OnSpecialUp(int Key, int X, int Y)
{
	if (this->scene)
	{
		this->scene->GetRoot()->OnKeyUp(this->keyMapper[Key + 128], X, Y);
	}
}

void GLMain::OnMouse(int Button, int State, int X, int Y)
{
	this->mouseX = X;
	this->mouseY = Y;

	if (this->scene)
	{
		if (State == GLUT_DOWN)
		{
			this->mouseButton = Button;
			this->scene->GetRoot()->OnMouseDown(Button, X, Y);
		}
		else if (State == GLUT_UP)
		{
			this->mouseButton = -1;
			this->scene->GetRoot()->OnMouseUp(Button, X, Y);
		}
	}
}

void GLMain::OnMouseWheel(int wheel, int direction, int X, int Y)
{
	this->mouseX = X;
	this->mouseY = Y;

	if (this->scene)
	{
		this->scene->GetRoot()->OnMouseWheel(wheel, direction, X, Y);
	}
}

void GLMain::OnMotion(int X, int Y)
{
	this->mouseX = X;
	this->mouseY = Y;

	if (this->scene)
	{
		this->scene->GetRoot()->OnMouseMove(this->mouseButton, X, Y);
	}
}

void GLMain::OnPassiveMotion(int X, int Y)
{
	this->mouseX = X;
	this->mouseY = Y;

	if (this->scene)
	{
		this->scene->GetRoot()->OnMouseMove(-1, X, Y);
	}
}

void GLMain::OnEntry(int State)
{
	if (this->scene)
	{
		if (State == GLUT_LEFT)
		{
			this->scene->GetRoot()->OnMouseLeave();
		}
		else if (State == GLUT_ENTERED)
		{
			this->scene->GetRoot()->OnMouseEnter();
		}
	}
}

int GLMain::SetTimeout(int Msec, std::function<void()> Func)
{
	GLSharedPtr<GLTimeoutCallback> Callback = GLCreate<GLTimeoutCallback>(this->uniqueIdProvider++, Func, Msec);
	this->callbacks[Callback->Id] = Callback;

	glutTimerFunc(Callback->TimeoutMsec, __GLMainIntervalCallbackRunner, Callback->Id);

	return Callback->Id;
}

int GLMain::SetInterval(int Msec, std::function<void()> Func)
{
	GLSharedPtr<GLIntervalCallback> Callback = GLCreate<GLIntervalCallback>(this->uniqueIdProvider++, Func, Msec);
	this->callbacks[Callback->Id] = Callback;

	glutTimerFunc(Callback->IntervalMsec, __GLMainIntervalCallbackRunner, Callback->Id);

	return Callback->Id;
}

bool GLMain::ClearInterval(int id)
{
	if (this->callbacks.find(id) != this->callbacks.end())
	{
		auto Callback = std::static_pointer_cast<GLIntervalCallback>(this->callbacks[id]);
	    Callback->bIntervalFinished = true;
		return true;
	}

	return false;
}

GLSharedPtr<GLCallback> GLMain::GetCallback(int Id)
{
	auto CallbackInfo = this->callbacks.find(Id);
	if (CallbackInfo != this->callbacks.end())
	{
		return CallbackInfo->second;
	}

	return nullptr;
}

void GLMain::DeleteCallback(int Id)
{
	auto Callback = this->callbacks.find(Id);
	if (Callback != this->callbacks.end())
	{
		this->callbacks.erase(Callback);
	}
}

void GLMain::Exit()
{
	glutLeaveMainLoop();
}

void __GLMainOnDraw()
{
	GLMain::GetInstance()->OnDraw();
}

void __GLMainOnIdle()
{
	GLMain::GetInstance()->OnIdle();
}

void __GLMainOnReshape(int W, int H)
{
	GLMain::GetInstance()->OnReshape(W, H);
}

void __GLMainOnKeyboard(unsigned char Key, int X, int Y)
{
	GLMain::GetInstance()->OnKeyboard(Key, X, Y);
}

void __GLMainOnKeyboardUp(unsigned char Key, int X, int Y)
{
	GLMain::GetInstance()->OnKeyboardUp(Key, X, Y);
}

void __GLMainOnSpecial(int Key, int X, int Y)
{
	GLMain::GetInstance()->OnSpecial(Key, X, Y);
}

void __GLMainOnSpecialUp(int Key, int X, int Y)
{
	GLMain::GetInstance()->OnSpecialUp(Key, X, Y);
}

void __GLMainOnMouse(int button, int state, int X, int Y)
{
	GLMain::GetInstance()->OnMouse(button, state, X, Y);
}

void __GLMainOnMouseWheel(int wheel, int direction, int X, int Y)
{
	GLMain::GetInstance()->OnMouseWheel(wheel, direction, X, Y);
}

void __GLMainOnMotion(int X, int Y)
{
	GLMain::GetInstance()->OnMotion(X, Y);
}

void __GLMainOnPassiveMotion(int X, int Y)
{
	GLMain::GetInstance()->OnPassiveMotion(X, Y);
}

void __GLMainOnEntry(int State)
{
	GLMain::GetInstance()->OnEntry(State);
}

void __GLMainTimeoutCallbackRunner(int Id)
{
	auto Callback = GLMain::GetInstance()->GetCallback(Id);

	if (Callback == nullptr)
	{
		return;
	}

	(*Callback)();

	GLMain::GetInstance()->DeleteCallback(Callback->Id);
}

void __GLMainIntervalCallbackRunner(int Id)
{
	GLSharedPtr<GLIntervalCallback> Callback = std::static_pointer_cast<GLIntervalCallback>(GLMain::GetInstance()->GetCallback(Id));

	if (Callback == nullptr)
	{
		return;
	}

	(*Callback)();

	if (Callback->bIntervalFinished)
	{
		GLMain::GetInstance()->DeleteCallback(Callback->Id);
		return;
	}

	glutTimerFunc(Callback->IntervalMsec, __GLMainIntervalCallbackRunner, Id);
}

