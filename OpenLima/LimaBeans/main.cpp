#include <openlima/graphics/Window.hpp>
#include <openlima/graphics/WavefrontObjReader.hpp>
#include <openlima/graphics/IRenderable.hpp>
#include <openlima/util/macros.hpp>
#include <openlima/input/Mouse.hpp>


using namespace openlima::graphics;
using namespace openlima::input;

IRenderable* myRenderable;

void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-2.0f, -1.2f, -5.0f);
	
	myRenderable->render();

	glutSwapBuffers();
}

L_MAIN(int argc, char** argv) {
	myRenderable = WavefrontObjReader::readStatic("resources/simpleCube.obj");
	
	Window::hideConsole();
	Window::getInstance().setup(&argc, argv, "Testapplikation", 800, 600);
	Window::getInstance().setDrawFunction(draw);

	// OpenGL-Flags will be extracted into openlima::graphics
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	
	GLfloat ambientColor[]= {0.2f, 0.2f, 0.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	// Lightning stuff will be extracted into openlima::graphics
	glEnable(GL_LIGHT0);
	GLfloat lightColor[] = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat lightPos[] = {2.0f, 0.0f, 0.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	Window::getInstance().loop();

	return 0;
}