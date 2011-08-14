#include <openlima/graphics/Window.hpp>
#include <openlima/graphics/WavefrontObjReader.hpp>
#include <openlima/graphics/IRenderable.hpp>
#include <openlima/util/macros.hpp>
#include <openlima/input/GlobalMouse.hpp>


using namespace openlima::graphics;
using namespace openlima::input;

IRenderable* myRenderable;

int i = 10000;

void onMouseMoveEvent(Mouse& source, const MouseMoveEvent& e) {
	//std::cout << e.getDelta().x << " - " << e.getDelta().y << std::endl;
}

void onMouseClickEvent(Mouse& source, const MouseClickEvent& e) {
	if(e.getButton() == LEFT) {
		std::cout << "Left button " << (e.getState() == RELEASED ? "released" : "pressed") <<
			"!" << std::endl;
	} else if(e.getButton() == MIDDLE) {
		std::cout << "Middle button " << (e.getState() == RELEASED ? "released" : "pressed") <<
			"!" << std::endl;
	} else if(e.getButton() == RIGHT) {
		std::cout << "Right button " << (e.getState() == RELEASED ? "released" : "pressed") <<
			"!" << std::endl;
	}
}

void draw() {
	if(i-- > 0) {
		if(i == 0) {
			GlobalMouse::getInstance().setSticky(false);
		}
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-2.0f, -1.2f, -5.0f);
	
	myRenderable->render();

	glutSwapBuffers();
}

OPENLIMA_MAIN(int argc, char** argv) {
	myRenderable = WavefrontObjReader::readStatic("resources/simpleCube.obj");
	
	//Window::hideConsole();
	Window::getInstance().setup(&argc, argv, "LimaBeans", 800, 600);
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

	GlobalMouse::getInstance().setSticky(true);
	GlobalMouse::getInstance().setVisible(false);
	GlobalMouse::getInstance().onMouseMove.connect(&onMouseMoveEvent);
	GlobalMouse::getInstance().onMouseClick.connect(&onMouseClickEvent);

	Window::getInstance().loop();

	std::cout << "end" << std::endl;

	return 0;
}