#include "../GL/GL.h"
#include "GWorld.h"


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	GLSetWindow(GLCreate<GLWindow>(0, 0, 800, 800, "Training28"));

	InitializeGLEW();

	glEnable(GL_DEPTH_TEST);

	auto scene = GLCreate<GLScene>("Training28");
	auto world = GCreate(GWorld);
	scene->Root->AddChild(world);

	scene->SetBackgroundColor(GLColor(0.0f, 0.0f, 0.0f));

	world->Initialize();

	GLLoadScene(scene);

	glutMainLoop();
}