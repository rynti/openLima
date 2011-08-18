// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <GL/glut.h>

#include "GlutMouse.hpp"

using namespace openlima::util;


namespace openlima {
	namespace input {
		
		std::map<GlutHandle, GlutMouse*> GlutMouse::registeredMouses;


		GlutMouse::GlutMouse(GlutHandle glutWindowId) {
			GlutMouse::registeredMouses[glutWindowId] = this;

			this->glutWindowId = glutWindowId;
			if(glutGetWindow() != glutWindowId)
				glutSetWindow(glutWindowId);

			glutMotionFunc(&GlutMouse::globalMouseMove);
			glutPassiveMotionFunc(&GlutMouse::globalMouseMove);
			glutMouseFunc(&GlutMouse::globalMouseClick);
		}

		GlutMouse::~GlutMouse() {
			GlutMouse::registeredMouses.erase(this->glutWindowId);
		}


		void GlutMouse::globalMouseMove(int x, int y) {
			GlutMouse::registeredMouses[glutGetWindow()]->mouseMove(x, y);
		}

		void GlutMouse::globalMouseClick(int button, int state, int x, int y) {
			GlutMouse::registeredMouses[glutGetWindow()]->mouseClick(button, state, x, y);
		}

		void GlutMouse::mouseMove(int x, int y) {
			if(this->position == Vector2i(x, y))
				return;

			this->delta = Vector2i(x - this->position.x, y - this->position.y);

			this->position = Vector2i(x, y);

			this->onMouseMove(*this, MouseMoveEvent(this->getPosition(), this->getDelta()));
			
			if(this->sticky && (this->delta.x != 0 || this->delta.y != 0)) {
				glutSetWindow(this->glutWindowId);
				int newX = glutGet(GLUT_WINDOW_WIDTH) / 2;
				int newY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
				this->setPosition(Vector2i(newX, newY));
			}
		}

		void GlutMouse::mouseClick(int button, int state, int x, int y) {
			bool isPressed = (state == GLUT_DOWN);
			MouseClickEvent* eventArgs;

			if(button == GLUT_LEFT_BUTTON) {
				eventArgs = new MouseClickEvent(Vector2i(x, y), MouseButtonType::LEFT, isPressed);
			} else if(button == GLUT_MIDDLE_BUTTON) {
				eventArgs = new MouseClickEvent(Vector2i(x, y), MouseButtonType::MIDDLE, isPressed);
			} else if(button == GLUT_RIGHT_BUTTON) {
				eventArgs = new MouseClickEvent(Vector2i(x, y), MouseButtonType::RIGHT, isPressed);
			} else {
				return;
			}

			if(isPressed) {
				this->mouseButtonStates |= (1 << (int)eventArgs->getButton());
			} else {
				this->mouseButtonStates &= ~(1 << (int)eventArgs->getButton());
			}

			this->onMouseClick(*this, *eventArgs);
			delete eventArgs;
		}

		void GlutMouse::setPosition(Vector2i position) {
			Mouse::setPosition(position);
			glutSetWindow(this->glutWindowId);
			glutWarpPointer(position.x, position.y);
		}

		void GlutMouse::setVisible(bool visible) {
			Mouse::setVisible(visible);

			glutSetWindow(this->glutWindowId);
			if(visible) {
				glutSetCursor(GLUT_CURSOR_INHERIT);
			} else {
				glutSetCursor(GLUT_CURSOR_NONE);
			}
		}

	}
}
