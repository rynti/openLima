#include <openlima/graphics/Window.hpp>
#include <openlima/graphics/WavefrontObjReader.hpp>
#include <openlima/graphics/IRenderable.hpp>
#include <openlima/util/macros.hpp>


using namespace openlima::graphics;

IRenderable* myRenderable;

void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-1.5f, -0.2f, -5.0f);
	
	myRenderable->render();

	glutSwapBuffers();
}

L_MAIN(int argc, char** argv) {
	myRenderable = WavefrontObjReader::readStatic("resources/simpleCube.obj");
	
	Window::hideConsole();
	Window::getInstance().setup(&argc, argv, "Testapplikation", 800, 600);
	Window::getInstance().setDrawFunction(draw);
	Window::getInstance().loop();

	return 0;
}