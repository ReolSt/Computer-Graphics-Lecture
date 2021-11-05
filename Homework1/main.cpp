#include <iostream>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>

#include "GL/GL.h"

#include "GWorld.h"

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	GLSetWindow(GLCreate<GLWindow>(0, 0, 800, 800, "Homework1"));

	InitializeGLEW();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	auto scene = GLCreate<GLScene>("Homework1");
	scene->SetBackgroundColor(GLColor(0.0f, 0.0f, 0.0f));
	GLLoadScene(scene);

	auto world = GCreate(GWorld);
	scene->Root->AddChild(world);

	world->Initialize();

	glutMainLoop();
}