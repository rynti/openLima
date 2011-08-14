#include <GL/freeglut.h>

#include "Window.hpp"

#ifdef L_WIN
#include <windows.h>
#endif


namespace openlima {
	namespace graphics {

		// Static methods:

		void Window::resizeHandler(int winWidth, int winHeight) {
			glViewport(0, 0, winWidth, winHeight);

			glMatrixMode(GL_PROJECTION);

			glLoadIdentity();
			gluPerspective(45.0, (double)winWidth / (double)winHeight, 1.0, 200.0);
		}

		void Window::drawHandler() {
			Window::getInstance().draw();
		}

		Window& Window::getInstance() {
			static Window window;
			return window;
		}

		void Window::hideConsole() {
#ifdef L_WIN
			FreeConsole();
#endif
		}


		// Methods:

		void Window::setup(int* argcp, char** argv, const char* winCaption, int winWidth,
			int winHeight, unsigned int displayMode) {

			glutInit(argcp, argv);
			glutInitDisplayMode(displayMode);
			glutInitWindowSize(winWidth, winHeight);

			glutCreateWindow(winCaption);
			glutReshapeFunc(resizeHandler);
			glutDisplayFunc(drawHandler);
			glutIdleFunc(drawHandler);
			glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
		}

		void Window::setDrawFunction(boost::function<void()> func) {
			this->drawFunction = func;
		}

		void Window::loop() {
			glutMainLoop();
		}

		void Window::draw() {
			this->drawFunction();
		}

	}
}