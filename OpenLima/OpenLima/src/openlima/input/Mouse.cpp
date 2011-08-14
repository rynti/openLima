#include <GL\freeglut.h>
#include <iostream>

#include "Mouse.hpp"


using namespace openlima::util;

namespace openlima {
	namespace input {

		Mouse::Mouse() {
			sticky = false;
			visible = true;
			mouseButtonStates = 0;
		}

		Vector2i Mouse::getPosition() {
			return position;
		}

		Vector2i Mouse::getDelta() {
			return delta;
		}

		bool Mouse::isSticky() {
			return this->sticky;
		}

		void Mouse::setSticky(bool sticky) {
			this->sticky = sticky;
		}

		bool Mouse::isVisible() {
			return this->visible;
		}

		void Mouse::setVisible(bool visible) {
			this->visible = visible;
			if(visible) {
				glutSetCursor(GLUT_CURSOR_INHERIT);
			} else {
				glutSetCursor(GLUT_CURSOR_NONE);
			}
		}

		MouseButtonState Mouse::getButtonState(MouseButton button) {
			return ((this->mouseButtonStates & (1 << (int)button)) != 0) ? PRESSED : RELEASED;
		}

	}
}