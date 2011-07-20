#include <GL\freeglut.h>

#include "Mouse.hpp"


using namespace openlima::util;

namespace openlima {
	namespace input {

		Mouse::Mouse() {
			// TODO
		}

		Mouse& Mouse::getInstance() {
			static Mouse mouse;
			return mouse;
		}

		Vector2i Mouse::getPosition() {
			return Vector2i(); // TODO
		}

		void Mouse::setPosition(Vector2i position) {
			// TODO
		}

		void Mouse::setMouseSticking(bool sticking) {
			// TODO
		}

		void Mouse::setMouseVisibility(bool visible) {
			if(visible) {
				glutSetCursor(GLUT_CURSOR_INHERIT);
			} else {
				glutSetCursor(GLUT_CURSOR_NONE);
			}
		}

	}
}